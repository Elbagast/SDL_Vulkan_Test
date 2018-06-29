#include "instance_functions.hpp"

#include "global_functions.hpp"

#include <iostream>

//---------------------------------------------------------------------------
// Instance_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions require a specific VkInstance to 
// use. These cannot be aquired until an instance is created so they are 
// seperate from the global functions.

// Special 6
//============================================================
// Construct with all the stored function pointers as nullptr. All calls
// will fail in this state.
sdlxvulkan::Instance_Functions::Instance_Functions():
  vkGetDeviceProcAddr{ nullptr }

  // Core Functions:
  , vkCreateDevice{ nullptr }
  , vkDestroyInstance{ nullptr }
  , vkEnumerateDeviceExtensionProperties{ nullptr }
  , vkEnumerateDeviceLayerProperties{ nullptr }
  , vkEnumeratePhysicalDeviceGroups{ nullptr }
  , vkEnumeratePhysicalDevices{ nullptr }
  , vkGetPhysicalDeviceExternalBufferProperties{ nullptr }
  , vkGetPhysicalDeviceExternalFenceProperties{ nullptr }
  , vkGetPhysicalDeviceExternalSemaphoreProperties{ nullptr }
  , vkGetPhysicalDeviceFeatures{ nullptr }
  , vkGetPhysicalDeviceFeatures2{ nullptr }
  , vkGetPhysicalDeviceFormatProperties{ nullptr }
  , vkGetPhysicalDeviceFormatProperties2{ nullptr }
  , vkGetPhysicalDeviceImageFormatProperties{ nullptr }
  , vkGetPhysicalDeviceImageFormatProperties2{ nullptr }
  , vkGetPhysicalDeviceMemoryProperties{ nullptr }
  , vkGetPhysicalDeviceMemoryProperties2{ nullptr }
  , vkGetPhysicalDeviceProperties{ nullptr }
  , vkGetPhysicalDeviceProperties2{ nullptr }
  , vkGetPhysicalDeviceQueueFamilyProperties{ nullptr }
  , vkGetPhysicalDeviceQueueFamilyProperties2{ nullptr }
  , vkGetPhysicalDeviceSparseImageFormatProperties{ nullptr }
  , vkGetPhysicalDeviceSparseImageFormatProperties2{ nullptr }

  // Extension Functions:
  , vkCreateDebugReportCallbackEXT{ nullptr }
  , vkCreateDebugUtilsMessengerEXT{ nullptr }
  , vkCreateDisplayModeKHR{ nullptr }
  , vkCreateDisplayPlaneSurfaceKHR{ nullptr }
  , vkDebugReportMessageEXT{ nullptr }
  , vkDestroyDebugReportCallbackEXT{ nullptr }
  , vkDestroyDebugUtilsMessengerEXT{ nullptr }
  , vkDestroySurfaceKHR{ nullptr }
  , vkEnumeratePhysicalDeviceGroupsKHR{ nullptr }
  , vkGetDisplayModePropertiesKHR{ nullptr }
  , vkGetDisplayPlaneCapabilitiesKHR{ nullptr }
  , vkGetDisplayPlaneSupportedDisplaysKHR{ nullptr }
  , vkGetPhysicalDeviceDisplayPlanePropertiesKHR{ nullptr }
  , vkGetPhysicalDeviceDisplayPropertiesKHR{ nullptr }
  , vkGetPhysicalDeviceExternalBufferPropertiesKHR{ nullptr }
  , vkGetPhysicalDeviceExternalFencePropertiesKHR{ nullptr }
  , vkGetPhysicalDeviceExternalImageFormatPropertiesNV{ nullptr }
  , vkGetPhysicalDeviceExternalSemaphorePropertiesKHR{ nullptr }
  , vkGetPhysicalDeviceFeatures2KHR{ nullptr }
  , vkGetPhysicalDeviceFormatProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX{ nullptr }
  , vkGetPhysicalDeviceImageFormatProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceMemoryProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceMultisamplePropertiesEXT{ nullptr }
  , vkGetPhysicalDevicePresentRectanglesKHR{ nullptr }
  , vkGetPhysicalDeviceProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceQueueFamilyProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceSparseImageFormatProperties2KHR{ nullptr }
  , vkGetPhysicalDeviceSurfaceCapabilities2EXT{ nullptr }
  , vkGetPhysicalDeviceSurfaceCapabilities2KHR{ nullptr }
  , vkGetPhysicalDeviceSurfaceCapabilitiesKHR{ nullptr }
  , vkGetPhysicalDeviceSurfaceFormats2KHR{ nullptr }
  , vkGetPhysicalDeviceSurfaceFormatsKHR{ nullptr }
  , vkGetPhysicalDeviceSurfacePresentModesKHR{ nullptr }
  , vkGetPhysicalDeviceSurfaceSupportKHR{ nullptr }
  , vkReleaseDisplayEXT{ nullptr }
  , vkSubmitDebugUtilsMessageEXT{ nullptr }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , vkCreateAndroidSurfaceKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
  , vkCreateIOSSurfaceMVK{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
  , vkCreateMacOSSurfaceMVK{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
  , vkCreateMirSurfaceKHR{ nullptr }
  , vkGetPhysicalDeviceMirPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , vkCreateViSurfaceNN{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
  , vkCreateWaylandSurfaceKHR{ nullptr }
  , vkGetPhysicalDeviceWaylandPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , vkCreateWin32SurfaceKHR{ nullptr }
  , vkGetPhysicalDeviceWin32PresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
  , vkCreateXcbSurfaceKHR{ nullptr }
  , vkGetPhysicalDeviceXcbPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
  , vkCreateXlibSurfaceKHR{ nullptr }
  , vkGetPhysicalDeviceXlibPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
  , vkAcquireXlibDisplayEXT{ nullptr }
  , vkGetRandROutputDisplayEXT{ nullptr }
#endif

{
    std::cout << "sdlxvulkan::Instance_Functions::Instance_Functions()" << std::endl;
}

// Construct using the supplied Global_Functions::vkCreateInstance function,
// using the supplied VkInstance. The instance is not stored here. Only
// functions that relate to the version and extensions that the instance was
// created with will work.
sdlxvulkan::Instance_Functions::Instance_Functions(VkInstance a_instance, Global_Functions const& a_global_functions) :
  vkGetDeviceProcAddr{ reinterpret_cast<PFN_vkGetDeviceProcAddr>(a_global_functions.vkGetInstanceProcAddr(a_instance, "vkGetDeviceProcAddr")) }

  // Core Functions:
  , vkCreateDevice{ reinterpret_cast<PFN_vkCreateDevice>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDevice")) }
  , vkDestroyInstance{ reinterpret_cast<PFN_vkDestroyInstance>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyInstance")) }
  , vkEnumerateDeviceExtensionProperties{ reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumerateDeviceExtensionProperties")) }
  , vkEnumerateDeviceLayerProperties{ reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumerateDeviceLayerProperties")) }
  , vkEnumeratePhysicalDeviceGroups{ reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDeviceGroups")) }
  , vkEnumeratePhysicalDevices{ reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDevices")) }
  , vkGetPhysicalDeviceExternalBufferProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalBufferProperties")) }
  , vkGetPhysicalDeviceExternalFenceProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalFenceProperties")) }
  , vkGetPhysicalDeviceExternalSemaphoreProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalSemaphoreProperties")) }
  , vkGetPhysicalDeviceFeatures{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures")) }
  , vkGetPhysicalDeviceFeatures2{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures2")) }
  , vkGetPhysicalDeviceFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties")) }
  , vkGetPhysicalDeviceFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties2")) }
  , vkGetPhysicalDeviceImageFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties")) }
  , vkGetPhysicalDeviceImageFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties2")) }
  , vkGetPhysicalDeviceMemoryProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties")) }
  , vkGetPhysicalDeviceMemoryProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties2")) }
  , vkGetPhysicalDeviceProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties")) }
  , vkGetPhysicalDeviceProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties2")) }
  , vkGetPhysicalDeviceQueueFamilyProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties")) }
  , vkGetPhysicalDeviceQueueFamilyProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties2")) }
  , vkGetPhysicalDeviceSparseImageFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties")) }
  , vkGetPhysicalDeviceSparseImageFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties2")) }

  // Extension Functions:
  , vkCreateDebugReportCallbackEXT{ reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDebugReportCallbackEXT")) }
  , vkCreateDebugUtilsMessengerEXT{ reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDebugUtilsMessengerEXT")) }
  , vkCreateDisplayModeKHR{ reinterpret_cast<PFN_vkCreateDisplayModeKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDisplayModeKHR")) }
  , vkCreateDisplayPlaneSurfaceKHR{ reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDisplayPlaneSurfaceKHR")) }
  , vkDebugReportMessageEXT{ reinterpret_cast<PFN_vkDebugReportMessageEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDebugReportMessageEXT")) }
  , vkDestroyDebugReportCallbackEXT{ reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyDebugReportCallbackEXT")) }
  , vkDestroyDebugUtilsMessengerEXT{ reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyDebugUtilsMessengerEXT")) }
  , vkDestroySurfaceKHR{ reinterpret_cast<PFN_vkDestroySurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroySurfaceKHR")) }
  , vkEnumeratePhysicalDeviceGroupsKHR{ reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroupsKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDeviceGroupsKHR")) }
  , vkGetDisplayModePropertiesKHR{ reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayModePropertiesKHR")) }
  , vkGetDisplayPlaneCapabilitiesKHR{ reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayPlaneCapabilitiesKHR")) }
  , vkGetDisplayPlaneSupportedDisplaysKHR{ reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayPlaneSupportedDisplaysKHR")) }
  , vkGetPhysicalDeviceDisplayPlanePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceDisplayPlanePropertiesKHR")) }
  , vkGetPhysicalDeviceDisplayPropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceDisplayPropertiesKHR")) }
  , vkGetPhysicalDeviceExternalBufferPropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalBufferPropertiesKHR")) }
  , vkGetPhysicalDeviceExternalFencePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalFencePropertiesKHR")) }
  , vkGetPhysicalDeviceExternalImageFormatPropertiesNV{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalImageFormatPropertiesNV")) }
  , vkGetPhysicalDeviceExternalSemaphorePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalSemaphorePropertiesKHR")) }
  , vkGetPhysicalDeviceFeatures2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures2KHR")) }
  , vkGetPhysicalDeviceFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties2KHR")) }
  , vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX{ reinterpret_cast<PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX")) }
  , vkGetPhysicalDeviceImageFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties2KHR")) }
  , vkGetPhysicalDeviceMemoryProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties2KHR")) }
  , vkGetPhysicalDeviceMultisamplePropertiesEXT{ reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMultisamplePropertiesEXT")) }
  , vkGetPhysicalDevicePresentRectanglesKHR{ reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDevicePresentRectanglesKHR")) }
  , vkGetPhysicalDeviceProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties2KHR")) }
  , vkGetPhysicalDeviceQueueFamilyProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties2KHR")) }
  , vkGetPhysicalDeviceSparseImageFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties2KHR")) }
  , vkGetPhysicalDeviceSurfaceCapabilities2EXT{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilities2EXT")) }
  , vkGetPhysicalDeviceSurfaceCapabilities2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilities2KHR")) }
  , vkGetPhysicalDeviceSurfaceCapabilitiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilitiesKHR")) }
  , vkGetPhysicalDeviceSurfaceFormats2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceFormats2KHR")) }
  , vkGetPhysicalDeviceSurfaceFormatsKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceFormatsKHR")) }
  , vkGetPhysicalDeviceSurfacePresentModesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfacePresentModesKHR")) }
  , vkGetPhysicalDeviceSurfaceSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceSupportKHR")) }
  , vkReleaseDisplayEXT{ reinterpret_cast<PFN_vkReleaseDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkReleaseDisplayEXT")) }
  , vkSubmitDebugUtilsMessageEXT{ reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkSubmitDebugUtilsMessageEXT")) }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , vkCreateAndroidSurfaceKHR{ reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateAndroidSurfaceKHR")) }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
  , vkCreateIOSSurfaceMVK{ reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateIOSSurfaceMVK")) }
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
  , vkCreateMacOSSurfaceMVK{ reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateMacOSSurfaceMVK")) }
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
  , vkCreateMirSurfaceKHR{ reinterpret_cast<PFN_vkCreateMirSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateMirSurfaceKHR")) }
  , vkGetPhysicalDeviceMirPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceMirPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMirPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , vkCreateViSurfaceNN{ reinterpret_cast<PFN_vkCreateViSurfaceNN>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateViSurfaceNN")) }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
  , vkCreateWaylandSurfaceKHR{ reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateWaylandSurfaceKHR")) }
  , vkGetPhysicalDeviceWaylandPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceWaylandPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , vkCreateWin32SurfaceKHR{ reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateWin32SurfaceKHR")) }
  , vkGetPhysicalDeviceWin32PresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceWin32PresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
  , vkCreateXcbSurfaceKHR{ reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateXcbSurfaceKHR")) }
  , vkGetPhysicalDeviceXcbPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceXcbPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
  , vkCreateXlibSurfaceKHR{ reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateXlibSurfaceKHR")) }
  , vkGetPhysicalDeviceXlibPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceXlibPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
  , vkAcquireXlibDisplayEXT{ reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkAcquireXlibDisplayEXT")) }
  , vkGetRandROutputDisplayEXT{ reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetRandROutputDisplayEXT")) }
#endif

{
  std::cout << "sdlxvulkan::Instance_Functions::Instance_Functions( data )" << std::endl;
}
