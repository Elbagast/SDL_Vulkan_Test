#ifndef SDLXVULKAN_COMMAND_POOL_HPP
#define SDLXVULKAN_COMMAND_POOL_HPP

#include "handle.hpp"
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
    using Data_Type = Vulkan_Handle<VkCommandPool>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    // Create using for a given device and queue family, setting its create 
    // flags. Refer to VkCommandPoolCreateFlagBits documentation.
    Command_Pool
    (
      Device const& a_device,
      uint32_t a_queue_family_index,
      VkCommandPoolCreateFlags a_flags = 0
    );

    ~Command_Pool();

    Command_Pool(Command_Pool const& a_other);
    Command_Pool& operator=(Command_Pool const& a_other);

    Command_Pool(Command_Pool && a_other);
    Command_Pool& operator=(Command_Pool && a_other);

    // Interface
    //============================================================
    Data_Type::Pointer get() const noexcept       { return m_data.get(); }
    operator Data_Type::Pointer() const noexcept  { return m_data.get(); }

    Device const& get_device() const noexcept;

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