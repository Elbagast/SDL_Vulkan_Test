#ifndef SDLXVULKAN_GLOBAL_FUNCTIONS_HPP
#define SDLXVULKAN_GLOBAL_FUNCTIONS_HPP

#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Global_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions that don't require a specific 
  // VkInstance to use - the ones required to make a VkInstance. Also guards
  // access to them so that any usage problems are caught.

  class Global_Functions
  {
  public:
    // Member Data
    //============================================================   
    // The function that will get the others.
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

    // Functions that don't need an instance to use
    PFN_vkCreateInstance vkCreateInstance;
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
    PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;

    // Special 6
    //============================================================
    // Construct with all the stored function pointers as nullptr. All calls
    // will fail in this state.
    Global_Functions() noexcept;

    // Construct using the supplied vkGetInstanceProcAddr function pointer, 
    // storing it and using it to get the other function pointers. All calls
    // *should* succeed in this state.
    explicit Global_Functions(PFN_vkGetInstanceProcAddr a_vkGetInstanceProcAddr) noexcept;
    
    ~Global_Functions();

    Global_Functions(Global_Functions const& a_other);
    Global_Functions& operator=(Global_Functions const& a_other);

    Global_Functions(Global_Functions && a_other);
    Global_Functions& operator=(Global_Functions && a_other);
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Global_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions that don't require a specific 
// VkInstance to use - the ones required to make a VkInstance. Also guards
// access to them so that any usage problems are caught.

// Special 6
//============================================================
inline sdlxvulkan::Global_Functions::~Global_Functions() = default;

inline sdlxvulkan::Global_Functions::Global_Functions(Global_Functions const& a_other) = default;
inline sdlxvulkan::Global_Functions& sdlxvulkan::Global_Functions::operator=(Global_Functions const& a_other) = default;

inline sdlxvulkan::Global_Functions::Global_Functions(Global_Functions && a_other) = default;
inline sdlxvulkan::Global_Functions& sdlxvulkan::Global_Functions::operator=(Global_Functions && a_other) = default;

#endif // SDLXVULKAN_GLOBAL_FUNCTIONS_HPP