#ifndef SDLXVULKAN_DEVICE_HPP
#define SDLXVULKAN_DEVICE_HPP

#include "handle.hpp"
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
  class Instance;
  class Physical_Device;
  class Device_Functions;

  //---------------------------------------------------------------------------
  // Device
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Logical Device.

  class Device
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Handle<VkDevice>;
    Data_Type m_data;
    
  public:
    // Special 6
    //============================================================
    explicit Device
    (
      Physical_Device const& a_physical_device, 
      uint32_t a_graphics_qfi, 
      uint32_t a_present_qfi, 
      std::vector<std::string> const& a_extensions
    );
    ~Device();

    Device(Device const& a_other);
    Device& operator=(Device const& a_other);

    Device(Device && a_other);
    Device& operator=(Device && a_other);

    // Interface
    //============================================================
    Data_Type::Pointer get() const noexcept { return m_data.get(); }
    operator Data_Type::Pointer() const noexcept { return m_data.get(); }

    Device_Functions const& vk_functions() const noexcept;

    Physical_Device const& get_physical_device() const noexcept;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Device
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Device::Device(Device const& a_other) = default;
inline sdlxvulkan::Device& sdlxvulkan::Device::operator=(Device const& a_other) = default;

inline sdlxvulkan::Device::Device(Device && a_other) = default;
inline sdlxvulkan::Device& sdlxvulkan::Device::operator=(Device && a_other) = default;

// Interface
//============================================================

#endif // SDLXVULKAN_DEVICE_HPP