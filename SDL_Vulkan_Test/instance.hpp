#ifndef SDLXVULKAN_INSTANCE_HPP
#define SDLXVULKAN_INSTANCE_HPP

#include "handle.hpp"
#include <vector>
#include <string>
#include <vulkan/vulkan_core.h>

namespace sdlxvulkan
{
  class System;
  class Window;

  struct Instance_Functions;

  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------
  // Holds a VkInstance with reference counting and cleans up properly. 

  class Instance :
    private Vulkan_Handle<VkInstance>
  {
  private:
    using Inherited_Type = Vulkan_Handle<VkInstance>;
  public:
    using Inherited_Type::get;
    using Inherited_Type::operator Pointer;
    
    // Special 6
    //============================================================
    // Create using the supplied data.
    Instance
    (
      System const& a_system,
      Window const& a_window, 
      std::vector<std::string> const& a_extension_names,
      std::vector<std::string> const& a_layer_names,
      std::string const& a_application_name,
      uint32_t a_application_version,
      std::string const& a_engine_name,
      uint32_t a_engine_version,
      uint32_t a_vulkan_version
    );

    ~Instance();

    Instance(Instance const& a_other);
    Instance& operator=(Instance const& a_other);

    Instance(Instance && a_other);
    Instance& operator=(Instance && a_other);

    // Interface
    //============================================================
    static Instance_Functions const& vk_functions();

    std::vector<VkPhysicalDevice> get_physical_devices() const;
    VkPhysicalDevice get_first_physical_device() const;

  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Instance
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Instance::Instance(Instance const& a_other) = default;
inline sdlxvulkan::Instance& sdlxvulkan::Instance::operator=(Instance const& a_other) = default;

inline sdlxvulkan::Instance::Instance(Instance && a_other) = default;
inline sdlxvulkan::Instance& sdlxvulkan::Instance::operator=(Instance && a_other) = default;

#endif // SDLXVULKAN_INSTANCE_HPP