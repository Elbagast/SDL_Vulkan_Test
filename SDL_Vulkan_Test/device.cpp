#include "device.hpp"

#include "physical_device.hpp"
#include "instance.hpp"
#include "instance_functions.hpp"
#include "device_functions.hpp"

#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
#ifdef SDLXVULKAN_SINGLE_DEVICE
    static Device_Functions s_functions{};
#endif
    
    //---------------------------------------------------------------------------
    // Device_Destroyer
    //---------------------------------------------------------------------------
    // Doesn't actually do anything but hold the dependent handles.

    class Device_Destroyer2
    {
    public:
      // Member Data
      //============================================================
      Physical_Device_OLD m_physical_device;
      uint32_t m_graphics_qfi;
      uint32_t m_present_qfi;
      std::vector<std::string> const& m_extensions;
      VkAllocationCallbacks const* m_allocation_callbacks;

#ifndef SDLXVULKAN_SINGLE_DEVICE
      Device_Functions m_functions;
#endif

      // Special 6
      //============================================================

      Device_Destroyer2
      (
        Physical_Device_OLD const& a_physical_device,
        uint32_t a_graphics_qfi,
        uint32_t a_present_qfi,
        std::vector<std::string> const& a_extensions,
        VkAllocationCallbacks const* a_allocation_callbacks

#ifndef SDLXVULKAN_SINGLE_DEVICE
        ,Device_Functions const& a_functions
#endif
      ) :
        m_physical_device{ a_physical_device },
        m_graphics_qfi{ a_graphics_qfi },
        m_present_qfi{ a_present_qfi },
        m_extensions{ a_extensions },
        m_allocation_callbacks{ a_allocation_callbacks }

#ifndef SDLXVULKAN_SINGLE_DEVICE
       , m_functions{ a_functions }
#endif
      {
        std::cout << "sdlxvulkan::Device_Destroyer::Device_Destroyer()" << std::endl;
      }
      
      // Interface
      //============================================================
      void operator()(VkDevice a_device) const noexcept
      {
#ifndef SDLXVULKAN_SINGLE_DEVICE
        m_functions.vkDestroyDevice(a_device, m_allocation_callbacks);
#else
        s_functions.vkDestroyDevice(a_device, m_allocation_callbacks);
#endif
        std::cout << "sdlxvulkan::Device_Destroyer::operator()" << std::endl;
      }
    };

    decltype(auto) make_except_simple_device
    (
      Physical_Device_OLD const& a_physical_device,
      uint32_t a_graphics_qfi,
      uint32_t a_present_qfi,
      std::vector<std::string> const& a_extensions,
      VkAllocationCallbacks const* a_allocation_callbacks
    )
    {
      //m_graphics_qfi = m_physical_device.first_graphics_qfi();

      //m_present_qfi = m_physical_device.first_present_qfi(m_surface);
      //m_present_qfi = 1;
      // check presenting...

      float l_queue_priorities[1] = { 0.0 };

      VkDeviceQueueCreateInfo l_queue_infos[2]{};

      // first is graphics
      l_queue_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      l_queue_infos[0].pNext = nullptr;
      l_queue_infos[0].flags = 0;
      l_queue_infos[0].queueFamilyIndex = a_graphics_qfi;
      l_queue_infos[0].queueCount = 1;
      l_queue_infos[0].pQueuePriorities = l_queue_priorities;

      // second is presenting
      l_queue_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      l_queue_infos[1].pNext = nullptr;
      l_queue_infos[1].flags = 0;
      l_queue_infos[1].queueFamilyIndex = a_present_qfi;
      l_queue_infos[1].queueCount = 1;
      l_queue_infos[1].pQueuePriorities = l_queue_priorities;

      // Logical Device
      //-------------

      // Configure our queue info
      VkDeviceQueueCreateInfo l_queue_info{};
      l_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      l_queue_info.pNext = nullptr;
      l_queue_info.flags = 0;
      l_queue_info.queueFamilyIndex = a_graphics_qfi;
      l_queue_info.queueCount = 1;
      l_queue_info.pQueuePriorities = l_queue_priorities;


      std::vector<char const*> l_device_extensions{};
      uint32_t l_device_extension_count = static_cast<uint32_t>(a_extensions.size());
      std::vector<char const*> l_extensions{};
      l_device_extensions.reserve(a_extensions.size());
      for (auto const& l_ext : a_extensions)
      {
        l_device_extensions.push_back(l_ext.c_str());
      }

      // Make some device info
      VkDeviceCreateInfo l_device_info = {};
      l_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
      l_device_info.pNext = nullptr;
      l_device_info.flags = 0;

      if (a_graphics_qfi == a_present_qfi)
      {
        l_device_info.queueCreateInfoCount = 1;
      }
      else
      {
        l_device_info.queueCreateInfoCount = 2;
      }
      l_device_info.pQueueCreateInfos = l_queue_infos;
      l_device_info.enabledLayerCount = 0;          // Deprecated, IGNORE
      l_device_info.ppEnabledLayerNames = nullptr;  // Deprecated, IGNORE
      l_device_info.enabledExtensionCount = l_device_extension_count;
      l_device_info.ppEnabledExtensionNames = l_device_extensions.data();
      l_device_info.pEnabledFeatures = nullptr;

      VkDevice l_device{};
      // Create the device
      if (vkCreateDevice(a_physical_device, &l_device_info, a_allocation_callbacks, &l_device) != VK_SUCCESS)
      {
        throw std::runtime_error("Vulkan: Failed to create logical device.");
      }

      auto l_functions = Device_Functions{ l_device, a_physical_device.get_instance().vk_functions() };
#ifndef SDLXVULKAN_SINGLE_DEVICE
      return make_except_vulkan_sptr<VkDevice, Device_Destroyer2>(l_device, a_physical_device, a_graphics_qfi, a_present_qfi, a_extensions, a_allocation_callbacks, l_functions);
#else
      s_functions = l_functions;
      return make_except_vulkan_sptr<VkDevice, Device_Destroyer2>(l_device, a_physical_device, a_graphics_qfi, a_present_qfi, a_extensions, a_allocation_callbacks);
#endif
    }

  } // namespace  
} // namespace sdlxvulkan

