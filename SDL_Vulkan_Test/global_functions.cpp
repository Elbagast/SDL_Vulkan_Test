#include "global_functions.hpp"

#include <iostream>

//---------------------------------------------------------------------------
// Global_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions that don't require a specific 
// VkInstance to use - the ones required to make a VkInstance. Also guards
// access to them so that any usage problems are caught.

// Member Data
//============================================================   
// The function that will get the others.
PFN_vkGetInstanceProcAddr m_vkGetInstanceProcAddr;

// Functions that don't need an instance to use
PFN_vkCreateInstance m_vkCreateInstance;
PFN_vkEnumerateInstanceExtensionProperties m_vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties m_vkEnumerateInstanceLayerProperties;
PFN_vkEnumerateInstanceVersion m_vkEnumerateInstanceVersion;


// Special 6
//============================================================

#define INIT_GLOBAL_FUNC1(a_name) m_##a_name { nullptr }

// Construct with all the stored function pointers as nullptr. All calls
// will fail in this state.
sdlxvulkan::Global_Functions::Global_Functions() noexcept :
  INIT_GLOBAL_FUNC1(vkGetInstanceProcAddr),
  INIT_GLOBAL_FUNC1(vkCreateInstance),
  INIT_GLOBAL_FUNC1(vkEnumerateInstanceExtensionProperties),
  INIT_GLOBAL_FUNC1(vkEnumerateInstanceLayerProperties),
  INIT_GLOBAL_FUNC1(vkEnumerateInstanceVersion)
{
  std::cout << "sdlxvulkan::Global_Functions::Global_Functions()" << std::endl;
}

namespace
{
  PFN_vkGetInstanceProcAddr verify_input(PFN_vkGetInstanceProcAddr a_vkGetInstanceProcAddr) noexcept
  {
    assert(a_vkGetInstanceProcAddr != nullptr);
    return a_vkGetInstanceProcAddr;
  }
}

#define INIT_GLOBAL_FUNC2(a_name) m_##a_name { reinterpret_cast<PFN_##a_name>(m_vkGetInstanceProcAddr(VK_NULL_HANDLE, #a_name)) }

// Construct using the supplied vkGetInstanceProcAddr function pointer, 
// storing it and using it to get the other function pointers. All calls
// *should* succeed in this state.
sdlxvulkan::Global_Functions::Global_Functions(PFN_vkGetInstanceProcAddr a_vkGetInstanceProcAddr) noexcept :
  m_vkGetInstanceProcAddr{ verify_input(a_vkGetInstanceProcAddr) },
  INIT_GLOBAL_FUNC2(vkCreateInstance),
  INIT_GLOBAL_FUNC2(vkEnumerateInstanceExtensionProperties),
  INIT_GLOBAL_FUNC2(vkEnumerateInstanceLayerProperties),
  INIT_GLOBAL_FUNC2(vkEnumerateInstanceVersion)
{
  std::cout << "sdlxvulkan::Global_Functions::Global_Functions( data )" << std::endl;
}