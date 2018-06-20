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
  m_vkGetDeviceProcAddr{ nullptr }

  // Core Functions:
  , m_vkCreateDevice{ nullptr }
  , m_vkDestroyInstance{ nullptr }
  , m_vkEnumerateDeviceExtensionProperties{ nullptr }
  , m_vkEnumerateDeviceLayerProperties{ nullptr }
  , m_vkEnumeratePhysicalDeviceGroups{ nullptr }
  , m_vkEnumeratePhysicalDevices{ nullptr }
  , m_vkGetPhysicalDeviceExternalBufferProperties{ nullptr }
  , m_vkGetPhysicalDeviceExternalFenceProperties{ nullptr }
  , m_vkGetPhysicalDeviceExternalSemaphoreProperties{ nullptr }
  , m_vkGetPhysicalDeviceFeatures{ nullptr }
  , m_vkGetPhysicalDeviceFeatures2{ nullptr }
  , m_vkGetPhysicalDeviceFormatProperties{ nullptr }
  , m_vkGetPhysicalDeviceFormatProperties2{ nullptr }
  , m_vkGetPhysicalDeviceImageFormatProperties{ nullptr }
  , m_vkGetPhysicalDeviceImageFormatProperties2{ nullptr }
  , m_vkGetPhysicalDeviceMemoryProperties{ nullptr }
  , m_vkGetPhysicalDeviceMemoryProperties2{ nullptr }
  , m_vkGetPhysicalDeviceProperties{ nullptr }
  , m_vkGetPhysicalDeviceProperties2{ nullptr }
  , m_vkGetPhysicalDeviceQueueFamilyProperties{ nullptr }
  , m_vkGetPhysicalDeviceQueueFamilyProperties2{ nullptr }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties{ nullptr }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties2{ nullptr }

  // Extension Functions:
  , m_vkCreateDebugReportCallbackEXT{ nullptr }
  , m_vkCreateDebugUtilsMessengerEXT{ nullptr }
  , m_vkCreateDisplayModeKHR{ nullptr }
  , m_vkCreateDisplayPlaneSurfaceKHR{ nullptr }
  , m_vkDebugReportMessageEXT{ nullptr }
  , m_vkDestroyDebugReportCallbackEXT{ nullptr }
  , m_vkDestroyDebugUtilsMessengerEXT{ nullptr }
  , m_vkDestroySurfaceKHR{ nullptr }
  , m_vkEnumeratePhysicalDeviceGroupsKHR{ nullptr }
  , m_vkGetDisplayModePropertiesKHR{ nullptr }
  , m_vkGetDisplayPlaneCapabilitiesKHR{ nullptr }
  , m_vkGetDisplayPlaneSupportedDisplaysKHR{ nullptr }
  , m_vkGetPhysicalDeviceDisplayPlanePropertiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceDisplayPropertiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceExternalBufferPropertiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceExternalFencePropertiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceExternalImageFormatPropertiesNV{ nullptr }
  , m_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceFeatures2KHR{ nullptr }
  , m_vkGetPhysicalDeviceFormatProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX{ nullptr }
  , m_vkGetPhysicalDeviceImageFormatProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceMemoryProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceMultisamplePropertiesEXT{ nullptr }
  , m_vkGetPhysicalDevicePresentRectanglesKHR{ nullptr }
  , m_vkGetPhysicalDeviceProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceQueueFamilyProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties2KHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceCapabilities2EXT{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceCapabilities2KHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceCapabilitiesKHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceFormats2KHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceFormatsKHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfacePresentModesKHR{ nullptr }
  , m_vkGetPhysicalDeviceSurfaceSupportKHR{ nullptr }
  , m_vkReleaseDisplayEXT{ nullptr }
  , m_vkSubmitDebugUtilsMessageEXT{ nullptr }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , m_vkCreateAndroidSurfaceKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
  , m_vkCreateIOSSurfaceMVK{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
  , m_vkCreateMacOSSurfaceMVK{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
  , m_vkCreateMirSurfaceKHR{ nullptr }
  , m_vkGetPhysicalDeviceMirPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , m_vkCreateViSurfaceNN{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
  , m_vkCreateWaylandSurfaceKHR{ nullptr }
  , m_vkGetPhysicalDeviceWaylandPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , m_vkCreateWin32SurfaceKHR{ nullptr }
  , m_vkGetPhysicalDeviceWin32PresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
  , m_vkCreateXcbSurfaceKHR{ nullptr }
  , m_vkGetPhysicalDeviceXcbPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
  , m_vkCreateXlibSurfaceKHR{ nullptr }
  , m_vkGetPhysicalDeviceXlibPresentationSupportKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
  , m_vkAcquireXlibDisplayEXT{ nullptr }
  , m_vkGetRandROutputDisplayEXT{ nullptr }
#endif

{
    std::cout << "sdlxvulkan::Instance_Functions::Instance_Functions()" << std::endl;
}

#define INIT_INSTANCE_FUNC2(a_func_name) m_##a_func_name{ reinterpret_cast<PFN_##a_func_name>(a_global_functions.vkGetInstanceProcAddr(a_instance, #a_func_name)) }

// Construct using the supplied Global_Functions::vkCreateInstance function,
// using the supplied VkInstance. The instance is not stored here. Only
// functions that relate to the version and extensions that the instance was
// created with will work.
sdlxvulkan::Instance_Functions::Instance_Functions(VkInstance a_instance, Global_Functions const& a_global_functions) :
  m_vkGetDeviceProcAddr{ reinterpret_cast<PFN_vkGetDeviceProcAddr>(a_global_functions.vkGetInstanceProcAddr(a_instance, "vkGetDeviceProcAddr")) }

  // Core Functions:
  , m_vkCreateDevice{ reinterpret_cast<PFN_vkCreateDevice>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDevice")) }
  , m_vkDestroyInstance{ reinterpret_cast<PFN_vkDestroyInstance>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyInstance")) }
  , m_vkEnumerateDeviceExtensionProperties{ reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumerateDeviceExtensionProperties")) }
  , m_vkEnumerateDeviceLayerProperties{ reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumerateDeviceLayerProperties")) }
  , m_vkEnumeratePhysicalDeviceGroups{ reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDeviceGroups")) }
  , m_vkEnumeratePhysicalDevices{ reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDevices")) }
  , m_vkGetPhysicalDeviceExternalBufferProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalBufferProperties")) }
  , m_vkGetPhysicalDeviceExternalFenceProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalFenceProperties")) }
  , m_vkGetPhysicalDeviceExternalSemaphoreProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalSemaphoreProperties")) }
  , m_vkGetPhysicalDeviceFeatures{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures")) }
  , m_vkGetPhysicalDeviceFeatures2{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures2")) }
  , m_vkGetPhysicalDeviceFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties")) }
  , m_vkGetPhysicalDeviceFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties2")) }
  , m_vkGetPhysicalDeviceImageFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties")) }
  , m_vkGetPhysicalDeviceImageFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties2")) }
  , m_vkGetPhysicalDeviceMemoryProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties")) }
  , m_vkGetPhysicalDeviceMemoryProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties2")) }
  , m_vkGetPhysicalDeviceProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties")) }
  , m_vkGetPhysicalDeviceProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties2")) }
  , m_vkGetPhysicalDeviceQueueFamilyProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties")) }
  , m_vkGetPhysicalDeviceQueueFamilyProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties2")) }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties")) }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties2{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties2")) }

  // Extension Functions:
  , m_vkCreateDebugReportCallbackEXT{ reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDebugReportCallbackEXT")) }
  , m_vkCreateDebugUtilsMessengerEXT{ reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDebugUtilsMessengerEXT")) }
  , m_vkCreateDisplayModeKHR{ reinterpret_cast<PFN_vkCreateDisplayModeKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDisplayModeKHR")) }
  , m_vkCreateDisplayPlaneSurfaceKHR{ reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateDisplayPlaneSurfaceKHR")) }
  , m_vkDebugReportMessageEXT{ reinterpret_cast<PFN_vkDebugReportMessageEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDebugReportMessageEXT")) }
  , m_vkDestroyDebugReportCallbackEXT{ reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyDebugReportCallbackEXT")) }
  , m_vkDestroyDebugUtilsMessengerEXT{ reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroyDebugUtilsMessengerEXT")) }
  , m_vkDestroySurfaceKHR{ reinterpret_cast<PFN_vkDestroySurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkDestroySurfaceKHR")) }
  , m_vkEnumeratePhysicalDeviceGroupsKHR{ reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroupsKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkEnumeratePhysicalDeviceGroupsKHR")) }
  , m_vkGetDisplayModePropertiesKHR{ reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayModePropertiesKHR")) }
  , m_vkGetDisplayPlaneCapabilitiesKHR{ reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayPlaneCapabilitiesKHR")) }
  , m_vkGetDisplayPlaneSupportedDisplaysKHR{ reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetDisplayPlaneSupportedDisplaysKHR")) }
  , m_vkGetPhysicalDeviceDisplayPlanePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceDisplayPlanePropertiesKHR")) }
  , m_vkGetPhysicalDeviceDisplayPropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceDisplayPropertiesKHR")) }
  , m_vkGetPhysicalDeviceExternalBufferPropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalBufferPropertiesKHR")) }
  , m_vkGetPhysicalDeviceExternalFencePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalFencePropertiesKHR")) }
  , m_vkGetPhysicalDeviceExternalImageFormatPropertiesNV{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalImageFormatPropertiesNV")) }
  , m_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceExternalSemaphorePropertiesKHR")) }
  , m_vkGetPhysicalDeviceFeatures2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFeatures2KHR")) }
  , m_vkGetPhysicalDeviceFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceFormatProperties2KHR")) }
  , m_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX{ reinterpret_cast<PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX")) }
  , m_vkGetPhysicalDeviceImageFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceImageFormatProperties2KHR")) }
  , m_vkGetPhysicalDeviceMemoryProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMemoryProperties2KHR")) }
  , m_vkGetPhysicalDeviceMultisamplePropertiesEXT{ reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMultisamplePropertiesEXT")) }
  , m_vkGetPhysicalDevicePresentRectanglesKHR{ reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDevicePresentRectanglesKHR")) }
  , m_vkGetPhysicalDeviceProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceProperties2KHR")) }
  , m_vkGetPhysicalDeviceQueueFamilyProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceQueueFamilyProperties2KHR")) }
  , m_vkGetPhysicalDeviceSparseImageFormatProperties2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSparseImageFormatProperties2KHR")) }
  , m_vkGetPhysicalDeviceSurfaceCapabilities2EXT{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilities2EXT")) }
  , m_vkGetPhysicalDeviceSurfaceCapabilities2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilities2KHR")) }
  , m_vkGetPhysicalDeviceSurfaceCapabilitiesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceCapabilitiesKHR")) }
  , m_vkGetPhysicalDeviceSurfaceFormats2KHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceFormats2KHR")) }
  , m_vkGetPhysicalDeviceSurfaceFormatsKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceFormatsKHR")) }
  , m_vkGetPhysicalDeviceSurfacePresentModesKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfacePresentModesKHR")) }
  , m_vkGetPhysicalDeviceSurfaceSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceSurfaceSupportKHR")) }
  , m_vkReleaseDisplayEXT{ reinterpret_cast<PFN_vkReleaseDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkReleaseDisplayEXT")) }
  , m_vkSubmitDebugUtilsMessageEXT{ reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkSubmitDebugUtilsMessageEXT")) }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , m_vkCreateAndroidSurfaceKHR{ reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateAndroidSurfaceKHR")) }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
  , m_vkCreateIOSSurfaceMVK{ reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateIOSSurfaceMVK")) }
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
  , m_vkCreateMacOSSurfaceMVK{ reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateMacOSSurfaceMVK")) }
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
  , m_vkCreateMirSurfaceKHR{ reinterpret_cast<PFN_vkCreateMirSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateMirSurfaceKHR")) }
  , m_vkGetPhysicalDeviceMirPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceMirPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceMirPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , m_vkCreateViSurfaceNN{ reinterpret_cast<PFN_vkCreateViSurfaceNN>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateViSurfaceNN")) }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
  , m_vkCreateWaylandSurfaceKHR{ reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateWaylandSurfaceKHR")) }
  , m_vkGetPhysicalDeviceWaylandPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceWaylandPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , m_vkCreateWin32SurfaceKHR{ reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateWin32SurfaceKHR")) }
  , m_vkGetPhysicalDeviceWin32PresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceWin32PresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
  , m_vkCreateXcbSurfaceKHR{ reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateXcbSurfaceKHR")) }
  , m_vkGetPhysicalDeviceXcbPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceXcbPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
  , m_vkCreateXlibSurfaceKHR{ reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkCreateXlibSurfaceKHR")) }
  , m_vkGetPhysicalDeviceXlibPresentationSupportKHR{ reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetPhysicalDeviceXlibPresentationSupportKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
  , m_vkAcquireXlibDisplayEXT{ reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkAcquireXlibDisplayEXT")) }
  , m_vkGetRandROutputDisplayEXT{ reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(a_global_functions.vkGetInstanceProcAddr(a_instance, u8"vkGetRandROutputDisplayEXT")) }
#endif

{
  std::cout << "sdlxvulkan::Instance_Functions::Instance_Functions( data )" << std::endl;
}
