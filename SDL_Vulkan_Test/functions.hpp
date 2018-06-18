#ifndef SDLXVULKAN_FUNCTIONS_HPP
#define SDLXVULKAN_FUNCTIONS_HPP

#include <vulkan/vulkan.h>

#define SDLXVULKAN_DECLARE_VULKAN_FUNC(a_func_name) PFN_##a_func_name a_func_name{nullptr};

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Global_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions that don't require a specific 
  // VkInstance to use - the ones required to make a VkInstance.

  struct Global_Functions
  {
    // The function that will get the others.
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetInstanceProcAddr)

    // Functions that don't need an instance to use
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateInstance)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEnumerateInstanceExtensionProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEnumerateInstanceLayerProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEnumerateInstanceVersion)
  };

  // Uses the supplied function to initalise the function pointers
  void init_global_functions(Global_Functions& a_globals, PFN_vkGetInstanceProcAddr a_getter);

  //---------------------------------------------------------------------------
  // Instance_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions require a specific VkInstance to 
  // use.

  struct Instance_Functions
  {
    // The function that will be used to initialise Device_Functions
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetDeviceProcAddr)

    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateDevice)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateDebugReportCallbackEXT)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyDebugReportCallbackEXT)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyInstance)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroySurfaceKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEnumerateDeviceExtensionProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEnumeratePhysicalDevices)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceFeatures)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceMemoryProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceQueueFamilyProperties)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceFormatsKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfacePresentModesKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR)
  };

  // Uses Global_Functions::vkGetInstanceProcAddr
  void init_instance_functions(Instance_Functions& a_instance_functions, VkInstance a_instance, Global_Functions const& a_globals);

  //---------------------------------------------------------------------------
  // Device_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions require a specific VkDevice to 
  // use.

  struct Device_Functions
  {
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkAcquireNextImageKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkAllocateCommandBuffers)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkAllocateDescriptorSets)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkAllocateMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkBeginCommandBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkBindBufferMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkBindImageMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdBeginRenderPass)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdBindPipeline)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdBindDescriptorSets)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdBindIndexBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdBindVertexBuffers)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdClearColorImage)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdCopyBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdDraw)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdDrawIndexed)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdEndRenderPass)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdPipelineBarrier)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdSetViewport)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCmdSetScissor)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateCommandPool)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateDescriptorPool)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateDescriptorSetLayout)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateFence)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateFramebuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateGraphicsPipelines)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateImageView)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreatePipelineLayout)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateRenderPass)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateSemaphore)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateShaderModule)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkCreateSwapchainKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyCommandPool)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyDescriptorPool)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyDescriptorSetLayout)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyDevice)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyFence)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyFramebuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyImageView)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyPipeline)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyPipelineLayout)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyRenderPass)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroySemaphore)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroyShaderModule)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDestroySwapchainKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkDeviceWaitIdle)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkEndCommandBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkFreeCommandBuffers)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkFreeMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetBufferMemoryRequirements)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetDeviceQueue)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetFenceStatus)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetImageMemoryRequirements)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkGetSwapchainImagesKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkMapMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkQueuePresentKHR)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkQueueSubmit)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkQueueWaitIdle)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkResetCommandBuffer)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkResetFences)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkUnmapMemory)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkUpdateDescriptorSets)
    SDLXVULKAN_DECLARE_VULKAN_FUNC(vkWaitForFences)
  };

  // Uses Instance_Functions::vkGetDeviceProcAddr
  void init_device_functions(Device_Functions& a_device_functions, VkDevice a_device, Instance_Functions const& a_instance_functions);
}

#undef SDLXVULKAN_DECLARE_VULKAN_FUNC

#endif // SDLXVULKAN_FUNCTIONS_HPP