#include "physical_device.hpp"

#include "instance.hpp"
#include "instance_functions.hpp"
#include "surface.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace sdlxvulkan
{
  namespace
  {
    VkPhysicalDeviceProperties imp_get_properties(Instance_OLD const& a_instance, VkPhysicalDevice a_physical_device) 
    {
      VkPhysicalDeviceProperties l_result{};
      a_instance.vk_functions().vkGetPhysicalDeviceProperties(a_physical_device, &l_result);
      return l_result;
    }

    VkPhysicalDeviceMemoryProperties imp_get_memory_properties(Instance_OLD const& a_instance, VkPhysicalDevice a_physical_device)
    {
      VkPhysicalDeviceMemoryProperties l_result{};
      a_instance.vk_functions().vkGetPhysicalDeviceMemoryProperties(a_physical_device, &l_result);
      return l_result;
    }

    std::vector<VkQueueFamilyProperties> imp_get_queue_familiy_properties(Instance_OLD const& a_instance, VkPhysicalDevice a_physical_device)
    {
      uint32_t l_count{0};
      a_instance.vk_functions().vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, nullptr);

      std::vector<VkQueueFamilyProperties> l_result{};
      l_result.resize(l_count);

      a_instance.vk_functions().vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, l_result.data());

      return l_result;
    }

    std::vector<VkExtensionProperties> imp_get_extension_properties(Instance_OLD const& a_instance, VkPhysicalDevice a_physical_device)
    {
      uint32_t l_count{0};
      a_instance.vk_functions().vkEnumerateDeviceExtensionProperties(a_physical_device, nullptr, &l_count, nullptr);

      std::vector<VkExtensionProperties> l_result{};
      l_result.resize(l_count);

      a_instance.vk_functions().vkEnumerateDeviceExtensionProperties(a_physical_device, nullptr, &l_count, l_result.data());

      return l_result;
    }
    

    constexpr uint32_t c_invalid_index{ std::numeric_limits<uint32_t>::max() };


    bool is_graphics_capable(VkQueueFamilyProperties const& a_qf)
    {
      return a_qf.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    }

    bool imp_can_graphics(std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties)
    {
      auto l_found = std::find_if(a_queue_familiy_properties.cbegin(), a_queue_familiy_properties.cend(), is_graphics_capable);
      if (l_found != a_queue_familiy_properties.cend())
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    uint32_t imp_get_first_graphics_qfi(std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties)
    {
      auto l_found = std::find_if(a_queue_familiy_properties.cbegin(), a_queue_familiy_properties.cend(), is_graphics_capable);
      if (l_found != a_queue_familiy_properties.cend())
      {
        return static_cast<uint32_t>(std::distance(a_queue_familiy_properties.cbegin(), l_found));
      }
      else
      {
        return c_invalid_index;
      }
    }
    
    bool is_present_capable(VkPhysicalDevice a_pd, uint32_t a_qfi, Surface_OLD const& a_surface, Instance_OLD const& a_instance)
    {
      VkBool32 l_qf_can_present{ VK_FALSE };
      a_instance.vk_functions().vkGetPhysicalDeviceSurfaceSupportKHR(a_pd, a_qfi, a_surface, &l_qf_can_present);

      return l_qf_can_present == VK_TRUE;
    }

    bool imp_can_present(VkPhysicalDevice a_physical_device, std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties, Surface_OLD const& a_surface, Instance_OLD const& a_instance)
    {
      for (uint32_t l_index = 0, l_end = static_cast<uint32_t>(a_queue_familiy_properties.size()); l_index != l_end; ++l_index)
      {
        if (is_present_capable(a_physical_device, l_index, a_surface, a_instance))
        {
          return true;
        }
      }
      return false;
    }

    uint32_t imp_get_first_present_qfi(VkPhysicalDevice a_physical_device, std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties, Surface_OLD const& a_surface, Instance_OLD const& a_instance)
    {
      for (uint32_t l_index = 0, l_end = static_cast<uint32_t>(a_queue_familiy_properties.size()); l_index != l_end; ++l_index)
      {
        if (is_present_capable(a_physical_device, l_index, a_surface, a_instance))
        {
          return l_index;
        }
      }
      return c_invalid_index;
    }

    VkSurfaceCapabilitiesKHR imp_get_surface_cababilites(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance, Surface_OLD const& a_surface)
    {
      VkSurfaceCapabilitiesKHR l_result{};
      // Get the capabilities
      if (a_instance.vk_functions().vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_physical_device, a_surface, &l_result) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to get surface capabilites." };
      }
      return l_result;
    }

    std::vector<VkSurfaceFormatKHR> imp_get_surface_formats(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance, Surface_OLD const& a_surface)
    {
      // Get the formats that can be used with this device/surface combo.
      uint32_t l_count{ 0 };
      if (a_instance.vk_functions().vkGetPhysicalDeviceSurfaceFormatsKHR(a_physical_device, a_surface, &l_count, nullptr) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to get surface format count." };
      }
      std::vector<VkSurfaceFormatKHR> l_result{};
      l_result.resize(l_count);
      if (a_instance.vk_functions().vkGetPhysicalDeviceSurfaceFormatsKHR(a_physical_device, a_surface, &l_count, l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to get surface formats." };
      }
      return l_result;
    }

    std::vector<VkPresentModeKHR> imp_get_present_modes(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance, Surface_OLD const& a_surface)
    {
      // Get the formats that can be used with this device/surface combo.
      uint32_t l_count{ 0 };
      if (a_instance.vk_functions().vkGetPhysicalDeviceSurfacePresentModesKHR(a_physical_device, a_surface, &l_count, nullptr) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to get surface present modes."};
      }
      std::vector<VkPresentModeKHR> l_result{};
      l_result.resize(l_count);
      if (a_instance.vk_functions().vkGetPhysicalDeviceSurfacePresentModesKHR(a_physical_device, a_surface, &l_count, l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to get surface present modes." };
      }
      return l_result;
    }


    //---------------------------------------------------------------------------
    // Physical_Device_Destroyer
    //---------------------------------------------------------------------------
    // Doesn't actually do anything but hold the dependent handles.

    class Physical_Device_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Instance_OLD m_instance;
      // Caching goes here...

      // Special 6
      //============================================================
      Physical_Device_Destroyer(Instance_OLD const& a_instance) noexcept :
        m_instance{ a_instance }
      {
        std::cout << "sdlxvulkan::Physical_Device_Destroyer::Physical_Device_Destroyer()" << std::endl;
      }

      // Interface
      //============================================================
      void operator()(VkPhysicalDevice) const noexcept
      {
        std::cout << "sdlxvulkan::Physical_Device_Destroyer::operator() - does nothing" << std::endl;
      }

    };


    decltype(auto) make_except_physical_device(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance)
    {
      assert(a_physical_device != VK_NULL_HANDLE);
      return make_except_vulkan_sptr<VkPhysicalDevice, Physical_Device_Destroyer>(a_physical_device, a_instance);
    }
  } // namespace  
} // namespace sdlxvulkan

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------
// Holds all of the information relating to a Vulkan Physical Device.

