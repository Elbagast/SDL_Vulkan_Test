#ifndef SDLXVULKAN_INSTANCE_FUNCTIONS_HPP
#define SDLXVULKAN_INSTANCE_FUNCTIONS_HPP

#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

namespace sdlxvulkan
{
  class Global_Functions;

  //---------------------------------------------------------------------------
  // Instance_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions require a specific VkInstance to 
  // use. These cannot be aquired until an instance is created so they are 
  // seperate from the global functions.

  class Instance_Functions
  {
  private:
    // Member Data
    //============================================================  
    // The function that will be used to initialise Device_Functions
    PFN_vkGetDeviceProcAddr m_vkGetDeviceProcAddr;

    // Core Functions:
    PFN_vkCreateDevice m_vkCreateDevice;
    PFN_vkDestroyInstance m_vkDestroyInstance;
    PFN_vkEnumerateDeviceExtensionProperties m_vkEnumerateDeviceExtensionProperties;
    PFN_vkEnumerateDeviceLayerProperties m_vkEnumerateDeviceLayerProperties;
    PFN_vkEnumeratePhysicalDeviceGroups m_vkEnumeratePhysicalDeviceGroups;
    PFN_vkEnumeratePhysicalDevices m_vkEnumeratePhysicalDevices;
    PFN_vkGetPhysicalDeviceExternalBufferProperties m_vkGetPhysicalDeviceExternalBufferProperties;
    PFN_vkGetPhysicalDeviceExternalFenceProperties m_vkGetPhysicalDeviceExternalFenceProperties;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties m_vkGetPhysicalDeviceExternalSemaphoreProperties;
    PFN_vkGetPhysicalDeviceFeatures m_vkGetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFeatures2 m_vkGetPhysicalDeviceFeatures2;
    PFN_vkGetPhysicalDeviceFormatProperties m_vkGetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceFormatProperties2 m_vkGetPhysicalDeviceFormatProperties2;
    PFN_vkGetPhysicalDeviceImageFormatProperties m_vkGetPhysicalDeviceImageFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 m_vkGetPhysicalDeviceImageFormatProperties2;
    PFN_vkGetPhysicalDeviceMemoryProperties m_vkGetPhysicalDeviceMemoryProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties2 m_vkGetPhysicalDeviceMemoryProperties2;
    PFN_vkGetPhysicalDeviceProperties m_vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceProperties2 m_vkGetPhysicalDeviceProperties2;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties m_vkGetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 m_vkGetPhysicalDeviceQueueFamilyProperties2;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties m_vkGetPhysicalDeviceSparseImageFormatProperties;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 m_vkGetPhysicalDeviceSparseImageFormatProperties2;

