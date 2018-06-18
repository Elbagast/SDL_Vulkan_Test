#include "physical_device.hpp"

#include "instance.hpp"
#include "surface.hpp"
#include "functions.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <limits>
#include <exception>

namespace sdlxvulkan
{
  namespace
  {
    VkPhysicalDeviceProperties imp_get_properties(Instance const& a_instance, VkPhysicalDevice a_physical_device) 
    {
      assert(a_instance.vk_functions().vkGetPhysicalDeviceProperties != nullptr);

      VkPhysicalDeviceProperties l_result{};
      a_instance.vk_functions().vkGetPhysicalDeviceProperties(a_physical_device, &l_result);
      return l_result;
    }

    VkPhysicalDeviceMemoryProperties imp_get_memory_properties(Instance const& a_instance, VkPhysicalDevice a_physical_device)
    {
      assert(a_instance.vk_functions().vkGetPhysicalDeviceMemoryProperties != nullptr);

      VkPhysicalDeviceMemoryProperties l_result{};
      a_instance.vk_functions().vkGetPhysicalDeviceMemoryProperties(a_physical_device, &l_result);
      return l_result;
    }

    std::vector<VkQueueFamilyProperties> imp_get_queue_familiy_properties(Instance const& a_instance, VkPhysicalDevice a_physical_device)
    {
      assert(a_instance.vk_functions().vkGetPhysicalDeviceQueueFamilyProperties != nullptr);

      uint32_t l_count{0};
      a_instance.vk_functions().vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, nullptr);

      std::vector<VkQueueFamilyProperties> l_result{};
      l_result.resize(l_count);

      a_instance.vk_functions().vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, l_result.data());

      return l_result;
    }

    std::vector<VkExtensionProperties> imp_get_extension_properties(Instance const& a_instance, VkPhysicalDevice a_physical_device)
    {
      assert(a_instance.vk_functions().vkEnumerateDeviceExtensionProperties != nullptr);

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


    bool is_present_capable(VkPhysicalDevice a_pd, uint32_t a_qfi, Surface const& a_surface, Instance const& a_instance)
    {
      VkBool32 l_qf_can_present{ VK_FALSE };
      a_instance.vk_functions().vkGetPhysicalDeviceSurfaceSupportKHR(a_pd, a_qfi, a_surface, &l_qf_can_present);

      return l_qf_can_present == VK_TRUE;
    }

    uint32_t imp_get_first_present_qfi(VkPhysicalDevice a_physical_device, std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties, Surface const& a_surface, Instance const& a_instance)
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
  }
}

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------
// Holds all of the information relating to a Vulkan Physical Device.

// Special 6
//============================================================
sdlxvulkan::Physical_Device::Physical_Device(VkPhysicalDevice a_physical_device, Instance const& a_instance, Surface const& a_surface) :
  m_physical_device{ a_physical_device },
  m_instance{ a_instance },
  m_surface{ a_surface },
  m_properties{ imp_get_properties(m_instance, m_physical_device) },
  m_memory_properties{ imp_get_memory_properties(m_instance, m_physical_device) },
  m_queue_familiy_properties{ imp_get_queue_familiy_properties(m_instance, m_physical_device) },
  m_extension_properties{ imp_get_extension_properties(m_instance, m_physical_device) },
  m_graphics_qfi{ imp_get_first_graphics_qfi(m_queue_familiy_properties) },
  m_present_qfi{ imp_get_first_present_qfi(m_physical_device, m_queue_familiy_properties, m_surface, m_instance)  }
{
  std::cout << "sdlxvulkan::Physical_Device::Physical_Device()" << std::endl;
}

sdlxvulkan::Physical_Device::~Physical_Device()
{
  std::cout << "sdlxvulkan::Physical_Device::~Physical_Device()" << std::endl;
}

// Interface
//============================================================
VkPhysicalDeviceProperties const& sdlxvulkan::Physical_Device::get_properties() const noexcept
{
  return m_properties;
}

VkPhysicalDeviceMemoryProperties const& sdlxvulkan::Physical_Device::get_memory_properties() const noexcept
{
  return m_memory_properties;
}

std::vector<VkQueueFamilyProperties> const& sdlxvulkan::Physical_Device::get_queue_familiy_properties() const noexcept
{
  return m_queue_familiy_properties;
}

std::vector<VkExtensionProperties> const& sdlxvulkan::Physical_Device::get_extension_properties() const noexcept
{
  return m_extension_properties;
}

bool sdlxvulkan::Physical_Device::can_graphics() const noexcept
{
  return m_graphics_qfi != c_invalid_index;
}
bool sdlxvulkan::Physical_Device::can_present() const noexcept
{
  return m_present_qfi != c_invalid_index;
}

// Using the supplied properties, determine the right kind of memory to allocate.
// Success returns the index to the value required to allocate the right type of memory. 
// Failure throws if no matching memory found.

uint32_t sdlxvulkan::Physical_Device::get_memory_type_from_properties(uint32_t a_typebits, VkMemoryPropertyFlags  a_requirements) const
{
  // Search memtypes to find first index with those properties
  for (uint32_t i = 0; i < m_memory_properties.memoryTypeCount; i++)
  {
    // If has 
    if (a_typebits & (1 << i))
    {
      // Type is available, does it match user properties?
      if ((m_memory_properties.memoryTypes[i].propertyFlags & a_requirements) == a_requirements)
      {
        return i;
      }
    }
    a_typebits >>= 1;
  }
  // No memory types matched, return failure
  throw std::runtime_error{ "Vulkan: Failed to find a suitable memory type." };
}
