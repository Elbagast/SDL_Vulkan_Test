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

// Construct with all the stored function pointers as nullptr. All calls
// will fail in this state.
sdlxvulkan::Global_Functions::Global_Functions() noexcept :
  vkGetInstanceProcAddr{ nullptr },
  vkCreateInstance{ nullptr },
  vkEnumerateInstanceExtensionProperties{ nullptr },
  vkEnumerateInstanceLayerProperties{ nullptr },
  vkEnumerateInstanceVersion{ nullptr }
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


// Construct using the supplied vkGetInstanceProcAddr function pointer, 
// storing it and using it to get the other function pointers. All calls
// *should* succeed in this state.
sdlxvulkan::Global_Functions::Global_Functions(PFN_vkGetInstanceProcAddr a_vkGetInstanceProcAddr) noexcept :
  vkGetInstanceProcAddr{ verify_input(a_vkGetInstanceProcAddr) },
  vkCreateInstance{ reinterpret_cast<PFN_vkCreateInstance>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance")) },
  vkEnumerateInstanceExtensionProperties{ reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties")) },
  vkEnumerateInstanceLayerProperties{ reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceLayerProperties")) },
  vkEnumerateInstanceVersion{ reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceVersion")) }
{
  std::cout << "sdlxvulkan::Global_Functions::Global_Functions( data )" << std::endl;
}