    // Extension Functions:
    PFN_vkCreateDebugReportCallbackEXT m_vkCreateDebugReportCallbackEXT;
    PFN_vkCreateDebugUtilsMessengerEXT m_vkCreateDebugUtilsMessengerEXT;
    PFN_vkCreateDisplayModeKHR m_vkCreateDisplayModeKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR m_vkCreateDisplayPlaneSurfaceKHR;
    PFN_vkDebugReportMessageEXT m_vkDebugReportMessageEXT;
    PFN_vkDestroyDebugReportCallbackEXT m_vkDestroyDebugReportCallbackEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT m_vkDestroyDebugUtilsMessengerEXT;
    PFN_vkDestroySurfaceKHR m_vkDestroySurfaceKHR;
    PFN_vkEnumeratePhysicalDeviceGroupsKHR m_vkEnumeratePhysicalDeviceGroupsKHR;
    PFN_vkGetDisplayModePropertiesKHR m_vkGetDisplayModePropertiesKHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR m_vkGetDisplayPlaneCapabilitiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR m_vkGetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR m_vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR m_vkGetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR m_vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR m_vkGetPhysicalDeviceExternalFencePropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV m_vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR m_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    PFN_vkGetPhysicalDeviceFeatures2KHR m_vkGetPhysicalDeviceFeatures2KHR;
    PFN_vkGetPhysicalDeviceFormatProperties2KHR m_vkGetPhysicalDeviceFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX m_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX;
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR m_vkGetPhysicalDeviceImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR m_vkGetPhysicalDeviceMemoryProperties2KHR;
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT m_vkGetPhysicalDeviceMultisamplePropertiesEXT;
    PFN_vkGetPhysicalDevicePresentRectanglesKHR m_vkGetPhysicalDevicePresentRectanglesKHR;
    PFN_vkGetPhysicalDeviceProperties2KHR m_vkGetPhysicalDeviceProperties2KHR;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR m_vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR m_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT m_vkGetPhysicalDeviceSurfaceCapabilities2EXT;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR m_vkGetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR m_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR m_vkGetPhysicalDeviceSurfaceFormats2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR m_vkGetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR m_vkGetPhysicalDeviceSurfacePresentModesKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR m_vkGetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkReleaseDisplayEXT m_vkReleaseDisplayEXT;
    PFN_vkSubmitDebugUtilsMessageEXT m_vkSubmitDebugUtilsMessageEXT;


#ifdef VK_USE_PLATFORM_ANDROID_KHR
    //Android Platform Functions:
    PFN_vkCreateAndroidSurfaceKHR m_vkCreateAndroidSurfaceKHR;
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
    //IOS Platform Functions:
    PFN_vkCreateIOSSurfaceMVK m_vkCreateIOSSurfaceMVK;
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
    //MacOS Platform Functions:
    PFN_vkCreateMacOSSurfaceMVK m_vkCreateMacOSSurfaceMVK;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
    //Mir Platform Functions:
    PFN_vkCreateMirSurfaceKHR m_vkCreateMirSurfaceKHR;
    PFN_vkGetPhysicalDeviceMirPresentationSupportKHR m_vkGetPhysicalDeviceMirPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_VI_NN
    //Vi Platform Functions:
    PFN_vkCreateViSurfaceNN m_vkCreateViSurfaceNN;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    //Wayland Platform Functions:
    PFN_vkCreateWaylandSurfaceKHR m_vkCreateWaylandSurfaceKHR;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR m_vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    //Win32 Platform Functions:
    PFN_vkCreateWin32SurfaceKHR m_vkCreateWin32SurfaceKHR;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR m_vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
    //Xcb Platform Functions:
    PFN_vkCreateXcbSurfaceKHR m_vkCreateXcbSurfaceKHR;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR m_vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
    //Xlib Platform Functions:
    PFN_vkCreateXlibSurfaceKHR m_vkCreateXlibSurfaceKHR;
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR m_vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
    //Xlib XRAndR Platform Functions:
    PFN_vkAcquireXlibDisplayEXT m_vkAcquireXlibDisplayEXT;
    PFN_vkGetRandROutputDisplayEXT m_vkGetRandROutputDisplayEXT;
#endif


  public:
    // Special 6
    //============================================================
    // Construct with all the stored function pointers as nullptr. All calls
    // will fail in this state.
    Instance_Functions();

    // Construct using the supplied Global_Functions::vkCreateInstance function,
    // using the supplied VkInstance. The instance is not stored here. Only
    // functions that relate to the version and extensions that the instance was
    // created with will work.
    Instance_Functions(VkInstance a_instance, Global_Functions const& a_global_functions);
    
    ~Instance_Functions();

    Instance_Functions(Instance_Functions const& a_other);
    Instance_Functions& operator=(Instance_Functions const& a_other);

    Instance_Functions(Instance_Functions && a_other);
    Instance_Functions& operator=(Instance_Functions && a_other);

    // Interface
    //============================================================
    PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, char const* pName) const noexcept;

