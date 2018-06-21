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

    class Device_Destroyer
    {
    private:
      // Member Data
      //============================================================
      Physical_Device m_physical_device;
#ifndef SDLXVULKAN_SINGLE_DEVICE
      Device_Functions m_functions;
#endif

    public:
      // Special 6
      //============================================================
#ifndef SDLXVULKAN_SINGLE_DEVICE
      Device_Destroyer(Physical_Device const& a_physical_device, Device_Functions const& a_functions) :
        m_physical_device{ a_physical_device },
        m_functions{ a_functions }
      {
      }
#else
      Device_Destroyer(Physical_Device const& a_physical_device) :
        m_physical_device{ a_physical_device }
      {
      }
#endif
      ~Device_Destroyer() = default;

      Device_Destroyer(Device_Destroyer const& a_other) = default;
      Device_Destroyer& operator=(Device_Destroyer const& a_other) = default;

      Device_Destroyer(Device_Destroyer && a_other) = default;
      Device_Destroyer& operator=(Device_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(VkDevice a_device) const noexcept
      {
#ifndef SDLXVULKAN_SINGLE_DEVICE
        m_functions.vkDestroyDevice(a_device, nullptr);
#else
        s_functions.vkDestroyDevice(a_device, nullptr);
#endif
        std::cout << "sdlxvulkan::Device_Destroyer::operator()" << std::endl;
      }

      Physical_Device const& get_physical_device() const noexcept
      {
        return m_physical_device;
      }

#ifndef SDLXVULKAN_SINGLE_DEVICE
      Device_Functions const& get_functions() const noexcept
      {
        return m_functions;
      }
#endif
    };

    Vulkan_Handle<VkDevice> make_except_simple_device
    (
      Physical_Device const& a_physical_device,
      uint32_t a_graphics_qfi,
      uint32_t a_present_qfi,
      std::vector<std::string> const& a_extensions
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
      if (vkCreateDevice(a_physical_device, &l_device_info, nullptr, &l_device) != VK_SUCCESS)
      {
        throw std::runtime_error("Vulkan: Failed to create logical device.");
      }

      auto l_functions = Device_Functions{ l_device, a_physical_device.get_instance().vk_functions() };
#ifndef SDLXVULKAN_SINGLE_DEVICE
      return Vulkan_Handle<VkDevice>{l_device, Device_Destroyer{ a_physical_device, l_functions } };
#else
      s_functions = l_functions;
      return Vulkan_Handle<VkDevice>{l_device, Device_Destroyer{ a_physical_device } };
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
sdlxvulkan::Device::Device
(
  Physical_Device const& a_physical_device,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  std::vector<std::string> const& a_extensions
) :
  m_data{ make_except_simple_device(a_physical_device, a_graphics_qfi, a_present_qfi,a_extensions) }
{
  std::cout << "sdlxvulkan::Device::Device()" << std::endl;
}
sdlxvulkan::Device::~Device()
{
  std::cout << "sdlxvulkan::Device::~Device()" << std::endl;
}


// Interface
//============================================================

sdlxvulkan::Device_Functions const& sdlxvulkan::Device::vk_functions() const noexcept
{
#ifndef SDLXVULKAN_SINGLE_DEVICE
  return m_data.get_destroyer<Device_Destroyer>()->get_functions();
#else
  return s_functions;
#endif
}

sdlxvulkan::Physical_Device const& sdlxvulkan::Device::get_physical_device() const noexcept
{
  return m_data.get_destroyer<Device_Destroyer>()->get_physical_device();
}
