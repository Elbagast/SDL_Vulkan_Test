#ifndef SDLXVULKAN_DEVICE_FUNCTIONS_HPP
#define SDLXVULKAN_DEVICE_FUNCTIONS_HPP

#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

namespace sdlxvulkan
{
  class Instance_Functions;

  //---------------------------------------------------------------------------
  // Device_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions require a specific VkDevice to 
  // use. These cannot be aquired until an VkDevice is created so they are 
  // seperate from the instance functions.

  class Device_Functions
  {
  private:
    // Member Data
    //============================================================  
    // Core Functions:
    PFN_vkAllocateCommandBuffers m_vkAllocateCommandBuffers;
    PFN_vkAllocateDescriptorSets m_vkAllocateDescriptorSets;
    PFN_vkAllocateMemory m_vkAllocateMemory;
    PFN_vkBeginCommandBuffer m_vkBeginCommandBuffer;
    PFN_vkBindBufferMemory m_vkBindBufferMemory;
    PFN_vkBindBufferMemory2 m_vkBindBufferMemory2;
    PFN_vkBindImageMemory m_vkBindImageMemory;
    PFN_vkBindImageMemory2 m_vkBindImageMemory2;
    PFN_vkCmdBeginQuery m_vkCmdBeginQuery;
    PFN_vkCmdBeginRenderPass m_vkCmdBeginRenderPass;
    PFN_vkCmdBindDescriptorSets m_vkCmdBindDescriptorSets;
    PFN_vkCmdBindIndexBuffer m_vkCmdBindIndexBuffer;
    PFN_vkCmdBindPipeline m_vkCmdBindPipeline;
    PFN_vkCmdBindVertexBuffers m_vkCmdBindVertexBuffers;
    PFN_vkCmdBlitImage m_vkCmdBlitImage;
    PFN_vkCmdClearAttachments m_vkCmdClearAttachments;
    PFN_vkCmdClearColorImage m_vkCmdClearColorImage;
    PFN_vkCmdClearDepthStencilImage m_vkCmdClearDepthStencilImage;
    PFN_vkCmdCopyBuffer m_vkCmdCopyBuffer;
    PFN_vkCmdCopyBufferToImage m_vkCmdCopyBufferToImage;
    PFN_vkCmdCopyImage m_vkCmdCopyImage;
    PFN_vkCmdCopyImageToBuffer m_vkCmdCopyImageToBuffer;
    PFN_vkCmdCopyQueryPoolResults m_vkCmdCopyQueryPoolResults;
    PFN_vkCmdDispatch m_vkCmdDispatch;
    PFN_vkCmdDispatchBase m_vkCmdDispatchBase;
    PFN_vkCmdDispatchIndirect m_vkCmdDispatchIndirect;
    PFN_vkCmdDraw m_vkCmdDraw;
    PFN_vkCmdDrawIndexed m_vkCmdDrawIndexed;
    PFN_vkCmdDrawIndexedIndirect m_vkCmdDrawIndexedIndirect;
    PFN_vkCmdDrawIndirect m_vkCmdDrawIndirect;
    PFN_vkCmdEndQuery m_vkCmdEndQuery;
    PFN_vkCmdEndRenderPass m_vkCmdEndRenderPass;
    PFN_vkCmdExecuteCommands m_vkCmdExecuteCommands;
    PFN_vkCmdFillBuffer m_vkCmdFillBuffer;
    PFN_vkCmdNextSubpass m_vkCmdNextSubpass;
    PFN_vkCmdPipelineBarrier m_vkCmdPipelineBarrier;
    PFN_vkCmdPushConstants m_vkCmdPushConstants;
    PFN_vkCmdResetEvent m_vkCmdResetEvent;
    PFN_vkCmdResetQueryPool m_vkCmdResetQueryPool;
    PFN_vkCmdResolveImage m_vkCmdResolveImage;
    PFN_vkCmdSetBlendConstants m_vkCmdSetBlendConstants;
    PFN_vkCmdSetDepthBias m_vkCmdSetDepthBias;
    PFN_vkCmdSetDepthBounds m_vkCmdSetDepthBounds;
    PFN_vkCmdSetDeviceMask m_vkCmdSetDeviceMask;
    PFN_vkCmdSetEvent m_vkCmdSetEvent;
    PFN_vkCmdSetLineWidth m_vkCmdSetLineWidth;
    PFN_vkCmdSetScissor m_vkCmdSetScissor;
    PFN_vkCmdSetStencilCompareMask m_vkCmdSetStencilCompareMask;
    PFN_vkCmdSetStencilReference m_vkCmdSetStencilReference;
    PFN_vkCmdSetStencilWriteMask m_vkCmdSetStencilWriteMask;
    PFN_vkCmdSetViewport m_vkCmdSetViewport;
    PFN_vkCmdUpdateBuffer m_vkCmdUpdateBuffer;
    PFN_vkCmdWaitEvents m_vkCmdWaitEvents;
    PFN_vkCmdWriteTimestamp m_vkCmdWriteTimestamp;
    PFN_vkCreateBuffer m_vkCreateBuffer;
    PFN_vkCreateBufferView m_vkCreateBufferView;
    PFN_vkCreateCommandPool m_vkCreateCommandPool;
    PFN_vkCreateComputePipelines m_vkCreateComputePipelines;
    PFN_vkCreateDescriptorPool m_vkCreateDescriptorPool;
    PFN_vkCreateDescriptorSetLayout m_vkCreateDescriptorSetLayout;
    PFN_vkCreateDescriptorUpdateTemplate m_vkCreateDescriptorUpdateTemplate;
    PFN_vkCreateEvent m_vkCreateEvent;
    PFN_vkCreateFence m_vkCreateFence;
    PFN_vkCreateFramebuffer m_vkCreateFramebuffer;
    PFN_vkCreateGraphicsPipelines m_vkCreateGraphicsPipelines;
    PFN_vkCreateImage m_vkCreateImage;
    PFN_vkCreateImageView m_vkCreateImageView;
    PFN_vkCreatePipelineCache m_vkCreatePipelineCache;
    PFN_vkCreatePipelineLayout m_vkCreatePipelineLayout;
    PFN_vkCreateQueryPool m_vkCreateQueryPool;
    PFN_vkCreateRenderPass m_vkCreateRenderPass;
    PFN_vkCreateSampler m_vkCreateSampler;
    PFN_vkCreateSamplerYcbcrConversion m_vkCreateSamplerYcbcrConversion;
    PFN_vkCreateSemaphore m_vkCreateSemaphore;
    PFN_vkCreateShaderModule m_vkCreateShaderModule;
    PFN_vkDestroyBuffer m_vkDestroyBuffer;
    PFN_vkDestroyBufferView m_vkDestroyBufferView;
    PFN_vkDestroyCommandPool m_vkDestroyCommandPool;
    PFN_vkDestroyDescriptorPool m_vkDestroyDescriptorPool;
    PFN_vkDestroyDescriptorSetLayout m_vkDestroyDescriptorSetLayout;
    PFN_vkDestroyDescriptorUpdateTemplate m_vkDestroyDescriptorUpdateTemplate;
    PFN_vkDestroyDevice m_vkDestroyDevice;
    PFN_vkDestroyEvent m_vkDestroyEvent;
    PFN_vkDestroyFence m_vkDestroyFence;
    PFN_vkDestroyFramebuffer m_vkDestroyFramebuffer;
    PFN_vkDestroyImage m_vkDestroyImage;
    PFN_vkDestroyImageView m_vkDestroyImageView;
    PFN_vkDestroyPipeline m_vkDestroyPipeline;
    PFN_vkDestroyPipelineCache m_vkDestroyPipelineCache;
    PFN_vkDestroyPipelineLayout m_vkDestroyPipelineLayout;
    PFN_vkDestroyQueryPool m_vkDestroyQueryPool;
    PFN_vkDestroyRenderPass m_vkDestroyRenderPass;
    PFN_vkDestroySampler m_vkDestroySampler;
    PFN_vkDestroySamplerYcbcrConversion m_vkDestroySamplerYcbcrConversion;
    PFN_vkDestroySemaphore m_vkDestroySemaphore;
    PFN_vkDestroyShaderModule m_vkDestroyShaderModule;
    PFN_vkDeviceWaitIdle m_vkDeviceWaitIdle;
    PFN_vkEndCommandBuffer m_vkEndCommandBuffer;
    PFN_vkFlushMappedMemoryRanges m_vkFlushMappedMemoryRanges;
    PFN_vkFreeCommandBuffers m_vkFreeCommandBuffers;
    PFN_vkFreeDescriptorSets m_vkFreeDescriptorSets;
    PFN_vkFreeMemory m_vkFreeMemory;
    PFN_vkGetBufferMemoryRequirements m_vkGetBufferMemoryRequirements;
    PFN_vkGetBufferMemoryRequirements2 m_vkGetBufferMemoryRequirements2;
    PFN_vkGetDescriptorSetLayoutSupport m_vkGetDescriptorSetLayoutSupport;
    PFN_vkGetDeviceGroupPeerMemoryFeatures m_vkGetDeviceGroupPeerMemoryFeatures;
    PFN_vkGetDeviceMemoryCommitment m_vkGetDeviceMemoryCommitment;
    PFN_vkGetDeviceQueue m_vkGetDeviceQueue;
    PFN_vkGetDeviceQueue2 m_vkGetDeviceQueue2;
    PFN_vkGetEventStatus m_vkGetEventStatus;
    PFN_vkGetFenceStatus m_vkGetFenceStatus;
    PFN_vkGetImageMemoryRequirements m_vkGetImageMemoryRequirements;
    PFN_vkGetImageMemoryRequirements2 m_vkGetImageMemoryRequirements2;
    PFN_vkGetImageSparseMemoryRequirements m_vkGetImageSparseMemoryRequirements;
    PFN_vkGetImageSparseMemoryRequirements2 m_vkGetImageSparseMemoryRequirements2;
    PFN_vkGetImageSubresourceLayout m_vkGetImageSubresourceLayout;
    PFN_vkGetPipelineCacheData m_vkGetPipelineCacheData;
    PFN_vkGetQueryPoolResults m_vkGetQueryPoolResults;
    PFN_vkGetRenderAreaGranularity m_vkGetRenderAreaGranularity;
    PFN_vkInvalidateMappedMemoryRanges m_vkInvalidateMappedMemoryRanges;
    PFN_vkMapMemory m_vkMapMemory;
    PFN_vkMergePipelineCaches m_vkMergePipelineCaches;
    PFN_vkQueueBindSparse m_vkQueueBindSparse;
    PFN_vkQueueSubmit m_vkQueueSubmit;
    PFN_vkQueueWaitIdle m_vkQueueWaitIdle;
    PFN_vkResetCommandBuffer m_vkResetCommandBuffer;
    PFN_vkResetCommandPool m_vkResetCommandPool;
    PFN_vkResetDescriptorPool m_vkResetDescriptorPool;
    PFN_vkResetEvent m_vkResetEvent;
    PFN_vkResetFences m_vkResetFences;
    PFN_vkSetEvent m_vkSetEvent;
    PFN_vkTrimCommandPool m_vkTrimCommandPool;
    PFN_vkUnmapMemory m_vkUnmapMemory;
    PFN_vkUpdateDescriptorSetWithTemplate m_vkUpdateDescriptorSetWithTemplate;
    PFN_vkUpdateDescriptorSets m_vkUpdateDescriptorSets;
    PFN_vkWaitForFences m_vkWaitForFences;