    // Core Functions:
    VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, VkDeviceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDevice* pDevice) const noexcept;
    void vkDestroyInstance(VkInstance instance, VkAllocationCallbacks const* pAllocator) const noexcept;
    VkResult vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const noexcept;
    VkResult vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties) const noexcept;
    VkResult vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) const noexcept;
    VkResult vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const noexcept;
    void vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalBufferInfo const* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) const noexcept;
    void vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalFenceInfo const* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) const noexcept;
    void vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalSemaphoreInfo const* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) const noexcept;
    void vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) const noexcept;
    void vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) const noexcept;
    void vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) const noexcept;
    void vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) const noexcept;
    VkResult vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties) const noexcept;
    VkResult vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceImageFormatInfo2 const* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) const noexcept;
    void vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) const noexcept;
    void vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) const noexcept;
    void vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) const noexcept;
    void vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) const noexcept;
    void vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) const noexcept;
    void vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) const noexcept;
    void vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties) const noexcept;
    void vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSparseImageFormatInfo2 const* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) const noexcept;

    // Extension Functions:
    VkResult vkCreateDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDebugReportCallbackEXT* pCallback) const noexcept;
    VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDebugUtilsMessengerEXT* pMessenger) const noexcept;
    VkResult vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, VkDisplayModeCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDisplayModeKHR* pMode) const noexcept;
    VkResult vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, VkDisplaySurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    void vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, char const* pLayerPrefix, char const* pMessage) const noexcept;
    void vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, VkAllocationCallbacks const* pAllocator) const noexcept;
    VkResult vkEnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) const noexcept;
    VkResult vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties) const noexcept;
    VkResult vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities) const noexcept;
    VkResult vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays) const noexcept;
    VkResult vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties) const noexcept;
    VkResult vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties) const noexcept;
    void vkGetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalBufferInfo const* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) const noexcept;
    void vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalFenceInfo const* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) const noexcept;
    VkResult vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties) const noexcept;
    void vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalSemaphoreInfo const* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) const noexcept;
    void vkGetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) const noexcept;
    void vkGetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) const noexcept;
    void vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX* pFeatures, VkDeviceGeneratedCommandsLimitsNVX* pLimits) const noexcept;
    VkResult vkGetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceImageFormatInfo2 const* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) const noexcept;
    void vkGetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) const noexcept;
    void vkGetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties) const noexcept;
    VkResult vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects) const noexcept;
    void vkGetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) const noexcept;
    void vkGetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) const noexcept;
    void vkGetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSparseImageFormatInfo2 const* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSurfaceInfo2KHR const* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSurfaceInfo2KHR const* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats) const noexcept;
    VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) const noexcept;
    VkResult vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported) const noexcept;
    VkResult vkReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) const noexcept;
    void vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData) const noexcept;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    //Android Platform Functions:
    VkResult vkCreateAndroidSurfaceKHR(VkInstance instance, VkAndroidSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
    //IOS Platform Functions:
    VkResult vkCreateIOSSurfaceMVK(VkInstance instance, VkIOSSurfaceCreateInfoMVK const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
    //MacOS Platform Functions:
    VkResult vkCreateMacOSSurfaceMVK(VkInstance instance, VkMacOSSurfaceCreateInfoMVK const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
    //Mir Platform Functions:
    VkResult vkCreateMirSurfaceKHR(VkInstance instance, VkMirSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    VkBool32 vkGetPhysicalDeviceMirPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, MirConnection* connection) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_VI_NN
    //Vi Platform Functions:
    VkResult vkCreateViSurfaceNN(VkInstance instance, VkViSurfaceCreateInfoNN const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    //Wayland Platform Functions:
    VkResult vkCreateWaylandSurfaceKHR(VkInstance instance, VkWaylandSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    VkBool32 vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    //Win32 Platform Functions:
    VkResult vkCreateWin32SurfaceKHR(VkInstance instance, VkWin32SurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    VkBool32 vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
    //Xcb Platform Functions:
    VkResult vkCreateXcbSurfaceKHR(VkInstance instance, VkXcbSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    VkBool32 vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
    //Xlib Platform Functions:
    VkResult vkCreateXlibSurfaceKHR(VkInstance instance, VkXlibSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept;
    VkBool32 vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
    //Xlib XRAndR Platform Functions:
    VkResult vkAcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display) const noexcept;
    VkResult vkGetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay) const noexcept;
#endif
  };
}

#undef SDLXVULKAN_DECLARE_VULKAN_FUNC

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Instance_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions require a specific VkInstance to 
// use. These cannot be aquired until an instance is created so they are 
// seperate from the global functions.

// Special 6
//============================================================
inline sdlxvulkan::Instance_Functions::~Instance_Functions() = default;

inline sdlxvulkan::Instance_Functions::Instance_Functions(Instance_Functions const& a_other) = default;
inline sdlxvulkan::Instance_Functions& sdlxvulkan::Instance_Functions::operator=(Instance_Functions const& a_other) = default;

inline sdlxvulkan::Instance_Functions::Instance_Functions(Instance_Functions && a_other) = default;
inline sdlxvulkan::Instance_Functions& sdlxvulkan::Instance_Functions::operator=(Instance_Functions && a_other) = default;

// Interface
//============================================================
inline PFN_vkVoidFunction sdlxvulkan::Instance_Functions::vkGetDeviceProcAddr(VkDevice device, char const* pName) const noexcept
{
  assert(m_vkGetDeviceProcAddr != nullptr);
  return m_vkGetDeviceProcAddr(device, pName);
}

// Core Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateDevice(VkPhysicalDevice physicalDevice, VkDeviceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDevice* pDevice) const noexcept
{
  assert(m_vkCreateDevice != nullptr);
  return m_vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

inline void sdlxvulkan::Instance_Functions::vkDestroyInstance(VkInstance instance, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyInstance != nullptr);
  return m_vkDestroyInstance(instance, pAllocator);
}

inline VkResult sdlxvulkan::Instance_Functions::vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const noexcept
{
  assert(m_vkEnumerateDeviceExtensionProperties != nullptr);
  return m_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties) const noexcept
{
  assert(m_vkEnumerateDeviceLayerProperties != nullptr);
  return m_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) const noexcept
{
  assert(m_vkEnumeratePhysicalDeviceGroups != nullptr);
  return m_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const noexcept
{
  assert(m_vkEnumeratePhysicalDevices != nullptr);
  return m_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalBufferInfo const* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalBufferProperties != nullptr);
  return m_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalFenceInfo const* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalFenceProperties != nullptr);
  return m_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalSemaphoreInfo const* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalSemaphoreProperties != nullptr);
  return m_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) const noexcept
{
  assert(m_vkGetPhysicalDeviceFeatures != nullptr);
  return m_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) const noexcept
{
  assert(m_vkGetPhysicalDeviceFeatures2 != nullptr);
  return m_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceFormatProperties != nullptr);
  return m_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceFormatProperties2 != nullptr);
  return m_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceImageFormatProperties != nullptr);
  return m_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceImageFormatInfo2 const* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceImageFormatProperties2 != nullptr);
  return m_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceMemoryProperties != nullptr);
  return m_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceMemoryProperties2 != nullptr);
  return m_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceProperties != nullptr);
  return m_vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceProperties2 != nullptr);
  return m_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceQueueFamilyProperties != nullptr);
  return m_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceQueueFamilyProperties2 != nullptr);
  return m_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceSparseImageFormatProperties != nullptr);
  return m_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSparseImageFormatInfo2 const* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceSparseImageFormatProperties2 != nullptr);
  return m_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}


