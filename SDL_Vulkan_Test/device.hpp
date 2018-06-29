#ifndef SDLXVULKAN_DEVICE_HPP
#define SDLXVULKAN_DEVICE_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#include <vector>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

// If you are using only one device for the application lifetime, you can 
// enable this to compile so that the Device_Functions are stored as a 
// single static instance.
//#define SDLXVULKAN_SINGLE_DEVICE

namespace sdlxvulkan
{
  class Instance_OLD;
  class Physical_Device_OLD;
  class Device_Functions;

  //---------------------------------------------------------------------------
  // Device
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Logical Device.

  class Device_OLD
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkDevice>;
    Data_Type m_data;
    
  public:
    // Special 6
    //============================================================
    explicit Device_OLD
    (
      Physical_Device_OLD const& a_physical_device, 
      uint32_t a_graphics_qfi, 
      uint32_t a_present_qfi, 
      std::vector<std::string> const& a_extensions,
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );
    ~Device_OLD();

    Device_OLD(Device_OLD const& a_other);
    Device_OLD& operator=(Device_OLD const& a_other);

    Device_OLD(Device_OLD && a_other);
    Device_OLD& operator=(Device_OLD && a_other);

    // Interface
    //============================================================
    VkDevice get() const noexcept { return m_data.get(); }
    operator VkDevice() const noexcept { return m_data.get(); }

    Device_Functions const& vk_functions() const noexcept;

    Physical_Device_OLD const& get_physical_device() const noexcept;
    uint32_t get_graphics_qfi() const noexcept;
    uint32_t get_present_qfi() const noexcept;
    std::vector<std::string> const& get_extensions() const noexcept;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Device
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Device_OLD::Device_OLD(Device_OLD const& a_other) = default;
inline sdlxvulkan::Device_OLD& sdlxvulkan::Device_OLD::operator=(Device_OLD const& a_other) = default;

inline sdlxvulkan::Device_OLD::Device_OLD(Device_OLD && a_other) = default;
inline sdlxvulkan::Device_OLD& sdlxvulkan::Device_OLD::operator=(Device_OLD && a_other) = default;

// Interface
//============================================================

#endif // SDLXVULKAN_DEVICE_HPP