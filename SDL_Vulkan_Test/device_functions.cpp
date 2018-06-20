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
   m_vkAllocateCommandBuffers{ nullptr }
  , m_vkAllocateDescriptorSets{ nullptr }
  , m_vkAllocateMemory{ nullptr }
  , m_vkBeginCommandBuffer{ nullptr }
  , m_vkBindBufferMemory{ nullptr }
  , m_vkBindBufferMemory2{ nullptr }
  , m_vkBindImageMemory{ nullptr }
  , m_vkBindImageMemory2{ nullptr }
  , m_vkCmdBeginQuery{ nullptr }
  , m_vkCmdBeginRenderPass{ nullptr }
  , m_vkCmdBindDescriptorSets{ nullptr }
  , m_vkCmdBindIndexBuffer{ nullptr }
  , m_vkCmdBindPipeline{ nullptr }
  , m_vkCmdBindVertexBuffers{ nullptr }
  , m_vkCmdBlitImage{ nullptr }
  , m_vkCmdClearAttachments{ nullptr }
  , m_vkCmdClearColorImage{ nullptr }
  , m_vkCmdClearDepthStencilImage{ nullptr }
  , m_vkCmdCopyBuffer{ nullptr }
  , m_vkCmdCopyBufferToImage{ nullptr }
  , m_vkCmdCopyImage{ nullptr }
  , m_vkCmdCopyImageToBuffer{ nullptr }
  , m_vkCmdCopyQueryPoolResults{ nullptr }
  , m_vkCmdDispatch{ nullptr }
  , m_vkCmdDispatchBase{ nullptr }
  , m_vkCmdDispatchIndirect{ nullptr }
  , m_vkCmdDraw{ nullptr }
  , m_vkCmdDrawIndexed{ nullptr }
  , m_vkCmdDrawIndexedIndirect{ nullptr }
  , m_vkCmdDrawIndirect{ nullptr }
  , m_vkCmdEndQuery{ nullptr }
  , m_vkCmdEndRenderPass{ nullptr }
  , m_vkCmdExecuteCommands{ nullptr }
  , m_vkCmdFillBuffer{ nullptr }
  , m_vkCmdNextSubpass{ nullptr }
  , m_vkCmdPipelineBarrier{ nullptr }
  , m_vkCmdPushConstants{ nullptr }
  , m_vkCmdResetEvent{ nullptr }
  , m_vkCmdResetQueryPool{ nullptr }
  , m_vkCmdResolveImage{ nullptr }
  , m_vkCmdSetBlendConstants{ nullptr }
  , m_vkCmdSetDepthBias{ nullptr }
  , m_vkCmdSetDepthBounds{ nullptr }
  , m_vkCmdSetDeviceMask{ nullptr }
  , m_vkCmdSetEvent{ nullptr }
  , m_vkCmdSetLineWidth{ nullptr }
  , m_vkCmdSetScissor{ nullptr }
  , m_vkCmdSetStencilCompareMask{ nullptr }
  , m_vkCmdSetStencilReference{ nullptr }
  , m_vkCmdSetStencilWriteMask{ nullptr }
  , m_vkCmdSetViewport{ nullptr }
  , m_vkCmdUpdateBuffer{ nullptr }
  , m_vkCmdWaitEvents{ nullptr }
  , m_vkCmdWriteTimestamp{ nullptr }
  , m_vkCreateBuffer{ nullptr }
  , m_vkCreateBufferView{ nullptr }
  , m_vkCreateCommandPool{ nullptr }
  , m_vkCreateComputePipelines{ nullptr }
  , m_vkCreateDescriptorPool{ nullptr }
  , m_vkCreateDescriptorSetLayout{ nullptr }
  , m_vkCreateDescriptorUpdateTemplate{ nullptr }
  , m_vkCreateEvent{ nullptr }
  , m_vkCreateFence{ nullptr }
  , m_vkCreateFramebuffer{ nullptr }
  , m_vkCreateGraphicsPipelines{ nullptr }
  , m_vkCreateImage{ nullptr }
  , m_vkCreateImageView{ nullptr }
  , m_vkCreatePipelineCache{ nullptr }
  , m_vkCreatePipelineLayout{ nullptr }
  , m_vkCreateQueryPool{ nullptr }
  , m_vkCreateRenderPass{ nullptr }
  , m_vkCreateSampler{ nullptr }
  , m_vkCreateSamplerYcbcrConversion{ nullptr }
  , m_vkCreateSemaphore{ nullptr }
  , m_vkCreateShaderModule{ nullptr }
  , m_vkDestroyBuffer{ nullptr }
  , m_vkDestroyBufferView{ nullptr }
  , m_vkDestroyCommandPool{ nullptr }
  , m_vkDestroyDescriptorPool{ nullptr }
  , m_vkDestroyDescriptorSetLayout{ nullptr }
  , m_vkDestroyDescriptorUpdateTemplate{ nullptr }
  , m_vkDestroyDevice{ nullptr }
  , m_vkDestroyEvent{ nullptr }
  , m_vkDestroyFence{ nullptr }
  , m_vkDestroyFramebuffer{ nullptr }
  , m_vkDestroyImage{ nullptr }
  , m_vkDestroyImageView{ nullptr }
  , m_vkDestroyPipeline{ nullptr }
  , m_vkDestroyPipelineCache{ nullptr }
  , m_vkDestroyPipelineLayout{ nullptr }
  , m_vkDestroyQueryPool{ nullptr }
  , m_vkDestroyRenderPass{ nullptr }
  , m_vkDestroySampler{ nullptr }
  , m_vkDestroySamplerYcbcrConversion{ nullptr }
  , m_vkDestroySemaphore{ nullptr }
  , m_vkDestroyShaderModule{ nullptr }
  , m_vkDeviceWaitIdle{ nullptr }
  , m_vkEndCommandBuffer{ nullptr }
  , m_vkFlushMappedMemoryRanges{ nullptr }
  , m_vkFreeCommandBuffers{ nullptr }
  , m_vkFreeDescriptorSets{ nullptr }
  , m_vkFreeMemory{ nullptr }
  , m_vkGetBufferMemoryRequirements{ nullptr }
  , m_vkGetBufferMemoryRequirements2{ nullptr }
  , m_vkGetDescriptorSetLayoutSupport{ nullptr }
  , m_vkGetDeviceGroupPeerMemoryFeatures{ nullptr }
  , m_vkGetDeviceMemoryCommitment{ nullptr }
  , m_vkGetDeviceQueue{ nullptr }
  , m_vkGetDeviceQueue2{ nullptr }
  , m_vkGetEventStatus{ nullptr }
  , m_vkGetFenceStatus{ nullptr }
  , m_vkGetImageMemoryRequirements{ nullptr }
  , m_vkGetImageMemoryRequirements2{ nullptr }
  , m_vkGetImageSparseMemoryRequirements{ nullptr }
  , m_vkGetImageSparseMemoryRequirements2{ nullptr }
  , m_vkGetImageSubresourceLayout{ nullptr }
  , m_vkGetPipelineCacheData{ nullptr }
  , m_vkGetQueryPoolResults{ nullptr }
  , m_vkGetRenderAreaGranularity{ nullptr }
  , m_vkInvalidateMappedMemoryRanges{ nullptr }
  , m_vkMapMemory{ nullptr }
  , m_vkMergePipelineCaches{ nullptr }
  , m_vkQueueBindSparse{ nullptr }
  , m_vkQueueSubmit{ nullptr }
  , m_vkQueueWaitIdle{ nullptr }
  , m_vkResetCommandBuffer{ nullptr }
  , m_vkResetCommandPool{ nullptr }
  , m_vkResetDescriptorPool{ nullptr }
  , m_vkResetEvent{ nullptr }
  , m_vkResetFences{ nullptr }
  , m_vkSetEvent{ nullptr }
  , m_vkTrimCommandPool{ nullptr }
  , m_vkUnmapMemory{ nullptr }
  , m_vkUpdateDescriptorSetWithTemplate{ nullptr }
  , m_vkUpdateDescriptorSets{ nullptr }
  , m_vkWaitForFences{ nullptr }

  // Extension Functions:
  , m_vkAcquireNextImage2KHR{ nullptr }
  , m_vkAcquireNextImageKHR{ nullptr }
  , m_vkBindBufferMemory2KHR{ nullptr }
  , m_vkBindImageMemory2KHR{ nullptr }
  , m_vkCmdBeginDebugUtilsLabelEXT{ nullptr }
  , m_vkCmdDebugMarkerBeginEXT{ nullptr }
  , m_vkCmdDebugMarkerEndEXT{ nullptr }
  , m_vkCmdDebugMarkerInsertEXT{ nullptr }
  , m_vkCmdDispatchBaseKHR{ nullptr }
  , m_vkCmdDrawIndexedIndirectCountAMD{ nullptr }
  , m_vkCmdDrawIndirectCountAMD{ nullptr }
  , m_vkCmdEndDebugUtilsLabelEXT{ nullptr }
  , m_vkCmdInsertDebugUtilsLabelEXT{ nullptr }
  , m_vkCmdProcessCommandsNVX{ nullptr }
  , m_vkCmdPushDescriptorSetKHR{ nullptr }
  , m_vkCmdPushDescriptorSetWithTemplateKHR{ nullptr }
  , m_vkCmdReserveSpaceForCommandsNVX{ nullptr }
  , m_vkCmdSetDeviceMaskKHR{ nullptr }
  , m_vkCmdSetDiscardRectangleEXT{ nullptr }
  , m_vkCmdSetSampleLocationsEXT{ nullptr }
  , m_vkCmdWriteBufferMarkerAMD{ nullptr }
  , m_vkCreateDescriptorUpdateTemplateKHR{ nullptr }
  , m_vkCreateIndirectCommandsLayoutNVX{ nullptr }
  , m_vkCreateObjectTableNVX{ nullptr }
  , m_vkCreateSamplerYcbcrConversionKHR{ nullptr }
  , m_vkCreateSharedSwapchainsKHR{ nullptr }
  , m_vkCreateSwapchainKHR{ nullptr }
  , m_vkCreateValidationCacheEXT{ nullptr }
  , m_vkDebugMarkerSetObjectNameEXT{ nullptr }
  , m_vkDebugMarkerSetObjectTagEXT{ nullptr }
  , m_vkDestroyDescriptorUpdateTemplateKHR{ nullptr }
  , m_vkDestroyIndirectCommandsLayoutNVX{ nullptr }
  , m_vkDestroyObjectTableNVX{ nullptr }
  , m_vkDestroySamplerYcbcrConversionKHR{ nullptr }
  , m_vkDestroySwapchainKHR{ nullptr }
  , m_vkDestroyValidationCacheEXT{ nullptr }
  , m_vkDisplayPowerControlEXT{ nullptr }
  , m_vkGetBufferMemoryRequirements2KHR{ nullptr }
  , m_vkGetDescriptorSetLayoutSupportKHR{ nullptr }
  , m_vkGetDeviceGroupPeerMemoryFeaturesKHR{ nullptr }
  , m_vkGetDeviceGroupPresentCapabilitiesKHR{ nullptr }
  , m_vkGetDeviceGroupSurfacePresentModesKHR{ nullptr }
  , m_vkGetFenceFdKHR{ nullptr }
  , m_vkGetImageMemoryRequirements2KHR{ nullptr }
  , m_vkGetImageSparseMemoryRequirements2KHR{ nullptr }
  , m_vkGetMemoryFdKHR{ nullptr }
  , m_vkGetMemoryFdPropertiesKHR{ nullptr }
  , m_vkGetMemoryHostPointerPropertiesEXT{ nullptr }
  , m_vkGetPastPresentationTimingGOOGLE{ nullptr }
  , m_vkGetRefreshCycleDurationGOOGLE{ nullptr }
  , m_vkGetSemaphoreFdKHR{ nullptr }
  , m_vkGetShaderInfoAMD{ nullptr }
  , m_vkGetSwapchainCounterEXT{ nullptr }
  , m_vkGetSwapchainImagesKHR{ nullptr }
  , m_vkGetSwapchainStatusKHR{ nullptr }
  , m_vkGetValidationCacheDataEXT{ nullptr }
  , m_vkImportFenceFdKHR{ nullptr }
  , m_vkImportSemaphoreFdKHR{ nullptr }
  , m_vkMergeValidationCachesEXT{ nullptr }
  , m_vkQueueBeginDebugUtilsLabelEXT{ nullptr }
  , m_vkQueueEndDebugUtilsLabelEXT{ nullptr }
  , m_vkQueueInsertDebugUtilsLabelEXT{ nullptr }
  , m_vkQueuePresentKHR{ nullptr }
  , m_vkRegisterDeviceEventEXT{ nullptr }
  , m_vkRegisterDisplayEventEXT{ nullptr }
  , m_vkRegisterObjectsNVX{ nullptr }
  , m_vkSetDebugUtilsObjectNameEXT{ nullptr }
  , m_vkSetDebugUtilsObjectTagEXT{ nullptr }
  , m_vkSetHdrMetadataEXT{ nullptr }
  , m_vkTrimCommandPoolKHR{ nullptr }
  , m_vkUnregisterObjectsNVX{ nullptr }
  , m_vkUpdateDescriptorSetWithTemplateKHR{ nullptr }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , m_vkGetAndroidHardwareBufferPropertiesANDROID{ nullptr }
  , m_vkGetMemoryAndroidHardwareBufferANDROID{ nullptr }
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
  , m_vkCmdSetViewportWScalingNV{ nullptr }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , m_vkGetFenceWin32HandleKHR{ nullptr }
  , m_vkGetMemoryWin32HandleKHR{ nullptr }
  , m_vkGetMemoryWin32HandleNV{ nullptr }
  , m_vkGetMemoryWin32HandlePropertiesKHR{ nullptr }
  , m_vkGetSemaphoreWin32HandleKHR{ nullptr }
  , m_vkImportFenceWin32HandleKHR{ nullptr }
  , m_vkImportSemaphoreWin32HandleKHR{ nullptr }
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
   m_vkAllocateCommandBuffers{ reinterpret_cast<PFN_vkAllocateCommandBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateCommandBuffers")) }
  , m_vkAllocateDescriptorSets{ reinterpret_cast<PFN_vkAllocateDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateDescriptorSets")) }
  , m_vkAllocateMemory{ reinterpret_cast<PFN_vkAllocateMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAllocateMemory")) }
  , m_vkBeginCommandBuffer{ reinterpret_cast<PFN_vkBeginCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBeginCommandBuffer")) }
  , m_vkBindBufferMemory{ reinterpret_cast<PFN_vkBindBufferMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory")) }
  , m_vkBindBufferMemory2{ reinterpret_cast<PFN_vkBindBufferMemory2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory2")) }
  , m_vkBindImageMemory{ reinterpret_cast<PFN_vkBindImageMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory")) }
  , m_vkBindImageMemory2{ reinterpret_cast<PFN_vkBindImageMemory2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory2")) }
  , m_vkCmdBeginQuery{ reinterpret_cast<PFN_vkCmdBeginQuery>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginQuery")) }
  , m_vkCmdBeginRenderPass{ reinterpret_cast<PFN_vkCmdBeginRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginRenderPass")) }
  , m_vkCmdBindDescriptorSets{ reinterpret_cast<PFN_vkCmdBindDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindDescriptorSets")) }
  , m_vkCmdBindIndexBuffer{ reinterpret_cast<PFN_vkCmdBindIndexBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindIndexBuffer")) }
  , m_vkCmdBindPipeline{ reinterpret_cast<PFN_vkCmdBindPipeline>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindPipeline")) }
  , m_vkCmdBindVertexBuffers{ reinterpret_cast<PFN_vkCmdBindVertexBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBindVertexBuffers")) }
  , m_vkCmdBlitImage{ reinterpret_cast<PFN_vkCmdBlitImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBlitImage")) }
  , m_vkCmdClearAttachments{ reinterpret_cast<PFN_vkCmdClearAttachments>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearAttachments")) }
  , m_vkCmdClearColorImage{ reinterpret_cast<PFN_vkCmdClearColorImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearColorImage")) }
  , m_vkCmdClearDepthStencilImage{ reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdClearDepthStencilImage")) }
  , m_vkCmdCopyBuffer{ reinterpret_cast<PFN_vkCmdCopyBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyBuffer")) }
  , m_vkCmdCopyBufferToImage{ reinterpret_cast<PFN_vkCmdCopyBufferToImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyBufferToImage")) }
  , m_vkCmdCopyImage{ reinterpret_cast<PFN_vkCmdCopyImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyImage")) }
  , m_vkCmdCopyImageToBuffer{ reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyImageToBuffer")) }
  , m_vkCmdCopyQueryPoolResults{ reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdCopyQueryPoolResults")) }
  , m_vkCmdDispatch{ reinterpret_cast<PFN_vkCmdDispatch>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatch")) }
  , m_vkCmdDispatchBase{ reinterpret_cast<PFN_vkCmdDispatchBase>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchBase")) }
  , m_vkCmdDispatchIndirect{ reinterpret_cast<PFN_vkCmdDispatchIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchIndirect")) }
  , m_vkCmdDraw{ reinterpret_cast<PFN_vkCmdDraw>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDraw")) }
  , m_vkCmdDrawIndexed{ reinterpret_cast<PFN_vkCmdDrawIndexed>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexed")) }
  , m_vkCmdDrawIndexedIndirect{ reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexedIndirect")) }
  , m_vkCmdDrawIndirect{ reinterpret_cast<PFN_vkCmdDrawIndirect>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndirect")) }
  , m_vkCmdEndQuery{ reinterpret_cast<PFN_vkCmdEndQuery>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndQuery")) }
  , m_vkCmdEndRenderPass{ reinterpret_cast<PFN_vkCmdEndRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndRenderPass")) }
  , m_vkCmdExecuteCommands{ reinterpret_cast<PFN_vkCmdExecuteCommands>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdExecuteCommands")) }
  , m_vkCmdFillBuffer{ reinterpret_cast<PFN_vkCmdFillBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdFillBuffer")) }
  , m_vkCmdNextSubpass{ reinterpret_cast<PFN_vkCmdNextSubpass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdNextSubpass")) }
  , m_vkCmdPipelineBarrier{ reinterpret_cast<PFN_vkCmdPipelineBarrier>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPipelineBarrier")) }
  , m_vkCmdPushConstants{ reinterpret_cast<PFN_vkCmdPushConstants>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushConstants")) }
  , m_vkCmdResetEvent{ reinterpret_cast<PFN_vkCmdResetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResetEvent")) }
  , m_vkCmdResetQueryPool{ reinterpret_cast<PFN_vkCmdResetQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResetQueryPool")) }
  , m_vkCmdResolveImage{ reinterpret_cast<PFN_vkCmdResolveImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdResolveImage")) }
  , m_vkCmdSetBlendConstants{ reinterpret_cast<PFN_vkCmdSetBlendConstants>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetBlendConstants")) }
  , m_vkCmdSetDepthBias{ reinterpret_cast<PFN_vkCmdSetDepthBias>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDepthBias")) }
  , m_vkCmdSetDepthBounds{ reinterpret_cast<PFN_vkCmdSetDepthBounds>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDepthBounds")) }
  , m_vkCmdSetDeviceMask{ reinterpret_cast<PFN_vkCmdSetDeviceMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDeviceMask")) }
  , m_vkCmdSetEvent{ reinterpret_cast<PFN_vkCmdSetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetEvent")) }
  , m_vkCmdSetLineWidth{ reinterpret_cast<PFN_vkCmdSetLineWidth>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetLineWidth")) }
  , m_vkCmdSetScissor{ reinterpret_cast<PFN_vkCmdSetScissor>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetScissor")) }
  , m_vkCmdSetStencilCompareMask{ reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilCompareMask")) }
  , m_vkCmdSetStencilReference{ reinterpret_cast<PFN_vkCmdSetStencilReference>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilReference")) }
  , m_vkCmdSetStencilWriteMask{ reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetStencilWriteMask")) }
  , m_vkCmdSetViewport{ reinterpret_cast<PFN_vkCmdSetViewport>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetViewport")) }
  , m_vkCmdUpdateBuffer{ reinterpret_cast<PFN_vkCmdUpdateBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdUpdateBuffer")) }
  , m_vkCmdWaitEvents{ reinterpret_cast<PFN_vkCmdWaitEvents>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWaitEvents")) }
  , m_vkCmdWriteTimestamp{ reinterpret_cast<PFN_vkCmdWriteTimestamp>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWriteTimestamp")) }
  , m_vkCreateBuffer{ reinterpret_cast<PFN_vkCreateBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateBuffer")) }
  , m_vkCreateBufferView{ reinterpret_cast<PFN_vkCreateBufferView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateBufferView")) }
  , m_vkCreateCommandPool{ reinterpret_cast<PFN_vkCreateCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateCommandPool")) }
  , m_vkCreateComputePipelines{ reinterpret_cast<PFN_vkCreateComputePipelines>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateComputePipelines")) }
  , m_vkCreateDescriptorPool{ reinterpret_cast<PFN_vkCreateDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorPool")) }
  , m_vkCreateDescriptorSetLayout{ reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorSetLayout")) }
  , m_vkCreateDescriptorUpdateTemplate{ reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorUpdateTemplate")) }
  , m_vkCreateEvent{ reinterpret_cast<PFN_vkCreateEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateEvent")) }
  , m_vkCreateFence{ reinterpret_cast<PFN_vkCreateFence>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateFence")) }
  , m_vkCreateFramebuffer{ reinterpret_cast<PFN_vkCreateFramebuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateFramebuffer")) }
  , m_vkCreateGraphicsPipelines{ reinterpret_cast<PFN_vkCreateGraphicsPipelines>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateGraphicsPipelines")) }
  , m_vkCreateImage{ reinterpret_cast<PFN_vkCreateImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateImage")) }
  , m_vkCreateImageView{ reinterpret_cast<PFN_vkCreateImageView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateImageView")) }
  , m_vkCreatePipelineCache{ reinterpret_cast<PFN_vkCreatePipelineCache>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreatePipelineCache")) }
  , m_vkCreatePipelineLayout{ reinterpret_cast<PFN_vkCreatePipelineLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreatePipelineLayout")) }
  , m_vkCreateQueryPool{ reinterpret_cast<PFN_vkCreateQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateQueryPool")) }
  , m_vkCreateRenderPass{ reinterpret_cast<PFN_vkCreateRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateRenderPass")) }
  , m_vkCreateSampler{ reinterpret_cast<PFN_vkCreateSampler>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSampler")) }
  , m_vkCreateSamplerYcbcrConversion{ reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSamplerYcbcrConversion")) }
  , m_vkCreateSemaphore{ reinterpret_cast<PFN_vkCreateSemaphore>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSemaphore")) }
  , m_vkCreateShaderModule{ reinterpret_cast<PFN_vkCreateShaderModule>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateShaderModule")) }
  , m_vkDestroyBuffer{ reinterpret_cast<PFN_vkDestroyBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyBuffer")) }
  , m_vkDestroyBufferView{ reinterpret_cast<PFN_vkDestroyBufferView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyBufferView")) }
  , m_vkDestroyCommandPool{ reinterpret_cast<PFN_vkDestroyCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyCommandPool")) }
  , m_vkDestroyDescriptorPool{ reinterpret_cast<PFN_vkDestroyDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorPool")) }
  , m_vkDestroyDescriptorSetLayout{ reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorSetLayout")) }
  , m_vkDestroyDescriptorUpdateTemplate{ reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorUpdateTemplate")) }
  , m_vkDestroyDevice{ reinterpret_cast<PFN_vkDestroyDevice>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDevice")) }
  , m_vkDestroyEvent{ reinterpret_cast<PFN_vkDestroyEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyEvent")) }
  , m_vkDestroyFence{ reinterpret_cast<PFN_vkDestroyFence>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyFence")) }
  , m_vkDestroyFramebuffer{ reinterpret_cast<PFN_vkDestroyFramebuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyFramebuffer")) }
  , m_vkDestroyImage{ reinterpret_cast<PFN_vkDestroyImage>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyImage")) }
  , m_vkDestroyImageView{ reinterpret_cast<PFN_vkDestroyImageView>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyImageView")) }
  , m_vkDestroyPipeline{ reinterpret_cast<PFN_vkDestroyPipeline>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipeline")) }
  , m_vkDestroyPipelineCache{ reinterpret_cast<PFN_vkDestroyPipelineCache>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipelineCache")) }
  , m_vkDestroyPipelineLayout{ reinterpret_cast<PFN_vkDestroyPipelineLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyPipelineLayout")) }
  , m_vkDestroyQueryPool{ reinterpret_cast<PFN_vkDestroyQueryPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyQueryPool")) }
  , m_vkDestroyRenderPass{ reinterpret_cast<PFN_vkDestroyRenderPass>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyRenderPass")) }
  , m_vkDestroySampler{ reinterpret_cast<PFN_vkDestroySampler>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySampler")) }
  , m_vkDestroySamplerYcbcrConversion{ reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySamplerYcbcrConversion")) }
  , m_vkDestroySemaphore{ reinterpret_cast<PFN_vkDestroySemaphore>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySemaphore")) }
  , m_vkDestroyShaderModule{ reinterpret_cast<PFN_vkDestroyShaderModule>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyShaderModule")) }
  , m_vkDeviceWaitIdle{ reinterpret_cast<PFN_vkDeviceWaitIdle>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDeviceWaitIdle")) }
  , m_vkEndCommandBuffer{ reinterpret_cast<PFN_vkEndCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkEndCommandBuffer")) }
  , m_vkFlushMappedMemoryRanges{ reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFlushMappedMemoryRanges")) }
  , m_vkFreeCommandBuffers{ reinterpret_cast<PFN_vkFreeCommandBuffers>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeCommandBuffers")) }
  , m_vkFreeDescriptorSets{ reinterpret_cast<PFN_vkFreeDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeDescriptorSets")) }
  , m_vkFreeMemory{ reinterpret_cast<PFN_vkFreeMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkFreeMemory")) }
  , m_vkGetBufferMemoryRequirements{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements")) }
  , m_vkGetBufferMemoryRequirements2{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements2")) }
  , m_vkGetDescriptorSetLayoutSupport{ reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDescriptorSetLayoutSupport")) }
  , m_vkGetDeviceGroupPeerMemoryFeatures{ reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPeerMemoryFeatures")) }
  , m_vkGetDeviceMemoryCommitment{ reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceMemoryCommitment")) }
  , m_vkGetDeviceQueue{ reinterpret_cast<PFN_vkGetDeviceQueue>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceQueue")) }
  , m_vkGetDeviceQueue2{ reinterpret_cast<PFN_vkGetDeviceQueue2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceQueue2")) }
  , m_vkGetEventStatus{ reinterpret_cast<PFN_vkGetEventStatus>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetEventStatus")) }
  , m_vkGetFenceStatus{ reinterpret_cast<PFN_vkGetFenceStatus>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceStatus")) }
  , m_vkGetImageMemoryRequirements{ reinterpret_cast<PFN_vkGetImageMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements")) }
  , m_vkGetImageMemoryRequirements2{ reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements2")) }
  , m_vkGetImageSparseMemoryRequirements{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements")) }
  , m_vkGetImageSparseMemoryRequirements2{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements2")) }
  , m_vkGetImageSubresourceLayout{ reinterpret_cast<PFN_vkGetImageSubresourceLayout>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSubresourceLayout")) }
  , m_vkGetPipelineCacheData{ reinterpret_cast<PFN_vkGetPipelineCacheData>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetPipelineCacheData")) }
  , m_vkGetQueryPoolResults{ reinterpret_cast<PFN_vkGetQueryPoolResults>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetQueryPoolResults")) }
  , m_vkGetRenderAreaGranularity{ reinterpret_cast<PFN_vkGetRenderAreaGranularity>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetRenderAreaGranularity")) }
  , m_vkInvalidateMappedMemoryRanges{ reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkInvalidateMappedMemoryRanges")) }
  , m_vkMapMemory{ reinterpret_cast<PFN_vkMapMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMapMemory")) }
  , m_vkMergePipelineCaches{ reinterpret_cast<PFN_vkMergePipelineCaches>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMergePipelineCaches")) }
  , m_vkQueueBindSparse{ reinterpret_cast<PFN_vkQueueBindSparse>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueBindSparse")) }
  , m_vkQueueSubmit{ reinterpret_cast<PFN_vkQueueSubmit>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueSubmit")) }
  , m_vkQueueWaitIdle{ reinterpret_cast<PFN_vkQueueWaitIdle>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueWaitIdle")) }
  , m_vkResetCommandBuffer{ reinterpret_cast<PFN_vkResetCommandBuffer>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetCommandBuffer")) }
  , m_vkResetCommandPool{ reinterpret_cast<PFN_vkResetCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetCommandPool")) }
  , m_vkResetDescriptorPool{ reinterpret_cast<PFN_vkResetDescriptorPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetDescriptorPool")) }
  , m_vkResetEvent{ reinterpret_cast<PFN_vkResetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetEvent")) }
  , m_vkResetFences{ reinterpret_cast<PFN_vkResetFences>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkResetFences")) }
  , m_vkSetEvent{ reinterpret_cast<PFN_vkSetEvent>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetEvent")) }
  , m_vkTrimCommandPool{ reinterpret_cast<PFN_vkTrimCommandPool>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkTrimCommandPool")) }
  , m_vkUnmapMemory{ reinterpret_cast<PFN_vkUnmapMemory>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUnmapMemory")) }
  , m_vkUpdateDescriptorSetWithTemplate{ reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSetWithTemplate")) }
  , m_vkUpdateDescriptorSets{ reinterpret_cast<PFN_vkUpdateDescriptorSets>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSets")) }
  , m_vkWaitForFences{ reinterpret_cast<PFN_vkWaitForFences>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkWaitForFences")) }

  // Extension Functions:
  , m_vkAcquireNextImage2KHR{ reinterpret_cast<PFN_vkAcquireNextImage2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAcquireNextImage2KHR")) }
  , m_vkAcquireNextImageKHR{ reinterpret_cast<PFN_vkAcquireNextImageKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkAcquireNextImageKHR")) }
  , m_vkBindBufferMemory2KHR{ reinterpret_cast<PFN_vkBindBufferMemory2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindBufferMemory2KHR")) }
  , m_vkBindImageMemory2KHR{ reinterpret_cast<PFN_vkBindImageMemory2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkBindImageMemory2KHR")) }
  , m_vkCmdBeginDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdBeginDebugUtilsLabelEXT")) }
  , m_vkCmdDebugMarkerBeginEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerBeginEXT")) }
  , m_vkCmdDebugMarkerEndEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerEndEXT")) }
  , m_vkCmdDebugMarkerInsertEXT{ reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDebugMarkerInsertEXT")) }
  , m_vkCmdDispatchBaseKHR{ reinterpret_cast<PFN_vkCmdDispatchBaseKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDispatchBaseKHR")) }
  , m_vkCmdDrawIndexedIndirectCountAMD{ reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCountAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndexedIndirectCountAMD")) }
  , m_vkCmdDrawIndirectCountAMD{ reinterpret_cast<PFN_vkCmdDrawIndirectCountAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdDrawIndirectCountAMD")) }
  , m_vkCmdEndDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdEndDebugUtilsLabelEXT")) }
  , m_vkCmdInsertDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdInsertDebugUtilsLabelEXT")) }
  , m_vkCmdProcessCommandsNVX{ reinterpret_cast<PFN_vkCmdProcessCommandsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdProcessCommandsNVX")) }
  , m_vkCmdPushDescriptorSetKHR{ reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushDescriptorSetKHR")) }
  , m_vkCmdPushDescriptorSetWithTemplateKHR{ reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdPushDescriptorSetWithTemplateKHR")) }
  , m_vkCmdReserveSpaceForCommandsNVX{ reinterpret_cast<PFN_vkCmdReserveSpaceForCommandsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdReserveSpaceForCommandsNVX")) }
  , m_vkCmdSetDeviceMaskKHR{ reinterpret_cast<PFN_vkCmdSetDeviceMaskKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDeviceMaskKHR")) }
  , m_vkCmdSetDiscardRectangleEXT{ reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetDiscardRectangleEXT")) }
  , m_vkCmdSetSampleLocationsEXT{ reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetSampleLocationsEXT")) }
  , m_vkCmdWriteBufferMarkerAMD{ reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdWriteBufferMarkerAMD")) }
  , m_vkCreateDescriptorUpdateTemplateKHR{ reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateDescriptorUpdateTemplateKHR")) }
  , m_vkCreateIndirectCommandsLayoutNVX{ reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateIndirectCommandsLayoutNVX")) }
  , m_vkCreateObjectTableNVX{ reinterpret_cast<PFN_vkCreateObjectTableNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateObjectTableNVX")) }
  , m_vkCreateSamplerYcbcrConversionKHR{ reinterpret_cast<PFN_vkCreateSamplerYcbcrConversionKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSamplerYcbcrConversionKHR")) }
  , m_vkCreateSharedSwapchainsKHR{ reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSharedSwapchainsKHR")) }
  , m_vkCreateSwapchainKHR{ reinterpret_cast<PFN_vkCreateSwapchainKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateSwapchainKHR")) }
  , m_vkCreateValidationCacheEXT{ reinterpret_cast<PFN_vkCreateValidationCacheEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCreateValidationCacheEXT")) }
  , m_vkDebugMarkerSetObjectNameEXT{ reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDebugMarkerSetObjectNameEXT")) }
  , m_vkDebugMarkerSetObjectTagEXT{ reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDebugMarkerSetObjectTagEXT")) }
  , m_vkDestroyDescriptorUpdateTemplateKHR{ reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyDescriptorUpdateTemplateKHR")) }
  , m_vkDestroyIndirectCommandsLayoutNVX{ reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyIndirectCommandsLayoutNVX")) }
  , m_vkDestroyObjectTableNVX{ reinterpret_cast<PFN_vkDestroyObjectTableNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyObjectTableNVX")) }
  , m_vkDestroySamplerYcbcrConversionKHR{ reinterpret_cast<PFN_vkDestroySamplerYcbcrConversionKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySamplerYcbcrConversionKHR")) }
  , m_vkDestroySwapchainKHR{ reinterpret_cast<PFN_vkDestroySwapchainKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroySwapchainKHR")) }
  , m_vkDestroyValidationCacheEXT{ reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDestroyValidationCacheEXT")) }
  , m_vkDisplayPowerControlEXT{ reinterpret_cast<PFN_vkDisplayPowerControlEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkDisplayPowerControlEXT")) }
  , m_vkGetBufferMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetBufferMemoryRequirements2KHR")) }
  , m_vkGetDescriptorSetLayoutSupportKHR{ reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupportKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDescriptorSetLayoutSupportKHR")) }
  , m_vkGetDeviceGroupPeerMemoryFeaturesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPeerMemoryFeaturesKHR")) }
  , m_vkGetDeviceGroupPresentCapabilitiesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupPresentCapabilitiesKHR")) }
  , m_vkGetDeviceGroupSurfacePresentModesKHR{ reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetDeviceGroupSurfacePresentModesKHR")) }
  , m_vkGetFenceFdKHR{ reinterpret_cast<PFN_vkGetFenceFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceFdKHR")) }
  , m_vkGetImageMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetImageMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageMemoryRequirements2KHR")) }
  , m_vkGetImageSparseMemoryRequirements2KHR{ reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2KHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetImageSparseMemoryRequirements2KHR")) }
  , m_vkGetMemoryFdKHR{ reinterpret_cast<PFN_vkGetMemoryFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryFdKHR")) }
  , m_vkGetMemoryFdPropertiesKHR{ reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryFdPropertiesKHR")) }
  , m_vkGetMemoryHostPointerPropertiesEXT{ reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryHostPointerPropertiesEXT")) }
  , m_vkGetPastPresentationTimingGOOGLE{ reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetPastPresentationTimingGOOGLE")) }
  , m_vkGetRefreshCycleDurationGOOGLE{ reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetRefreshCycleDurationGOOGLE")) }
  , m_vkGetSemaphoreFdKHR{ reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSemaphoreFdKHR")) }
  , m_vkGetShaderInfoAMD{ reinterpret_cast<PFN_vkGetShaderInfoAMD>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetShaderInfoAMD")) }
  , m_vkGetSwapchainCounterEXT{ reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainCounterEXT")) }
  , m_vkGetSwapchainImagesKHR{ reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainImagesKHR")) }
  , m_vkGetSwapchainStatusKHR{ reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSwapchainStatusKHR")) }
  , m_vkGetValidationCacheDataEXT{ reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetValidationCacheDataEXT")) }
  , m_vkImportFenceFdKHR{ reinterpret_cast<PFN_vkImportFenceFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportFenceFdKHR")) }
  , m_vkImportSemaphoreFdKHR{ reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportSemaphoreFdKHR")) }
  , m_vkMergeValidationCachesEXT{ reinterpret_cast<PFN_vkMergeValidationCachesEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkMergeValidationCachesEXT")) }
  , m_vkQueueBeginDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueBeginDebugUtilsLabelEXT")) }
  , m_vkQueueEndDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueEndDebugUtilsLabelEXT")) }
  , m_vkQueueInsertDebugUtilsLabelEXT{ reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueueInsertDebugUtilsLabelEXT")) }
  , m_vkQueuePresentKHR{ reinterpret_cast<PFN_vkQueuePresentKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkQueuePresentKHR")) }
  , m_vkRegisterDeviceEventEXT{ reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterDeviceEventEXT")) }
  , m_vkRegisterDisplayEventEXT{ reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterDisplayEventEXT")) }
  , m_vkRegisterObjectsNVX{ reinterpret_cast<PFN_vkRegisterObjectsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkRegisterObjectsNVX")) }
  , m_vkSetDebugUtilsObjectNameEXT{ reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetDebugUtilsObjectNameEXT")) }
  , m_vkSetDebugUtilsObjectTagEXT{ reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetDebugUtilsObjectTagEXT")) }
  , m_vkSetHdrMetadataEXT{ reinterpret_cast<PFN_vkSetHdrMetadataEXT>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkSetHdrMetadataEXT")) }
  , m_vkTrimCommandPoolKHR{ reinterpret_cast<PFN_vkTrimCommandPoolKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkTrimCommandPoolKHR")) }
  , m_vkUnregisterObjectsNVX{ reinterpret_cast<PFN_vkUnregisterObjectsNVX>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUnregisterObjectsNVX")) }
  , m_vkUpdateDescriptorSetWithTemplateKHR{ reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplateKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkUpdateDescriptorSetWithTemplateKHR")) }

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Functions:
  , m_vkGetAndroidHardwareBufferPropertiesANDROID{ reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetAndroidHardwareBufferPropertiesANDROID")) }
  , m_vkGetMemoryAndroidHardwareBufferANDROID{ reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryAndroidHardwareBufferANDROID")) }
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
  , m_vkCmdSetViewportWScalingNV{ reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkCmdSetViewportWScalingNV")) }
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Functions:
  , m_vkGetFenceWin32HandleKHR{ reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetFenceWin32HandleKHR")) }
  , m_vkGetMemoryWin32HandleKHR{ reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandleKHR")) }
  , m_vkGetMemoryWin32HandleNV{ reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandleNV")) }
  , m_vkGetMemoryWin32HandlePropertiesKHR{ reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetMemoryWin32HandlePropertiesKHR")) }
  , m_vkGetSemaphoreWin32HandleKHR{ reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkGetSemaphoreWin32HandleKHR")) }
  , m_vkImportFenceWin32HandleKHR{ reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportFenceWin32HandleKHR")) }
  , m_vkImportSemaphoreWin32HandleKHR{ reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(a_instance_functions.vkGetDeviceProcAddr(a_device, u8"vkImportSemaphoreWin32HandleKHR")) }
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