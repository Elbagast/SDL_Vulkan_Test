#include "command_pool.hpp"

#include "device.hpp"
#include "device_functions.hpp"

#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Command_Pool_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Command_Pool_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Device m_device;
      uint32_t m_queue_family_index;
      VkCommandPoolCreateFlags m_flags;
      VkAllocationCallbacks const* m_allocation_callbacks;

      // Special 6
      //============================================================
      explicit Command_Pool_Destroyer
      (
        Device const& a_device,
        uint32_t a_queue_family_index,
        VkCommandPoolCreateFlags a_flags,
        VkAllocationCallbacks const* a_allocation_callbacks
      ):
        m_device{ a_device },
        m_queue_family_index{ a_queue_family_index },
        m_flags{ a_flags },
        m_allocation_callbacks{ a_allocation_callbacks }
      {
        std::cout << "sdlxvulkan::Command_Pool_Destroyer::Command_Pool_Destroyer()" << std::endl;
      }

      // Interface
      //============================================================
      void operator()(VkCommandPool a_command_pool) const noexcept
      {
        m_device.vk_functions().vkDestroyCommandPool(m_device, a_command_pool, nullptr);
        std::cout << "sdlxvulkan::Command_Pool_Destroyer::operator()" << std::endl;
      }
    };


    decltype(auto) make_except_command_pool
    (
      Device const& a_device,
      uint32_t a_queue_family_index,
      VkCommandPoolCreateFlags a_flags,
      VkAllocationCallbacks const* a_allocation_callbacks
    )
    {
      // Initialise some creation info
      VkCommandPoolCreateInfo l_command_pool_info{};
      l_command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
      l_command_pool_info.pNext = nullptr;
      l_command_pool_info.flags = a_flags;
      l_command_pool_info.queueFamilyIndex = a_queue_family_index;

      VkCommandPool l_command_pool{ VK_NULL_HANDLE };
      // Make the pool using the device.
      if (a_device.vk_functions().vkCreateCommandPool(a_device, &l_command_pool_info, a_allocation_callbacks, &l_command_pool) != VK_SUCCESS)
      {
        throw std::runtime_error("Vulkan: Failed to create command pool.");
      }

      return make_except_vulkan_sptr<VkCommandPool, Command_Pool_Destroyer>(l_command_pool, a_device, a_queue_family_index, a_flags, a_allocation_callbacks);
    }
  } // namespace  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Pool
//---------------------------------------------------------------------------
// Holds a VkInstance with reference counting and cleans up properly. 

// Special 6
//============================================================
// Create using for a given device and queue family, setting its create 
// flags. Refer to VkCommandPoolCreateFlagBits documentation.
sdlxvulkan::Command_Pool::Command_Pool
(
  Device const& a_device,
  uint32_t a_queue_family_index,
  VkCommandPoolCreateFlags a_flags,
  VkAllocationCallbacks const* a_allocation_callbacks
) :
  m_data{ make_except_command_pool(a_device, a_queue_family_index, a_flags, a_allocation_callbacks) }
{
  //std::cout << "sdlxvulkan::Command_Pool::~Command_Pool()" << std::endl;
}

sdlxvulkan::Command_Pool::~Command_Pool()
{
  //std::cout << "sdlxvulkan::Command_Pool::~Command_Pool()" << std::endl;
}

// Interface
//============================================================
sdlxvulkan::Device const& sdlxvulkan::Command_Pool::get_device() const noexcept
{
  return std::get_deleter<Command_Pool_Destroyer>(m_data)->m_device;
}

uint32_t sdlxvulkan::Command_Pool::get_queue_family_index() const noexcept
{
  return std::get_deleter<Command_Pool_Destroyer>(m_data)->m_queue_family_index;
}

VkCommandPoolCreateFlags sdlxvulkan::Command_Pool::get_flags() const noexcept
{
  return std::get_deleter<Command_Pool_Destroyer>(m_data)->m_flags;
}

VkAllocationCallbacks const* sdlxvulkan::Command_Pool::get_allocation_callbacks() const noexcept
{
  return std::get_deleter<Command_Pool_Destroyer>(m_data)->m_allocation_callbacks;
}

// Analagous to vkResetCommandPool on this.
// Flags CAN be set to a mask of VkCommandPoolResetFlagBits values.
void sdlxvulkan::Command_Pool::reset(VkCommandPoolResetFlags a_flags)
{
  get_device().vk_functions().vkResetCommandPool(get_device(), get(), a_flags);
}

// Analagous to vkTrimCommandPool on this.
// Flags are reserved and MUST be zero.
void sdlxvulkan::Command_Pool::trim(VkCommandPoolTrimFlags a_flags)
{
  get_device().vk_functions().vkTrimCommandPool(get_device(), get(), a_flags);
}