    // Extension Functions:
    PFN_vkAcquireNextImage2KHR m_vkAcquireNextImage2KHR;
    PFN_vkAcquireNextImageKHR m_vkAcquireNextImageKHR;
    PFN_vkBindBufferMemory2KHR m_vkBindBufferMemory2KHR;
    PFN_vkBindImageMemory2KHR m_vkBindImageMemory2KHR;
    PFN_vkCmdBeginDebugUtilsLabelEXT m_vkCmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdDebugMarkerBeginEXT m_vkCmdDebugMarkerBeginEXT;
    PFN_vkCmdDebugMarkerEndEXT m_vkCmdDebugMarkerEndEXT;
    PFN_vkCmdDebugMarkerInsertEXT m_vkCmdDebugMarkerInsertEXT;
    PFN_vkCmdDispatchBaseKHR m_vkCmdDispatchBaseKHR;
    PFN_vkCmdDrawIndexedIndirectCountAMD m_vkCmdDrawIndexedIndirectCountAMD;
    PFN_vkCmdDrawIndirectCountAMD m_vkCmdDrawIndirectCountAMD;
    PFN_vkCmdEndDebugUtilsLabelEXT m_vkCmdEndDebugUtilsLabelEXT;
    PFN_vkCmdInsertDebugUtilsLabelEXT m_vkCmdInsertDebugUtilsLabelEXT;
    PFN_vkCmdProcessCommandsNVX m_vkCmdProcessCommandsNVX;
    PFN_vkCmdPushDescriptorSetKHR m_vkCmdPushDescriptorSetKHR;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR m_vkCmdPushDescriptorSetWithTemplateKHR;
    PFN_vkCmdReserveSpaceForCommandsNVX m_vkCmdReserveSpaceForCommandsNVX;
    PFN_vkCmdSetDeviceMaskKHR m_vkCmdSetDeviceMaskKHR;
    PFN_vkCmdSetDiscardRectangleEXT m_vkCmdSetDiscardRectangleEXT;
    PFN_vkCmdSetSampleLocationsEXT m_vkCmdSetSampleLocationsEXT;
    PFN_vkCmdWriteBufferMarkerAMD m_vkCmdWriteBufferMarkerAMD;
    PFN_vkCreateDescriptorUpdateTemplateKHR m_vkCreateDescriptorUpdateTemplateKHR;
    PFN_vkCreateIndirectCommandsLayoutNVX m_vkCreateIndirectCommandsLayoutNVX;
    PFN_vkCreateObjectTableNVX m_vkCreateObjectTableNVX;
    PFN_vkCreateSamplerYcbcrConversionKHR m_vkCreateSamplerYcbcrConversionKHR;
    PFN_vkCreateSharedSwapchainsKHR m_vkCreateSharedSwapchainsKHR;
    PFN_vkCreateSwapchainKHR m_vkCreateSwapchainKHR;
    PFN_vkCreateValidationCacheEXT m_vkCreateValidationCacheEXT;
    PFN_vkDebugMarkerSetObjectNameEXT m_vkDebugMarkerSetObjectNameEXT;
    PFN_vkDebugMarkerSetObjectTagEXT m_vkDebugMarkerSetObjectTagEXT;
    PFN_vkDestroyDescriptorUpdateTemplateKHR m_vkDestroyDescriptorUpdateTemplateKHR;
    PFN_vkDestroyIndirectCommandsLayoutNVX m_vkDestroyIndirectCommandsLayoutNVX;
    PFN_vkDestroyObjectTableNVX m_vkDestroyObjectTableNVX;
    PFN_vkDestroySamplerYcbcrConversionKHR m_vkDestroySamplerYcbcrConversionKHR;
    PFN_vkDestroySwapchainKHR m_vkDestroySwapchainKHR;
    PFN_vkDestroyValidationCacheEXT m_vkDestroyValidationCacheEXT;
    PFN_vkDisplayPowerControlEXT m_vkDisplayPowerControlEXT;
    PFN_vkGetBufferMemoryRequirements2KHR m_vkGetBufferMemoryRequirements2KHR;
    PFN_vkGetDescriptorSetLayoutSupportKHR m_vkGetDescriptorSetLayoutSupportKHR;
    PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR m_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR m_vkGetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR m_vkGetDeviceGroupSurfacePresentModesKHR;
    PFN_vkGetFenceFdKHR m_vkGetFenceFdKHR;
    PFN_vkGetImageMemoryRequirements2KHR m_vkGetImageMemoryRequirements2KHR;
    PFN_vkGetImageSparseMemoryRequirements2KHR m_vkGetImageSparseMemoryRequirements2KHR;
    PFN_vkGetMemoryFdKHR m_vkGetMemoryFdKHR;
    PFN_vkGetMemoryFdPropertiesKHR m_vkGetMemoryFdPropertiesKHR;
    PFN_vkGetMemoryHostPointerPropertiesEXT m_vkGetMemoryHostPointerPropertiesEXT;
    PFN_vkGetPastPresentationTimingGOOGLE m_vkGetPastPresentationTimingGOOGLE;
    PFN_vkGetRefreshCycleDurationGOOGLE m_vkGetRefreshCycleDurationGOOGLE;
    PFN_vkGetSemaphoreFdKHR m_vkGetSemaphoreFdKHR;
    PFN_vkGetShaderInfoAMD m_vkGetShaderInfoAMD;
    PFN_vkGetSwapchainCounterEXT m_vkGetSwapchainCounterEXT;
    PFN_vkGetSwapchainImagesKHR m_vkGetSwapchainImagesKHR;
    PFN_vkGetSwapchainStatusKHR m_vkGetSwapchainStatusKHR;
    PFN_vkGetValidationCacheDataEXT m_vkGetValidationCacheDataEXT;
    PFN_vkImportFenceFdKHR m_vkImportFenceFdKHR;
    PFN_vkImportSemaphoreFdKHR m_vkImportSemaphoreFdKHR;
    PFN_vkMergeValidationCachesEXT m_vkMergeValidationCachesEXT;
    PFN_vkQueueBeginDebugUtilsLabelEXT m_vkQueueBeginDebugUtilsLabelEXT;
    PFN_vkQueueEndDebugUtilsLabelEXT m_vkQueueEndDebugUtilsLabelEXT;
    PFN_vkQueueInsertDebugUtilsLabelEXT m_vkQueueInsertDebugUtilsLabelEXT;
    PFN_vkQueuePresentKHR m_vkQueuePresentKHR;
    PFN_vkRegisterDeviceEventEXT m_vkRegisterDeviceEventEXT;
    PFN_vkRegisterDisplayEventEXT m_vkRegisterDisplayEventEXT;
    PFN_vkRegisterObjectsNVX m_vkRegisterObjectsNVX;
    PFN_vkSetDebugUtilsObjectNameEXT m_vkSetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT m_vkSetDebugUtilsObjectTagEXT;
    PFN_vkSetHdrMetadataEXT m_vkSetHdrMetadataEXT;
    PFN_vkTrimCommandPoolKHR m_vkTrimCommandPoolKHR;
    PFN_vkUnregisterObjectsNVX m_vkUnregisterObjectsNVX;
    PFN_vkUpdateDescriptorSetWithTemplateKHR m_vkUpdateDescriptorSetWithTemplateKHR;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    //Android Platform Functions:
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID m_vkGetAndroidHardwareBufferPropertiesANDROID;
    PFN_vkGetMemoryAndroidHardwareBufferANDROID m_vkGetMemoryAndroidHardwareBufferANDROID;
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
    PFN_vkCmdSetViewportWScalingNV m_vkCmdSetViewportWScalingNV;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    //Win32 Platform Functions:
    PFN_vkGetFenceWin32HandleKHR m_vkGetFenceWin32HandleKHR;
    PFN_vkGetMemoryWin32HandleKHR m_vkGetMemoryWin32HandleKHR;
    PFN_vkGetMemoryWin32HandleNV m_vkGetMemoryWin32HandleNV;
    PFN_vkGetMemoryWin32HandlePropertiesKHR m_vkGetMemoryWin32HandlePropertiesKHR;
    PFN_vkGetSemaphoreWin32HandleKHR m_vkGetSemaphoreWin32HandleKHR;
    PFN_vkImportFenceWin32HandleKHR m_vkImportFenceWin32HandleKHR;
    PFN_vkImportSemaphoreWin32HandleKHR m_vkImportSemaphoreWin32HandleKHR;
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
    

