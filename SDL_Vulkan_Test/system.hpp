#ifndef SDLXVULKAN_SYSTEM_HPP
#define SDLXVULKAN_SYSTEM_HPP

#include "result.hpp"
#include <vector>
#include <memory>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Global_Functions;

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

    Global_Functions const& vk_functions() const;

    // Simplified access to the above data.
    Result<std::vector<VkExtensionProperties>> instance_extension_properties(char const* a_layer_name) const;
    Result<std::vector<VkLayerProperties>> instance_layer_properties() const;
    uint32_t vulkan_api_version() const;

    bool supports_layer(std::string const& a_layer_name) const;
    bool supports_layers(std::vector<std::string> const& a_layer_names) const;
  };
}

#endif // SDLXVULKAN_SYSTEM_HPP