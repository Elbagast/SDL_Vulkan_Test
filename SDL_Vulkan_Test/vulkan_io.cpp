#include "vulkan_io.hpp"

#include <iostream>
#include <string>

std::ostream& flags_out(std::ostream& a_ostream, VkQueueFlags a_queue_flags)
{
  a_ostream << u8"{ ";
  if (a_queue_flags & VK_QUEUE_GRAPHICS_BIT) a_ostream << u8"VK_QUEUE_GRAPHICS_BIT ";
  if (a_queue_flags & VK_QUEUE_COMPUTE_BIT) a_ostream << u8"VK_QUEUE_COMPUTE_BIT ";
  if (a_queue_flags & VK_QUEUE_TRANSFER_BIT) a_ostream << u8"VK_QUEUE_TRANSFER_BIT ";
  if (a_queue_flags & VK_QUEUE_SPARSE_BINDING_BIT) a_ostream << u8"VK_QUEUE_SPARSE_BINDING_BIT ";
  if (a_queue_flags & VK_QUEUE_PROTECTED_BIT) a_ostream << u8"VK_QUEUE_PROTECTED_BIT ";
  a_ostream << u8"}";
  return a_ostream;
}

std::ostream& operator<<(std::ostream& a_ostream, VkExtent3D const& a_extent)
{
  a_ostream
    << u8"{ "
    << a_extent.width << u8", "
    << a_extent.height << u8", "
    << a_extent.depth
    << u8" }";
  return a_ostream;
}

std::ostream& operator<<(std::ostream& a_ostream, VkExtent2D const& a_ext)
{
  std::cout << a_ext.width << "x" << a_ext.height;
  return a_ostream;
}


std::ostream& operator<<(std::ostream& a_ostream, VkSurfaceCapabilitiesKHR const& a_sc)
{
  std::cout
    << "VkSurfaceCapabilitiesKHR " << std::endl
    << "minImageCount " << a_sc.minImageCount << std::endl
    << "maxImageCount " << a_sc.maxImageCount << std::endl
    << "currentExtent " << a_sc.currentExtent << std::endl
    << "minImageExtent " << a_sc.minImageExtent << std::endl
    << "maxImageExtent " << a_sc.maxImageExtent << std::endl
    << "maxImageArrayLayers " << a_sc.maxImageArrayLayers << std::endl
    << "supportedTransforms " << a_sc.supportedTransforms << std::endl
    << "currentTransform " << a_sc.currentTransform << std::endl
    << "supportedCompositeAlpha " << a_sc.supportedCompositeAlpha << std::endl
    << "supportedUsageFlags " << a_sc.supportedUsageFlags << std::endl
    << std::endl;

  return a_ostream;
}


char const* vkresult_c_string(VkResult a_value)
{
  switch (a_value)
  {
  case(VK_SUCCESS): return "VK_SUCCESS";
  case(VK_NOT_READY): return "VK_NOT_READY ";
  case(VK_TIMEOUT): return "VK_TIMEOUT ";
  case(VK_EVENT_SET): return "VK_EVENT_SET ";
  case(VK_EVENT_RESET): return "VK_EVENT_RESET ";
  case(VK_INCOMPLETE): return "VK_INCOMPLETE ";
  case(VK_ERROR_OUT_OF_HOST_MEMORY): return "VK_ERROR_OUT_OF_HOST_MEMORY ";
  case(VK_ERROR_OUT_OF_DEVICE_MEMORY): return "VK_ERROR_OUT_OF_DEVICE_MEMORY ";
  case(VK_ERROR_INITIALIZATION_FAILED): return "VK_ERROR_INITIALIZATION_FAILED ";
  case(VK_ERROR_DEVICE_LOST): return "VK_ERROR_DEVICE_LOST ";
  case(VK_ERROR_MEMORY_MAP_FAILED): return "VK_ERROR_MEMORY_MAP_FAILED ";
  case(VK_ERROR_LAYER_NOT_PRESENT): return "VK_ERROR_LAYER_NOT_PRESENT ";
  case(VK_ERROR_EXTENSION_NOT_PRESENT): return "VK_ERROR_EXTENSION_NOT_PRESENT ";
  case(VK_ERROR_FEATURE_NOT_PRESENT): return "VK_ERROR_FEATURE_NOT_PRESENT ";
  case(VK_ERROR_INCOMPATIBLE_DRIVER): return "VK_ERROR_INCOMPATIBLE_DRIVER ";
  case(VK_ERROR_TOO_MANY_OBJECTS): return "VK_ERROR_TOO_MANY_OBJECTS ";
  case(VK_ERROR_FORMAT_NOT_SUPPORTED): return "VK_ERROR_FORMAT_NOT_SUPPORTED ";
  case(VK_ERROR_FRAGMENTED_POOL): return "VK_ERROR_FRAGMENTED_POOL ";
  case(VK_ERROR_OUT_OF_POOL_MEMORY): return "VK_ERROR_OUT_OF_POOL_MEMORY ";
  case(VK_ERROR_INVALID_EXTERNAL_HANDLE): return "VK_ERROR_INVALID_EXTERNAL_HANDLE ";
  case(VK_ERROR_SURFACE_LOST_KHR): return "VK_ERROR_SURFACE_LOST_KHR ";
  case(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR): return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ";
  case(VK_SUBOPTIMAL_KHR): return "VK_SUBOPTIMAL_KHR ";
  case(VK_ERROR_OUT_OF_DATE_KHR): return "VK_ERROR_OUT_OF_DATE_KHR ";
  case(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR): return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ";
  case(VK_ERROR_VALIDATION_FAILED_EXT): return "VK_ERROR_VALIDATION_FAILED_EXT ";
  case(VK_ERROR_INVALID_SHADER_NV): return "VK_ERROR_INVALID_SHADER_NV ";
  case(VK_ERROR_FRAGMENTATION_EXT): return "VK_ERROR_FRAGMENTATION_EXT ";
  case(VK_ERROR_NOT_PERMITTED_EXT): return "VK_ERROR_NOT_PERMITTED_EXT ";
  default: return "BAD VKRESULT";
  }
}


std::string vkresult_string(VkResult a_value)
{
  return vkresult_c_string(a_value);
}