// Extension Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDebugReportCallbackEXT* pCallback) const noexcept
{
  assert(m_vkCreateDebugReportCallbackEXT != nullptr);
  return m_vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
}

inline VkResult sdlxvulkan::Instance_Functions::vkCreateDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDebugUtilsMessengerEXT* pMessenger) const noexcept
{
  assert(m_vkCreateDebugUtilsMessengerEXT != nullptr);
  return m_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
}

inline VkResult sdlxvulkan::Instance_Functions::vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, VkDisplayModeCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDisplayModeKHR* pMode) const noexcept
{
  assert(m_vkCreateDisplayModeKHR != nullptr);
  return m_vkCreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode);
}

inline VkResult sdlxvulkan::Instance_Functions::vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, VkDisplaySurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateDisplayPlaneSurfaceKHR != nullptr);
  return m_vkCreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline void sdlxvulkan::Instance_Functions::vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, char const* pLayerPrefix, char const* pMessage) const noexcept
{
  assert(m_vkDebugReportMessageEXT != nullptr);
  return m_vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}

inline void sdlxvulkan::Instance_Functions::vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDebugReportCallbackEXT != nullptr);
  return m_vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}

inline void sdlxvulkan::Instance_Functions::vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDebugUtilsMessengerEXT != nullptr);
  return m_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
}

inline void sdlxvulkan::Instance_Functions::vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySurfaceKHR != nullptr);
  return m_vkDestroySurfaceKHR(instance, surface, pAllocator);
}

inline VkResult sdlxvulkan::Instance_Functions::vkEnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) const noexcept
{
  assert(m_vkEnumeratePhysicalDeviceGroupsKHR != nullptr);
  return m_vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties) const noexcept
{
  assert(m_vkGetDisplayModePropertiesKHR != nullptr);
  return m_vkGetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities) const noexcept
{
  assert(m_vkGetDisplayPlaneCapabilitiesKHR != nullptr);
  return m_vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays) const noexcept
{
  assert(m_vkGetDisplayPlaneSupportedDisplaysKHR != nullptr);
  return m_vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceDisplayPlanePropertiesKHR != nullptr);
  return m_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceDisplayPropertiesKHR != nullptr);
  return m_vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalBufferInfo const* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalBufferPropertiesKHR != nullptr);
  return m_vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalFenceInfo const* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalFencePropertiesKHR != nullptr);
  return m_vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalImageFormatPropertiesNV != nullptr);
  return m_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceExternalSemaphoreInfo const* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR != nullptr);
  return m_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) const noexcept
{
  assert(m_vkGetPhysicalDeviceFeatures2KHR != nullptr);
  return m_vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceFormatProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX* pFeatures, VkDeviceGeneratedCommandsLimitsNVX* pLimits) const noexcept
{
  assert(m_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX != nullptr);
  return m_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(physicalDevice, pFeatures, pLimits);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceImageFormatInfo2 const* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceImageFormatProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceMemoryProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceMultisamplePropertiesEXT != nullptr);
  return m_vkGetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects) const noexcept
{
  assert(m_vkGetPhysicalDevicePresentRectanglesKHR != nullptr);
  return m_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceQueueFamilyProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

inline void sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSparseImageFormatInfo2 const* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) const noexcept
{
  assert(m_vkGetPhysicalDeviceSparseImageFormatProperties2KHR != nullptr);
  return m_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceCapabilities2EXT != nullptr);
  return m_vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSurfaceInfo2KHR const* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceCapabilities2KHR != nullptr);
  return m_vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceCapabilitiesKHR != nullptr);
  return m_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceSurfaceInfo2KHR const* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceFormats2KHR != nullptr);
  return m_vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceFormatsKHR != nullptr);
  return m_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfacePresentModesKHR != nullptr);
  return m_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported) const noexcept
{
  assert(m_vkGetPhysicalDeviceSurfaceSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
}

inline VkResult sdlxvulkan::Instance_Functions::vkReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) const noexcept
{
  assert(m_vkReleaseDisplayEXT != nullptr);
  return m_vkReleaseDisplayEXT(physicalDevice, display);
}