  public:
    // Special 6
    //============================================================
    // Construct with all the stored function pointers as nullptr. All calls
    // will fail in this state.
    Device_Functions();

    // Construct using the supplied Global_Functions::vkCreateInstance function,
    // using the supplied VkInstance. The instance is not stored here. Only
    // functions that relate to the version and extensions that the instance was
    // created with will work.
    Device_Functions(VkDevice a_device, Instance_Functions const& a_instance_functions);

    ~Device_Functions();

    Device_Functions(Device_Functions const& a_other);
    Device_Functions& operator=(Device_Functions const& a_other);

    Device_Functions(Device_Functions && a_other);
    Device_Functions& operator=(Device_Functions && a_other);

    // Interface
    //============================================================

    // Core Functions:
    VkResult vkAllocateCommandBuffers(VkDevice device, VkCommandBufferAllocateInfo const* pAllocateInfo, VkCommandBuffer* pCommandBuffers) const noexcept;
    VkResult vkAllocateDescriptorSets(VkDevice device, VkDescriptorSetAllocateInfo const* pAllocateInfo, VkDescriptorSet* pDescriptorSets) const noexcept;
    VkResult vkAllocateMemory(VkDevice device, VkMemoryAllocateInfo const* pAllocateInfo, VkAllocationCallbacks const* pAllocator, VkDeviceMemory* pMemory) const noexcept;
    VkResult vkBeginCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferBeginInfo const* pBeginInfo) const noexcept;
    VkResult vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept;
    VkResult vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, VkBindBufferMemoryInfo const* pBindInfos) const noexcept;
    VkResult vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept;
    VkResult vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, VkBindImageMemoryInfo const* pBindInfos) const noexcept;
    void vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) const noexcept;
    void vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, VkRenderPassBeginInfo const* pRenderPassBegin, VkSubpassContents contents) const noexcept;
    void vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets, uint32_t dynamicOffsetCount, uint32_t const* pDynamicOffsets) const noexcept;
    void vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const noexcept;
    void vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) const noexcept;
    void vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, VkBuffer const* pBuffers, VkDeviceSize const* pOffsets) const noexcept;
    void vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageBlit const* pRegions, VkFilter filter) const noexcept;
    void vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, VkClearAttachment const* pAttachments, uint32_t rectCount, VkClearRect const* pRects) const noexcept;
    void vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, VkClearColorValue const* pColor, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept;
    void vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, VkClearDepthStencilValue const* pDepthStencil, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept;
    void vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, VkBufferCopy const* pRegions) const noexcept;
    void vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept;
    void vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageCopy const* pRegions) const noexcept;
    void vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept;
    void vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept;
    void vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) const noexcept;
    void vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const noexcept;
    void vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const noexcept;
    void vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept;
    void vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept;
    void vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) const noexcept;
    void vkCmdEndRenderPass(VkCommandBuffer commandBuffer) const noexcept;
    void vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept;
    void vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const noexcept;
    void vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) const noexcept;
    void vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept;
    void vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, void const* pValues) const noexcept;
    void vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept;
    void vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept;
    void vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageResolve const* pRegions) const noexcept;
    void vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, float const blendConstants[4]) const noexcept;
    void vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const noexcept;
    void vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) const noexcept;
    void vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept;
    void vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept;
    void vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) const noexcept;
    void vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, VkRect2D const* pScissors) const noexcept;
    void vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) const noexcept;
    void vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) const noexcept;
    void vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) const noexcept;
    void vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, VkViewport const* pViewports) const noexcept;
    void vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, void const* pData) const noexcept;
    void vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, VkEvent const* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept;
    void vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) const noexcept;
    VkResult vkCreateBuffer(VkDevice device, VkBufferCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkBuffer* pBuffer) const noexcept;
    VkResult vkCreateBufferView(VkDevice device, VkBufferViewCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkBufferView* pView) const noexcept;
    VkResult vkCreateCommandPool(VkDevice device, VkCommandPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkCommandPool* pCommandPool) const noexcept;
    VkResult vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, VkComputePipelineCreateInfo const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkPipeline* pPipelines) const noexcept;
    VkResult vkCreateDescriptorPool(VkDevice device, VkDescriptorPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorPool* pDescriptorPool) const noexcept;
    VkResult vkCreateDescriptorSetLayout(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorSetLayout* pSetLayout) const noexcept;
    VkResult vkCreateDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplateCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) const noexcept;
    VkResult vkCreateEvent(VkDevice device, VkEventCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkEvent* pEvent) const noexcept;
    VkResult vkCreateFence(VkDevice device, VkFenceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept;
    VkResult vkCreateFramebuffer(VkDevice device, VkFramebufferCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkFramebuffer* pFramebuffer) const noexcept;
    VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, VkGraphicsPipelineCreateInfo const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkPipeline* pPipelines) const noexcept;
    VkResult vkCreateImage(VkDevice device, VkImageCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkImage* pImage) const noexcept;
    VkResult vkCreateImageView(VkDevice device, VkImageViewCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkImageView* pView) const noexcept;
    VkResult vkCreatePipelineCache(VkDevice device, VkPipelineCacheCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkPipelineCache* pPipelineCache) const noexcept;
    VkResult vkCreatePipelineLayout(VkDevice device, VkPipelineLayoutCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkPipelineLayout* pPipelineLayout) const noexcept;
    VkResult vkCreateQueryPool(VkDevice device, VkQueryPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkQueryPool* pQueryPool) const noexcept;
    VkResult vkCreateRenderPass(VkDevice device, VkRenderPassCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkRenderPass* pRenderPass) const noexcept;
    VkResult vkCreateSampler(VkDevice device, VkSamplerCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSampler* pSampler) const noexcept;
    VkResult vkCreateSamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversionCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) const noexcept;
    VkResult vkCreateSemaphore(VkDevice device, VkSemaphoreCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSemaphore* pSemaphore) const noexcept;
    VkResult vkCreateShaderModule(VkDevice device, VkShaderModuleCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkShaderModule* pShaderModule) const noexcept;
    void vkDestroyBuffer(VkDevice device, VkBuffer buffer, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyBufferView(VkDevice device, VkBufferView bufferView, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyDevice(VkDevice device, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyEvent(VkDevice device, VkEvent event, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyFence(VkDevice device, VkFence fence, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyImage(VkDevice device, VkImage image, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyImageView(VkDevice device, VkImageView imageView, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyPipeline(VkDevice device, VkPipeline pipeline, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySampler(VkDevice device, VkSampler sampler, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, VkAllocationCallbacks const* pAllocator) const noexcept;
    VkResult vkDeviceWaitIdle(VkDevice device) const noexcept;
    VkResult vkEndCommandBuffer(VkCommandBuffer commandBuffer) const noexcept;
    VkResult vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, VkMappedMemoryRange const* pMemoryRanges) const noexcept;
    void vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept;
    VkResult vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets) const noexcept;
    void vkFreeMemory(VkDevice device, VkDeviceMemory memory, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) const noexcept;
    void vkGetBufferMemoryRequirements2(VkDevice device, VkBufferMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept;
    void vkGetDescriptorSetLayoutSupport(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) const noexcept;
    void vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) const noexcept;
    void vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) const noexcept;
    void vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) const noexcept;
    void vkGetDeviceQueue2(VkDevice device, VkDeviceQueueInfo2 const* pQueueInfo, VkQueue* pQueue) const noexcept;
    VkResult vkGetEventStatus(VkDevice device, VkEvent event) const noexcept;
    VkResult vkGetFenceStatus(VkDevice device, VkFence fence) const noexcept;
    void vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) const noexcept;
    void vkGetImageMemoryRequirements2(VkDevice device, VkImageMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept;
    void vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) const noexcept;
    void vkGetImageSparseMemoryRequirements2(VkDevice device, VkImageSparseMemoryRequirementsInfo2 const* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) const noexcept;
    void vkGetImageSubresourceLayout(VkDevice device, VkImage image, VkImageSubresource const* pSubresource, VkSubresourceLayout* pLayout) const noexcept;
    VkResult vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) const noexcept;
    VkResult vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept;
    void vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) const noexcept;
    VkResult vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, VkMappedMemoryRange const* pMemoryRanges) const noexcept;
    VkResult vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) const noexcept;
    VkResult vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, VkPipelineCache const* pSrcCaches) const noexcept;
    VkResult vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, VkBindSparseInfo const* pBindInfo, VkFence fence) const noexcept;
    VkResult vkQueueSubmit(VkQueue queue, uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence) const noexcept;
    VkResult vkQueueWaitIdle(VkQueue queue) const noexcept;
    VkResult vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) const noexcept;
    VkResult vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) const noexcept;
    VkResult vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) const noexcept;
    VkResult vkResetEvent(VkDevice device, VkEvent event) const noexcept;
    VkResult vkResetFences(VkDevice device, uint32_t fenceCount, VkFence const* pFences) const noexcept;
    VkResult vkSetEvent(VkDevice device, VkEvent event) const noexcept;
    void vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) const noexcept;
    void vkUnmapMemory(VkDevice device, VkDeviceMemory memory) const noexcept;
    void vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, void const* pData) const noexcept;
    void vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites, uint32_t descriptorCopyCount, VkCopyDescriptorSet const* pDescriptorCopies) const noexcept;
    VkResult vkWaitForFences(VkDevice device, uint32_t fenceCount, VkFence const* pFences, VkBool32 waitAll, uint64_t timeout) const noexcept;

    // Extension Functions:
    VkResult vkAcquireNextImage2KHR(VkDevice device, VkAcquireNextImageInfoKHR const* pAcquireInfo, uint32_t* pImageIndex) const noexcept;
    VkResult vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) const noexcept;
    VkResult vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, VkBindBufferMemoryInfo const* pBindInfos) const noexcept;
    VkResult vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, VkBindImageMemoryInfo const* pBindInfos) const noexcept;
    void vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    void vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept;
    void vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) const noexcept;
    void vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept;
    void vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept;
    void vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept;
    void vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) const noexcept;
    void vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    void vkCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, VkCmdProcessCommandsInfoNVX const* pProcessCommandsInfo) const noexcept;
    void vkCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites) const noexcept;
    void vkCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, void const* pData) const noexcept;
    void vkCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, VkCmdReserveSpaceForCommandsInfoNVX const* pReserveSpaceInfo) const noexcept;
    void vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept;
    void vkCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, VkRect2D const* pDiscardRectangles) const noexcept;
    void vkCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, VkSampleLocationsInfoEXT const* pSampleLocationsInfo) const noexcept;
    void vkCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) const noexcept;
    VkResult vkCreateDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplateCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) const noexcept;
    VkResult vkCreateIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutCreateInfoNVX const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkIndirectCommandsLayoutNVX* pIndirectCommandsLayout) const noexcept;
    VkResult vkCreateObjectTableNVX(VkDevice device, VkObjectTableCreateInfoNVX const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkObjectTableNVX* pObjectTable) const noexcept;
    VkResult vkCreateSamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversionCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) const noexcept;
    VkResult vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, VkSwapchainCreateInfoKHR const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkSwapchainKHR* pSwapchains) const noexcept;
    VkResult vkCreateSwapchainKHR(VkDevice device, VkSwapchainCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSwapchainKHR* pSwapchain) const noexcept;
    VkResult vkCreateValidationCacheEXT(VkDevice device, VkValidationCacheCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkValidationCacheEXT* pValidationCache) const noexcept;
    VkResult vkDebugMarkerSetObjectNameEXT(VkDevice device, VkDebugMarkerObjectNameInfoEXT const* pNameInfo) const noexcept;
    VkResult vkDebugMarkerSetObjectTagEXT(VkDevice device, VkDebugMarkerObjectTagInfoEXT const* pTagInfo) const noexcept;
    void vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutNVX indirectCommandsLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyObjectTableNVX(VkDevice device, VkObjectTableNVX objectTable, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, VkAllocationCallbacks const* pAllocator) const noexcept;
    void vkDestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, VkAllocationCallbacks const* pAllocator) const noexcept;
    VkResult vkDisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, VkDisplayPowerInfoEXT const* pDisplayPowerInfo) const noexcept;
    void vkGetBufferMemoryRequirements2KHR(VkDevice device, VkBufferMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept;
    void vkGetDescriptorSetLayoutSupportKHR(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) const noexcept;
    void vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) const noexcept;
    VkResult vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) const noexcept;
    VkResult vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) const noexcept;
    VkResult vkGetFenceFdKHR(VkDevice device, VkFenceGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept;
    void vkGetImageMemoryRequirements2KHR(VkDevice device, VkImageMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept;
    void vkGetImageSparseMemoryRequirements2KHR(VkDevice device, VkImageSparseMemoryRequirementsInfo2 const* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) const noexcept;
    VkResult vkGetMemoryFdKHR(VkDevice device, VkMemoryGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept;
    VkResult vkGetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) const noexcept;
    VkResult vkGetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, void const* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) const noexcept;
    VkResult vkGetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) const noexcept;
    VkResult vkGetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) const noexcept;
    VkResult vkGetSemaphoreFdKHR(VkDevice device, VkSemaphoreGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept;
    VkResult vkGetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) const noexcept;
    VkResult vkGetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) const noexcept;
    VkResult vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) const noexcept;
    VkResult vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) const noexcept;
    VkResult vkGetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) const noexcept;
    VkResult vkImportFenceFdKHR(VkDevice device, VkImportFenceFdInfoKHR const* pImportFenceFdInfo) const noexcept;
    VkResult vkImportSemaphoreFdKHR(VkDevice device, VkImportSemaphoreFdInfoKHR const* pImportSemaphoreFdInfo) const noexcept;
    VkResult vkMergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, VkValidationCacheEXT const* pSrcCaches) const noexcept;
    void vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    void vkQueueEndDebugUtilsLabelEXT(VkQueue queue) const noexcept;
    void vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    VkResult vkQueuePresentKHR(VkQueue queue, VkPresentInfoKHR const* pPresentInfo) const noexcept;
    VkResult vkRegisterDeviceEventEXT(VkDevice device, VkDeviceEventInfoEXT const* pDeviceEventInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept;
    VkResult vkRegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, VkDisplayEventInfoEXT const* pDisplayEventInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept;
    VkResult vkRegisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, VkObjectTableEntryNVX const*const* ppObjectTableEntries, uint32_t const* pObjectIndices) const noexcept;
    VkResult vkSetDebugUtilsObjectNameEXT(VkDevice device, VkDebugUtilsObjectNameInfoEXT const* pNameInfo) const noexcept;
    VkResult vkSetDebugUtilsObjectTagEXT(VkDevice device, VkDebugUtilsObjectTagInfoEXT const* pTagInfo) const noexcept;
    void vkSetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, VkSwapchainKHR const* pSwapchains, VkHdrMetadataEXT const* pMetadata) const noexcept;
    void vkTrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) const noexcept;
    VkResult vkUnregisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, VkObjectEntryTypeNVX const* pObjectEntryTypes, uint32_t const* pObjectIndices) const noexcept;
    void vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, void const* pData) const noexcept;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    //Android Platform Functions:
    VkResult vkGetAndroidHardwareBufferPropertiesANDROID(VkDevice device, struct const AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) const noexcept;
    VkResult vkGetMemoryAndroidHardwareBufferANDROID(VkDevice device, VkMemoryGetAndroidHardwareBufferInfoANDROID const* pInfo, struct AHardwareBuffer** pBuffer) const noexcept;
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
    void vkCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, VkViewportWScalingNV const* pViewportWScalings) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    //Win32 Platform Functions:
    VkResult vkGetFenceWin32HandleKHR(VkDevice device, VkFenceGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept;
    VkResult vkGetMemoryWin32HandleKHR(VkDevice device, VkMemoryGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept;
    VkResult vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) const noexcept;
    VkResult vkGetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) const noexcept;
    VkResult vkGetSemaphoreWin32HandleKHR(VkDevice device, VkSemaphoreGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept;
    VkResult vkImportFenceWin32HandleKHR(VkDevice device, VkImportFenceWin32HandleInfoKHR const* pImportFenceWin32HandleInfo) const noexcept;
    VkResult vkImportSemaphoreWin32HandleKHR(VkDevice device, VkImportSemaphoreWin32HandleInfoKHR const* pImportSemaphoreWin32HandleInfo) const noexcept;
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
  };
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Device_Functions
//---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions require a specific VkDevice to 
  // use. These cannot be aquired until an VkDevice is created so they are 
  // seperate from the instance functions.

