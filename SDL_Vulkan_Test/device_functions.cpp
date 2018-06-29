#include "device_functions.hpp"

#include "instance_functions.hpp"

#include <iostream>

//---------------------------------------------------------------------------
// Device_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions require a specific VkDevice to 
// use. These cannot be aquired until an VkDevice is created so they are 
// seperate from the instance functions.

// Special 6
//============================================================
// Construct with all the stored function pointers as nullptr. All calls
// will fail in this state.
sdlxvulkan::Device_Functions::Device_Functions() :
  // Core Functions:
   vkAllocateCommandBuffers{ nullptr }
  , vkAllocateDescriptorSets{ nullptr }
  , vkAllocateMemory{ nullptr }
  , vkBeginCommandBuffer{ nullptr }
  , vkBindBufferMemory{ nullptr }
  , vkBindBufferMemory2{ nullptr }
  , vkBindImageMemory{ nullptr }
  , vkBindImageMemory2{ nullptr }
  , vkCmdBeginQuery{ nullptr }
  , vkCmdBeginRenderPass{ nullptr }
  , vkCmdBindDescriptorSets{ nullptr }
  , vkCmdBindIndexBuffer{ nullptr }
  , vkCmdBindPipeline{ nullptr }
  , vkCmdBindVertexBuffers{ nullptr }
  , vkCmdBlitImage{ nullptr }
  , vkCmdClearAttachments{ nullptr }
  , vkCmdClearColorImage{ nullptr }
  , vkCmdClearDepthStencilImage{ nullptr }
  , vkCmdCopyBuffer{ nullptr }
  , vkCmdCopyBufferToImage{ nullptr }
  , vkCmdCopyImage{ nullptr }
  , vkCmdCopyImageToBuffer{ nullptr }
  , vkCmdCopyQueryPoolResults{ nullptr }
  , vkCmdDispatch{ nullptr }
  , vkCmdDispatchBase{ nullptr }
  , vkCmdDispatchIndirect{ nullptr }
  , vkCmdDraw{ nullptr }
  , vkCmdDrawIndexed{ nullptr }
  , vkCmdDrawIndexedIndirect{ nullptr }
  , vkCmdDrawIndirect{ nullptr }
  , vkCmdEndQuery{ nullptr }
  , vkCmdEndRenderPass{ nullptr }
  , vkCmdExecuteCommands{ nullptr }
  , vkCmdFillBuffer{ nullptr }
  , vkCmdNextSubpass{ nullptr }
  , vkCmdPipelineBarrier{ nullptr }
  , vkCmdPushConstants{ nullptr }
  , vkCmdResetEvent{ nullptr }
  , vkCmdResetQueryPool{ nullptr }
  , vkCmdResolveImage{ nullptr }
  , vkCmdSetBlendConstants{ nullptr }
  , vkCmdSetDepthBias{ nullptr }
  , vkCmdSetDepthBounds{ nullptr }
  , vkCmdSetDeviceMask{ nullptr }
  , vkCmdSetEvent{ nullptr }
  , vkCmdSetLineWidth{ nullptr }
  , vkCmdSetScissor{ nullptr }
  , vkCmdSetStencilCompareMask{ nullptr }
  , vkCmdSetStencilReference{ nullptr }
  , vkCmdSetStencilWriteMask{ nullptr }
  , vkCmdSetViewport{ nullptr }
  , vkCmdUpdateBuffer{ nullptr }
  , vkCmdWaitEvents{ nullptr }
  , vkCmdWriteTimestamp{ nullptr }
  , vkCreateBuffer{ nullptr }
  , vkCreateBufferView{ nullptr }
  , vkCreateCommandPool{ nullptr }
  , vkCreateComputePipelines{ nullptr }
  , vkCreateDescriptorPool{ nullptr }
  , vkCreateDescriptorSetLayout{ nullptr }
  , vkCreateDescriptorUpdateTemplate{ nullptr }
  , vkCreateEvent{ nullptr }
  , vkCreateFence{ nullptr }
  , vkCreateFramebuffer{ nullptr }
  , vkCreateGraphicsPipelines{ nullptr }
  , vkCreateImage{ nullptr }
  , vkCreateImageView{ nullptr }
  , vkCreatePipelineCache{ nullptr }
  , vkCreatePipelineLayout{ nullptr }
  , vkCreateQueryPool{ nullptr }
  , vkCreateRenderPass{ nullptr }
  , vkCreateSampler{ nullptr }
  , vkCreateSamplerYcbcrConversion{ nullptr }
  , vkCreateSemaphore{ nullptr }
  , vkCreateShaderModule{ nullptr }
  , vkDestroyBuffer{ nullptr }
  , vkDestroyBufferView{ nullptr }
  , vkDestroyCommandPool{ nullptr }
  , vkDestroyDescriptorPool{ nullptr }
  , vkDestroyDescriptorSetLayout{ nullptr }
  , vkDestroyDescriptorUpdateTemplate{ nullptr }
  , vkDestroyDevice{ nullptr }
  , vkDestroyEvent{ nullptr }
  , vkDestroyFence{ nullptr }
  , vkDestroyFramebuffer{ nullptr }
  , vkDestroyImage{ nullptr }
  , vkDestroyImageView{ nullptr }
  , vkDestroyPipeline{ nullptr }
  , vkDestroyPipelineCache{ nullptr }
  , vkDestroyPipelineLayout{ nullptr }
  , vkDestroyQueryPool{ nullptr }
  , vkDestroyRenderPass{ nullptr }
  , vkDestroySampler{ nullptr }
  , vkDestroySamplerYcbcrConversion{ nullptr }
  , vkDestroySemaphore{ nullptr }
  , vkDestroyShaderModule{ nullptr }
  , vkDeviceWaitIdle{ nullptr }
  , vkEndCommandBuffer{ nullptr }
  , vkFlushMappedMemoryRanges{ nullptr }
  , vkFreeCommandBuffers{ nullptr }
  , vkFreeDescriptorSets{ nullptr }
  , vkFreeMemory{ nullptr }
  , vkGetBufferMemoryRequirements{ nullptr }
  , vkGetBufferMemoryRequirements2{ nullptr }
  , vkGetDescriptorSetLayoutSupport{ nullptr }
  , vkGetDeviceGroupPeerMemoryFeatures{ nullptr }
  , vkGetDeviceMemoryCommitment{ nullptr }
  , vkGetDeviceQueue{ nullptr }
  , vkGetDeviceQueue2{ nullptr }
  , vkGetEventStatus{ nullptr }
  , vkGetFenceStatus{ nullptr }
  , vkGetImageMemoryRequirements{ nullptr }
  , vkGetImageMemoryRequirements2{ nullptr }
  , vkGetImageSparseMemoryRequirements{ nullptr }
  , vkGetImageSparseMemoryRequirements2{ nullptr }
  , vkGetImageSubresourceLayout{ nullptr }
  , vkGetPipelineCacheData{ nullptr }
  , vkGetQueryPoolResults{ nullptr }
  , vkGetRenderAreaGranularity{ nullptr }
  , vkInvalidateMappedMemoryRanges{ nullptr }
  , vkMapMemory{ nullptr }
  , vkMergePipelineCaches{ nullptr }
  , vkQueueBindSparse{ nullptr }
  , vkQueueSubmit{ nullptr }
  , vkQueueWaitIdle{ nullptr }
  , vkResetCommandBuffer{ nullptr }
  , vkResetCommandPool{ nullptr }
  , vkResetDescriptorPool{ nullptr }
  , vkResetEvent{ nullptr }
  , vkResetFences{ nullptr }
  , vkSetEvent{ nullptr }
  , vkTrimCommandPool{ nullptr }
  , vkUnmapMemory{ nullptr }
  , vkUpdateDescriptorSetWithTemplate{ nullptr }
  , vkUpdateDescriptorSets{ nullptr }
  , vkWaitForFences{ nullptr }

  // Extension Functions:
  , vkAcquireNextImage2KHR{ nullptr }
  , vkAcquireNextImageKHR{ nullptr }
  , vkBindBufferMemory2KHR{ nullptr }
  , vkBindImageMemory2KHR{ nullptr }
  , vkCmdBeginDebugUtilsLabelEXT{ nullptr }
  , vkCmdDebugMarkerBeginEXT{ nullptr }
  , vkCmdDebugMarkerEndEXT{ nullptr }
  , vkCmdDebugMarkerInsertEXT{ nullptr }
  , vkCmdDispatchBaseKHR{ nullptr }
  , vkCmdDrawIndexedIndirectCountAMD{ nullptr }
  , vkCmdDrawIndirectCountAMD{ nullptr }
  , vkCmdEndDebugUtilsLabelEXT{ nullptr }
  , vkCmdInsertDebugUtilsLabelEXT{ nullptr }
  , vkCmdProcessCommandsNVX{ nullptr }
  , vkCmdPushDescriptorSetKHR{ nullptr }
  , vkCmdPushDescriptorSetWithTemplateKHR{ nullptr }
  , vkCmdReserveSpaceForCommandsNVX{ nullptr }
  , vkCmdSetDeviceMaskKHR{ nullptr }
  , vkCmdSetDiscardRectangleEXT{ nullptr }
  , vkCmdSetSampleLocationsEXT{ nullptr }
  , vkCmdWriteBufferMarkerAMD{ nullptr }
  , vkCreateDescriptorUpdateTemplateKHR{ nullptr }
  , vkCreateIndirectCommandsLayoutNVX{ nullptr }
  , vkCreateObjectTableNVX{ nullptr }
  , vkCreateSamplerYcbcrConversionKHR{ nullptr }
  , vkCreateSharedSwapchainsKHR{ nullptr }
  , vkCreateSwapchainKHR{ nullptr }
  , vkCreateValidationCacheEXT{ nullptr }
  , vkDebugMarkerSetObjectNameEXT{ nullptr }
  , vkDebugMarkerSetObjectTagEXT{ nullptr }
  , vkDestroyDescriptorUpdateTemplateKHR{ nullptr }
  , vkDestroyIndirectCommandsLayoutNVX{ nullptr }
  , vkDestroyObjectTableNVX{ nullptr }
  , vkDestroySamplerYcbcrConversionKHR{ nullptr }
  , vkDestroySwapchainKHR{ nullptr }
  , vkDestroyValidationCacheEXT{ nullptr }
  , vkDisplayPowerControlEXT{ nullptr }
  , vkGetBufferMemoryRequirements2KHR{ nullptr }
  , vkGetDescriptorSetLayoutSupportKHR{ nullptr }
  , vkGetDeviceGroupPeerMemoryFeaturesKHR{ nullptr }
  , vkGetDeviceGroupPresentCapabilitiesKHR{ nullptr }
  , vkGetDeviceGroupSurfacePresentModesKHR{ nullptr }
  , vkGetFenceFdKHR{ nullptr }
  , vkGetImageMemoryRequirements2KHR{ nullptr }
  , vkGetImageSparseMemoryRequirements2KHR{ nullptr }
  , vkGetMemoryFdKHR{ nullptr }
  , vkGetMemoryFdPropertiesKHR{ nullptr }
  , vkGetMemoryHostPointerPropertiesEXT{ nullptr }
  , vkGetPastPresentationTimingGOOGLE{ nullptr }
  , vkGetRefreshCycleDurationGOOGLE{ nullptr }
  , vkGetSemaphoreFdKHR{ nullptr }
  , vkGetShaderInfoAMD{ nullptr }
  , vkGetSwapchainCounterEXT{ nullptr }
  , vkGetSwapchainImagesKHR{ nullptr }
  , vkGetSwapchainStatusKHR{ nullptr }
  , vkGetValidationCacheDataEXT{ nullptr }
  , vkImportFenceFdKHR{ nullptr }
  , vkImportSemaphoreFdKHR{ nullptr }
  , vkMergeValidationCachesEXT{ nullptr }
  , vkQueueBeginDebugUtilsLabelEXT{ nullptr }
  , vkQueueEndDebugUtilsLabelEXT{ nullptr }
  , vkQueueInsertDebugUtilsLabelEXT{ nullptr }
  , vkQueuePresentKHR{ nullptr }
  , vkRegisterDeviceEventEXT{ nullptr }
  , vkRegisterDisplayEventEXT{ nullptr }
  , vkRegisterObjectsNVX{ nullptr }
  , vkSetDebugUtilsObjectNameEXT{ nullptr }
  , vkSetDebugUtilsObjectTagEXT{ nullptr }
  , vkSetHdrMetadataEXT{ nullptr }
  , vkTrimCommandPoolKHR{ nullptr }
  , vkUnregisterObjectsNVX{ nullptr }
  , vkUpdateDescriptorSetWithTemplateKHR{ nullptr }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , vkGetAndroidHardwareBufferPropertiesANDROID{ nullptr }
  , vkGetMemoryAndroidHardwareBufferANDROID{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , vkCmdSetViewportWScalingNV{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , vkGetFenceWin32HandleKHR{ nullptr }
  , vkGetMemoryWin32HandleKHR{ nullptr }
  , vkGetMemoryWin32HandleNV{ nullptr }
  , vkGetMemoryWin32HandlePropertiesKHR{ nullptr }
  , vkGetSemaphoreWin32HandleKHR{ nullptr }
  , vkImportFenceWin32HandleKHR{ nullptr }
  , vkImportSemaphoreWin32HandleKHR{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
#endif
{
  std::cout << "sdlxvulkan::Device_Functions::Device_Functions()" << std::endl;
}


// Construct using the supplied Global_Functions::vkCreateInstance function,
// using the supplied VkInstance. The instance is not stored here. Only
// functions that relate to the version and extensions that the instance was
// created with will work.
sdlxvulkan::Device_Functions::Device_Functions(VkDevice a_device, Instance_Functions const& a_instance_functions) :// Core Functions:
   vkAllocateCommandBuffers{ reinterpret_cast<PFN_vkAllocateCommandBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateCommandBuffers")) }
  , vkAllocateDescriptorSets{ reinterpret_cast<PFN_vkAllocateDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateDescriptorSets")) }
  , vkAllocateMemory{ reinterpret_cast<PFN_vkAllocateMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateMemory")) }
  , vkBeginCommandBuffer{ reinterpret_cast<PFN_vkBeginCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBeginCommandBuffer")) }
  , vkBindBufferMemory{ reinterpret_cast<PFN_vkBindBufferMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory")) }
  , vkBindBufferMemory2{ reinterpret_cast<PFN_vkBindBufferMemory2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory2")) }
  , vkBindImageMemory{ reinterpret_cast<PFN_vkBindImageMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory")) }
  , vkBindImageMemory2{ reinterpret_cast<PFN_vkBindImageMemory2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory2")) }
  , vkCmdBeginQuery{ reinterpret_cast<PFN_vkCmdBeginQuery>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginQuery")) }
  , vkCmdBeginRenderPass{ reinterpret_cast<PFN_vkCmdBeginRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginRenderPass")) }
  , vkCmdBindDescriptorSets{ reinterpret_cast<PFN_vkCmdBindDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindDescriptorSets")) }
  , vkCmdBindIndexBuffer{ reinterpret_cast<PFN_vkCmdBindIndexBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindIndexBuffer")) }
  , vkCmdBindPipeline{ reinterpret_cast<PFN_vkCmdBindPipeline>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindPipeline")) }
  , vkCmdBindVertexBuffers{ reinterpret_cast<PFN_vkCmdBindVertexBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindVertexBuffers")) }
  , vkCmdBlitImage{ reinterpret_cast<PFN_vkCmdBlitImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBlitImage")) }
  , vkCmdClearAttachments{ reinterpret_cast<PFN_vkCmdClearAttachments>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearAttachments")) }
  , vkCmdClearColorImage{ reinterpret_cast<PFN_vkCmdClearColorImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearColorImage")) }
  , vkCmdClearDepthStencilImage{ reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearDepthStencilImage")) }
  , vkCmdCopyBuffer{ reinterpret_cast<PFN_vkCmdCopyBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyBuffer")) }
  , vkCmdCopyBufferToImage{ reinterpret_cast<PFN_vkCmdCopyBufferToImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyBufferToImage")) }
  , vkCmdCopyImage{ reinterpret_cast<PFN_vkCmdCopyImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyImage")) }
  , vkCmdCopyImageToBuffer{ reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyImageToBuffer")) }
  , vkCmdCopyQueryPoolResults{ reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyQueryPoolResults")) }
  , vkCmdDispatch{ reinterpret_cast<PFN_vkCmdDispatch>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatch")) }
  , vkCmdDispatchBase{ reinterpret_cast<PFN_vkCmdDispatchBase>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchBase")) }
  , vkCmdDispatchIndirect{ reinterpret_cast<PFN_vkCmdDispatchIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchIndirect")) }
  , vkCmdDraw{ reinterpret_cast<PFN_vkCmdDraw>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDraw")) }
  , vkCmdDrawIndexed{ reinterpret_cast<PFN_vkCmdDrawIndexed>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexed")) }
  , vkCmdDrawIndexedIndirect{ reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexedIndirect")) }
  , vkCmdDrawIndirect{ reinterpret_cast<PFN_vkCmdDrawIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndirect")) }
  , vkCmdEndQuery{ reinterpret_cast<PFN_vkCmdEndQuery>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndQuery")) }
  , vkCmdEndRenderPass{ reinterpret_cast<PFN_vkCmdEndRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndRenderPass")) }
  , vkCmdExecuteCommands{ reinterpret_cast<PFN_vkCmdExecuteCommands>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdExecuteCommands")) }
  , vkCmdFillBuffer{ reinterpret_cast<PFN_vkCmdFillBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdFillBuffer")) }
  , vkCmdNextSubpass{ reinterpret_cast<PFN_vkCmdNextSubpass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdNextSubpass")) }
  , vkCmdPipelineBarrier{ reinterpret_cast<PFN_vkCmdPipelineBarrier>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPipelineBarrier")) }
  , vkCmdPushConstants{ reinterpret_cast<PFN_vkCmdPushConstants>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushConstants")) }
  , vkCmdResetEvent{ reinterpret_cast<PFN_vkCmdResetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResetEvent")) }
  , vkCmdResetQueryPool{ reinterpret_cast<PFN_vkCmdResetQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResetQueryPool")) }
  , vkCmdResolveImage{ reinterpret_cast<PFN_vkCmdResolveImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResolveImage")) }
  , vkCmdSetBlendConstants{ reinterpret_cast<PFN_vkCmdSetBlendConstants>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetBlendConstants")) }
  , vkCmdSetDepthBias{ reinterpret_cast<PFN_vkCmdSetDepthBias>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDepthBias")) }
  , vkCmdSetDepthBounds{ reinterpret_cast<PFN_vkCmdSetDepthBounds>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDepthBounds")) }
  , vkCmdSetDeviceMask{ reinterpret_cast<PFN_vkCmdSetDeviceMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDeviceMask")) }
  , vkCmdSetEvent{ reinterpret_cast<PFN_vkCmdSetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetEvent")) }
  , vkCmdSetLineWidth{ reinterpret_cast<PFN_vkCmdSetLineWidth>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetLineWidth")) }
  , vkCmdSetScissor{ reinterpret_cast<PFN_vkCmdSetScissor>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetScissor")) }
  , vkCmdSetStencilCompareMask{ reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilCompareMask")) }
  , vkCmdSetStencilReference{ reinterpret_cast<PFN_vkCmdSetStencilReference>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilReference")) }
  , vkCmdSetStencilWriteMask{ reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilWriteMask")) }
  , vkCmdSetViewport{ reinterpret_cast<PFN_vkCmdSetViewport>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetViewport")) }
  , vkCmdUpdateBuffer{ reinterpret_cast<PFN_vkCmdUpdateBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdUpdateBuffer")) }
  , vkCmdWaitEvents{ reinterpret_cast<PFN_vkCmdWaitEvents>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWaitEvents")) }
  , vkCmdWriteTimestamp{ reinterpret_cast<PFN_vkCmdWriteTimestamp>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWriteTimestamp")) }
  , vkCreateBuffer{ reinterpret_cast<PFN_vkCreateBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateBuffer")) }
  , vkCreateBufferView{ reinterpret_cast<PFN_vkCreateBufferView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateBufferView")) }
  , vkCreateCommandPool{ reinterpret_cast<PFN_vkCreateCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateCommandPool")) }
  , vkCreateComputePipelines{ reinterpret_cast<PFN_vkCreateComputePipelines>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateComputePipelines")) }
  , vkCreateDescriptorPool{ reinterpret_cast<PFN_vkCreateDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorPool")) }
  , vkCreateDescriptorSetLayout{ reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorSetLayout")) }
  , vkCreateDescriptorUpdateTemplate{ reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorUpdateTemplate")) }
  , vkCreateEvent{ reinterpret_cast<PFN_vkCreateEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateEvent")) }
  , vkCreateFence{ reinterpret_cast<PFN_vkCreateFence>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateFence")) }
  , vkCreateFramebuffer{ reinterpret_cast<PFN_vkCreateFramebuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateFramebuffer")) }
  , vkCreateGraphicsPipelines{ reinterpret_cast<PFN_vkCreateGraphicsPipelines>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateGraphicsPipelines")) }
  , vkCreateImage{ reinterpret_cast<PFN_vkCreateImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateImage")) }
  , vkCreateImageView{ reinterpret_cast<PFN_vkCreateImageView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateImageView")) }
  , vkCreatePipelineCache{ reinterpret_cast<PFN_vkCreatePipelineCache>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreatePipelineCache")) }
  , vkCreatePipelineLayout{ reinterpret_cast<PFN_vkCreatePipelineLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreatePipelineLayout")) }
  , vkCreateQueryPool{ reinterpret_cast<PFN_vkCreateQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateQueryPool")) }
  , vkCreateRenderPass{ reinterpret_cast<PFN_vkCreateRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateRenderPass")) }
  , vkCreateSampler{ reinterpret_cast<PFN_vkCreateSampler>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSampler")) }
  , vkCreateSamplerYcbcrConversion{ reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSamplerYcbcrConversion")) }
  , vkCreateSemaphore{ reinterpret_cast<PFN_vkCreateSemaphore>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSemaphore")) }
  , vkCreateShaderModule{ reinterpret_cast<PFN_vkCreateShaderModule>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateShaderModule")) }
  , vkDestroyBuffer{ reinterpret_cast<PFN_vkDestroyBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyBuffer")) }
  , vkDestroyBufferView{ reinterpret_cast<PFN_vkDestroyBufferView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyBufferView")) }
  , vkDestroyCommandPool{ reinterpret_cast<PFN_vkDestroyCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyCommandPool")) }
  , vkDestroyDescriptorPool{ reinterpret_cast<PFN_vkDestroyDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorPool")) }
  , vkDestroyDescriptorSetLayout{ reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorSetLayout")) }
  , vkDestroyDescriptorUpdateTemplate{ reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorUpdateTemplate")) }
  , vkDestroyDevice{ reinterpret_cast<PFN_vkDestroyDevice>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDevice")) }
  , vkDestroyEvent{ reinterpret_cast<PFN_vkDestroyEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyEvent")) }
  , vkDestroyFence{ reinterpret_cast<PFN_vkDestroyFence>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyFence")) }
  , vkDestroyFramebuffer{ reinterpret_cast<PFN_vkDestroyFramebuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyFramebuffer")) }
  , vkDestroyImage{ reinterpret_cast<PFN_vkDestroyImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyImage")) }
  , vkDestroyImageView{ reinterpret_cast<PFN_vkDestroyImageView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyImageView")) }
  , vkDestroyPipeline{ reinterpret_cast<PFN_vkDestroyPipeline>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipeline")) }
  , vkDestroyPipelineCache{ reinterpret_cast<PFN_vkDestroyPipelineCache>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipelineCache")) }
  , vkDestroyPipelineLayout{ reinterpret_cast<PFN_vkDestroyPipelineLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipelineLayout")) }
  , vkDestroyQueryPool{ reinterpret_cast<PFN_vkDestroyQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyQueryPool")) }
  , vkDestroyRenderPass{ reinterpret_cast<PFN_vkDestroyRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyRenderPass")) }
  , vkDestroySampler{ reinterpret_cast<PFN_vkDestroySampler>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySampler")) }
  , vkDestroySamplerYcbcrConversion{ reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySamplerYcbcrConversion")) }
  , vkDestroySemaphore{ reinterpret_cast<PFN_vkDestroySemaphore>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySemaphore")) }
  , vkDestroyShaderModule{ reinterpret_cast<PFN_vkDestroyShaderModule>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyShaderModule")) }
  , vkDeviceWaitIdle{ reinterpret_cast<PFN_vkDeviceWaitIdle>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDeviceWaitIdle")) }
  , vkEndCommandBuffer{ reinterpret_cast<PFN_vkEndCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkEndCommandBuffer")) }
  , vkFlushMappedMemoryRanges{ reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFlushMappedMemoryRanges")) }
  , vkFreeCommandBuffers{ reinterpret_cast<PFN_vkFreeCommandBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeCommandBuffers")) }
  , vkFreeDescriptorSets{ reinterpret_cast<PFN_vkFreeDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeDescriptorSets")) }
  , vkFreeMemory{ reinterpret_cast<PFN_vkFreeMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeMemory")) }
  , vkGetBufferMemoryRequirements{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements")) }
  , vkGetBufferMemoryRequirements2{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements2")) }
  , vkGetDescriptorSetLayoutSupport{ reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDescriptorSetLayoutSupport")) }
  , vkGetDeviceGroupPeerMemoryFeatures{ reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPeerMemoryFeatures")) }
  , vkGetDeviceMemoryCommitment{ reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceMemoryCommitment")) }
  , vkGetDeviceQueue{ reinterpret_cast<PFN_vkGetDeviceQueue>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceQueue")) }
  , vkGetDeviceQueue2{ reinterpret_cast<PFN_vkGetDeviceQueue2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceQueue2")) }
  , vkGetEventStatus{ reinterpret_cast<PFN_vkGetEventStatus>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetEventStatus")) }
  , vkGetFenceStatus{ reinterpret_cast<PFN_vkGetFenceStatus>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceStatus")) }
  , vkGetImageMemoryRequirements{ reinterpret_cast<PFN_vkGetImageMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements")) }
  , vkGetImageMemoryRequirements2{ reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements2")) }
  , vkGetImageSparseMemoryRequirements{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements")) }
  , vkGetImageSparseMemoryRequirements2{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements2")) }
  , vkGetImageSubresourceLayout{ reinterpret_cast<PFN_vkGetImageSubresourceLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSubresourceLayout")) }
  , vkGetPipelineCacheData{ reinterpret_cast<PFN_vkGetPipelineCacheData>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetPipelineCacheData")) }
  , vkGetQueryPoolResults{ reinterpret_cast<PFN_vkGetQueryPoolResults>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetQueryPoolResults")) }
  , vkGetRenderAreaGranularity{ reinterpret_cast<PFN_vkGetRenderAreaGranularity>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetRenderAreaGranularity")) }
  , vkInvalidateMappedMemoryRanges{ reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkInvalidateMappedMemoryRanges")) }
  , vkMapMemory{ reinterpret_cast<PFN_vkMapMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMapMemory")) }
  , vkMergePipelineCaches{ reinterpret_cast<PFN_vkMergePipelineCaches>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMergePipelineCaches")) }
  , vkQueueBindSparse{ reinterpret_cast<PFN_vkQueueBindSparse>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueBindSparse")) }
  , vkQueueSubmit{ reinterpret_cast<PFN_vkQueueSubmit>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueSubmit")) }
  , vkQueueWaitIdle{ reinterpret_cast<PFN_vkQueueWaitIdle>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueWaitIdle")) }
  , vkResetCommandBuffer{ reinterpret_cast<PFN_vkResetCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetCommandBuffer")) }
  , vkResetCommandPool{ reinterpret_cast<PFN_vkResetCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetCommandPool")) }
  , vkResetDescriptorPool{ reinterpret_cast<PFN_vkResetDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetDescriptorPool")) }
  , vkResetEvent{ reinterpret_cast<PFN_vkResetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetEvent")) }
  , vkResetFences{ reinterpret_cast<PFN_vkResetFences>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetFences")) }
  , vkSetEvent{ reinterpret_cast<PFN_vkSetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetEvent")) }
  , vkTrimCommandPool{ reinterpret_cast<PFN_vkTrimCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkTrimCommandPool")) }
  , vkUnmapMemory{ reinterpret_cast<PFN_vkUnmapMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUnmapMemory")) }
  , vkUpdateDescriptorSetWithTemplate{ reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSetWithTemplate")) }
  , vkUpdateDescriptorSets{ reinterpret_cast<PFN_vkUpdateDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSets")) }
  , vkWaitForFences{ reinterpret_cast<PFN_vkWaitForFences>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkWaitForFences")) }

  // Extension Functions:
  , vkAcquireNextImage2KHR{ reinterpret_cast<PFN_vkAcquireNextImage2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAcquireNextImage2KHR")) }
  , vkAcquireNextImageKHR{ reinterpret_cast<PFN_vkAcquireNextImageKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAcquireNextImageKHR")) }
  , vkBindBufferMemory2KHR{ reinterpret_cast<PFN_vkBindBufferMemory2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory2KHR")) }
  , vkBindImageMemory2KHR{ reinterpret_cast<PFN_vkBindImageMemory2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory2KHR")) }
  , vkCmdBeginDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginDebugUtilsLabelEXT")) }
  , vkCmdDebugMarkerBeginEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerBeginEXT")) }
  , vkCmdDebugMarkerEndEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerEndEXT")) }
  , vkCmdDebugMarkerInsertEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerInsertEXT")) }
  , vkCmdDispatchBaseKHR{ reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchBaseKHR")) }
  , vkCmdDrawIndexedIndirectCountAMD{ reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexedIndirectCountAMD")) }
  , vkCmdDrawIndirectCountAMD{ reinterpret_cast<PFN_vkCmdDrawIndirectCountAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndirectCountAMD")) }
  , vkCmdEndDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndDebugUtilsLabelEXT")) }
  , vkCmdInsertDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdInsertDebugUtilsLabelEXT")) }
  , vkCmdProcessCommandsNVX{ reinterpret_cast<PFN_vkCmdProcessCommandsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdProcessCommandsNVX")) }
  , vkCmdPushDescriptorSetKHR{ reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushDescriptorSetKHR")) }
  , vkCmdPushDescriptorSetWithTemplateKHR{ reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushDescriptorSetWithTemplateKHR")) }
  , vkCmdReserveSpaceForCommandsNVX{ reinterpret_cast<PFN_vkCmdReserveSpaceForCommandsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdReserveSpaceForCommandsNVX")) }
  , vkCmdSetDeviceMaskKHR{ reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDeviceMaskKHR")) }
  , vkCmdSetDiscardRectangleEXT{ reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDiscardRectangleEXT")) }
  , vkCmdSetSampleLocationsEXT{ reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetSampleLocationsEXT")) }
  , vkCmdWriteBufferMarkerAMD{ reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWriteBufferMarkerAMD")) }
  , vkCreateDescriptorUpdateTemplateKHR{ reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorUpdateTemplateKHR")) }
  , vkCreateIndirectCommandsLayoutNVX{ reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateIndirectCommandsLayoutNVX")) }
  , vkCreateObjectTableNVX{ reinterpret_cast<PFN_vkCreateObjectTableNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateObjectTableNVX")) }
  , vkCreateSamplerYcbcrConversionKHR{ reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSamplerYcbcrConversionKHR")) }
  , vkCreateSharedSwapchainsKHR{ reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSharedSwapchainsKHR")) }
  , vkCreateSwapchainKHR{ reinterpret_cast<PFN_vkCreateSwapchainKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSwapchainKHR")) }
  , vkCreateValidationCacheEXT{ reinterpret_cast<PFN_vkCreateValidationCacheEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateValidationCacheEXT")) }
  , vkDebugMarkerSetObjectNameEXT{ reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDebugMarkerSetObjectNameEXT")) }
  , vkDebugMarkerSetObjectTagEXT{ reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDebugMarkerSetObjectTagEXT")) }
  , vkDestroyDescriptorUpdateTemplateKHR{ reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorUpdateTemplateKHR")) }
  , vkDestroyIndirectCommandsLayoutNVX{ reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyIndirectCommandsLayoutNVX")) }
  , vkDestroyObjectTableNVX{ reinterpret_cast<PFN_vkDestroyObjectTableNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyObjectTableNVX")) }
  , vkDestroySamplerYcbcrConversionKHR{ reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySamplerYcbcrConversionKHR")) }
  , vkDestroySwapchainKHR{ reinterpret_cast<PFN_vkDestroySwapchainKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySwapchainKHR")) }
  , vkDestroyValidationCacheEXT{ reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyValidationCacheEXT")) }
  , vkDisplayPowerControlEXT{ reinterpret_cast<PFN_vkDisplayPowerControlEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDisplayPowerControlEXT")) }
  , vkGetBufferMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements2KHR")) }
  , vkGetDescriptorSetLayoutSupportKHR{ reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDescriptorSetLayoutSupportKHR")) }
  , vkGetDeviceGroupPeerMemoryFeaturesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPeerMemoryFeaturesKHR")) }
  , vkGetDeviceGroupPresentCapabilitiesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPresentCapabilitiesKHR")) }
  , vkGetDeviceGroupSurfacePresentModesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupSurfacePresentModesKHR")) }
  , vkGetFenceFdKHR{ reinterpret_cast<PFN_vkGetFenceFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceFdKHR")) }
  , vkGetImageMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements2KHR")) }
  , vkGetImageSparseMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements2KHR")) }
  , vkGetMemoryFdKHR{ reinterpret_cast<PFN_vkGetMemoryFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryFdKHR")) }
  , vkGetMemoryFdPropertiesKHR{ reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryFdPropertiesKHR")) }
  , vkGetMemoryHostPointerPropertiesEXT{ reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryHostPointerPropertiesEXT")) }
  , vkGetPastPresentationTimingGOOGLE{ reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetPastPresentationTimingGOOGLE")) }
  , vkGetRefreshCycleDurationGOOGLE{ reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetRefreshCycleDurationGOOGLE")) }
  , vkGetSemaphoreFdKHR{ reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSemaphoreFdKHR")) }
  , vkGetShaderInfoAMD{ reinterpret_cast<PFN_vkGetShaderInfoAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetShaderInfoAMD")) }
  , vkGetSwapchainCounterEXT{ reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainCounterEXT")) }
  , vkGetSwapchainImagesKHR{ reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainImagesKHR")) }
  , vkGetSwapchainStatusKHR{ reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainStatusKHR")) }
  , vkGetValidationCacheDataEXT{ reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetValidationCacheDataEXT")) }
  , vkImportFenceFdKHR{ reinterpret_cast<PFN_vkImportFenceFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportFenceFdKHR")) }
  , vkImportSemaphoreFdKHR{ reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportSemaphoreFdKHR")) }
  , vkMergeValidationCachesEXT{ reinterpret_cast<PFN_vkMergeValidationCachesEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMergeValidationCachesEXT")) }
  , vkQueueBeginDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueBeginDebugUtilsLabelEXT")) }
  , vkQueueEndDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueEndDebugUtilsLabelEXT")) }
  , vkQueueInsertDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueInsertDebugUtilsLabelEXT")) }
  , vkQueuePresentKHR{ reinterpret_cast<PFN_vkQueuePresentKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueuePresentKHR")) }
  , vkRegisterDeviceEventEXT{ reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterDeviceEventEXT")) }
  , vkRegisterDisplayEventEXT{ reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterDisplayEventEXT")) }
  , vkRegisterObjectsNVX{ reinterpret_cast<PFN_vkRegisterObjectsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterObjectsNVX")) }
  , vkSetDebugUtilsObjectNameEXT{ reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetDebugUtilsObjectNameEXT")) }
  , vkSetDebugUtilsObjectTagEXT{ reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetDebugUtilsObjectTagEXT")) }
  , vkSetHdrMetadataEXT{ reinterpret_cast<PFN_vkSetHdrMetadataEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetHdrMetadataEXT")) }
  , vkTrimCommandPoolKHR{ reinterpret_cast<PFN_vkTrimCommandPoolKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkTrimCommandPoolKHR")) }
  , vkUnregisterObjectsNVX{ reinterpret_cast<PFN_vkUnregisterObjectsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUnregisterObjectsNVX")) }
  , vkUpdateDescriptorSetWithTemplateKHR{ reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSetWithTemplateKHR")) }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , vkGetAndroidHardwareBufferPropertiesANDROID{ reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetAndroidHardwareBufferPropertiesANDROID")) }
  , vkGetMemoryAndroidHardwareBufferANDROID{ reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryAndroidHardwareBufferANDROID")) }
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Functions:
  , vkCmdSetViewportWScalingNV{ reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetViewportWScalingNV")) }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , vkGetFenceWin32HandleKHR{ reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceWin32HandleKHR")) }
  , vkGetMemoryWin32HandleKHR{ reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandleKHR")) }
  , vkGetMemoryWin32HandleNV{ reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandleNV")) }
  , vkGetMemoryWin32HandlePropertiesKHR{ reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandlePropertiesKHR")) }
  , vkGetSemaphoreWin32HandleKHR{ reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSemaphoreWin32HandleKHR")) }
  , vkImportFenceWin32HandleKHR{ reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportFenceWin32HandleKHR")) }
  , vkImportSemaphoreWin32HandleKHR{ reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportSemaphoreWin32HandleKHR")) }
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Functions:
#endif
{
  std::cout << "sdlxvulkan::Device_Functions::Device_Functions( data )" << std::endl;
}