inline void sdlxvulkan::Instance_Functions::vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData) const noexcept
{
  assert(m_vkSubmitDebugUtilsMessageEXT != nullptr);
  return m_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
}


#ifdef VK_USE_PLATFORM_ANDROID_KHR
//Android Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateAndroidSurfaceKHR(VkInstance instance, VkAndroidSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateAndroidSurfaceKHR != nullptr);
  return m_vkCreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
//IOS Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateIOSSurfaceMVK(VkInstance instance, VkIOSSurfaceCreateInfoMVK const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateIOSSurfaceMVK != nullptr);
  return m_vkCreateIOSSurfaceMVK(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
//MacOS Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateMacOSSurfaceMVK(VkInstance instance, VkMacOSSurfaceCreateInfoMVK const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateMacOSSurfaceMVK != nullptr);
  return m_vkCreateMacOSSurfaceMVK(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
//Mir Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateMirSurfaceKHR(VkInstance instance, VkMirSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateMirSurfaceKHR != nullptr);
  return m_vkCreateMirSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline VkBool32 sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceMirPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, MirConnection* connection) const noexcept
{
  assert(m_vkGetPhysicalDeviceMirPresentationSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceMirPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection);
}

#endif

#ifdef VK_USE_PLATFORM_VI_NN
//Vi Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateViSurfaceNN(VkInstance instance, VkViSurfaceCreateInfoNN const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateViSurfaceNN != nullptr);
  return m_vkCreateViSurfaceNN(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//Wayland Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateWaylandSurfaceKHR(VkInstance instance, VkWaylandSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateWaylandSurfaceKHR != nullptr);
  return m_vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline VkBool32 sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display) const noexcept
{
  assert(m_vkGetPhysicalDeviceWaylandPresentationSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, wl_display* display);
}

#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
//Win32 Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateWin32SurfaceKHR(VkInstance instance, VkWin32SurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateWin32SurfaceKHR != nullptr);
  return m_vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline VkBool32 sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const noexcept
{
  assert(m_vkGetPhysicalDeviceWin32PresentationSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
}

#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
//Xcb Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateXcbSurfaceKHR(VkInstance instance, VkXcbSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateXcbSurfaceKHR != nullptr);
  return m_vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline VkBool32 sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id) const noexcept
{
  assert(m_vkGetPhysicalDeviceXcbPresentationSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
}

#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
//Xlib Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkCreateXlibSurfaceKHR(VkInstance instance, VkXlibSurfaceCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSurfaceKHR* pSurface) const noexcept
{
  assert(m_vkCreateXlibSurfaceKHR != nullptr);
  return m_vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

inline VkBool32 sdlxvulkan::Instance_Functions::vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID) const noexcept
{
  assert(m_vkGetPhysicalDeviceXlibPresentationSupportKHR != nullptr);
  return m_vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
}

#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
//Xlib XRAndR Platform Functions:
inline VkResult sdlxvulkan::Instance_Functions::vkAcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display) const noexcept
{
  assert(m_vkAcquireXlibDisplayEXT != nullptr);
  return m_vkAcquireXlibDisplayEXT(physicalDevice, dpy, display);
}

inline VkResult sdlxvulkan::Instance_Functions::vkGetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay) const noexcept
{
  assert(m_vkGetRandROutputDisplayEXT != nullptr);
  return m_vkGetRandROutputDisplayEXT(physicalDevice, dpy, rrOutput, pDisplay);
}

#endif


#endif // SDLXVULKAN_INSTANCE_FUNCTIONS_HPP