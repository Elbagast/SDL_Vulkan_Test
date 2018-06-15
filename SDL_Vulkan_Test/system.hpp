#ifndef SDLXVULKAN_SYSTEM_HPP
#define SDLXVULKAN_SYSTEM_HPP

#include "result.hpp"
#include <vector>
#include <memory>
#include <vulkan/vulkan_core.h>

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // System
  //---------------------------------------------------------------------------
  // Manages the SDL system and Vulkan interface with reference counting so it 
  // cleans up properly. Since Vulkan must be loaded by SDL, the system has 
  // state that is essentially global, but also must be initalised and shut
  // down properly.
  
  class System
  {
  private:
    // Member Data
    //============================================================   
    class Implementation;
    std::shared_ptr<Implementation> m_implementation;

  public:
    // Special 6
    //============================================================
    explicit System(uint32_t a_flags);
    ~System();

    System(System const& a_other);
    System& operator=(System const& a_other);

    System(System && a_other);
    System& operator=(System && a_other);

    // Interface
    //============================================================
    // DO NOT CALL THESE FUNCTIONS BEFORE A System OBJECT HAS BEEN 
    // SUCCESSFULLY CONSTRUCTED.

    static PFN_vkGetInstanceProcAddr get_vkGetInstanceProcAddr();

    // Direct access to the Vulkan functions, as in the Vulkan documentation.
    static PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, char const* pName);
    static VkResult vkCreateInstance(VkInstanceCreateInfo const*  pCreateInfo, VkAllocationCallbacks const* pAllocator, VkInstance* pInstance);
    static VkResult vkEnumerateInstanceExtensionProperties(char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
    static VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);
    static VkResult vkEnumerateInstanceVersion(uint32_t* pApiVersion);

    // Simplified access to the above data.
    static Result<std::vector<VkExtensionProperties>> instance_extension_properties(char const* a_layer_name);
    static Result<std::vector<VkLayerProperties>> instance_layer_properties();
    static uint32_t vulkan_api_version();

    static bool supports_layer(std::string const& a_layer_name);
    static bool supports_layers(std::vector<std::string> const& a_layer_names);
  };
}

#endif // SDLXVULKAN_SYSTEM_HPP