// Special 6
//============================================================
sdlxvulkan::Physical_Device_OLD::Physical_Device_OLD(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance) :
  m_data{ a_physical_device, Physical_Device_Destroyer{a_instance} }
{
  //std::cout << "sdlxvulkan::Physical_Device::Physical_Device()" << std::endl;
}

sdlxvulkan::Physical_Device_OLD::~Physical_Device_OLD()
{
  //std::cout << "sdlxvulkan::Physical_Device::~Physical_Device()" << std::endl;
}

// Interface
//============================================================

sdlxvulkan::Instance_OLD const& sdlxvulkan::Physical_Device_OLD::get_instance() const noexcept
{
  return std::get_deleter<Physical_Device_Destroyer>(m_data)->m_instance;
}



VkPhysicalDeviceProperties sdlxvulkan::Physical_Device_OLD::get_properties() const
{
  return imp_get_properties(get_instance(), get());
}

VkPhysicalDeviceMemoryProperties sdlxvulkan::Physical_Device_OLD::get_memory_properties() const
{
  return imp_get_memory_properties(get_instance(), get());
}

std::vector<VkQueueFamilyProperties> sdlxvulkan::Physical_Device_OLD::get_queue_familiy_properties() const
{
  return imp_get_queue_familiy_properties(get_instance(), get());
}

std::vector<VkExtensionProperties> sdlxvulkan::Physical_Device_OLD::get_extension_properties() const
{
  return imp_get_extension_properties(get_instance(), get());
}

// Using the supplied properties, determine the right kind of memory to allocate.
// Success returns the index to the value required to allocate the right type of memory. 
// Failure throws if no matching memory found.
uint32_t sdlxvulkan::Physical_Device_OLD::get_memory_type_from_properties(uint32_t a_typebits, VkMemoryPropertyFlags a_requirements) const
{
  return sdlxvulkan::get_memory_type_from_properties(get_memory_properties(), a_typebits, a_requirements);
}

bool sdlxvulkan::Physical_Device_OLD::can_graphics() const
{
  return imp_can_graphics(get_queue_familiy_properties());
}

uint32_t sdlxvulkan::Physical_Device_OLD::first_graphics_qfi() const
{
  return imp_get_first_graphics_qfi(get_queue_familiy_properties());
}


bool sdlxvulkan::Physical_Device_OLD::can_present(Surface_OLD const& a_surface) const
{
  return imp_can_present(get(), get_queue_familiy_properties(), a_surface, get_instance());
}

uint32_t sdlxvulkan::Physical_Device_OLD::first_present_qfi(Surface_OLD const& a_surface) const
{
  return imp_get_first_present_qfi(get(), get_queue_familiy_properties(), a_surface, get_instance());
}




VkSurfaceCapabilitiesKHR sdlxvulkan::Physical_Device_OLD::get_surface_cababilites(Surface_OLD const& a_surface) const
{
  return imp_get_surface_cababilites(get(), get_instance(), a_surface);
}

std::vector<VkSurfaceFormatKHR> sdlxvulkan::Physical_Device_OLD::get_surface_formats(Surface_OLD const& a_surface) const
{
  return imp_get_surface_formats(get(), get_instance(), a_surface);
}

std::vector<VkPresentModeKHR> sdlxvulkan::Physical_Device_OLD::get_present_modes(Surface_OLD const& a_surface) const
{
  return imp_get_present_modes(get(), get_instance(), a_surface);
}
/*
// Using the supplied properties, determine the right kind of memory to allocate.
// Success returns the index to the value required to allocate the right type of memory. 
// Failure throws if no matching memory found.
uint32_t sdlxvulkan::get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags  a_requirements)
{
  // Search memtypes to find first index with those properties
  for (uint32_t i = 0; i < a_properties.memoryTypeCount; i++)
  {
    // If has 
    if (a_typebits & (1 << i))
    {
      // Type is available, does it match user properties?
      if ((a_properties.memoryTypes[i].propertyFlags & a_requirements) == a_requirements)
      {
        return i;
      }
    }
    a_typebits >>= 1;
  }
  // No memory types matched, return failure
  throw std::runtime_error{ "Vulkan: Failed to find a suitable memory type." };
}
*/