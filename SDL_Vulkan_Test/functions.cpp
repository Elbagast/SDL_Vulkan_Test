#include "functions.hpp"

#include <cassert>

#define INIT_VULKAN_GLOBAL_FUNC(a_func_name) a_globals.a_func_name = (PFN_##a_func_name)(a_getter(VK_NULL_HANDLE, #a_func_name));

// Uses the supplied function to initalise the function pointers
void sdlxvulkan::init_global_functions(Global_Functions& a_globals, PFN_vkGetInstanceProcAddr a_getter)
{
  assert(a_getter != nullptr);
  a_globals.vkGetInstanceProcAddr = a_getter;

  INIT_VULKAN_GLOBAL_FUNC(vkCreateInstance)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceExtensionProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceLayerProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceVersion)
}

#undef INIT_VULKAN_GLOBAL_FUNC


#define INIT_VULKAN_INSTANCE_FUNC(a_func_name) a_instance_functions.##a_func_name = reinterpret_cast<PFN_##a_func_name>(a_globals.vkGetInstanceProcAddr(a_instance, #a_func_name));

// Uses Global_Functions::vkGetInstanceProcAddr
void sdlxvulkan::init_instance_functions(Instance_Functions& a_instance_functions, VkInstance a_instance, Global_Functions const& a_globals)
{
  assert(a_globals.vkGetInstanceProcAddr != nullptr);
  //a_instance_functions.vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(a_globals.vkGetInstanceProcAddr(a_instance, "vkGetDeviceProcAddr"));

  INIT_VULKAN_INSTANCE_FUNC(vkGetDeviceProcAddr)
    
  INIT_VULKAN_INSTANCE_FUNC(vkCreateDevice)
  INIT_VULKAN_INSTANCE_FUNC(vkCreateDebugReportCallbackEXT)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroyDebugReportCallbackEXT)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroyInstance)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroySurfaceKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkEnumerateDeviceExtensionProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkEnumeratePhysicalDevices)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceFeatures)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceMemoryProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceQueueFamilyProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceFormatsKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfacePresentModesKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR)
}

#undef INIT_VULKAN_INSTANCE_FUNC

#define INIT_VULKAN_DEVICE_FUNC(a_func_name) a_device_functions.a_func_name = reinterpret_cast<PFN_##a_func_name>(a_instance_functions.vkGetDeviceProcAddr(a_device, #a_func_name));


// Uses Instance_Functions::vkGetDeviceProcAddr
void sdlxvulkan::init_device_functions(Device_Functions& a_device_functions, VkDevice a_device, Instance_Functions const& a_instance_functions)
{
  assert(a_instance_functions.vkGetDeviceProcAddr != nullptr);

  INIT_VULKAN_DEVICE_FUNC(vkAcquireNextImageKHR)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateCommandBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateMemory)
  INIT_VULKAN_DEVICE_FUNC(vkBeginCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkBindBufferMemory)
  INIT_VULKAN_DEVICE_FUNC(vkBindImageMemory)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBeginRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindPipeline)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindIndexBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindVertexBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkCmdClearColorImage)
  INIT_VULKAN_DEVICE_FUNC(vkCmdCopyBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCmdDraw)
  INIT_VULKAN_DEVICE_FUNC(vkCmdDrawIndexed)
  INIT_VULKAN_DEVICE_FUNC(vkCmdEndRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCmdPipelineBarrier)
  INIT_VULKAN_DEVICE_FUNC(vkCmdSetViewport)
  INIT_VULKAN_DEVICE_FUNC(vkCmdSetScissor)
  INIT_VULKAN_DEVICE_FUNC(vkCreateBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCreateCommandPool)
  INIT_VULKAN_DEVICE_FUNC(vkCreateDescriptorPool)
  INIT_VULKAN_DEVICE_FUNC(vkCreateDescriptorSetLayout)
  INIT_VULKAN_DEVICE_FUNC(vkCreateFence)
  INIT_VULKAN_DEVICE_FUNC(vkCreateFramebuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCreateGraphicsPipelines)
  INIT_VULKAN_DEVICE_FUNC(vkCreateImageView)
  INIT_VULKAN_DEVICE_FUNC(vkCreatePipelineLayout)
  INIT_VULKAN_DEVICE_FUNC(vkCreateRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCreateSemaphore)
  INIT_VULKAN_DEVICE_FUNC(vkCreateShaderModule)
  INIT_VULKAN_DEVICE_FUNC(vkCreateSwapchainKHR)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyCommandPool)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDescriptorPool)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDescriptorSetLayout)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDevice)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyFence)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyFramebuffer)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyImageView)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyPipeline)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyPipelineLayout)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkDestroySemaphore)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyShaderModule)
  INIT_VULKAN_DEVICE_FUNC(vkDestroySwapchainKHR)
  INIT_VULKAN_DEVICE_FUNC(vkDeviceWaitIdle)
  INIT_VULKAN_DEVICE_FUNC(vkEndCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkFreeCommandBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkFreeMemory)
  INIT_VULKAN_DEVICE_FUNC(vkGetBufferMemoryRequirements)
  INIT_VULKAN_DEVICE_FUNC(vkGetDeviceQueue)
  INIT_VULKAN_DEVICE_FUNC(vkGetFenceStatus)
  INIT_VULKAN_DEVICE_FUNC(vkGetImageMemoryRequirements)
  INIT_VULKAN_DEVICE_FUNC(vkGetSwapchainImagesKHR)
  INIT_VULKAN_DEVICE_FUNC(vkMapMemory)
  INIT_VULKAN_DEVICE_FUNC(vkQueuePresentKHR)
  INIT_VULKAN_DEVICE_FUNC(vkQueueSubmit)
  INIT_VULKAN_DEVICE_FUNC(vkQueueWaitIdle)
  INIT_VULKAN_DEVICE_FUNC(vkResetCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkResetFences)
  INIT_VULKAN_DEVICE_FUNC(vkUnmapMemory)
  INIT_VULKAN_DEVICE_FUNC(vkUpdateDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkWaitForFences)
}

#undef INIT_VULKAN_DEVICE_FUNC