//---------------------------------------------------------------------------
// Device
//---------------------------------------------------------------------------
// Holds all of the information relating to a Vulkan Logical Device.

// Special 6
//============================================================
sdlxvulkan::Device_OLD::Device_OLD
(
  Physical_Device_OLD const& a_physical_device,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  std::vector<std::string> const& a_extensions,
  VkAllocationCallbacks const* a_allocation_callbacks
) :
  m_data{ make_except_simple_device(a_physical_device, a_graphics_qfi, a_present_qfi, a_extensions, a_allocation_callbacks) }
{
  //std::cout << "sdlxvulkan::Device::Device()" << std::endl;
}
sdlxvulkan::Device_OLD::~Device_OLD()
{
  //std::cout << "sdlxvulkan::Device::~Device()" << std::endl;
}


// Interface
//============================================================

sdlxvulkan::Device_Functions const& sdlxvulkan::Device_OLD::vk_functions() const noexcept
{
#ifndef SDLXVULKAN_SINGLE_DEVICE
  return std::get_deleter<Device_Destroyer2>(m_data)->m_functions;
#else
  return s_functions;
#endif
}

sdlxvulkan::Physical_Device_OLD const& sdlxvulkan::Device_OLD::get_physical_device() const noexcept
{
  return std::get_deleter<Device_Destroyer2>(m_data)->m_physical_device;
}

uint32_t sdlxvulkan::Device_OLD::get_graphics_qfi() const noexcept
{
  return std::get_deleter<Device_Destroyer2>(m_data)->m_graphics_qfi;
}

uint32_t sdlxvulkan::Device_OLD::get_present_qfi() const noexcept
{
  return std::get_deleter<Device_Destroyer2>(m_data)->m_present_qfi;
}

std::vector<std::string> const& sdlxvulkan::Device_OLD::get_extensions() const noexcept
{
  return std::get_deleter<Device_Destroyer2>(m_data)->m_extensions;
}
