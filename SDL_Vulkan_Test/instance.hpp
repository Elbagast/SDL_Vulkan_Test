#ifndef SDLXVULKAN_INSTANCE_HPP
#define SDLXVULKAN_INSTANCE_HPP

//#include "system.hpp"

#include <vector>
#include <string>
#include <vulkan/vulkan_core.h>

namespace sdlxvulkan
{
  class System;
  class Window;
  /*
  namespace internal
  {
    static_assert(std::is_pointer_v<VkInstance>, "VkInstance is not a pointer type, don't do the next thing.");
    using Instance_Type = std::remove_pointer_t<VkInstance>;
    using Instance_Pointer = std::add_pointer_t<Instance_Type>;
    static_assert(std::is_same_v<VkInstance, Instance_Pointer>, "VkInstance is not the same type as deduced Instance_Pointer.");
  }*/

  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------
  // Holds a VkInstance with reference counting and cleans up properly. 

  class Instance
  {
  private:

    // Member Data
    //============================================================   
    class Implementation;
    std::shared_ptr<Implementation> m_implementation;

    // Member Data
    //============================================================   
    //System m_system;
    //std::shared_ptr<internal::Instance_Type> m_instance;
       
  public:
    // Special 6
    //============================================================
    // Create a null instance. It contains nothing and does nothing.
    //Instance();

    // Create using the supplied data.
    /*
    Instance
    (
      PFN_vkGetInstanceProcAddr a_get_func,
      std::vector<char const*> const& a_extension_names,
      std::vector<char const*> const& a_layer_names,
      char const* a_application_name,
      uint32_t a_application_version,
      char const* a_engine_name,
      uint32_t a_engine_version,
      uint32_t a_vulkan_version
    );*/
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
    // Explcitly get the VkInstance.
    VkInstance get() const;

    // Implicitly convert to VkInstance, allowing this to be passed
    // directly to Vulkan functions.
    operator VkInstance() const;

    // a shedload of instance functions....

    void vkDestroySurfaceKHR(VkSurfaceKHR surface, VkAllocationCallbacks const* pAllocator);

  };
}

#endif // SDLXVULKAN_INSTANCE_HPP