// Special 6
//============================================================
inline sdlxvulkan::Device_Functions::~Device_Functions() = default;

inline sdlxvulkan::Device_Functions::Device_Functions(Device_Functions const& a_other) = default;
inline sdlxvulkan::Device_Functions& sdlxvulkan::Device_Functions::operator=(Device_Functions const& a_other) = default;

inline sdlxvulkan::Device_Functions::Device_Functions(Device_Functions && a_other) = default;
inline sdlxvulkan::Device_Functions& sdlxvulkan::Device_Functions::operator=(Device_Functions && a_other) = default;

// Interface
//============================================================
// Core Functions:
inline VkResult sdlxvulkan::Device_Functions::vkAllocateCommandBuffers(VkDevice device, VkCommandBufferAllocateInfo const* pAllocateInfo, VkCommandBuffer* pCommandBuffers) const noexcept
{
  assert(m_vkAllocateCommandBuffers != nullptr);
  return m_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
}

inline VkResult sdlxvulkan::Device_Functions::vkAllocateDescriptorSets(VkDevice device, VkDescriptorSetAllocateInfo const* pAllocateInfo, VkDescriptorSet* pDescriptorSets) const noexcept
{
  assert(m_vkAllocateDescriptorSets != nullptr);
  return m_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
}

inline VkResult sdlxvulkan::Device_Functions::vkAllocateMemory(VkDevice device, VkMemoryAllocateInfo const* pAllocateInfo, VkAllocationCallbacks const* pAllocator, VkDeviceMemory* pMemory) const noexcept
{
  assert(m_vkAllocateMemory != nullptr);
  return m_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}

inline VkResult sdlxvulkan::Device_Functions::vkBeginCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferBeginInfo const* pBeginInfo) const noexcept
{
  assert(m_vkBeginCommandBuffer != nullptr);
  return m_vkBeginCommandBuffer(commandBuffer, pBeginInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept
{
  assert(m_vkBindBufferMemory != nullptr);
  return m_vkBindBufferMemory(device, buffer, memory, memoryOffset);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, VkBindBufferMemoryInfo const* pBindInfos) const noexcept
{
  assert(m_vkBindBufferMemory2 != nullptr);
  return m_vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) const noexcept
{
  assert(m_vkBindImageMemory != nullptr);
  return m_vkBindImageMemory(device, image, memory, memoryOffset);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, VkBindImageMemoryInfo const* pBindInfos) const noexcept
{
  assert(m_vkBindImageMemory2 != nullptr);
  return m_vkBindImageMemory2(device, bindInfoCount, pBindInfos);
}

inline void sdlxvulkan::Device_Functions::vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) const noexcept
{
  assert(m_vkCmdBeginQuery != nullptr);
  return m_vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
}

inline void sdlxvulkan::Device_Functions::vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, VkRenderPassBeginInfo const* pRenderPassBegin, VkSubpassContents contents) const noexcept
{
  assert(m_vkCmdBeginRenderPass != nullptr);
  return m_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

inline void sdlxvulkan::Device_Functions::vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets, uint32_t dynamicOffsetCount, uint32_t const* pDynamicOffsets) const noexcept
{
  assert(m_vkCmdBindDescriptorSets != nullptr);
  return m_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}

