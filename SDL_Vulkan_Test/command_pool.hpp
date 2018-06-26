#ifndef SDLXVULKAN_COMMAND_POOL_HPP
#define SDLXVULKAN_COMMAND_POOL_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Device;

  //---------------------------------------------------------------------------
  // Command_Pool
  //---------------------------------------------------------------------------
  // Holds a VkCommandPool with reference counting and cleans up properly. 
  // Allows wrapped manipulation of the VkCommandPool.

  class Command_Pool
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkCommandPool>;
    Data_Type m_data;

  public:
    enum class Create_Flags : VkFlags
    {
      None = 0,
      Transient_Bit = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
      Reset_Command_Buffer_Bit = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      Protected_Bit = VK_COMMAND_POOL_CREATE_PROTECTED_BIT,
    };

    enum class Reset_Flags : VkFlags
    {
      None = 0,
      Release_Resources_Bit = VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT
    };

    enum class Trim_Flags : VkFlags
    {
      None = 0
    };


    // Special 6
    //============================================================
    // Create using for a given device and queue family, setting its create 
    // flags. Refer to VkCommandPoolCreateFlagBits documentation.
    Command_Pool
    (
      Device const& a_device,
      uint32_t a_queue_family_index,
      VkCommandPoolCreateFlags a_flags = 0,
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );

    ~Command_Pool();

    Command_Pool(Command_Pool const& a_other);
    Command_Pool& operator=(Command_Pool const& a_other);

    Command_Pool(Command_Pool && a_other);
    Command_Pool& operator=(Command_Pool && a_other);

    // Interface
    //============================================================
    VkCommandPool get() const noexcept       { return m_data.get(); }
    operator VkCommandPool() const noexcept  { return m_data.get(); }

    Device const& get_device() const noexcept;

    uint32_t get_queue_family_index() const noexcept;
    VkCommandPoolCreateFlags get_flags() const noexcept;
    VkAllocationCallbacks const* get_allocation_callbacks() const noexcept;
    
    // Analagous to calling vkResetCommandPool on this.
    // Flags CAN be set to a mask of VkCommandPoolResetFlagBits values.
    void reset(VkCommandPoolResetFlags a_flags = 0);

    // Analagous to calling vkTrimCommandPool on this.
    // Vulkan 1.1.0: Flags are reserved and MUST be zero.
    void trim(VkCommandPoolTrimFlags a_flags = 0);
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Pool
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Command_Pool::Command_Pool(Command_Pool const& a_other) = default;
inline sdlxvulkan::Command_Pool& sdlxvulkan::Command_Pool::operator=(Command_Pool const& a_other) = default;

inline sdlxvulkan::Command_Pool::Command_Pool(Command_Pool && a_other) = default;
inline sdlxvulkan::Command_Pool& sdlxvulkan::Command_Pool::operator=(Command_Pool && a_other) = default;

#endif // SDLXVULKAN_COMMAND_POOL_HPP