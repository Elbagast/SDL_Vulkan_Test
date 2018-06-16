#ifndef SDLXVULKAN_PHYSICAL_DEVICE_HPP
#define SDLXVULKAN_PHYSICAL_DEVICE_HPP

#include "handle.hpp"
#include <vector>
#include <vulkan/vulkan_core.h>


namespace sdlxvulkan
{
  class Instance;
  class Surface;

  //---------------------------------------------------------------------------
  // Physical_Device
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Physical Device.

  class Physical_Device :
    private Vulkan_Handle<VkPhysicalDevice>
  {
  private:
    using Inherited_Type = Vulkan_Handle<VkPhysicalDevice>;
  public:
    using Inherited_Type::get;
    using Inherited_Type::operator Pointer;

    // cache properties etc here?

    // Special 6
    //============================================================
    Physical_Device(Instance const& a_instance, Surface const& a_surface, uint32_t a_index);
    ~Physical_Device();

    Physical_Device(Physical_Device const& a_other);
    Physical_Device& operator=(Physical_Device const& a_other);

    Physical_Device(Physical_Device && a_other);
    Physical_Device& operator=(Physical_Device && a_other);

    // Interface
    //============================================================
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Physical_Device::Physical_Device(Physical_Device const& a_other) = default;
inline sdlxvulkan::Physical_Device& sdlxvulkan::Physical_Device::operator=(Physical_Device const& a_other) = default;

inline sdlxvulkan::Physical_Device::Physical_Device(Physical_Device && a_other) = default;
inline sdlxvulkan::Physical_Device& sdlxvulkan::Physical_Device::operator=(Physical_Device && a_other) = default;

#endif // SDLXVULKAN_WINDOW_HPP