inline void sdlxvulkan::Device_Functions::vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const noexcept
{
  assert(m_vkCmdBindIndexBuffer != nullptr);
  return m_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}

inline void sdlxvulkan::Device_Functions::vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) const noexcept
{
  assert(m_vkCmdBindPipeline != nullptr);
  return m_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}

inline void sdlxvulkan::Device_Functions::vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, VkBuffer const* pBuffers, VkDeviceSize const* pOffsets) const noexcept
{
  assert(m_vkCmdBindVertexBuffers != nullptr);
  return m_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}

inline void sdlxvulkan::Device_Functions::vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageBlit const* pRegions, VkFilter filter) const noexcept
{
  assert(m_vkCmdBlitImage != nullptr);
  return m_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

inline void sdlxvulkan::Device_Functions::vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, VkClearAttachment const* pAttachments, uint32_t rectCount, VkClearRect const* pRects) const noexcept
{
  assert(m_vkCmdClearAttachments != nullptr);
  return m_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}

inline void sdlxvulkan::Device_Functions::vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, VkClearColorValue const* pColor, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept
{
  assert(m_vkCmdClearColorImage != nullptr);
  return m_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

inline void sdlxvulkan::Device_Functions::vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, VkClearDepthStencilValue const* pDepthStencil, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept
{
  assert(m_vkCmdClearDepthStencilImage != nullptr);
  return m_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

inline void sdlxvulkan::Device_Functions::vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, VkBufferCopy const* pRegions) const noexcept
{
  assert(m_vkCmdCopyBuffer != nullptr);
  return m_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

inline void sdlxvulkan::Device_Functions::vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept
{
  assert(m_vkCmdCopyBufferToImage != nullptr);
  return m_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

inline void sdlxvulkan::Device_Functions::vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageCopy const* pRegions) const noexcept
{
  assert(m_vkCmdCopyImage != nullptr);
  return m_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

inline void sdlxvulkan::Device_Functions::vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept
{
  assert(m_vkCmdCopyImageToBuffer != nullptr);
  return m_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

inline void sdlxvulkan::Device_Functions::vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept
{
  assert(m_vkCmdCopyQueryPoolResults != nullptr);
  return m_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

inline void sdlxvulkan::Device_Functions::vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept
{
  assert(m_vkCmdDispatch != nullptr);
  return m_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

inline void sdlxvulkan::Device_Functions::vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept
{
  assert(m_vkCmdDispatchBase != nullptr);
  return m_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

inline void sdlxvulkan::Device_Functions::vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) const noexcept
{
  assert(m_vkCmdDispatchIndirect != nullptr);
  return m_vkCmdDispatchIndirect(commandBuffer, buffer, offset);
}

inline void sdlxvulkan::Device_Functions::vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const noexcept
{
  assert(m_vkCmdDraw != nullptr);
  return m_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

inline void sdlxvulkan::Device_Functions::vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const noexcept
{
  assert(m_vkCmdDrawIndexed != nullptr);
  return m_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

inline void sdlxvulkan::Device_Functions::vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept
{
  assert(m_vkCmdDrawIndexedIndirect != nullptr);
  return m_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

inline void sdlxvulkan::Device_Functions::vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept
{
  assert(m_vkCmdDrawIndirect != nullptr);
  return m_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

inline void sdlxvulkan::Device_Functions::vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) const noexcept
{
  assert(m_vkCmdEndQuery != nullptr);
  return m_vkCmdEndQuery(commandBuffer, queryPool, query);
}

inline void sdlxvulkan::Device_Functions::vkCmdEndRenderPass(VkCommandBuffer commandBuffer) const noexcept
{
  assert(m_vkCmdEndRenderPass != nullptr);
  return m_vkCmdEndRenderPass(commandBuffer);
}

inline void sdlxvulkan::Device_Functions::vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept
{
  assert(m_vkCmdExecuteCommands != nullptr);
  return m_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
}

inline void sdlxvulkan::Device_Functions::vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const noexcept
{
  assert(m_vkCmdFillBuffer != nullptr);
  return m_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}

inline void sdlxvulkan::Device_Functions::vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) const noexcept
{
  assert(m_vkCmdNextSubpass != nullptr);
  return m_vkCmdNextSubpass(commandBuffer, contents);
}

inline void sdlxvulkan::Device_Functions::vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept
{
  assert(m_vkCmdPipelineBarrier != nullptr);
  return m_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

inline void sdlxvulkan::Device_Functions::vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, void const* pValues) const noexcept
{
  assert(m_vkCmdPushConstants != nullptr);
  return m_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}

inline void sdlxvulkan::Device_Functions::vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept
{
  assert(m_vkCmdResetEvent != nullptr);
  return m_vkCmdResetEvent(commandBuffer, event, stageMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept
{
  assert(m_vkCmdResetQueryPool != nullptr);
  return m_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}

inline void sdlxvulkan::Device_Functions::vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageResolve const* pRegions) const noexcept
{
  assert(m_vkCmdResolveImage != nullptr);
  return m_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, float const blendConstants[4]) const noexcept
{
  assert(m_vkCmdSetBlendConstants != nullptr);
  return m_vkCmdSetBlendConstants(commandBuffer, blendConstants);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const noexcept
{
  assert(m_vkCmdSetDepthBias != nullptr);
  return m_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) const noexcept
{
  assert(m_vkCmdSetDepthBounds != nullptr);
  return m_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept
{
  assert(m_vkCmdSetDeviceMask != nullptr);
  return m_vkCmdSetDeviceMask(commandBuffer, deviceMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) const noexcept
{
  assert(m_vkCmdSetEvent != nullptr);
  return m_vkCmdSetEvent(commandBuffer, event, stageMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) const noexcept
{
  assert(m_vkCmdSetLineWidth != nullptr);
  return m_vkCmdSetLineWidth(commandBuffer, lineWidth);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, VkRect2D const* pScissors) const noexcept
{
  assert(m_vkCmdSetScissor != nullptr);
  return m_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) const noexcept
{
  assert(m_vkCmdSetStencilCompareMask != nullptr);
  return m_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) const noexcept
{
  assert(m_vkCmdSetStencilReference != nullptr);
  return m_vkCmdSetStencilReference(commandBuffer, faceMask, reference);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) const noexcept
{
  assert(m_vkCmdSetStencilWriteMask != nullptr);
  return m_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, VkViewport const* pViewports) const noexcept
{
  assert(m_vkCmdSetViewport != nullptr);
  return m_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}

inline void sdlxvulkan::Device_Functions::vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, void const* pData) const noexcept
{
  assert(m_vkCmdUpdateBuffer != nullptr);
  return m_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

inline void sdlxvulkan::Device_Functions::vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, VkEvent const* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept
{
  assert(m_vkCmdWaitEvents != nullptr);
  return m_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

inline void sdlxvulkan::Device_Functions::vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) const noexcept
{
  assert(m_vkCmdWriteTimestamp != nullptr);
  return m_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateBuffer(VkDevice device, VkBufferCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkBuffer* pBuffer) const noexcept
{
  assert(m_vkCreateBuffer != nullptr);
  return m_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateBufferView(VkDevice device, VkBufferViewCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkBufferView* pView) const noexcept
{
  assert(m_vkCreateBufferView != nullptr);
  return m_vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateCommandPool(VkDevice device, VkCommandPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkCommandPool* pCommandPool) const noexcept
{
  assert(m_vkCreateCommandPool != nullptr);
  return m_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, VkComputePipelineCreateInfo const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkPipeline* pPipelines) const noexcept
{
  assert(m_vkCreateComputePipelines != nullptr);
  return m_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateDescriptorPool(VkDevice device, VkDescriptorPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorPool* pDescriptorPool) const noexcept
{
  assert(m_vkCreateDescriptorPool != nullptr);
  return m_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateDescriptorSetLayout(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorSetLayout* pSetLayout) const noexcept
{
  assert(m_vkCreateDescriptorSetLayout != nullptr);
  return m_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplateCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) const noexcept
{
  assert(m_vkCreateDescriptorUpdateTemplate != nullptr);
  return m_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateEvent(VkDevice device, VkEventCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkEvent* pEvent) const noexcept
{
  assert(m_vkCreateEvent != nullptr);
  return m_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateFence(VkDevice device, VkFenceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept
{
  assert(m_vkCreateFence != nullptr);
  return m_vkCreateFence(device, pCreateInfo, pAllocator, pFence);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateFramebuffer(VkDevice device, VkFramebufferCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkFramebuffer* pFramebuffer) const noexcept
{
  assert(m_vkCreateFramebuffer != nullptr);
  return m_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, VkGraphicsPipelineCreateInfo const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkPipeline* pPipelines) const noexcept
{
  assert(m_vkCreateGraphicsPipelines != nullptr);
  return m_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateImage(VkDevice device, VkImageCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkImage* pImage) const noexcept
{
  assert(m_vkCreateImage != nullptr);
  return m_vkCreateImage(device, pCreateInfo, pAllocator, pImage);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateImageView(VkDevice device, VkImageViewCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkImageView* pView) const noexcept
{
  assert(m_vkCreateImageView != nullptr);
  return m_vkCreateImageView(device, pCreateInfo, pAllocator, pView);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreatePipelineCache(VkDevice device, VkPipelineCacheCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkPipelineCache* pPipelineCache) const noexcept
{
  assert(m_vkCreatePipelineCache != nullptr);
  return m_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreatePipelineLayout(VkDevice device, VkPipelineLayoutCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkPipelineLayout* pPipelineLayout) const noexcept
{
  assert(m_vkCreatePipelineLayout != nullptr);
  return m_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateQueryPool(VkDevice device, VkQueryPoolCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkQueryPool* pQueryPool) const noexcept
{
  assert(m_vkCreateQueryPool != nullptr);
  return m_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateRenderPass(VkDevice device, VkRenderPassCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkRenderPass* pRenderPass) const noexcept
{
  assert(m_vkCreateRenderPass != nullptr);
  return m_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSampler(VkDevice device, VkSamplerCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSampler* pSampler) const noexcept
{
  assert(m_vkCreateSampler != nullptr);
  return m_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversionCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) const noexcept
{
  assert(m_vkCreateSamplerYcbcrConversion != nullptr);
  return m_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSemaphore(VkDevice device, VkSemaphoreCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSemaphore* pSemaphore) const noexcept
{
  assert(m_vkCreateSemaphore != nullptr);
  return m_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateShaderModule(VkDevice device, VkShaderModuleCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkShaderModule* pShaderModule) const noexcept
{
  assert(m_vkCreateShaderModule != nullptr);
  return m_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
}

inline void sdlxvulkan::Device_Functions::vkDestroyBuffer(VkDevice device, VkBuffer buffer, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyBuffer != nullptr);
  return m_vkDestroyBuffer(device, buffer, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyBufferView(VkDevice device, VkBufferView bufferView, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyBufferView != nullptr);
  return m_vkDestroyBufferView(device, bufferView, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyCommandPool != nullptr);
  return m_vkDestroyCommandPool(device, commandPool, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDescriptorPool != nullptr);
  return m_vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDescriptorSetLayout != nullptr);
  return m_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDescriptorUpdateTemplate != nullptr);
  return m_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyDevice(VkDevice device, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDevice != nullptr);
  return m_vkDestroyDevice(device, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyEvent(VkDevice device, VkEvent event, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyEvent != nullptr);
  return m_vkDestroyEvent(device, event, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyFence(VkDevice device, VkFence fence, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyFence != nullptr);
  return m_vkDestroyFence(device, fence, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyFramebuffer != nullptr);
  return m_vkDestroyFramebuffer(device, framebuffer, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyImage(VkDevice device, VkImage image, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyImage != nullptr);
  return m_vkDestroyImage(device, image, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyImageView(VkDevice device, VkImageView imageView, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyImageView != nullptr);
  return m_vkDestroyImageView(device, imageView, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyPipeline(VkDevice device, VkPipeline pipeline, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyPipeline != nullptr);
  return m_vkDestroyPipeline(device, pipeline, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyPipelineCache != nullptr);
  return m_vkDestroyPipelineCache(device, pipelineCache, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyPipelineLayout != nullptr);
  return m_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyQueryPool != nullptr);
  return m_vkDestroyQueryPool(device, queryPool, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyRenderPass != nullptr);
  return m_vkDestroyRenderPass(device, renderPass, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroySampler(VkDevice device, VkSampler sampler, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySampler != nullptr);
  return m_vkDestroySampler(device, sampler, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySamplerYcbcrConversion != nullptr);
  return m_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySemaphore != nullptr);
  return m_vkDestroySemaphore(device, semaphore, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyShaderModule != nullptr);
  return m_vkDestroyShaderModule(device, shaderModule, pAllocator);
}

inline VkResult sdlxvulkan::Device_Functions::vkDeviceWaitIdle(VkDevice device) const noexcept
{
  assert(m_vkDeviceWaitIdle != nullptr);
  return m_vkDeviceWaitIdle(device);
}

inline VkResult sdlxvulkan::Device_Functions::vkEndCommandBuffer(VkCommandBuffer commandBuffer) const noexcept
{
  assert(m_vkEndCommandBuffer != nullptr);
  return m_vkEndCommandBuffer(commandBuffer);
}

inline VkResult sdlxvulkan::Device_Functions::vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, VkMappedMemoryRange const* pMemoryRanges) const noexcept
{
  assert(m_vkFlushMappedMemoryRanges != nullptr);
  return m_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}

inline void sdlxvulkan::Device_Functions::vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept
{
  assert(m_vkFreeCommandBuffers != nullptr);
  return m_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}

inline VkResult sdlxvulkan::Device_Functions::vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets) const noexcept
{
  assert(m_vkFreeDescriptorSets != nullptr);
  return m_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}

inline void sdlxvulkan::Device_Functions::vkFreeMemory(VkDevice device, VkDeviceMemory memory, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkFreeMemory != nullptr);
  return m_vkFreeMemory(device, memory, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) const noexcept
{
  assert(m_vkGetBufferMemoryRequirements != nullptr);
  return m_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetBufferMemoryRequirements2(VkDevice device, VkBufferMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept
{
  assert(m_vkGetBufferMemoryRequirements2 != nullptr);
  return m_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetDescriptorSetLayoutSupport(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) const noexcept
{
  assert(m_vkGetDescriptorSetLayoutSupport != nullptr);
  return m_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
}

inline void sdlxvulkan::Device_Functions::vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) const noexcept
{
  assert(m_vkGetDeviceGroupPeerMemoryFeatures != nullptr);
  return m_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

inline void sdlxvulkan::Device_Functions::vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) const noexcept
{
  assert(m_vkGetDeviceMemoryCommitment != nullptr);
  return m_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}

inline void sdlxvulkan::Device_Functions::vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) const noexcept
{
  assert(m_vkGetDeviceQueue != nullptr);
  return m_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
}

inline void sdlxvulkan::Device_Functions::vkGetDeviceQueue2(VkDevice device, VkDeviceQueueInfo2 const* pQueueInfo, VkQueue* pQueue) const noexcept
{
  assert(m_vkGetDeviceQueue2 != nullptr);
  return m_vkGetDeviceQueue2(device, pQueueInfo, pQueue);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetEventStatus(VkDevice device, VkEvent event) const noexcept
{
  assert(m_vkGetEventStatus != nullptr);
  return m_vkGetEventStatus(device, event);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetFenceStatus(VkDevice device, VkFence fence) const noexcept
{
  assert(m_vkGetFenceStatus != nullptr);
  return m_vkGetFenceStatus(device, fence);
}

inline void sdlxvulkan::Device_Functions::vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) const noexcept
{
  assert(m_vkGetImageMemoryRequirements != nullptr);
  return m_vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetImageMemoryRequirements2(VkDevice device, VkImageMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept
{
  assert(m_vkGetImageMemoryRequirements2 != nullptr);
  return m_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) const noexcept
{
  assert(m_vkGetImageSparseMemoryRequirements != nullptr);
  return m_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetImageSparseMemoryRequirements2(VkDevice device, VkImageSparseMemoryRequirementsInfo2 const* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) const noexcept
{
  assert(m_vkGetImageSparseMemoryRequirements2 != nullptr);
  return m_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetImageSubresourceLayout(VkDevice device, VkImage image, VkImageSubresource const* pSubresource, VkSubresourceLayout* pLayout) const noexcept
{
  assert(m_vkGetImageSubresourceLayout != nullptr);
  return m_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) const noexcept
{
  assert(m_vkGetPipelineCacheData != nullptr);
  return m_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept
{
  assert(m_vkGetQueryPoolResults != nullptr);
  return m_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}

inline void sdlxvulkan::Device_Functions::vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) const noexcept
{
  assert(m_vkGetRenderAreaGranularity != nullptr);
  return m_vkGetRenderAreaGranularity(device, renderPass, pGranularity);
}

inline VkResult sdlxvulkan::Device_Functions::vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, VkMappedMemoryRange const* pMemoryRanges) const noexcept
{
  assert(m_vkInvalidateMappedMemoryRanges != nullptr);
  return m_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}

inline VkResult sdlxvulkan::Device_Functions::vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) const noexcept
{
  assert(m_vkMapMemory != nullptr);
  return m_vkMapMemory(device, memory, offset, size, flags, ppData);
}

inline VkResult sdlxvulkan::Device_Functions::vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, VkPipelineCache const* pSrcCaches) const noexcept
{
  assert(m_vkMergePipelineCaches != nullptr);
  return m_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
}

inline VkResult sdlxvulkan::Device_Functions::vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, VkBindSparseInfo const* pBindInfo, VkFence fence) const noexcept
{
  assert(m_vkQueueBindSparse != nullptr);
  return m_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
}

inline VkResult sdlxvulkan::Device_Functions::vkQueueSubmit(VkQueue queue, uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence) const noexcept
{
  assert(m_vkQueueSubmit != nullptr);
  return m_vkQueueSubmit(queue, submitCount, pSubmits, fence);
}

inline VkResult sdlxvulkan::Device_Functions::vkQueueWaitIdle(VkQueue queue) const noexcept
{
  assert(m_vkQueueWaitIdle != nullptr);
  return m_vkQueueWaitIdle(queue);
}

inline VkResult sdlxvulkan::Device_Functions::vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) const noexcept
{
  assert(m_vkResetCommandBuffer != nullptr);
  return m_vkResetCommandBuffer(commandBuffer, flags);
}

inline VkResult sdlxvulkan::Device_Functions::vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) const noexcept
{
  assert(m_vkResetCommandPool != nullptr);
  return m_vkResetCommandPool(device, commandPool, flags);
}

inline VkResult sdlxvulkan::Device_Functions::vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) const noexcept
{
  assert(m_vkResetDescriptorPool != nullptr);
  return m_vkResetDescriptorPool(device, descriptorPool, flags);
}

inline VkResult sdlxvulkan::Device_Functions::vkResetEvent(VkDevice device, VkEvent event) const noexcept
{
  assert(m_vkResetEvent != nullptr);
  return m_vkResetEvent(device, event);
}

inline VkResult sdlxvulkan::Device_Functions::vkResetFences(VkDevice device, uint32_t fenceCount, VkFence const* pFences) const noexcept
{
  assert(m_vkResetFences != nullptr);
  return m_vkResetFences(device, fenceCount, pFences);
}

inline VkResult sdlxvulkan::Device_Functions::vkSetEvent(VkDevice device, VkEvent event) const noexcept
{
  assert(m_vkSetEvent != nullptr);
  return m_vkSetEvent(device, event);
}

inline void sdlxvulkan::Device_Functions::vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) const noexcept
{
  assert(m_vkTrimCommandPool != nullptr);
  return m_vkTrimCommandPool(device, commandPool, flags);
}

inline void sdlxvulkan::Device_Functions::vkUnmapMemory(VkDevice device, VkDeviceMemory memory) const noexcept
{
  assert(m_vkUnmapMemory != nullptr);
  return m_vkUnmapMemory(device, memory);
}

inline void sdlxvulkan::Device_Functions::vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, void const* pData) const noexcept
{
  assert(m_vkUpdateDescriptorSetWithTemplate != nullptr);
  return m_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}

inline void sdlxvulkan::Device_Functions::vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites, uint32_t descriptorCopyCount, VkCopyDescriptorSet const* pDescriptorCopies) const noexcept
{
  assert(m_vkUpdateDescriptorSets != nullptr);
  return m_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

inline VkResult sdlxvulkan::Device_Functions::vkWaitForFences(VkDevice device, uint32_t fenceCount, VkFence const* pFences, VkBool32 waitAll, uint64_t timeout) const noexcept
{
  assert(m_vkWaitForFences != nullptr);
  return m_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
}


// Extension Functions:
inline VkResult sdlxvulkan::Device_Functions::vkAcquireNextImage2KHR(VkDevice device, VkAcquireNextImageInfoKHR const* pAcquireInfo, uint32_t* pImageIndex) const noexcept
{
  assert(m_vkAcquireNextImage2KHR != nullptr);
  return m_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
}

inline VkResult sdlxvulkan::Device_Functions::vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) const noexcept
{
  assert(m_vkAcquireNextImageKHR != nullptr);
  return m_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, VkBindBufferMemoryInfo const* pBindInfos) const noexcept
{
  assert(m_vkBindBufferMemory2KHR != nullptr);
  return m_vkBindBufferMemory2KHR(device, bindInfoCount, pBindInfos);
}

inline VkResult sdlxvulkan::Device_Functions::vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, VkBindImageMemoryInfo const* pBindInfos) const noexcept
{
  assert(m_vkBindImageMemory2KHR != nullptr);
  return m_vkBindImageMemory2KHR(device, bindInfoCount, pBindInfos);
}

inline void sdlxvulkan::Device_Functions::vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept
{
  assert(m_vkCmdBeginDebugUtilsLabelEXT != nullptr);
  return m_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept
{
  assert(m_vkCmdDebugMarkerBeginEXT != nullptr);
  return m_vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) const noexcept
{
  assert(m_vkCmdDebugMarkerEndEXT != nullptr);
  return m_vkCmdDebugMarkerEndEXT(commandBuffer);
}

inline void sdlxvulkan::Device_Functions::vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept
{
  assert(m_vkCmdDebugMarkerInsertEXT != nullptr);
  return m_vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept
{
  assert(m_vkCmdDispatchBaseKHR != nullptr);
  return m_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

inline void sdlxvulkan::Device_Functions::vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept
{
  assert(m_vkCmdDrawIndexedIndirectCountAMD != nullptr);
  return m_vkCmdDrawIndexedIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

inline void sdlxvulkan::Device_Functions::vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept
{
  assert(m_vkCmdDrawIndirectCountAMD != nullptr);
  return m_vkCmdDrawIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

inline void sdlxvulkan::Device_Functions::vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) const noexcept
{
  assert(m_vkCmdEndDebugUtilsLabelEXT != nullptr);
  return m_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

inline void sdlxvulkan::Device_Functions::vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept
{
  assert(m_vkCmdInsertDebugUtilsLabelEXT != nullptr);
  return m_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, VkCmdProcessCommandsInfoNVX const* pProcessCommandsInfo) const noexcept
{
  assert(m_vkCmdProcessCommandsNVX != nullptr);
  return m_vkCmdProcessCommandsNVX(commandBuffer, pProcessCommandsInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites) const noexcept
{
  assert(m_vkCmdPushDescriptorSetKHR != nullptr);
  return m_vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

inline void sdlxvulkan::Device_Functions::vkCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, void const* pData) const noexcept
{
  assert(m_vkCmdPushDescriptorSetWithTemplateKHR != nullptr);
  return m_vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

inline void sdlxvulkan::Device_Functions::vkCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, VkCmdReserveSpaceForCommandsInfoNVX const* pReserveSpaceInfo) const noexcept
{
  assert(m_vkCmdReserveSpaceForCommandsNVX != nullptr);
  return m_vkCmdReserveSpaceForCommandsNVX(commandBuffer, pReserveSpaceInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) const noexcept
{
  assert(m_vkCmdSetDeviceMaskKHR != nullptr);
  return m_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, VkRect2D const* pDiscardRectangles) const noexcept
{
  assert(m_vkCmdSetDiscardRectangleEXT != nullptr);
  return m_vkCmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

inline void sdlxvulkan::Device_Functions::vkCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, VkSampleLocationsInfoEXT const* pSampleLocationsInfo) const noexcept
{
  assert(m_vkCmdSetSampleLocationsEXT != nullptr);
  return m_vkCmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

inline void sdlxvulkan::Device_Functions::vkCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) const noexcept
{
  assert(m_vkCmdWriteBufferMarkerAMD != nullptr);
  return m_vkCmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplateCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) const noexcept
{
  assert(m_vkCreateDescriptorUpdateTemplateKHR != nullptr);
  return m_vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutCreateInfoNVX const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkIndirectCommandsLayoutNVX* pIndirectCommandsLayout) const noexcept
{
  assert(m_vkCreateIndirectCommandsLayoutNVX != nullptr);
  return m_vkCreateIndirectCommandsLayoutNVX(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateObjectTableNVX(VkDevice device, VkObjectTableCreateInfoNVX const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkObjectTableNVX* pObjectTable) const noexcept
{
  assert(m_vkCreateObjectTableNVX != nullptr);
  return m_vkCreateObjectTableNVX(device, pCreateInfo, pAllocator, pObjectTable);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversionCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) const noexcept
{
  assert(m_vkCreateSamplerYcbcrConversionKHR != nullptr);
  return m_vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, VkSwapchainCreateInfoKHR const* pCreateInfos, VkAllocationCallbacks const* pAllocator, VkSwapchainKHR* pSwapchains) const noexcept
{
  assert(m_vkCreateSharedSwapchainsKHR != nullptr);
  return m_vkCreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateSwapchainKHR(VkDevice device, VkSwapchainCreateInfoKHR const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkSwapchainKHR* pSwapchain) const noexcept
{
  assert(m_vkCreateSwapchainKHR != nullptr);
  return m_vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
}

inline VkResult sdlxvulkan::Device_Functions::vkCreateValidationCacheEXT(VkDevice device, VkValidationCacheCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkValidationCacheEXT* pValidationCache) const noexcept
{
  assert(m_vkCreateValidationCacheEXT != nullptr);
  return m_vkCreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache);
}

inline VkResult sdlxvulkan::Device_Functions::vkDebugMarkerSetObjectNameEXT(VkDevice device, VkDebugMarkerObjectNameInfoEXT const* pNameInfo) const noexcept
{
  assert(m_vkDebugMarkerSetObjectNameEXT != nullptr);
  return m_vkDebugMarkerSetObjectNameEXT(device, pNameInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkDebugMarkerSetObjectTagEXT(VkDevice device, VkDebugMarkerObjectTagInfoEXT const* pTagInfo) const noexcept
{
  assert(m_vkDebugMarkerSetObjectTagEXT != nullptr);
  return m_vkDebugMarkerSetObjectTagEXT(device, pTagInfo);
}

inline void sdlxvulkan::Device_Functions::vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyDescriptorUpdateTemplateKHR != nullptr);
  return m_vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutNVX indirectCommandsLayout, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyIndirectCommandsLayoutNVX != nullptr);
  return m_vkDestroyIndirectCommandsLayoutNVX(device, indirectCommandsLayout, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyObjectTableNVX(VkDevice device, VkObjectTableNVX objectTable, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyObjectTableNVX != nullptr);
  return m_vkDestroyObjectTableNVX(device, objectTable, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySamplerYcbcrConversionKHR != nullptr);
  return m_vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroySwapchainKHR != nullptr);
  return m_vkDestroySwapchainKHR(device, swapchain, pAllocator);
}

inline void sdlxvulkan::Device_Functions::vkDestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, VkAllocationCallbacks const* pAllocator) const noexcept
{
  assert(m_vkDestroyValidationCacheEXT != nullptr);
  return m_vkDestroyValidationCacheEXT(device, validationCache, pAllocator);
}

inline VkResult sdlxvulkan::Device_Functions::vkDisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, VkDisplayPowerInfoEXT const* pDisplayPowerInfo) const noexcept
{
  assert(m_vkDisplayPowerControlEXT != nullptr);
  return m_vkDisplayPowerControlEXT(device, display, pDisplayPowerInfo);
}

inline void sdlxvulkan::Device_Functions::vkGetBufferMemoryRequirements2KHR(VkDevice device, VkBufferMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept
{
  assert(m_vkGetBufferMemoryRequirements2KHR != nullptr);
  return m_vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetDescriptorSetLayoutSupportKHR(VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) const noexcept
{
  assert(m_vkGetDescriptorSetLayoutSupportKHR != nullptr);
  return m_vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
}

inline void sdlxvulkan::Device_Functions::vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) const noexcept
{
  assert(m_vkGetDeviceGroupPeerMemoryFeaturesKHR != nullptr);
  return m_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) const noexcept
{
  assert(m_vkGetDeviceGroupPresentCapabilitiesKHR != nullptr);
  return m_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) const noexcept
{
  assert(m_vkGetDeviceGroupSurfacePresentModesKHR != nullptr);
  return m_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetFenceFdKHR(VkDevice device, VkFenceGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept
{
  assert(m_vkGetFenceFdKHR != nullptr);
  return m_vkGetFenceFdKHR(device, pGetFdInfo, pFd);
}

inline void sdlxvulkan::Device_Functions::vkGetImageMemoryRequirements2KHR(VkDevice device, VkImageMemoryRequirementsInfo2 const* pInfo, VkMemoryRequirements2* pMemoryRequirements) const noexcept
{
  assert(m_vkGetImageMemoryRequirements2KHR != nullptr);
  return m_vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

inline void sdlxvulkan::Device_Functions::vkGetImageSparseMemoryRequirements2KHR(VkDevice device, VkImageSparseMemoryRequirementsInfo2 const* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) const noexcept
{
  assert(m_vkGetImageSparseMemoryRequirements2KHR != nullptr);
  return m_vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryFdKHR(VkDevice device, VkMemoryGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept
{
  assert(m_vkGetMemoryFdKHR != nullptr);
  return m_vkGetMemoryFdKHR(device, pGetFdInfo, pFd);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) const noexcept
{
  assert(m_vkGetMemoryFdPropertiesKHR != nullptr);
  return m_vkGetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, void const* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) const noexcept
{
  assert(m_vkGetMemoryHostPointerPropertiesEXT != nullptr);
  return m_vkGetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) const noexcept
{
  assert(m_vkGetPastPresentationTimingGOOGLE != nullptr);
  return m_vkGetPastPresentationTimingGOOGLE(device, swapchain, pPresentationTimingCount, pPresentationTimings);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) const noexcept
{
  assert(m_vkGetRefreshCycleDurationGOOGLE != nullptr);
  return m_vkGetRefreshCycleDurationGOOGLE(device, swapchain, pDisplayTimingProperties);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetSemaphoreFdKHR(VkDevice device, VkSemaphoreGetFdInfoKHR const* pGetFdInfo, int* pFd) const noexcept
{
  assert(m_vkGetSemaphoreFdKHR != nullptr);
  return m_vkGetSemaphoreFdKHR(device, pGetFdInfo, pFd);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) const noexcept
{
  assert(m_vkGetShaderInfoAMD != nullptr);
  return m_vkGetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) const noexcept
{
  assert(m_vkGetSwapchainCounterEXT != nullptr);
  return m_vkGetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) const noexcept
{
  assert(m_vkGetSwapchainImagesKHR != nullptr);
  return m_vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) const noexcept
{
  assert(m_vkGetSwapchainStatusKHR != nullptr);
  return m_vkGetSwapchainStatusKHR(device, swapchain);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) const noexcept
{
  assert(m_vkGetValidationCacheDataEXT != nullptr);
  return m_vkGetValidationCacheDataEXT(device, validationCache, pDataSize, pData);
}

inline VkResult sdlxvulkan::Device_Functions::vkImportFenceFdKHR(VkDevice device, VkImportFenceFdInfoKHR const* pImportFenceFdInfo) const noexcept
{
  assert(m_vkImportFenceFdKHR != nullptr);
  return m_vkImportFenceFdKHR(device, pImportFenceFdInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkImportSemaphoreFdKHR(VkDevice device, VkImportSemaphoreFdInfoKHR const* pImportSemaphoreFdInfo) const noexcept
{
  assert(m_vkImportSemaphoreFdKHR != nullptr);
  return m_vkImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkMergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, VkValidationCacheEXT const* pSrcCaches) const noexcept
{
  assert(m_vkMergeValidationCachesEXT != nullptr);
  return m_vkMergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches);
}

inline void sdlxvulkan::Device_Functions::vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept
{
  assert(m_vkQueueBeginDebugUtilsLabelEXT != nullptr);
  return m_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

inline void sdlxvulkan::Device_Functions::vkQueueEndDebugUtilsLabelEXT(VkQueue queue) const noexcept
{
  assert(m_vkQueueEndDebugUtilsLabelEXT != nullptr);
  return m_vkQueueEndDebugUtilsLabelEXT(queue);
}

inline void sdlxvulkan::Device_Functions::vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept
{
  assert(m_vkQueueInsertDebugUtilsLabelEXT != nullptr);
  return m_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkQueuePresentKHR(VkQueue queue, VkPresentInfoKHR const* pPresentInfo) const noexcept
{
  assert(m_vkQueuePresentKHR != nullptr);
  return m_vkQueuePresentKHR(queue, pPresentInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkRegisterDeviceEventEXT(VkDevice device, VkDeviceEventInfoEXT const* pDeviceEventInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept
{
  assert(m_vkRegisterDeviceEventEXT != nullptr);
  return m_vkRegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
}

inline VkResult sdlxvulkan::Device_Functions::vkRegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, VkDisplayEventInfoEXT const* pDisplayEventInfo, VkAllocationCallbacks const* pAllocator, VkFence* pFence) const noexcept
{
  assert(m_vkRegisterDisplayEventEXT != nullptr);
  return m_vkRegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
}

inline VkResult sdlxvulkan::Device_Functions::vkRegisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, VkObjectTableEntryNVX const*const* ppObjectTableEntries, uint32_t const* pObjectIndices) const noexcept
{
  assert(m_vkRegisterObjectsNVX != nullptr);
  return m_vkRegisterObjectsNVX(device, objectTable, objectCount, ppObjectTableEntries, pObjectIndices);
}

inline VkResult sdlxvulkan::Device_Functions::vkSetDebugUtilsObjectNameEXT(VkDevice device, VkDebugUtilsObjectNameInfoEXT const* pNameInfo) const noexcept
{
  assert(m_vkSetDebugUtilsObjectNameEXT != nullptr);
  return m_vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkSetDebugUtilsObjectTagEXT(VkDevice device, VkDebugUtilsObjectTagInfoEXT const* pTagInfo) const noexcept
{
  assert(m_vkSetDebugUtilsObjectTagEXT != nullptr);
  return m_vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
}

inline void sdlxvulkan::Device_Functions::vkSetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, VkSwapchainKHR const* pSwapchains, VkHdrMetadataEXT const* pMetadata) const noexcept
{
  assert(m_vkSetHdrMetadataEXT != nullptr);
  return m_vkSetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}

inline void sdlxvulkan::Device_Functions::vkTrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) const noexcept
{
  assert(m_vkTrimCommandPoolKHR != nullptr);
  return m_vkTrimCommandPoolKHR(device, commandPool, flags);
}

inline VkResult sdlxvulkan::Device_Functions::vkUnregisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, VkObjectEntryTypeNVX const* pObjectEntryTypes, uint32_t const* pObjectIndices) const noexcept
{
  assert(m_vkUnregisterObjectsNVX != nullptr);
  return m_vkUnregisterObjectsNVX(device, objectTable, objectCount, pObjectEntryTypes, pObjectIndices);
}

inline void sdlxvulkan::Device_Functions::vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, void const* pData) const noexcept
{
  assert(m_vkUpdateDescriptorSetWithTemplateKHR != nullptr);
  return m_vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
}


#ifdef VK_USE_PLATFORM_ANDROID_KHR
//Android Platform Functions:
inline VkResult sdlxvulkan::Device_Functions::vkGetAndroidHardwareBufferPropertiesANDROID(VkDevice device, struct const AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) const noexcept
{
  assert(m_vkGetAndroidHardwareBufferPropertiesANDROID != nullptr);
  return m_vkGetAndroidHardwareBufferPropertiesANDROID(device, AHardwareBuffer* buffer, pProperties);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryAndroidHardwareBufferANDROID(VkDevice device, VkMemoryGetAndroidHardwareBufferInfoANDROID const* pInfo, struct AHardwareBuffer** pBuffer) const noexcept
{
  assert(m_vkGetMemoryAndroidHardwareBufferANDROID != nullptr);
  return m_vkGetMemoryAndroidHardwareBufferANDROID(device, pInfo, AHardwareBuffer** pBuffer);
}

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
inline void sdlxvulkan::Device_Functions::vkCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, VkViewportWScalingNV const* pViewportWScalings) const noexcept
{
  assert(m_vkCmdSetViewportWScalingNV != nullptr);
  return m_vkCmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
}

#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
//Win32 Platform Functions:
inline VkResult sdlxvulkan::Device_Functions::vkGetFenceWin32HandleKHR(VkDevice device, VkFenceGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept
{
  assert(m_vkGetFenceWin32HandleKHR != nullptr);
  return m_vkGetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryWin32HandleKHR(VkDevice device, VkMemoryGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept
{
  assert(m_vkGetMemoryWin32HandleKHR != nullptr);
  return m_vkGetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) const noexcept
{
  assert(m_vkGetMemoryWin32HandleNV != nullptr);
  return m_vkGetMemoryWin32HandleNV(device, memory, handleType, pHandle);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) const noexcept
{
  assert(m_vkGetMemoryWin32HandlePropertiesKHR != nullptr);
  return m_vkGetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties);
}

inline VkResult sdlxvulkan::Device_Functions::vkGetSemaphoreWin32HandleKHR(VkDevice device, VkSemaphoreGetWin32HandleInfoKHR const* pGetWin32HandleInfo, HANDLE* pHandle) const noexcept
{
  assert(m_vkGetSemaphoreWin32HandleKHR != nullptr);
  return m_vkGetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle);
}

inline VkResult sdlxvulkan::Device_Functions::vkImportFenceWin32HandleKHR(VkDevice device, VkImportFenceWin32HandleInfoKHR const* pImportFenceWin32HandleInfo) const noexcept
{
  assert(m_vkImportFenceWin32HandleKHR != nullptr);
  return m_vkImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo);
}

inline VkResult sdlxvulkan::Device_Functions::vkImportSemaphoreWin32HandleKHR(VkDevice device, VkImportSemaphoreWin32HandleInfoKHR const* pImportSemaphoreWin32HandleInfo) const noexcept
{
  assert(m_vkImportSemaphoreWin32HandleKHR != nullptr);
  return m_vkImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo);
}

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



#endif // SDLXVULKAN_DEVICE_FUNCTIONS_HPP