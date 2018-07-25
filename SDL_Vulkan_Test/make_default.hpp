#ifndef SDLXVULKAN_MAKE_DEFAULT_HPP
#define SDLXVULKAN_MAKE_DEFAULT_HPP

#include <array>
#include <vulkan/vulkan.h>

namespace sdlxvulkan
{  
  template <typename T>
  T make_default() noexcept;

  template <typename T, std::size_t N>
  std::array<T, N> make_default_array() noexcept
  {
    std::array<T, N> l_result{};
    // We don't use .fill because it isn't noexcept
    for (std::size_t l_index = 0; l_index != N; ++l_index)
    {
      l_result[l_index] = make_default<T>();
    }
    return l_result;
  }

  // Core Structs:
  template <> VkAllocationCallbacks make_default<VkAllocationCallbacks>() noexcept;
  template <> VkApplicationInfo make_default<VkApplicationInfo>() noexcept;
  template <> VkAttachmentDescription make_default<VkAttachmentDescription>() noexcept;
  template <> VkAttachmentReference make_default<VkAttachmentReference>() noexcept;
  template <> VkBindBufferMemoryDeviceGroupInfo make_default<VkBindBufferMemoryDeviceGroupInfo>() noexcept;
  template <> VkBindBufferMemoryInfo make_default<VkBindBufferMemoryInfo>() noexcept;
  template <> VkBindImageMemoryDeviceGroupInfo make_default<VkBindImageMemoryDeviceGroupInfo>() noexcept;
  template <> VkBindImageMemoryInfo make_default<VkBindImageMemoryInfo>() noexcept;
  template <> VkBindImagePlaneMemoryInfo make_default<VkBindImagePlaneMemoryInfo>() noexcept;
  template <> VkBindSparseInfo make_default<VkBindSparseInfo>() noexcept;
  template <> VkBufferCopy make_default<VkBufferCopy>() noexcept;
  template <> VkBufferCreateInfo make_default<VkBufferCreateInfo>() noexcept;
  template <> VkBufferImageCopy make_default<VkBufferImageCopy>() noexcept;
  template <> VkBufferMemoryBarrier make_default<VkBufferMemoryBarrier>() noexcept;
  template <> VkBufferMemoryRequirementsInfo2 make_default<VkBufferMemoryRequirementsInfo2>() noexcept;
  template <> VkBufferViewCreateInfo make_default<VkBufferViewCreateInfo>() noexcept;
  template <> VkClearAttachment make_default<VkClearAttachment>() noexcept;
  template <> VkClearDepthStencilValue make_default<VkClearDepthStencilValue>() noexcept;
  template <> VkClearRect make_default<VkClearRect>() noexcept;
  template <> VkCommandBufferAllocateInfo make_default<VkCommandBufferAllocateInfo>() noexcept;
  template <> VkCommandBufferBeginInfo make_default<VkCommandBufferBeginInfo>() noexcept;
  template <> VkCommandBufferInheritanceInfo make_default<VkCommandBufferInheritanceInfo>() noexcept;
  template <> VkCommandPoolCreateInfo make_default<VkCommandPoolCreateInfo>() noexcept;
  template <> VkComponentMapping make_default<VkComponentMapping>() noexcept;
  template <> VkComputePipelineCreateInfo make_default<VkComputePipelineCreateInfo>() noexcept;
  template <> VkCopyDescriptorSet make_default<VkCopyDescriptorSet>() noexcept;
  template <> VkDescriptorBufferInfo make_default<VkDescriptorBufferInfo>() noexcept;
  template <> VkDescriptorImageInfo make_default<VkDescriptorImageInfo>() noexcept;
  template <> VkDescriptorPoolCreateInfo make_default<VkDescriptorPoolCreateInfo>() noexcept;
  template <> VkDescriptorPoolSize make_default<VkDescriptorPoolSize>() noexcept;
  template <> VkDescriptorSetAllocateInfo make_default<VkDescriptorSetAllocateInfo>() noexcept;
  template <> VkDescriptorSetLayoutBinding make_default<VkDescriptorSetLayoutBinding>() noexcept;
  template <> VkDescriptorSetLayoutCreateInfo make_default<VkDescriptorSetLayoutCreateInfo>() noexcept;
  template <> VkDescriptorSetLayoutSupport make_default<VkDescriptorSetLayoutSupport>() noexcept;
  template <> VkDescriptorUpdateTemplateCreateInfo make_default<VkDescriptorUpdateTemplateCreateInfo>() noexcept;
  template <> VkDescriptorUpdateTemplateEntry make_default<VkDescriptorUpdateTemplateEntry>() noexcept;
  template <> VkDeviceCreateInfo make_default<VkDeviceCreateInfo>() noexcept;
  template <> VkDeviceGroupBindSparseInfo make_default<VkDeviceGroupBindSparseInfo>() noexcept;
  template <> VkDeviceGroupCommandBufferBeginInfo make_default<VkDeviceGroupCommandBufferBeginInfo>() noexcept;
  template <> VkDeviceGroupDeviceCreateInfo make_default<VkDeviceGroupDeviceCreateInfo>() noexcept;
  template <> VkDeviceGroupRenderPassBeginInfo make_default<VkDeviceGroupRenderPassBeginInfo>() noexcept;
  template <> VkDeviceGroupSubmitInfo make_default<VkDeviceGroupSubmitInfo>() noexcept;
  template <> VkDeviceQueueCreateInfo make_default<VkDeviceQueueCreateInfo>() noexcept;
  template <> VkDeviceQueueInfo2 make_default<VkDeviceQueueInfo2>() noexcept;
  template <> VkDispatchIndirectCommand make_default<VkDispatchIndirectCommand>() noexcept;
  template <> VkDrawIndexedIndirectCommand make_default<VkDrawIndexedIndirectCommand>() noexcept;
  template <> VkDrawIndirectCommand make_default<VkDrawIndirectCommand>() noexcept;
  template <> VkEventCreateInfo make_default<VkEventCreateInfo>() noexcept;
  template <> VkExportFenceCreateInfo make_default<VkExportFenceCreateInfo>() noexcept;
  template <> VkExportMemoryAllocateInfo make_default<VkExportMemoryAllocateInfo>() noexcept;
  template <> VkExportSemaphoreCreateInfo make_default<VkExportSemaphoreCreateInfo>() noexcept;
  template <> VkExtensionProperties make_default<VkExtensionProperties>() noexcept;
  template <> VkExtent2D make_default<VkExtent2D>() noexcept;
  template <> VkExtent3D make_default<VkExtent3D>() noexcept;
  template <> VkExternalBufferProperties make_default<VkExternalBufferProperties>() noexcept;
  template <> VkExternalFenceProperties make_default<VkExternalFenceProperties>() noexcept;
  template <> VkExternalImageFormatProperties make_default<VkExternalImageFormatProperties>() noexcept;
  template <> VkExternalMemoryBufferCreateInfo make_default<VkExternalMemoryBufferCreateInfo>() noexcept;
  template <> VkExternalMemoryImageCreateInfo make_default<VkExternalMemoryImageCreateInfo>() noexcept;
  template <> VkExternalMemoryProperties make_default<VkExternalMemoryProperties>() noexcept;
  template <> VkExternalSemaphoreProperties make_default<VkExternalSemaphoreProperties>() noexcept;
  template <> VkFenceCreateInfo make_default<VkFenceCreateInfo>() noexcept;
  template <> VkFormatProperties make_default<VkFormatProperties>() noexcept;
  template <> VkFormatProperties2 make_default<VkFormatProperties2>() noexcept;
  template <> VkFramebufferCreateInfo make_default<VkFramebufferCreateInfo>() noexcept;
  template <> VkGraphicsPipelineCreateInfo make_default<VkGraphicsPipelineCreateInfo>() noexcept;
  template <> VkImageBlit make_default<VkImageBlit>() noexcept;
  template <> VkImageCopy make_default<VkImageCopy>() noexcept;
  template <> VkImageCreateInfo make_default<VkImageCreateInfo>() noexcept;
  template <> VkImageFormatProperties make_default<VkImageFormatProperties>() noexcept;
  template <> VkImageFormatProperties2 make_default<VkImageFormatProperties2>() noexcept;
  template <> VkImageMemoryBarrier make_default<VkImageMemoryBarrier>() noexcept;
  template <> VkImageMemoryRequirementsInfo2 make_default<VkImageMemoryRequirementsInfo2>() noexcept;
  template <> VkImagePlaneMemoryRequirementsInfo make_default<VkImagePlaneMemoryRequirementsInfo>() noexcept;
  template <> VkImageResolve make_default<VkImageResolve>() noexcept;
  template <> VkImageSparseMemoryRequirementsInfo2 make_default<VkImageSparseMemoryRequirementsInfo2>() noexcept;
  template <> VkImageSubresource make_default<VkImageSubresource>() noexcept;
  template <> VkImageSubresourceLayers make_default<VkImageSubresourceLayers>() noexcept;
  template <> VkImageSubresourceRange make_default<VkImageSubresourceRange>() noexcept;
  template <> VkImageViewCreateInfo make_default<VkImageViewCreateInfo>() noexcept;
  template <> VkImageViewUsageCreateInfo make_default<VkImageViewUsageCreateInfo>() noexcept;
  template <> VkInputAttachmentAspectReference make_default<VkInputAttachmentAspectReference>() noexcept;
  template <> VkInstanceCreateInfo make_default<VkInstanceCreateInfo>() noexcept;
  template <> VkLayerProperties make_default<VkLayerProperties>() noexcept;
  template <> VkMappedMemoryRange make_default<VkMappedMemoryRange>() noexcept;
  template <> VkMemoryAllocateFlagsInfo make_default<VkMemoryAllocateFlagsInfo>() noexcept;
  template <> VkMemoryAllocateInfo make_default<VkMemoryAllocateInfo>() noexcept;
  template <> VkMemoryBarrier make_default<VkMemoryBarrier>() noexcept;
  template <> VkMemoryDedicatedAllocateInfo make_default<VkMemoryDedicatedAllocateInfo>() noexcept;
  template <> VkMemoryDedicatedRequirements make_default<VkMemoryDedicatedRequirements>() noexcept;
  template <> VkMemoryHeap make_default<VkMemoryHeap>() noexcept;
  template <> VkMemoryRequirements make_default<VkMemoryRequirements>() noexcept;
  template <> VkMemoryRequirements2 make_default<VkMemoryRequirements2>() noexcept;
  template <> VkMemoryType make_default<VkMemoryType>() noexcept;
  template <> VkPhysicalDevice16BitStorageFeatures make_default<VkPhysicalDevice16BitStorageFeatures>() noexcept;
  template <> VkPhysicalDeviceExternalBufferInfo make_default<VkPhysicalDeviceExternalBufferInfo>() noexcept;
  template <> VkPhysicalDeviceExternalFenceInfo make_default<VkPhysicalDeviceExternalFenceInfo>() noexcept;
  template <> VkPhysicalDeviceExternalImageFormatInfo make_default<VkPhysicalDeviceExternalImageFormatInfo>() noexcept;
  template <> VkPhysicalDeviceExternalSemaphoreInfo make_default<VkPhysicalDeviceExternalSemaphoreInfo>() noexcept;
  template <> VkPhysicalDeviceFeatures make_default<VkPhysicalDeviceFeatures>() noexcept;
  template <> VkPhysicalDeviceFeatures2 make_default<VkPhysicalDeviceFeatures2>() noexcept;
  template <> VkPhysicalDeviceGroupProperties make_default<VkPhysicalDeviceGroupProperties>() noexcept;
  template <> VkPhysicalDeviceIDProperties make_default<VkPhysicalDeviceIDProperties>() noexcept;
  template <> VkPhysicalDeviceImageFormatInfo2 make_default<VkPhysicalDeviceImageFormatInfo2>() noexcept;
  template <> VkPhysicalDeviceLimits make_default<VkPhysicalDeviceLimits>() noexcept;
  template <> VkPhysicalDeviceMaintenance3Properties make_default<VkPhysicalDeviceMaintenance3Properties>() noexcept;
  template <> VkPhysicalDeviceMemoryProperties make_default<VkPhysicalDeviceMemoryProperties>() noexcept;
  template <> VkPhysicalDeviceMemoryProperties2 make_default<VkPhysicalDeviceMemoryProperties2>() noexcept;
  template <> VkPhysicalDeviceMultiviewFeatures make_default<VkPhysicalDeviceMultiviewFeatures>() noexcept;
  template <> VkPhysicalDeviceMultiviewProperties make_default<VkPhysicalDeviceMultiviewProperties>() noexcept;
  template <> VkPhysicalDevicePointClippingProperties make_default<VkPhysicalDevicePointClippingProperties>() noexcept;
  template <> VkPhysicalDeviceProperties make_default<VkPhysicalDeviceProperties>() noexcept;
  template <> VkPhysicalDeviceProperties2 make_default<VkPhysicalDeviceProperties2>() noexcept;
  template <> VkPhysicalDeviceProtectedMemoryFeatures make_default<VkPhysicalDeviceProtectedMemoryFeatures>() noexcept;
  template <> VkPhysicalDeviceProtectedMemoryProperties make_default<VkPhysicalDeviceProtectedMemoryProperties>() noexcept;
  template <> VkPhysicalDeviceSamplerYcbcrConversionFeatures make_default<VkPhysicalDeviceSamplerYcbcrConversionFeatures>() noexcept;
  template <> VkPhysicalDeviceShaderDrawParameterFeatures make_default<VkPhysicalDeviceShaderDrawParameterFeatures>() noexcept;
  template <> VkPhysicalDeviceSparseImageFormatInfo2 make_default<VkPhysicalDeviceSparseImageFormatInfo2>() noexcept;
  template <> VkPhysicalDeviceSparseProperties make_default<VkPhysicalDeviceSparseProperties>() noexcept;
  template <> VkPhysicalDeviceSubgroupProperties make_default<VkPhysicalDeviceSubgroupProperties>() noexcept;
  template <> VkPhysicalDeviceVariablePointerFeatures make_default<VkPhysicalDeviceVariablePointerFeatures>() noexcept;
  template <> VkPipelineCacheCreateInfo make_default<VkPipelineCacheCreateInfo>() noexcept;
  template <> VkPipelineColorBlendAttachmentState make_default<VkPipelineColorBlendAttachmentState>() noexcept;
  template <> VkPipelineColorBlendStateCreateInfo make_default<VkPipelineColorBlendStateCreateInfo>() noexcept;
  template <> VkPipelineDepthStencilStateCreateInfo make_default<VkPipelineDepthStencilStateCreateInfo>() noexcept;
  template <> VkPipelineDynamicStateCreateInfo make_default<VkPipelineDynamicStateCreateInfo>() noexcept;
  template <> VkPipelineInputAssemblyStateCreateInfo make_default<VkPipelineInputAssemblyStateCreateInfo>() noexcept;
  template <> VkPipelineLayoutCreateInfo make_default<VkPipelineLayoutCreateInfo>() noexcept;
  template <> VkPipelineMultisampleStateCreateInfo make_default<VkPipelineMultisampleStateCreateInfo>() noexcept;
  template <> VkPipelineRasterizationStateCreateInfo make_default<VkPipelineRasterizationStateCreateInfo>() noexcept;
  template <> VkPipelineShaderStageCreateInfo make_default<VkPipelineShaderStageCreateInfo>() noexcept;
  template <> VkPipelineTessellationDomainOriginStateCreateInfo make_default<VkPipelineTessellationDomainOriginStateCreateInfo>() noexcept;
  template <> VkPipelineTessellationStateCreateInfo make_default<VkPipelineTessellationStateCreateInfo>() noexcept;
  template <> VkPipelineVertexInputStateCreateInfo make_default<VkPipelineVertexInputStateCreateInfo>() noexcept;
  template <> VkPipelineViewportStateCreateInfo make_default<VkPipelineViewportStateCreateInfo>() noexcept;
  template <> VkProtectedSubmitInfo make_default<VkProtectedSubmitInfo>() noexcept;
  template <> VkPushConstantRange make_default<VkPushConstantRange>() noexcept;
  template <> VkQueryPoolCreateInfo make_default<VkQueryPoolCreateInfo>() noexcept;
  template <> VkQueueFamilyProperties make_default<VkQueueFamilyProperties>() noexcept;
  template <> VkQueueFamilyProperties2 make_default<VkQueueFamilyProperties2>() noexcept;
  template <> VkRenderPassBeginInfo make_default<VkRenderPassBeginInfo>() noexcept;
  template <> VkRenderPassCreateInfo make_default<VkRenderPassCreateInfo>() noexcept;
  template <> VkRenderPassInputAttachmentAspectCreateInfo make_default<VkRenderPassInputAttachmentAspectCreateInfo>() noexcept;
  template <> VkRenderPassMultiviewCreateInfo make_default<VkRenderPassMultiviewCreateInfo>() noexcept;
  template <> VkSamplerCreateInfo make_default<VkSamplerCreateInfo>() noexcept;
  template <> VkSamplerYcbcrConversionCreateInfo make_default<VkSamplerYcbcrConversionCreateInfo>() noexcept;
  template <> VkSamplerYcbcrConversionImageFormatProperties make_default<VkSamplerYcbcrConversionImageFormatProperties>() noexcept;
  template <> VkSamplerYcbcrConversionInfo make_default<VkSamplerYcbcrConversionInfo>() noexcept;
  template <> VkSemaphoreCreateInfo make_default<VkSemaphoreCreateInfo>() noexcept;
  template <> VkShaderModuleCreateInfo make_default<VkShaderModuleCreateInfo>() noexcept;
  template <> VkSparseBufferMemoryBindInfo make_default<VkSparseBufferMemoryBindInfo>() noexcept;
  template <> VkSparseImageFormatProperties make_default<VkSparseImageFormatProperties>() noexcept;
  template <> VkSparseImageFormatProperties2 make_default<VkSparseImageFormatProperties2>() noexcept;
  template <> VkSparseImageMemoryBind make_default<VkSparseImageMemoryBind>() noexcept;
  template <> VkSparseImageMemoryBindInfo make_default<VkSparseImageMemoryBindInfo>() noexcept;
  template <> VkSparseImageMemoryRequirements make_default<VkSparseImageMemoryRequirements>() noexcept;
  template <> VkSparseImageMemoryRequirements2 make_default<VkSparseImageMemoryRequirements2>() noexcept;
  template <> VkSparseImageOpaqueMemoryBindInfo make_default<VkSparseImageOpaqueMemoryBindInfo>() noexcept;
  template <> VkSparseMemoryBind make_default<VkSparseMemoryBind>() noexcept;
  template <> VkSpecializationInfo make_default<VkSpecializationInfo>() noexcept;
  template <> VkSpecializationMapEntry make_default<VkSpecializationMapEntry>() noexcept;
  template <> VkStencilOpState make_default<VkStencilOpState>() noexcept;
  template <> VkSubmitInfo make_default<VkSubmitInfo>() noexcept;
  template <> VkSubpassDependency make_default<VkSubpassDependency>() noexcept;
  template <> VkSubpassDescription make_default<VkSubpassDescription>() noexcept;
  template <> VkSubresourceLayout make_default<VkSubresourceLayout>() noexcept;
  template <> VkVertexInputAttributeDescription make_default<VkVertexInputAttributeDescription>() noexcept;
  template <> VkVertexInputBindingDescription make_default<VkVertexInputBindingDescription>() noexcept;
  template <> VkViewport make_default<VkViewport>() noexcept;
  template <> VkWriteDescriptorSet make_default<VkWriteDescriptorSet>() noexcept;

  // Extension Structs:
  template <> VkAcquireNextImageInfoKHR make_default<VkAcquireNextImageInfoKHR>() noexcept;
  template <> VkAttachmentSampleLocationsEXT make_default<VkAttachmentSampleLocationsEXT>() noexcept;
  template <> VkBindImageMemorySwapchainInfoKHR make_default<VkBindImageMemorySwapchainInfoKHR>() noexcept;
  template <> VkCmdProcessCommandsInfoNVX make_default<VkCmdProcessCommandsInfoNVX>() noexcept;
  template <> VkCmdReserveSpaceForCommandsInfoNVX make_default<VkCmdReserveSpaceForCommandsInfoNVX>() noexcept;
  template <> VkDebugMarkerMarkerInfoEXT make_default<VkDebugMarkerMarkerInfoEXT>() noexcept;
  template <> VkDebugMarkerObjectNameInfoEXT make_default<VkDebugMarkerObjectNameInfoEXT>() noexcept;
  template <> VkDebugMarkerObjectTagInfoEXT make_default<VkDebugMarkerObjectTagInfoEXT>() noexcept;
  template <> VkDebugReportCallbackCreateInfoEXT make_default<VkDebugReportCallbackCreateInfoEXT>() noexcept;
  template <> VkDebugUtilsLabelEXT make_default<VkDebugUtilsLabelEXT>() noexcept;
  template <> VkDebugUtilsMessengerCallbackDataEXT make_default<VkDebugUtilsMessengerCallbackDataEXT>() noexcept;
  template <> VkDebugUtilsMessengerCreateInfoEXT make_default<VkDebugUtilsMessengerCreateInfoEXT>() noexcept;
  template <> VkDebugUtilsObjectNameInfoEXT make_default<VkDebugUtilsObjectNameInfoEXT>() noexcept;
  template <> VkDebugUtilsObjectTagInfoEXT make_default<VkDebugUtilsObjectTagInfoEXT>() noexcept;
  template <> VkDedicatedAllocationBufferCreateInfoNV make_default<VkDedicatedAllocationBufferCreateInfoNV>() noexcept;
  template <> VkDedicatedAllocationImageCreateInfoNV make_default<VkDedicatedAllocationImageCreateInfoNV>() noexcept;
  template <> VkDedicatedAllocationMemoryAllocateInfoNV make_default<VkDedicatedAllocationMemoryAllocateInfoNV>() noexcept;
  template <> VkDescriptorSetLayoutBindingFlagsCreateInfoEXT make_default<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT>() noexcept;
  template <> VkDescriptorSetVariableDescriptorCountAllocateInfoEXT make_default<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT>() noexcept;
  template <> VkDescriptorSetVariableDescriptorCountLayoutSupportEXT make_default<VkDescriptorSetVariableDescriptorCountLayoutSupportEXT>() noexcept;
  template <> VkDeviceEventInfoEXT make_default<VkDeviceEventInfoEXT>() noexcept;
  template <> VkDeviceGeneratedCommandsFeaturesNVX make_default<VkDeviceGeneratedCommandsFeaturesNVX>() noexcept;
  template <> VkDeviceGeneratedCommandsLimitsNVX make_default<VkDeviceGeneratedCommandsLimitsNVX>() noexcept;
  template <> VkDeviceGroupPresentCapabilitiesKHR make_default<VkDeviceGroupPresentCapabilitiesKHR>() noexcept;
  template <> VkDeviceGroupPresentInfoKHR make_default<VkDeviceGroupPresentInfoKHR>() noexcept;
  template <> VkDeviceGroupSwapchainCreateInfoKHR make_default<VkDeviceGroupSwapchainCreateInfoKHR>() noexcept;
  template <> VkDeviceQueueGlobalPriorityCreateInfoEXT make_default<VkDeviceQueueGlobalPriorityCreateInfoEXT>() noexcept;
  template <> VkDisplayEventInfoEXT make_default<VkDisplayEventInfoEXT>() noexcept;
  template <> VkDisplayModeCreateInfoKHR make_default<VkDisplayModeCreateInfoKHR>() noexcept;
  template <> VkDisplayModeParametersKHR make_default<VkDisplayModeParametersKHR>() noexcept;
  template <> VkDisplayModePropertiesKHR make_default<VkDisplayModePropertiesKHR>() noexcept;
  template <> VkDisplayPlaneCapabilitiesKHR make_default<VkDisplayPlaneCapabilitiesKHR>() noexcept;
  template <> VkDisplayPlanePropertiesKHR make_default<VkDisplayPlanePropertiesKHR>() noexcept;
  template <> VkDisplayPowerInfoEXT make_default<VkDisplayPowerInfoEXT>() noexcept;
  template <> VkDisplayPresentInfoKHR make_default<VkDisplayPresentInfoKHR>() noexcept;
  template <> VkDisplayPropertiesKHR make_default<VkDisplayPropertiesKHR>() noexcept;
  template <> VkDisplaySurfaceCreateInfoKHR make_default<VkDisplaySurfaceCreateInfoKHR>() noexcept;
  template <> VkExportMemoryAllocateInfoNV make_default<VkExportMemoryAllocateInfoNV>() noexcept;
  template <> VkExternalImageFormatPropertiesNV make_default<VkExternalImageFormatPropertiesNV>() noexcept;
  template <> VkExternalMemoryImageCreateInfoNV make_default<VkExternalMemoryImageCreateInfoNV>() noexcept;
  template <> VkFenceGetFdInfoKHR make_default<VkFenceGetFdInfoKHR>() noexcept;
  template <> VkHdrMetadataEXT make_default<VkHdrMetadataEXT>() noexcept;
  template <> VkImageFormatListCreateInfoKHR make_default<VkImageFormatListCreateInfoKHR>() noexcept;
  template <> VkImageSwapchainCreateInfoKHR make_default<VkImageSwapchainCreateInfoKHR>() noexcept;
  template <> VkImportFenceFdInfoKHR make_default<VkImportFenceFdInfoKHR>() noexcept;
  template <> VkImportMemoryFdInfoKHR make_default<VkImportMemoryFdInfoKHR>() noexcept;
  template <> VkImportMemoryHostPointerInfoEXT make_default<VkImportMemoryHostPointerInfoEXT>() noexcept;
  template <> VkImportSemaphoreFdInfoKHR make_default<VkImportSemaphoreFdInfoKHR>() noexcept;
  template <> VkIndirectCommandsLayoutCreateInfoNVX make_default<VkIndirectCommandsLayoutCreateInfoNVX>() noexcept;
  template <> VkIndirectCommandsLayoutTokenNVX make_default<VkIndirectCommandsLayoutTokenNVX>() noexcept;
  template <> VkIndirectCommandsTokenNVX make_default<VkIndirectCommandsTokenNVX>() noexcept;
  template <> VkMemoryFdPropertiesKHR make_default<VkMemoryFdPropertiesKHR>() noexcept;
  template <> VkMemoryGetFdInfoKHR make_default<VkMemoryGetFdInfoKHR>() noexcept;
  template <> VkMultisamplePropertiesEXT make_default<VkMultisamplePropertiesEXT>() noexcept;
  template <> VkObjectTableCreateInfoNVX make_default<VkObjectTableCreateInfoNVX>() noexcept;
  template <> VkObjectTableDescriptorSetEntryNVX make_default<VkObjectTableDescriptorSetEntryNVX>() noexcept;
  template <> VkObjectTableEntryNVX make_default<VkObjectTableEntryNVX>() noexcept;
  template <> VkObjectTableIndexBufferEntryNVX make_default<VkObjectTableIndexBufferEntryNVX>() noexcept;
  template <> VkObjectTablePipelineEntryNVX make_default<VkObjectTablePipelineEntryNVX>() noexcept;
  template <> VkObjectTablePushConstantEntryNVX make_default<VkObjectTablePushConstantEntryNVX>() noexcept;
  template <> VkObjectTableVertexBufferEntryNVX make_default<VkObjectTableVertexBufferEntryNVX>() noexcept;
  template <> VkOffset2D make_default<VkOffset2D>() noexcept;
  template <> VkOffset3D make_default<VkOffset3D>() noexcept;
  template <> VkPastPresentationTimingGOOGLE make_default<VkPastPresentationTimingGOOGLE>() noexcept;
  template <> VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT make_default<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT>() noexcept;
  template <> VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT make_default<VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceConservativeRasterizationPropertiesEXT make_default<VkPhysicalDeviceConservativeRasterizationPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceDescriptorIndexingFeaturesEXT make_default<VkPhysicalDeviceDescriptorIndexingFeaturesEXT>() noexcept;
  template <> VkPhysicalDeviceDescriptorIndexingPropertiesEXT make_default<VkPhysicalDeviceDescriptorIndexingPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceDiscardRectanglePropertiesEXT make_default<VkPhysicalDeviceDiscardRectanglePropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceExternalMemoryHostPropertiesEXT make_default<VkPhysicalDeviceExternalMemoryHostPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX make_default<VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX>() noexcept;
  template <> VkPhysicalDevicePushDescriptorPropertiesKHR make_default<VkPhysicalDevicePushDescriptorPropertiesKHR>() noexcept;
  template <> VkPhysicalDeviceSampleLocationsPropertiesEXT make_default<VkPhysicalDeviceSampleLocationsPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT make_default<VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT>() noexcept;
  template <> VkPhysicalDeviceShaderCorePropertiesAMD make_default<VkPhysicalDeviceShaderCorePropertiesAMD>() noexcept;
  template <> VkPhysicalDeviceSurfaceInfo2KHR make_default<VkPhysicalDeviceSurfaceInfo2KHR>() noexcept;
  template <> VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT make_default<VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT>() noexcept;
  template <> VkPipelineColorBlendAdvancedStateCreateInfoEXT make_default<VkPipelineColorBlendAdvancedStateCreateInfoEXT>() noexcept;
  template <> VkPipelineCoverageModulationStateCreateInfoNV make_default<VkPipelineCoverageModulationStateCreateInfoNV>() noexcept;
  template <> VkPipelineCoverageToColorStateCreateInfoNV make_default<VkPipelineCoverageToColorStateCreateInfoNV>() noexcept;
  template <> VkPipelineDiscardRectangleStateCreateInfoEXT make_default<VkPipelineDiscardRectangleStateCreateInfoEXT>() noexcept;
  template <> VkPipelineRasterizationConservativeStateCreateInfoEXT make_default<VkPipelineRasterizationConservativeStateCreateInfoEXT>() noexcept;
  template <> VkPipelineRasterizationStateRasterizationOrderAMD make_default<VkPipelineRasterizationStateRasterizationOrderAMD>() noexcept;
  template <> VkPipelineSampleLocationsStateCreateInfoEXT make_default<VkPipelineSampleLocationsStateCreateInfoEXT>() noexcept;
  template <> VkPipelineVertexInputDivisorStateCreateInfoEXT make_default<VkPipelineVertexInputDivisorStateCreateInfoEXT>() noexcept;
  template <> VkPipelineViewportSwizzleStateCreateInfoNV make_default<VkPipelineViewportSwizzleStateCreateInfoNV>() noexcept;
  template <> VkPipelineViewportWScalingStateCreateInfoNV make_default<VkPipelineViewportWScalingStateCreateInfoNV>() noexcept;
  template <> VkPresentInfoKHR make_default<VkPresentInfoKHR>() noexcept;
  template <> VkPresentRegionKHR make_default<VkPresentRegionKHR>() noexcept;
  template <> VkPresentRegionsKHR make_default<VkPresentRegionsKHR>() noexcept;
  template <> VkPresentTimeGOOGLE make_default<VkPresentTimeGOOGLE>() noexcept;
  template <> VkPresentTimesInfoGOOGLE make_default<VkPresentTimesInfoGOOGLE>() noexcept;
  template <> VkRect2D make_default<VkRect2D>() noexcept;
  template <> VkRectLayerKHR make_default<VkRectLayerKHR>() noexcept;
  template <> VkRefreshCycleDurationGOOGLE make_default<VkRefreshCycleDurationGOOGLE>() noexcept;
  template <> VkRenderPassSampleLocationsBeginInfoEXT make_default<VkRenderPassSampleLocationsBeginInfoEXT>() noexcept;
  template <> VkSampleLocationEXT make_default<VkSampleLocationEXT>() noexcept;
  template <> VkSampleLocationsInfoEXT make_default<VkSampleLocationsInfoEXT>() noexcept;
  template <> VkSamplerReductionModeCreateInfoEXT make_default<VkSamplerReductionModeCreateInfoEXT>() noexcept;
  template <> VkSemaphoreGetFdInfoKHR make_default<VkSemaphoreGetFdInfoKHR>() noexcept;
  template <> VkShaderModuleValidationCacheCreateInfoEXT make_default<VkShaderModuleValidationCacheCreateInfoEXT>() noexcept;
  template <> VkShaderResourceUsageAMD make_default<VkShaderResourceUsageAMD>() noexcept;
  template <> VkShaderStatisticsInfoAMD make_default<VkShaderStatisticsInfoAMD>() noexcept;
  template <> VkSharedPresentSurfaceCapabilitiesKHR make_default<VkSharedPresentSurfaceCapabilitiesKHR>() noexcept;
  template <> VkSubpassSampleLocationsEXT make_default<VkSubpassSampleLocationsEXT>() noexcept;
  template <> VkSurfaceCapabilities2EXT make_default<VkSurfaceCapabilities2EXT>() noexcept;
  template <> VkSurfaceCapabilities2KHR make_default<VkSurfaceCapabilities2KHR>() noexcept;
  template <> VkSurfaceCapabilitiesKHR make_default<VkSurfaceCapabilitiesKHR>() noexcept;
  template <> VkSurfaceFormat2KHR make_default<VkSurfaceFormat2KHR>() noexcept;
  template <> VkSurfaceFormatKHR make_default<VkSurfaceFormatKHR>() noexcept;
  template <> VkSwapchainCounterCreateInfoEXT make_default<VkSwapchainCounterCreateInfoEXT>() noexcept;
  template <> VkSwapchainCreateInfoKHR make_default<VkSwapchainCreateInfoKHR>() noexcept;
  template <> VkTextureLODGatherFormatPropertiesAMD make_default<VkTextureLODGatherFormatPropertiesAMD>() noexcept;
  template <> VkValidationCacheCreateInfoEXT make_default<VkValidationCacheCreateInfoEXT>() noexcept;
  template <> VkValidationFlagsEXT make_default<VkValidationFlagsEXT>() noexcept;
  template <> VkVertexInputBindingDivisorDescriptionEXT make_default<VkVertexInputBindingDivisorDescriptionEXT>() noexcept;
  template <> VkViewportSwizzleNV make_default<VkViewportSwizzleNV>() noexcept;
  template <> VkViewportWScalingNV make_default<VkViewportWScalingNV>() noexcept;
  template <> VkXYColorEXT make_default<VkXYColorEXT>() noexcept;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
  //Android Platform Structs:
  template <> VkExternalFormatANDROID make_default<VkExternalFormatANDROID>() noexcept;
  template <> VkAndroidHardwareBufferFormatPropertiesANDROID make_default<VkAndroidHardwareBufferFormatPropertiesANDROID>() noexcept;
  template <> VkAndroidHardwareBufferPropertiesANDROID make_default<VkAndroidHardwareBufferPropertiesANDROID>() noexcept;
  template <> VkAndroidHardwareBufferUsageANDROID make_default<VkAndroidHardwareBufferUsageANDROID>() noexcept;
  template <> VkAndroidSurfaceCreateInfoKHR make_default<VkAndroidSurfaceCreateInfoKHR>() noexcept;
  template <> VkImportAndroidHardwareBufferInfoANDROID make_default<VkImportAndroidHardwareBufferInfoANDROID>() noexcept;
  template <> VkMemoryGetAndroidHardwareBufferInfoANDROID make_default<VkMemoryGetAndroidHardwareBufferInfoANDROID>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
  //IOS Platform Structs:
  template <> VkIOSSurfaceCreateInfoMVK make_default<VkIOSSurfaceCreateInfoMVK>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
  //MacOS Platform Structs:
  template <> VkMacOSSurfaceCreateInfoMVK make_default<VkMacOSSurfaceCreateInfoMVK>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
  //Mir Platform Structs:
  template <> VkMirSurfaceCreateInfoKHR make_default<VkMirSurfaceCreateInfoKHR>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_VI_NN
  //Vi Platform Structs:
  template <> VkViSurfaceCreateInfoNN make_default<VkViSurfaceCreateInfoNN>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  //Wayland Platform Structs:
  template <> VkWaylandSurfaceCreateInfoKHR make_default<VkWaylandSurfaceCreateInfoKHR>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
  //Win32 Platform Structs:
  template <> VkD3D12FenceSubmitInfoKHR make_default<VkD3D12FenceSubmitInfoKHR>() noexcept;
  template <> VkExportFenceWin32HandleInfoKHR make_default<VkExportFenceWin32HandleInfoKHR>() noexcept;
  template <> VkExportMemoryWin32HandleInfoKHR make_default<VkExportMemoryWin32HandleInfoKHR>() noexcept;
  template <> VkExportMemoryWin32HandleInfoNV make_default<VkExportMemoryWin32HandleInfoNV>() noexcept;
  template <> VkExportSemaphoreWin32HandleInfoKHR make_default<VkExportSemaphoreWin32HandleInfoKHR>() noexcept;
  template <> VkFenceGetWin32HandleInfoKHR make_default<VkFenceGetWin32HandleInfoKHR>() noexcept;
  template <> VkImportFenceWin32HandleInfoKHR make_default<VkImportFenceWin32HandleInfoKHR>() noexcept;
  template <> VkImportMemoryWin32HandleInfoKHR make_default<VkImportMemoryWin32HandleInfoKHR>() noexcept;
  template <> VkImportMemoryWin32HandleInfoNV make_default<VkImportMemoryWin32HandleInfoNV>() noexcept;
  template <> VkImportSemaphoreWin32HandleInfoKHR make_default<VkImportSemaphoreWin32HandleInfoKHR>() noexcept;
  template <> VkMemoryGetWin32HandleInfoKHR make_default<VkMemoryGetWin32HandleInfoKHR>() noexcept;
  template <> VkMemoryWin32HandlePropertiesKHR make_default<VkMemoryWin32HandlePropertiesKHR>() noexcept;
  template <> VkSemaphoreGetWin32HandleInfoKHR make_default<VkSemaphoreGetWin32HandleInfoKHR>() noexcept;
  template <> VkWin32KeyedMutexAcquireReleaseInfoKHR make_default<VkWin32KeyedMutexAcquireReleaseInfoKHR>() noexcept;
  template <> VkWin32KeyedMutexAcquireReleaseInfoNV make_default<VkWin32KeyedMutexAcquireReleaseInfoNV>() noexcept;
  template <> VkWin32SurfaceCreateInfoKHR make_default<VkWin32SurfaceCreateInfoKHR>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
  //Xcb Platform Structs:
  template <> VkXcbSurfaceCreateInfoKHR make_default<VkXcbSurfaceCreateInfoKHR>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
  //Xlib Platform Structs:
  template <> VkXlibSurfaceCreateInfoKHR make_default<VkXlibSurfaceCreateInfoKHR>() noexcept;
#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  //Xlib XRAndR Platform Structs:
#endif


  // Initialise an entire array with a given value.
  template <typename T, size_t N>
  void set_array(T(&a_array)[N], T&& a_value) noexcept
  {
    for (std::size_t l_index = 0; l_index != N; ++l_index)
    {
      a_array[l_index] = a_value;
    }
  }
} // namespace sdlxvulkan


  // Core Structs:
template <>
inline VkAllocationCallbacks sdlxvulkan::make_default<VkAllocationCallbacks>() noexcept
{
  VkAllocationCallbacks l_result{};
  l_result.pUserData = NULL;
  l_result.pfnAllocation = NULL;
  l_result.pfnReallocation = NULL;
  l_result.pfnFree = NULL;
  l_result.pfnInternalAllocation = NULL;
  l_result.pfnInternalFree = NULL;
  return l_result;
}

template <>
inline VkApplicationInfo sdlxvulkan::make_default<VkApplicationInfo>() noexcept
{
  VkApplicationInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  l_result.pNext = NULL;
  l_result.pApplicationName = NULL;
  l_result.applicationVersion = 0;
  l_result.pEngineName = NULL;
  l_result.engineVersion = 0;
  l_result.apiVersion = 0;
  return l_result;
}

template <>
inline VkAttachmentDescription sdlxvulkan::make_default<VkAttachmentDescription>() noexcept
{
  VkAttachmentDescription l_result{};
  l_result.flags = static_cast<VkAttachmentDescriptionFlags>(0);
  l_result.format = static_cast<VkFormat>(0);
  l_result.samples = static_cast<VkSampleCountFlagBits>(0);
  l_result.loadOp = static_cast<VkAttachmentLoadOp>(0);
  l_result.storeOp = static_cast<VkAttachmentStoreOp>(0);
  l_result.stencilLoadOp = static_cast<VkAttachmentLoadOp>(0);
  l_result.stencilStoreOp = static_cast<VkAttachmentStoreOp>(0);
  l_result.initialLayout = static_cast<VkImageLayout>(0);
  l_result.finalLayout = static_cast<VkImageLayout>(0);
  return l_result;
}

template <>
inline VkAttachmentReference sdlxvulkan::make_default<VkAttachmentReference>() noexcept
{
  VkAttachmentReference l_result{};
  l_result.attachment = 0;
  l_result.layout = static_cast<VkImageLayout>(0);
  return l_result;
}

template <>
inline VkBindBufferMemoryDeviceGroupInfo sdlxvulkan::make_default<VkBindBufferMemoryDeviceGroupInfo>() noexcept
{
  VkBindBufferMemoryDeviceGroupInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO;
  l_result.pNext = NULL;
  l_result.deviceIndexCount = 0;
  l_result.pDeviceIndices = NULL;
  return l_result;
}

template <>
inline VkBindBufferMemoryInfo sdlxvulkan::make_default<VkBindBufferMemoryInfo>() noexcept
{
  VkBindBufferMemoryInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO;
  l_result.pNext = NULL;
  l_result.buffer = VK_NULL_HANDLE;
  l_result.memory = VK_NULL_HANDLE;
  l_result.memoryOffset = 0;
  return l_result;
}

template <>
inline VkBindImageMemoryDeviceGroupInfo sdlxvulkan::make_default<VkBindImageMemoryDeviceGroupInfo>() noexcept
{
  VkBindImageMemoryDeviceGroupInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO;
  l_result.pNext = NULL;
  l_result.deviceIndexCount = 0;
  l_result.pDeviceIndices = NULL;
  l_result.splitInstanceBindRegionCount = 0;
  l_result.pSplitInstanceBindRegions = NULL;
  return l_result;
}

template <>
inline VkBindImageMemoryInfo sdlxvulkan::make_default<VkBindImageMemoryInfo>() noexcept
{
  VkBindImageMemoryInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
  l_result.pNext = NULL;
  l_result.image = VK_NULL_HANDLE;
  l_result.memory = VK_NULL_HANDLE;
  l_result.memoryOffset = 0;
  return l_result;
}

template <>
inline VkBindImagePlaneMemoryInfo sdlxvulkan::make_default<VkBindImagePlaneMemoryInfo>() noexcept
{
  VkBindImagePlaneMemoryInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
  l_result.pNext = NULL;
  l_result.planeAspect = static_cast<VkImageAspectFlagBits>(0);
  return l_result;
}

template <>
inline VkBindSparseInfo sdlxvulkan::make_default<VkBindSparseInfo>() noexcept
{
  VkBindSparseInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
  l_result.pNext = NULL;
  l_result.waitSemaphoreCount = 0;
  l_result.pWaitSemaphores = NULL;
  l_result.bufferBindCount = 0;
  l_result.pBufferBinds = NULL;
  l_result.imageOpaqueBindCount = 0;
  l_result.pImageOpaqueBinds = NULL;
  l_result.imageBindCount = 0;
  l_result.pImageBinds = NULL;
  l_result.signalSemaphoreCount = 0;
  l_result.pSignalSemaphores = NULL;
  return l_result;
}

template <>
inline VkBufferCopy sdlxvulkan::make_default<VkBufferCopy>() noexcept
{
  VkBufferCopy l_result{};
  l_result.srcOffset = 0;
  l_result.dstOffset = 0;
  l_result.size = 0;
  return l_result;
}

template <>
inline VkBufferCreateInfo sdlxvulkan::make_default<VkBufferCreateInfo>() noexcept
{
  VkBufferCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkBufferCreateFlags>(0);
  l_result.size = 0;
  l_result.usage = static_cast<VkBufferUsageFlags>(0);
  l_result.sharingMode = static_cast<VkSharingMode>(0);
  l_result.queueFamilyIndexCount = 0;
  l_result.pQueueFamilyIndices = NULL;
  return l_result;
}

template <>
inline VkBufferImageCopy sdlxvulkan::make_default<VkBufferImageCopy>() noexcept
{
  VkBufferImageCopy l_result{};
  l_result.bufferOffset = 0;
  l_result.bufferRowLength = 0;
  l_result.bufferImageHeight = 0;
  l_result.imageSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  l_result.imageOffset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.imageExtent = sdlxvulkan::make_default<VkExtent3D>();
  return l_result;
}

template <>
inline VkBufferMemoryBarrier sdlxvulkan::make_default<VkBufferMemoryBarrier>() noexcept
{
  VkBufferMemoryBarrier l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
  l_result.pNext = NULL;
  l_result.srcAccessMask = static_cast<VkAccessFlags>(0);
  l_result.dstAccessMask = static_cast<VkAccessFlags>(0);
  l_result.srcQueueFamilyIndex = 0;
  l_result.dstQueueFamilyIndex = 0;
  l_result.buffer = VK_NULL_HANDLE;
  l_result.offset = 0;
  l_result.size = 0;
  return l_result;
}

template <>
inline VkBufferMemoryRequirementsInfo2 sdlxvulkan::make_default<VkBufferMemoryRequirementsInfo2>() noexcept
{
  VkBufferMemoryRequirementsInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
  l_result.pNext = NULL;
  l_result.buffer = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkBufferViewCreateInfo sdlxvulkan::make_default<VkBufferViewCreateInfo>() noexcept
{
  VkBufferViewCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkBufferViewCreateFlags>(0);
  l_result.buffer = VK_NULL_HANDLE;
  l_result.format = static_cast<VkFormat>(0);
  l_result.offset = 0;
  l_result.range = 0;
  return l_result;
}

template <>
inline VkClearAttachment sdlxvulkan::make_default<VkClearAttachment>() noexcept
{
  VkClearAttachment l_result{};
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  l_result.colorAttachment = 0;
  l_result.clearValue = sdlxvulkan::make_default<VkClearValue>();
  return l_result;
}

template <>
inline VkClearDepthStencilValue sdlxvulkan::make_default<VkClearDepthStencilValue>() noexcept
{
  VkClearDepthStencilValue l_result{};
  l_result.depth = 0.0f;
  l_result.stencil = 0;
  return l_result;
}

template <>
inline VkClearRect sdlxvulkan::make_default<VkClearRect>() noexcept
{
  VkClearRect l_result{};
  l_result.rect = sdlxvulkan::make_default<VkRect2D>();
  l_result.baseArrayLayer = 0;
  l_result.layerCount = 0;
  return l_result;
}

template <>
inline VkCommandBufferAllocateInfo sdlxvulkan::make_default<VkCommandBufferAllocateInfo>() noexcept
{
  VkCommandBufferAllocateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_result.pNext = NULL;
  l_result.commandPool = VK_NULL_HANDLE;
  l_result.level = static_cast<VkCommandBufferLevel>(0);
  l_result.commandBufferCount = 0;
  return l_result;
}

template <>
inline VkCommandBufferBeginInfo sdlxvulkan::make_default<VkCommandBufferBeginInfo>() noexcept
{
  VkCommandBufferBeginInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkCommandBufferUsageFlags>(0);
  l_result.pInheritanceInfo = NULL;
  return l_result;
}

template <>
inline VkCommandBufferInheritanceInfo sdlxvulkan::make_default<VkCommandBufferInheritanceInfo>() noexcept
{
  VkCommandBufferInheritanceInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  l_result.pNext = NULL;
  l_result.renderPass = VK_NULL_HANDLE;
  l_result.subpass = 0;
  l_result.framebuffer = VK_NULL_HANDLE;
  l_result.occlusionQueryEnable = VK_FALSE;
  l_result.queryFlags = static_cast<VkQueryControlFlags>(0);
  l_result.pipelineStatistics = static_cast<VkQueryPipelineStatisticFlags>(0);
  return l_result;
}

template <>
inline VkCommandPoolCreateInfo sdlxvulkan::make_default<VkCommandPoolCreateInfo>() noexcept
{
  VkCommandPoolCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkCommandPoolCreateFlags>(0);
  l_result.queueFamilyIndex = 0;
  return l_result;
}

template <>
inline VkComponentMapping sdlxvulkan::make_default<VkComponentMapping>() noexcept
{
  VkComponentMapping l_result{};
  l_result.r = static_cast<VkComponentSwizzle>(0);
  l_result.g = static_cast<VkComponentSwizzle>(0);
  l_result.b = static_cast<VkComponentSwizzle>(0);
  l_result.a = static_cast<VkComponentSwizzle>(0);
  return l_result;
}

template <>
inline VkComputePipelineCreateInfo sdlxvulkan::make_default<VkComputePipelineCreateInfo>() noexcept
{
  VkComputePipelineCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineCreateFlags>(0);
  l_result.stage = sdlxvulkan::make_default<VkPipelineShaderStageCreateInfo>();
  l_result.layout = VK_NULL_HANDLE;
  l_result.basePipelineHandle = VK_NULL_HANDLE;
  l_result.basePipelineIndex = 0;
  return l_result;
}

template <>
inline VkCopyDescriptorSet sdlxvulkan::make_default<VkCopyDescriptorSet>() noexcept
{
  VkCopyDescriptorSet l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
  l_result.pNext = NULL;
  l_result.srcSet = VK_NULL_HANDLE;
  l_result.srcBinding = 0;
  l_result.srcArrayElement = 0;
  l_result.dstSet = VK_NULL_HANDLE;
  l_result.dstBinding = 0;
  l_result.dstArrayElement = 0;
  l_result.descriptorCount = 0;
  return l_result;
}

template <>
inline VkDescriptorBufferInfo sdlxvulkan::make_default<VkDescriptorBufferInfo>() noexcept
{
  VkDescriptorBufferInfo l_result{};
  l_result.buffer = VK_NULL_HANDLE;
  l_result.offset = 0;
  l_result.range = 0;
  return l_result;
}

template <>
inline VkDescriptorImageInfo sdlxvulkan::make_default<VkDescriptorImageInfo>() noexcept
{
  VkDescriptorImageInfo l_result{};
  l_result.sampler = VK_NULL_HANDLE;
  l_result.imageView = VK_NULL_HANDLE;
  l_result.imageLayout = static_cast<VkImageLayout>(0);
  return l_result;
}

template <>
inline VkDescriptorPoolCreateInfo sdlxvulkan::make_default<VkDescriptorPoolCreateInfo>() noexcept
{
  VkDescriptorPoolCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDescriptorPoolCreateFlags>(0);
  l_result.maxSets = 0;
  l_result.poolSizeCount = 0;
  l_result.pPoolSizes = NULL;
  return l_result;
}

template <>
inline VkDescriptorPoolSize sdlxvulkan::make_default<VkDescriptorPoolSize>() noexcept
{
  VkDescriptorPoolSize l_result{};
  l_result.type = static_cast<VkDescriptorType>(0);
  l_result.descriptorCount = 0;
  return l_result;
}

template <>
inline VkDescriptorSetAllocateInfo sdlxvulkan::make_default<VkDescriptorSetAllocateInfo>() noexcept
{
  VkDescriptorSetAllocateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  l_result.pNext = NULL;
  l_result.descriptorPool = VK_NULL_HANDLE;
  l_result.descriptorSetCount = 0;
  l_result.pSetLayouts = NULL;
  return l_result;
}

template <>
inline VkDescriptorSetLayoutBinding sdlxvulkan::make_default<VkDescriptorSetLayoutBinding>() noexcept
{
  VkDescriptorSetLayoutBinding l_result{};
  l_result.binding = 0;
  l_result.descriptorType = static_cast<VkDescriptorType>(0);
  l_result.descriptorCount = 0;
  l_result.stageFlags = static_cast<VkShaderStageFlags>(0);
  l_result.pImmutableSamplers = NULL;
  return l_result;
}

template <>
inline VkDescriptorSetLayoutCreateInfo sdlxvulkan::make_default<VkDescriptorSetLayoutCreateInfo>() noexcept
{
  VkDescriptorSetLayoutCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDescriptorSetLayoutCreateFlags>(0);
  l_result.bindingCount = 0;
  l_result.pBindings = NULL;
  return l_result;
}

template <>
inline VkDescriptorSetLayoutSupport sdlxvulkan::make_default<VkDescriptorSetLayoutSupport>() noexcept
{
  VkDescriptorSetLayoutSupport l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
  l_result.pNext = NULL;
  l_result.supported = VK_FALSE;
  return l_result;
}

template <>
inline VkDescriptorUpdateTemplateCreateInfo sdlxvulkan::make_default<VkDescriptorUpdateTemplateCreateInfo>() noexcept
{
  VkDescriptorUpdateTemplateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDescriptorUpdateTemplateCreateFlags>(0);
  l_result.descriptorUpdateEntryCount = 0;
  l_result.pDescriptorUpdateEntries = NULL;
  l_result.templateType = static_cast<VkDescriptorUpdateTemplateType>(0);
  l_result.descriptorSetLayout = VK_NULL_HANDLE;
  l_result.pipelineBindPoint = static_cast<VkPipelineBindPoint>(0);
  l_result.pipelineLayout = VK_NULL_HANDLE;
  l_result.set = 0;
  return l_result;
}

template <>
inline VkDescriptorUpdateTemplateEntry sdlxvulkan::make_default<VkDescriptorUpdateTemplateEntry>() noexcept
{
  VkDescriptorUpdateTemplateEntry l_result{};
  l_result.dstBinding = 0;
  l_result.dstArrayElement = 0;
  l_result.descriptorCount = 0;
  l_result.descriptorType = static_cast<VkDescriptorType>(0);
  l_result.offset = 0;
  l_result.stride = 0;
  return l_result;
}

template <>
inline VkDeviceCreateInfo sdlxvulkan::make_default<VkDeviceCreateInfo>() noexcept
{
  VkDeviceCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDeviceCreateFlags>(0);
  l_result.queueCreateInfoCount = 0;
  l_result.pQueueCreateInfos = NULL;
  l_result.enabledLayerCount = 0;       // Deprecated, IGNORE
  l_result.ppEnabledLayerNames = NULL;  // Deprecated, IGNORE
  l_result.enabledExtensionCount = 0;
  l_result.ppEnabledExtensionNames = NULL;
  l_result.pEnabledFeatures = NULL;
  return l_result;
}

template <>
inline VkDeviceGroupBindSparseInfo sdlxvulkan::make_default<VkDeviceGroupBindSparseInfo>() noexcept
{
  VkDeviceGroupBindSparseInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO;
  l_result.pNext = NULL;
  l_result.resourceDeviceIndex = 0;
  l_result.memoryDeviceIndex = 0;
  return l_result;
}

template <>
inline VkDeviceGroupCommandBufferBeginInfo sdlxvulkan::make_default<VkDeviceGroupCommandBufferBeginInfo>() noexcept
{
  VkDeviceGroupCommandBufferBeginInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
  l_result.pNext = NULL;
  l_result.deviceMask = 0;
  return l_result;
}

template <>
inline VkDeviceGroupDeviceCreateInfo sdlxvulkan::make_default<VkDeviceGroupDeviceCreateInfo>() noexcept
{
  VkDeviceGroupDeviceCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.physicalDeviceCount = 0;
  l_result.pPhysicalDevices = NULL;
  return l_result;
}

template <>
inline VkDeviceGroupRenderPassBeginInfo sdlxvulkan::make_default<VkDeviceGroupRenderPassBeginInfo>() noexcept
{
  VkDeviceGroupRenderPassBeginInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
  l_result.pNext = NULL;
  l_result.deviceMask = 0;
  l_result.deviceRenderAreaCount = 0;
  l_result.pDeviceRenderAreas = NULL;
  return l_result;
}

template <>
inline VkDeviceGroupSubmitInfo sdlxvulkan::make_default<VkDeviceGroupSubmitInfo>() noexcept
{
  VkDeviceGroupSubmitInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
  l_result.pNext = NULL;
  l_result.waitSemaphoreCount = 0;
  l_result.pWaitSemaphoreDeviceIndices = NULL;
  l_result.commandBufferCount = 0;
  l_result.pCommandBufferDeviceMasks = NULL;
  l_result.signalSemaphoreCount = 0;
  l_result.pSignalSemaphoreDeviceIndices = NULL;
  return l_result;
}

template <>
inline VkDeviceQueueCreateInfo sdlxvulkan::make_default<VkDeviceQueueCreateInfo>() noexcept
{
  VkDeviceQueueCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDeviceQueueCreateFlags>(0);
  l_result.queueFamilyIndex = 0;
  l_result.queueCount = 0;
  l_result.pQueuePriorities = NULL;
  return l_result;
}

template <>
inline VkDeviceQueueInfo2 sdlxvulkan::make_default<VkDeviceQueueInfo2>() noexcept
{
  VkDeviceQueueInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDeviceQueueCreateFlags>(0);
  l_result.queueFamilyIndex = 0;
  l_result.queueIndex = 0;
  return l_result;
}

template <>
inline VkDispatchIndirectCommand sdlxvulkan::make_default<VkDispatchIndirectCommand>() noexcept
{
  VkDispatchIndirectCommand l_result{};
  l_result.x = 0;
  l_result.y = 0;
  l_result.z = 0;
  return l_result;
}

template <>
inline VkDrawIndexedIndirectCommand sdlxvulkan::make_default<VkDrawIndexedIndirectCommand>() noexcept
{
  VkDrawIndexedIndirectCommand l_result{};
  l_result.indexCount = 0;
  l_result.instanceCount = 0;
  l_result.firstIndex = 0;
  l_result.vertexOffset = 0;
  l_result.firstInstance = 0;
  return l_result;
}

template <>
inline VkDrawIndirectCommand sdlxvulkan::make_default<VkDrawIndirectCommand>() noexcept
{
  VkDrawIndirectCommand l_result{};
  l_result.vertexCount = 0;
  l_result.instanceCount = 0;
  l_result.firstVertex = 0;
  l_result.firstInstance = 0;
  return l_result;
}

template <>
inline VkEventCreateInfo sdlxvulkan::make_default<VkEventCreateInfo>() noexcept
{
  VkEventCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkEventCreateFlags>(0);
  return l_result;
}

template <>
inline VkExportFenceCreateInfo sdlxvulkan::make_default<VkExportFenceCreateInfo>() noexcept
{
  VkExportFenceCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalFenceHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExportMemoryAllocateInfo sdlxvulkan::make_default<VkExportMemoryAllocateInfo>() noexcept
{
  VkExportMemoryAllocateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalMemoryHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExportSemaphoreCreateInfo sdlxvulkan::make_default<VkExportSemaphoreCreateInfo>() noexcept
{
  VkExportSemaphoreCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalSemaphoreHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExtensionProperties sdlxvulkan::make_default<VkExtensionProperties>() noexcept
{
  VkExtensionProperties l_result{};
  //l_result.extensionName = { u8'\0' };
  set_array(l_result.extensionName, u8'\0');
  l_result.specVersion = 0;
  return l_result;
}

template <>
inline VkExtent2D sdlxvulkan::make_default<VkExtent2D>() noexcept
{
  VkExtent2D l_result{};
  l_result.width = 0;
  l_result.height = 0;
  return l_result;
}

template <>
inline VkExtent3D sdlxvulkan::make_default<VkExtent3D>() noexcept
{
  VkExtent3D l_result{};
  l_result.width = 0;
  l_result.height = 0;
  l_result.depth = 0;
  return l_result;
}

template <>
inline VkExternalBufferProperties sdlxvulkan::make_default<VkExternalBufferProperties>() noexcept
{
  VkExternalBufferProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
  l_result.pNext = NULL;
  l_result.externalMemoryProperties = sdlxvulkan::make_default<VkExternalMemoryProperties>();
  return l_result;
}

template <>
inline VkExternalFenceProperties sdlxvulkan::make_default<VkExternalFenceProperties>() noexcept
{
  VkExternalFenceProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
  l_result.pNext = NULL;
  l_result.exportFromImportedHandleTypes = static_cast<VkExternalFenceHandleTypeFlags>(0);
  l_result.compatibleHandleTypes = static_cast<VkExternalFenceHandleTypeFlags>(0);
  l_result.externalFenceFeatures = static_cast<VkExternalFenceFeatureFlags>(0);
  return l_result;
}

template <>
inline VkExternalImageFormatProperties sdlxvulkan::make_default<VkExternalImageFormatProperties>() noexcept
{
  VkExternalImageFormatProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;
  l_result.pNext = NULL;
  l_result.externalMemoryProperties = sdlxvulkan::make_default<VkExternalMemoryProperties>();
  return l_result;
}

template <>
inline VkExternalMemoryBufferCreateInfo sdlxvulkan::make_default<VkExternalMemoryBufferCreateInfo>() noexcept
{
  VkExternalMemoryBufferCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalMemoryHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExternalMemoryImageCreateInfo sdlxvulkan::make_default<VkExternalMemoryImageCreateInfo>() noexcept
{
  VkExternalMemoryImageCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalMemoryHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExternalMemoryProperties sdlxvulkan::make_default<VkExternalMemoryProperties>() noexcept
{
  VkExternalMemoryProperties l_result{};
  l_result.externalMemoryFeatures = static_cast<VkExternalMemoryFeatureFlags>(0);
  l_result.exportFromImportedHandleTypes = static_cast<VkExternalMemoryHandleTypeFlags>(0);
  l_result.compatibleHandleTypes = static_cast<VkExternalMemoryHandleTypeFlags>(0);
  return l_result;
}

template <>
inline VkExternalSemaphoreProperties sdlxvulkan::make_default<VkExternalSemaphoreProperties>() noexcept
{
  VkExternalSemaphoreProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
  l_result.pNext = NULL;
  l_result.exportFromImportedHandleTypes = static_cast<VkExternalSemaphoreHandleTypeFlags>(0);
  l_result.compatibleHandleTypes = static_cast<VkExternalSemaphoreHandleTypeFlags>(0);
  l_result.externalSemaphoreFeatures = static_cast<VkExternalSemaphoreFeatureFlags>(0);
  return l_result;
}

template <>
inline VkFenceCreateInfo sdlxvulkan::make_default<VkFenceCreateInfo>() noexcept
{
  VkFenceCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkFenceCreateFlags>(0);
  return l_result;
}

template <>
inline VkFormatProperties sdlxvulkan::make_default<VkFormatProperties>() noexcept
{
  VkFormatProperties l_result{};
  l_result.linearTilingFeatures = static_cast<VkFormatFeatureFlags>(0);
  l_result.optimalTilingFeatures = static_cast<VkFormatFeatureFlags>(0);
  l_result.bufferFeatures = static_cast<VkFormatFeatureFlags>(0);
  return l_result;
}

template <>
inline VkFormatProperties2 sdlxvulkan::make_default<VkFormatProperties2>() noexcept
{
  VkFormatProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.formatProperties = sdlxvulkan::make_default<VkFormatProperties>();
  return l_result;
}

template <>
inline VkFramebufferCreateInfo sdlxvulkan::make_default<VkFramebufferCreateInfo>() noexcept
{
  VkFramebufferCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkFramebufferCreateFlags>(0);
  l_result.renderPass = VK_NULL_HANDLE;
  l_result.attachmentCount = 0;
  l_result.pAttachments = NULL;
  l_result.width = 0;
  l_result.height = 0;
  l_result.layers = 0;
  return l_result;
}

template <>
inline VkGraphicsPipelineCreateInfo sdlxvulkan::make_default<VkGraphicsPipelineCreateInfo>() noexcept
{
  VkGraphicsPipelineCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineCreateFlags>(0);
  l_result.stageCount = 0;
  l_result.pStages = NULL;
  l_result.pVertexInputState = NULL;
  l_result.pInputAssemblyState = NULL;
  l_result.pTessellationState = NULL;
  l_result.pViewportState = NULL;
  l_result.pRasterizationState = NULL;
  l_result.pMultisampleState = NULL;
  l_result.pDepthStencilState = NULL;
  l_result.pColorBlendState = NULL;
  l_result.pDynamicState = NULL;
  l_result.layout = VK_NULL_HANDLE;
  l_result.renderPass = VK_NULL_HANDLE;
  l_result.subpass = 0;
  l_result.basePipelineHandle = VK_NULL_HANDLE;
  l_result.basePipelineIndex = 0;
  return l_result;
}

template <>
inline VkImageBlit sdlxvulkan::make_default<VkImageBlit>() noexcept
{
  VkImageBlit l_result{};
  l_result.srcSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  //l_result.srcOffsets = { sdlxvulkan::make_default<VkOffset3D>() };
  set_array(l_result.srcOffsets, sdlxvulkan::make_default<VkOffset3D>());
  l_result.dstSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  //l_result.dstOffsets = { sdlxvulkan::make_default<VkOffset3D>() };
  set_array(l_result.dstOffsets, sdlxvulkan::make_default<VkOffset3D>());
  return l_result;
}

template <>
inline VkImageCopy sdlxvulkan::make_default<VkImageCopy>() noexcept
{
  VkImageCopy l_result{};
  l_result.srcSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  l_result.srcOffset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.dstSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  l_result.dstOffset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.extent = sdlxvulkan::make_default<VkExtent3D>();
  return l_result;
}

template <>
inline VkImageCreateInfo sdlxvulkan::make_default<VkImageCreateInfo>() noexcept
{
  VkImageCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkImageCreateFlags>(0);
  l_result.imageType = static_cast<VkImageType>(0);
  l_result.format = static_cast<VkFormat>(0);
  l_result.extent = sdlxvulkan::make_default<VkExtent3D>();
  l_result.mipLevels = 0;
  l_result.arrayLayers = 0;
  l_result.samples = static_cast<VkSampleCountFlagBits>(0);
  l_result.tiling = static_cast<VkImageTiling>(0);
  l_result.usage = static_cast<VkImageUsageFlags>(0);
  l_result.sharingMode = static_cast<VkSharingMode>(0);
  l_result.queueFamilyIndexCount = 0;
  l_result.pQueueFamilyIndices = NULL;
  l_result.initialLayout = static_cast<VkImageLayout>(0);
  return l_result;
}

template <>
inline VkImageFormatProperties sdlxvulkan::make_default<VkImageFormatProperties>() noexcept
{
  VkImageFormatProperties l_result{};
  l_result.maxExtent = sdlxvulkan::make_default<VkExtent3D>();
  l_result.maxMipLevels = 0;
  l_result.maxArrayLayers = 0;
  l_result.sampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.maxResourceSize = 0;
  return l_result;
}

template <>
inline VkImageFormatProperties2 sdlxvulkan::make_default<VkImageFormatProperties2>() noexcept
{
  VkImageFormatProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.imageFormatProperties = sdlxvulkan::make_default<VkImageFormatProperties>();
  return l_result;
}

template <>
inline VkImageMemoryBarrier sdlxvulkan::make_default<VkImageMemoryBarrier>() noexcept
{
  VkImageMemoryBarrier l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  l_result.pNext = NULL;
  l_result.srcAccessMask = static_cast<VkAccessFlags>(0);
  l_result.dstAccessMask = static_cast<VkAccessFlags>(0);
  l_result.oldLayout = static_cast<VkImageLayout>(0);
  l_result.newLayout = static_cast<VkImageLayout>(0);
  l_result.srcQueueFamilyIndex = 0;
  l_result.dstQueueFamilyIndex = 0;
  l_result.image = VK_NULL_HANDLE;
  l_result.subresourceRange = sdlxvulkan::make_default<VkImageSubresourceRange>();
  return l_result;
}

template <>
inline VkImageMemoryRequirementsInfo2 sdlxvulkan::make_default<VkImageMemoryRequirementsInfo2>() noexcept
{
  VkImageMemoryRequirementsInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
  l_result.pNext = NULL;
  l_result.image = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkImagePlaneMemoryRequirementsInfo sdlxvulkan::make_default<VkImagePlaneMemoryRequirementsInfo>() noexcept
{
  VkImagePlaneMemoryRequirementsInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO;
  l_result.pNext = NULL;
  l_result.planeAspect = static_cast<VkImageAspectFlagBits>(0);
  return l_result;
}

template <>
inline VkImageResolve sdlxvulkan::make_default<VkImageResolve>() noexcept
{
  VkImageResolve l_result{};
  l_result.srcSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  l_result.srcOffset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.dstSubresource = sdlxvulkan::make_default<VkImageSubresourceLayers>();
  l_result.dstOffset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.extent = sdlxvulkan::make_default<VkExtent3D>();
  return l_result;
}

template <>
inline VkImageSparseMemoryRequirementsInfo2 sdlxvulkan::make_default<VkImageSparseMemoryRequirementsInfo2>() noexcept
{
  VkImageSparseMemoryRequirementsInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
  l_result.pNext = NULL;
  l_result.image = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkImageSubresource sdlxvulkan::make_default<VkImageSubresource>() noexcept
{
  VkImageSubresource l_result{};
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  l_result.mipLevel = 0;
  l_result.arrayLayer = 0;
  return l_result;
}

template <>
inline VkImageSubresourceLayers sdlxvulkan::make_default<VkImageSubresourceLayers>() noexcept
{
  VkImageSubresourceLayers l_result{};
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  l_result.mipLevel = 0;
  l_result.baseArrayLayer = 0;
  l_result.layerCount = 0;
  return l_result;
}

template <>
inline VkImageSubresourceRange sdlxvulkan::make_default<VkImageSubresourceRange>() noexcept
{
  VkImageSubresourceRange l_result{};
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  l_result.baseMipLevel = 0;
  l_result.levelCount = 0;
  l_result.baseArrayLayer = 0;
  l_result.layerCount = 0;
  return l_result;
}

template <>
inline VkImageViewCreateInfo sdlxvulkan::make_default<VkImageViewCreateInfo>() noexcept
{
  VkImageViewCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkImageViewCreateFlags>(0);
  l_result.image = VK_NULL_HANDLE;
  l_result.viewType = static_cast<VkImageViewType>(0);
  l_result.format = static_cast<VkFormat>(0);
  l_result.components = sdlxvulkan::make_default<VkComponentMapping>();
  l_result.subresourceRange = sdlxvulkan::make_default<VkImageSubresourceRange>();
  return l_result;
}

template <>
inline VkImageViewUsageCreateInfo sdlxvulkan::make_default<VkImageViewUsageCreateInfo>() noexcept
{
  VkImageViewUsageCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.usage = static_cast<VkImageUsageFlags>(0);
  return l_result;
}

template <>
inline VkInputAttachmentAspectReference sdlxvulkan::make_default<VkInputAttachmentAspectReference>() noexcept
{
  VkInputAttachmentAspectReference l_result{};
  l_result.subpass = 0;
  l_result.inputAttachmentIndex = 0;
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  return l_result;
}

template <>
inline VkInstanceCreateInfo sdlxvulkan::make_default<VkInstanceCreateInfo>() noexcept
{
  VkInstanceCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkInstanceCreateFlags>(0);
  l_result.pApplicationInfo = NULL;
  l_result.enabledLayerCount = 0;
  l_result.ppEnabledLayerNames = NULL;
  l_result.enabledExtensionCount = 0;
  l_result.ppEnabledExtensionNames = NULL;
  return l_result;
}

template <>
inline VkLayerProperties sdlxvulkan::make_default<VkLayerProperties>() noexcept
{
  VkLayerProperties l_result{};
  //l_result.layerName = { u8'\0' };
  set_array(l_result.layerName, u8'\0');
  l_result.specVersion = 0;
  l_result.implementationVersion = 0;
  //l_result.description = { u8'\0' };
  set_array(l_result.description, u8'\0');
  return l_result;
}

template <>
inline VkMappedMemoryRange sdlxvulkan::make_default<VkMappedMemoryRange>() noexcept
{
  VkMappedMemoryRange l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
  l_result.pNext = NULL;
  l_result.memory = VK_NULL_HANDLE;
  l_result.offset = 0;
  l_result.size = 0;
  return l_result;
}

template <>
inline VkMemoryAllocateFlagsInfo sdlxvulkan::make_default<VkMemoryAllocateFlagsInfo>() noexcept
{
  VkMemoryAllocateFlagsInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkMemoryAllocateFlags>(0);
  l_result.deviceMask = 0;
  return l_result;
}

template <>
inline VkMemoryAllocateInfo sdlxvulkan::make_default<VkMemoryAllocateInfo>() noexcept
{
  VkMemoryAllocateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_result.pNext = NULL;
  l_result.allocationSize = 0;
  l_result.memoryTypeIndex = 0;
  return l_result;
}

template <>
inline VkMemoryBarrier sdlxvulkan::make_default<VkMemoryBarrier>() noexcept
{
  VkMemoryBarrier l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
  l_result.pNext = NULL;
  l_result.srcAccessMask = static_cast<VkAccessFlags>(0);
  l_result.dstAccessMask = static_cast<VkAccessFlags>(0);
  return l_result;
}

template <>
inline VkMemoryDedicatedAllocateInfo sdlxvulkan::make_default<VkMemoryDedicatedAllocateInfo>() noexcept
{
  VkMemoryDedicatedAllocateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
  l_result.pNext = NULL;
  l_result.image = VK_NULL_HANDLE;
  l_result.buffer = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkMemoryDedicatedRequirements sdlxvulkan::make_default<VkMemoryDedicatedRequirements>() noexcept
{
  VkMemoryDedicatedRequirements l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
  l_result.pNext = NULL;
  l_result.prefersDedicatedAllocation = VK_FALSE;
  l_result.requiresDedicatedAllocation = VK_FALSE;
  return l_result;
}

template <>
inline VkMemoryHeap sdlxvulkan::make_default<VkMemoryHeap>() noexcept
{
  VkMemoryHeap l_result{};
  l_result.size = 0;
  l_result.flags = static_cast<VkMemoryHeapFlags>(0);
  return l_result;
}

template <>
inline VkMemoryRequirements sdlxvulkan::make_default<VkMemoryRequirements>() noexcept
{
  VkMemoryRequirements l_result{};
  l_result.size = 0;
  l_result.alignment = 0;
  l_result.memoryTypeBits = 0;
  return l_result;
}

template <>
inline VkMemoryRequirements2 sdlxvulkan::make_default<VkMemoryRequirements2>() noexcept
{
  VkMemoryRequirements2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  l_result.pNext = NULL;
  l_result.memoryRequirements = sdlxvulkan::make_default<VkMemoryRequirements>();
  return l_result;
}

template <>
inline VkMemoryType sdlxvulkan::make_default<VkMemoryType>() noexcept
{
  VkMemoryType l_result{};
  l_result.propertyFlags = static_cast<VkMemoryPropertyFlags>(0);
  l_result.heapIndex = 0;
  return l_result;
}

template <>
inline VkPhysicalDevice16BitStorageFeatures sdlxvulkan::make_default<VkPhysicalDevice16BitStorageFeatures>() noexcept
{
  VkPhysicalDevice16BitStorageFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
  l_result.pNext = NULL;
  l_result.storageBuffer16BitAccess = VK_FALSE;
  l_result.uniformAndStorageBuffer16BitAccess = VK_FALSE;
  l_result.storagePushConstant16 = VK_FALSE;
  l_result.storageInputOutput16 = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceExternalBufferInfo sdlxvulkan::make_default<VkPhysicalDeviceExternalBufferInfo>() noexcept
{
  VkPhysicalDeviceExternalBufferInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkBufferCreateFlags>(0);
  l_result.usage = static_cast<VkBufferUsageFlags>(0);
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceExternalFenceInfo sdlxvulkan::make_default<VkPhysicalDeviceExternalFenceInfo>() noexcept
{
  VkPhysicalDeviceExternalFenceInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalFenceHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceExternalImageFormatInfo sdlxvulkan::make_default<VkPhysicalDeviceExternalImageFormatInfo>() noexcept
{
  VkPhysicalDeviceExternalImageFormatInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceExternalSemaphoreInfo sdlxvulkan::make_default<VkPhysicalDeviceExternalSemaphoreInfo>() noexcept
{
  VkPhysicalDeviceExternalSemaphoreInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalSemaphoreHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceFeatures sdlxvulkan::make_default<VkPhysicalDeviceFeatures>() noexcept
{
  VkPhysicalDeviceFeatures l_result{};
  l_result.robustBufferAccess = VK_FALSE;
  l_result.fullDrawIndexUint32 = VK_FALSE;
  l_result.imageCubeArray = VK_FALSE;
  l_result.independentBlend = VK_FALSE;
  l_result.geometryShader = VK_FALSE;
  l_result.tessellationShader = VK_FALSE;
  l_result.sampleRateShading = VK_FALSE;
  l_result.dualSrcBlend = VK_FALSE;
  l_result.logicOp = VK_FALSE;
  l_result.multiDrawIndirect = VK_FALSE;
  l_result.drawIndirectFirstInstance = VK_FALSE;
  l_result.depthClamp = VK_FALSE;
  l_result.depthBiasClamp = VK_FALSE;
  l_result.fillModeNonSolid = VK_FALSE;
  l_result.depthBounds = VK_FALSE;
  l_result.wideLines = VK_FALSE;
  l_result.largePoints = VK_FALSE;
  l_result.alphaToOne = VK_FALSE;
  l_result.multiViewport = VK_FALSE;
  l_result.samplerAnisotropy = VK_FALSE;
  l_result.textureCompressionETC2 = VK_FALSE;
  l_result.textureCompressionASTC_LDR = VK_FALSE;
  l_result.textureCompressionBC = VK_FALSE;
  l_result.occlusionQueryPrecise = VK_FALSE;
  l_result.pipelineStatisticsQuery = VK_FALSE;
  l_result.vertexPipelineStoresAndAtomics = VK_FALSE;
  l_result.fragmentStoresAndAtomics = VK_FALSE;
  l_result.shaderTessellationAndGeometryPointSize = VK_FALSE;
  l_result.shaderImageGatherExtended = VK_FALSE;
  l_result.shaderStorageImageExtendedFormats = VK_FALSE;
  l_result.shaderStorageImageMultisample = VK_FALSE;
  l_result.shaderStorageImageReadWithoutFormat = VK_FALSE;
  l_result.shaderStorageImageWriteWithoutFormat = VK_FALSE;
  l_result.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
  l_result.shaderSampledImageArrayDynamicIndexing = VK_FALSE;
  l_result.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
  l_result.shaderStorageImageArrayDynamicIndexing = VK_FALSE;
  l_result.shaderClipDistance = VK_FALSE;
  l_result.shaderCullDistance = VK_FALSE;
  l_result.shaderFloat64 = VK_FALSE;
  l_result.shaderInt64 = VK_FALSE;
  l_result.shaderInt16 = VK_FALSE;
  l_result.shaderResourceResidency = VK_FALSE;
  l_result.shaderResourceMinLod = VK_FALSE;
  l_result.sparseBinding = VK_FALSE;
  l_result.sparseResidencyBuffer = VK_FALSE;
  l_result.sparseResidencyImage2D = VK_FALSE;
  l_result.sparseResidencyImage3D = VK_FALSE;
  l_result.sparseResidency2Samples = VK_FALSE;
  l_result.sparseResidency4Samples = VK_FALSE;
  l_result.sparseResidency8Samples = VK_FALSE;
  l_result.sparseResidency16Samples = VK_FALSE;
  l_result.sparseResidencyAliased = VK_FALSE;
  l_result.variableMultisampleRate = VK_FALSE;
  l_result.inheritedQueries = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceFeatures2 sdlxvulkan::make_default<VkPhysicalDeviceFeatures2>() noexcept
{
  VkPhysicalDeviceFeatures2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  l_result.pNext = NULL;
  l_result.features = sdlxvulkan::make_default<VkPhysicalDeviceFeatures>();
  return l_result;
}

template <>
inline VkPhysicalDeviceGroupProperties sdlxvulkan::make_default<VkPhysicalDeviceGroupProperties>() noexcept
{
  VkPhysicalDeviceGroupProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
  l_result.pNext = NULL;
  l_result.physicalDeviceCount = 0;
  //l_result.physicalDevices = { VK_NULL_HANDLE };
  set_array(l_result.physicalDevices, static_cast<VkPhysicalDevice>(VK_NULL_HANDLE));
  l_result.subsetAllocation = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceIDProperties sdlxvulkan::make_default<VkPhysicalDeviceIDProperties>() noexcept
{
  VkPhysicalDeviceIDProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES;
  l_result.pNext = NULL;
  //l_result.deviceUUID = { 0 };
  set_array(l_result.deviceUUID, static_cast<uint8_t>(0u));
  //l_result.driverUUID = { 0 };
  set_array(l_result.driverUUID, static_cast<uint8_t>(0u));
  //l_result.deviceLUID = { 0 };
  set_array(l_result.deviceLUID, static_cast<uint8_t>(0u));
  l_result.deviceNodeMask = 0;
  l_result.deviceLUIDValid = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceImageFormatInfo2 sdlxvulkan::make_default<VkPhysicalDeviceImageFormatInfo2>() noexcept
{
  VkPhysicalDeviceImageFormatInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
  l_result.pNext = NULL;
  l_result.format = static_cast<VkFormat>(0);
  l_result.type = static_cast<VkImageType>(0);
  l_result.tiling = static_cast<VkImageTiling>(0);
  l_result.usage = static_cast<VkImageUsageFlags>(0);
  l_result.flags = static_cast<VkImageCreateFlags>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceLimits sdlxvulkan::make_default<VkPhysicalDeviceLimits>() noexcept
{
  VkPhysicalDeviceLimits l_result{};
  l_result.maxImageDimension1D = 0;
  l_result.maxImageDimension2D = 0;
  l_result.maxImageDimension3D = 0;
  l_result.maxImageDimensionCube = 0;
  l_result.maxImageArrayLayers = 0;
  l_result.maxTexelBufferElements = 0;
  l_result.maxUniformBufferRange = 0;
  l_result.maxStorageBufferRange = 0;
  l_result.maxPushConstantsSize = 0;
  l_result.maxMemoryAllocationCount = 0;
  l_result.maxSamplerAllocationCount = 0;
  l_result.bufferImageGranularity = 0;
  l_result.sparseAddressSpaceSize = 0;
  l_result.maxBoundDescriptorSets = 0;
  l_result.maxPerStageDescriptorSamplers = 0;
  l_result.maxPerStageDescriptorUniformBuffers = 0;
  l_result.maxPerStageDescriptorStorageBuffers = 0;
  l_result.maxPerStageDescriptorSampledImages = 0;
  l_result.maxPerStageDescriptorStorageImages = 0;
  l_result.maxPerStageDescriptorInputAttachments = 0;
  l_result.maxPerStageResources = 0;
  l_result.maxDescriptorSetSamplers = 0;
  l_result.maxDescriptorSetUniformBuffers = 0;
  l_result.maxDescriptorSetUniformBuffersDynamic = 0;
  l_result.maxDescriptorSetStorageBuffers = 0;
  l_result.maxDescriptorSetStorageBuffersDynamic = 0;
  l_result.maxDescriptorSetSampledImages = 0;
  l_result.maxDescriptorSetStorageImages = 0;
  l_result.maxDescriptorSetInputAttachments = 0;
  l_result.maxVertexInputAttributes = 0;
  l_result.maxVertexInputBindings = 0;
  l_result.maxVertexInputAttributeOffset = 0;
  l_result.maxVertexInputBindingStride = 0;
  l_result.maxVertexOutputComponents = 0;
  l_result.maxTessellationGenerationLevel = 0;
  l_result.maxTessellationPatchSize = 0;
  l_result.maxTessellationControlPerVertexInputComponents = 0;
  l_result.maxTessellationControlPerVertexOutputComponents = 0;
  l_result.maxTessellationControlPerPatchOutputComponents = 0;
  l_result.maxTessellationControlTotalOutputComponents = 0;
  l_result.maxTessellationEvaluationInputComponents = 0;
  l_result.maxTessellationEvaluationOutputComponents = 0;
  l_result.maxGeometryShaderInvocations = 0;
  l_result.maxGeometryInputComponents = 0;
  l_result.maxGeometryOutputComponents = 0;
  l_result.maxGeometryOutputVertices = 0;
  l_result.maxGeometryTotalOutputComponents = 0;
  l_result.maxFragmentInputComponents = 0;
  l_result.maxFragmentOutputAttachments = 0;
  l_result.maxFragmentDualSrcAttachments = 0;
  l_result.maxFragmentCombinedOutputResources = 0;
  l_result.maxComputeSharedMemorySize = 0;
  //l_result.maxComputeWorkGroupCount = { 0 };
  set_array(l_result.maxComputeWorkGroupCount, static_cast<uint32_t>(0u));
  l_result.maxComputeWorkGroupInvocations = 0;
  //l_result.maxComputeWorkGroupSize = { 0 };
  set_array(l_result.maxComputeWorkGroupSize, static_cast<uint32_t>(0u));
  l_result.subPixelPrecisionBits = 0;
  l_result.subTexelPrecisionBits = 0;
  l_result.mipmapPrecisionBits = 0;
  l_result.maxDrawIndexedIndexValue = 0;
  l_result.maxDrawIndirectCount = 0;
  l_result.maxSamplerLodBias = 0.0f;
  l_result.maxSamplerAnisotropy = 0.0f;
  l_result.maxViewports = 0;
  //l_result.maxViewportDimensions = { 0 };
  set_array(l_result.maxViewportDimensions, static_cast<uint32_t>(0u));
  //l_result.viewportBoundsRange = { 0.0f };
  set_array(l_result.viewportBoundsRange, 0.0f);
  l_result.viewportSubPixelBits = 0;
  l_result.minMemoryMapAlignment = 0;
  l_result.minTexelBufferOffsetAlignment = 0;
  l_result.minUniformBufferOffsetAlignment = 0;
  l_result.minStorageBufferOffsetAlignment = 0;
  l_result.minTexelOffset = 0;
  l_result.maxTexelOffset = 0;
  l_result.minTexelGatherOffset = 0;
  l_result.maxTexelGatherOffset = 0;
  l_result.minInterpolationOffset = 0.0f;
  l_result.maxInterpolationOffset = 0.0f;
  l_result.subPixelInterpolationOffsetBits = 0;
  l_result.maxFramebufferWidth = 0;
  l_result.maxFramebufferHeight = 0;
  l_result.maxFramebufferLayers = 0;
  l_result.framebufferColorSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.framebufferDepthSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.framebufferStencilSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.framebufferNoAttachmentsSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.maxColorAttachments = 0;
  l_result.sampledImageColorSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.sampledImageIntegerSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.sampledImageDepthSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.sampledImageStencilSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.storageImageSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.maxSampleMaskWords = 0;
  l_result.timestampComputeAndGraphics = VK_FALSE;
  l_result.timestampPeriod = 0.0f;
  l_result.maxClipDistances = 0;
  l_result.maxCullDistances = 0;
  l_result.maxCombinedClipAndCullDistances = 0;
  l_result.discreteQueuePriorities = 0;
  //l_result.pointSizeRange = { 0.0f };
  set_array(l_result.pointSizeRange, 0.0f);
  //l_result.lineWidthRange = { 0.0f };
  set_array(l_result.lineWidthRange, 0.0f);
  l_result.pointSizeGranularity = 0.0f;
  l_result.lineWidthGranularity = 0.0f;
  l_result.strictLines = VK_FALSE;
  l_result.standardSampleLocations = VK_FALSE;
  l_result.optimalBufferCopyOffsetAlignment = 0;
  l_result.optimalBufferCopyRowPitchAlignment = 0;
  l_result.nonCoherentAtomSize = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceMaintenance3Properties sdlxvulkan::make_default<VkPhysicalDeviceMaintenance3Properties>() noexcept
{
  VkPhysicalDeviceMaintenance3Properties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
  l_result.pNext = NULL;
  l_result.maxPerSetDescriptors = 0;
  l_result.maxMemoryAllocationSize = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceMemoryProperties sdlxvulkan::make_default<VkPhysicalDeviceMemoryProperties>() noexcept
{
  VkPhysicalDeviceMemoryProperties l_result{};
  l_result.memoryTypeCount = 0;
  //l_result.memoryTypes = { sdlxvulkan::make_default<VkMemoryType>() };
  set_array(l_result.memoryTypes, sdlxvulkan::make_default<VkMemoryType>());
  l_result.memoryHeapCount = 0;
  //l_result.memoryHeaps = { sdlxvulkan::make_default<VkMemoryHeap>() };
  set_array(l_result.memoryHeaps, sdlxvulkan::make_default<VkMemoryHeap>());
  return l_result;
}

template <>
inline VkPhysicalDeviceMemoryProperties2 sdlxvulkan::make_default<VkPhysicalDeviceMemoryProperties2>() noexcept
{
  VkPhysicalDeviceMemoryProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.memoryProperties = sdlxvulkan::make_default<VkPhysicalDeviceMemoryProperties>();
  return l_result;
}

template <>
inline VkPhysicalDeviceMultiviewFeatures sdlxvulkan::make_default<VkPhysicalDeviceMultiviewFeatures>() noexcept
{
  VkPhysicalDeviceMultiviewFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
  l_result.pNext = NULL;
  l_result.multiview = VK_FALSE;
  l_result.multiviewGeometryShader = VK_FALSE;
  l_result.multiviewTessellationShader = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX sdlxvulkan::make_default<VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX>() noexcept
{
  VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
  l_result.pNext = NULL;
  l_result.perViewPositionAllComponents = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceMultiviewProperties sdlxvulkan::make_default<VkPhysicalDeviceMultiviewProperties>() noexcept
{
  VkPhysicalDeviceMultiviewProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
  l_result.pNext = NULL;
  l_result.maxMultiviewViewCount = 0;
  l_result.maxMultiviewInstanceIndex = 0;
  return l_result;
}

template <>
inline VkPhysicalDevicePointClippingProperties sdlxvulkan::make_default<VkPhysicalDevicePointClippingProperties>() noexcept
{
  VkPhysicalDevicePointClippingProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
  l_result.pNext = NULL;
  l_result.pointClippingBehavior = static_cast<VkPointClippingBehavior>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceProperties sdlxvulkan::make_default<VkPhysicalDeviceProperties>() noexcept
{
  VkPhysicalDeviceProperties l_result{};
  l_result.apiVersion = 0;
  l_result.driverVersion = 0;
  l_result.vendorID = 0;
  l_result.deviceID = 0;
  l_result.deviceType = static_cast<VkPhysicalDeviceType>(0);
  //l_result.deviceName = { u8'\0' };
  set_array(l_result.deviceName, u8'\0');
  //l_result.pipelineCacheUUID = { 0 };
  set_array(l_result.pipelineCacheUUID, static_cast<uint8_t>(0u));
  l_result.limits = sdlxvulkan::make_default<VkPhysicalDeviceLimits>();
  l_result.sparseProperties = sdlxvulkan::make_default<VkPhysicalDeviceSparseProperties>();
  return l_result;
}

template <>
inline VkPhysicalDeviceProperties2 sdlxvulkan::make_default<VkPhysicalDeviceProperties2>() noexcept
{
  VkPhysicalDeviceProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.properties = sdlxvulkan::make_default<VkPhysicalDeviceProperties>();
  return l_result;
}

template <>
inline VkPhysicalDeviceProtectedMemoryFeatures sdlxvulkan::make_default<VkPhysicalDeviceProtectedMemoryFeatures>() noexcept
{
  VkPhysicalDeviceProtectedMemoryFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
  l_result.pNext = NULL;
  l_result.protectedMemory = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceProtectedMemoryProperties sdlxvulkan::make_default<VkPhysicalDeviceProtectedMemoryProperties>() noexcept
{
  VkPhysicalDeviceProtectedMemoryProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
  l_result.pNext = NULL;
  l_result.protectedNoFault = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceSamplerYcbcrConversionFeatures sdlxvulkan::make_default<VkPhysicalDeviceSamplerYcbcrConversionFeatures>() noexcept
{
  VkPhysicalDeviceSamplerYcbcrConversionFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
  l_result.pNext = NULL;
  l_result.samplerYcbcrConversion = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceShaderDrawParameterFeatures sdlxvulkan::make_default<VkPhysicalDeviceShaderDrawParameterFeatures>() noexcept
{
  VkPhysicalDeviceShaderDrawParameterFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETER_FEATURES;
  l_result.pNext = NULL;
  l_result.shaderDrawParameters = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceSparseImageFormatInfo2 sdlxvulkan::make_default<VkPhysicalDeviceSparseImageFormatInfo2>() noexcept
{
  VkPhysicalDeviceSparseImageFormatInfo2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
  l_result.pNext = NULL;
  l_result.format = static_cast<VkFormat>(0);
  l_result.type = static_cast<VkImageType>(0);
  l_result.samples = static_cast<VkSampleCountFlagBits>(0);
  l_result.usage = static_cast<VkImageUsageFlags>(0);
  l_result.tiling = static_cast<VkImageTiling>(0);
  return l_result;
}

template <>
inline VkPhysicalDeviceSparseProperties sdlxvulkan::make_default<VkPhysicalDeviceSparseProperties>() noexcept
{
  VkPhysicalDeviceSparseProperties l_result{};
  l_result.residencyStandard2DBlockShape = VK_FALSE;
  l_result.residencyStandard2DMultisampleBlockShape = VK_FALSE;
  l_result.residencyStandard3DBlockShape = VK_FALSE;
  l_result.residencyAlignedMipSize = VK_FALSE;
  l_result.residencyNonResidentStrict = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceSubgroupProperties sdlxvulkan::make_default<VkPhysicalDeviceSubgroupProperties>() noexcept
{
  VkPhysicalDeviceSubgroupProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
  l_result.pNext = NULL;
  l_result.subgroupSize = 0;
  l_result.supportedStages = static_cast<VkShaderStageFlags>(0);
  l_result.supportedOperations = static_cast<VkSubgroupFeatureFlags>(0);
  l_result.quadOperationsInAllStages = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceVariablePointerFeatures sdlxvulkan::make_default<VkPhysicalDeviceVariablePointerFeatures>() noexcept
{
  VkPhysicalDeviceVariablePointerFeatures l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTER_FEATURES;
  l_result.pNext = NULL;
  l_result.variablePointersStorageBuffer = VK_FALSE;
  l_result.variablePointers = VK_FALSE;
  return l_result;
}






template <>
inline VkPipelineCacheCreateInfo sdlxvulkan::make_default<VkPipelineCacheCreateInfo>() noexcept
{
  VkPipelineCacheCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineCacheCreateFlags>(0);
  l_result.initialDataSize = 0;
  l_result.pInitialData = NULL;
  return l_result;
}

template <>
inline VkPipelineColorBlendAttachmentState sdlxvulkan::make_default<VkPipelineColorBlendAttachmentState>() noexcept
{
  VkPipelineColorBlendAttachmentState l_result{};
  l_result.blendEnable = VK_FALSE;
  l_result.srcColorBlendFactor = static_cast<VkBlendFactor>(0);
  l_result.dstColorBlendFactor = static_cast<VkBlendFactor>(0);
  l_result.colorBlendOp = static_cast<VkBlendOp>(0);
  l_result.srcAlphaBlendFactor = static_cast<VkBlendFactor>(0);
  l_result.dstAlphaBlendFactor = static_cast<VkBlendFactor>(0);
  l_result.alphaBlendOp = static_cast<VkBlendOp>(0);
  l_result.colorWriteMask = static_cast<VkColorComponentFlags>(0);
  return l_result;
}

template <>
inline VkPipelineColorBlendStateCreateInfo sdlxvulkan::make_default<VkPipelineColorBlendStateCreateInfo>() noexcept
{
  VkPipelineColorBlendStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineColorBlendStateCreateFlags>(0);
  l_result.logicOpEnable = VK_FALSE;
  l_result.logicOp = static_cast<VkLogicOp>(0);
  l_result.attachmentCount = 0;
  l_result.pAttachments = NULL;
  //l_result.blendConstants = { 0.0f };
  set_array(l_result.blendConstants, 0.0f);
  return l_result;
}

template <>
inline VkPipelineDepthStencilStateCreateInfo sdlxvulkan::make_default<VkPipelineDepthStencilStateCreateInfo>() noexcept
{
  VkPipelineDepthStencilStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineDepthStencilStateCreateFlags>(0);
  l_result.depthTestEnable = VK_FALSE;
  l_result.depthWriteEnable = VK_FALSE;
  l_result.depthCompareOp = static_cast<VkCompareOp>(0);
  l_result.depthBoundsTestEnable = VK_FALSE;
  l_result.stencilTestEnable = VK_FALSE;
  l_result.front = sdlxvulkan::make_default<VkStencilOpState>();
  l_result.back = sdlxvulkan::make_default<VkStencilOpState>();
  l_result.minDepthBounds = 0.0f;
  l_result.maxDepthBounds = 0.0f;
  return l_result;
}

template <>
inline VkPipelineDynamicStateCreateInfo sdlxvulkan::make_default<VkPipelineDynamicStateCreateInfo>() noexcept
{
  VkPipelineDynamicStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineDynamicStateCreateFlags>(0);
  l_result.dynamicStateCount = 0;
  l_result.pDynamicStates = NULL;
  return l_result;
}

template <>
inline VkPipelineInputAssemblyStateCreateInfo sdlxvulkan::make_default<VkPipelineInputAssemblyStateCreateInfo>() noexcept
{
  VkPipelineInputAssemblyStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineInputAssemblyStateCreateFlags>(0);
  l_result.topology = static_cast<VkPrimitiveTopology>(0);
  l_result.primitiveRestartEnable = VK_FALSE;
  return l_result;
}

template <>
inline VkPipelineLayoutCreateInfo sdlxvulkan::make_default<VkPipelineLayoutCreateInfo>() noexcept
{
  VkPipelineLayoutCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineLayoutCreateFlags>(0);
  l_result.setLayoutCount = 0;
  l_result.pSetLayouts = NULL;
  l_result.pushConstantRangeCount = 0;
  l_result.pPushConstantRanges = NULL;
  return l_result;
}

template <>
inline VkPipelineMultisampleStateCreateInfo sdlxvulkan::make_default<VkPipelineMultisampleStateCreateInfo>() noexcept
{
  VkPipelineMultisampleStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineMultisampleStateCreateFlags>(0);
  l_result.rasterizationSamples = static_cast<VkSampleCountFlagBits>(0);
  l_result.sampleShadingEnable = VK_FALSE;
  l_result.minSampleShading = 0.0f;
  l_result.pSampleMask = NULL;
  l_result.alphaToCoverageEnable = VK_FALSE;
  l_result.alphaToOneEnable = VK_FALSE;
  return l_result;
}

template <>
inline VkPipelineRasterizationStateCreateInfo sdlxvulkan::make_default<VkPipelineRasterizationStateCreateInfo>() noexcept
{
  VkPipelineRasterizationStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineRasterizationStateCreateFlags>(0);
  l_result.depthClampEnable = VK_FALSE;
  l_result.rasterizerDiscardEnable = VK_FALSE;
  l_result.polygonMode = static_cast<VkPolygonMode>(0);
  l_result.cullMode = static_cast<VkCullModeFlags>(0);
  l_result.frontFace = static_cast<VkFrontFace>(0);
  l_result.depthBiasEnable = VK_FALSE;
  l_result.depthBiasConstantFactor = 0.0f;
  l_result.depthBiasClamp = 0.0f;
  l_result.depthBiasSlopeFactor = 0.0f;
  l_result.lineWidth = 0.0f;
  return l_result;
}

template <>
inline VkPipelineShaderStageCreateInfo sdlxvulkan::make_default<VkPipelineShaderStageCreateInfo>() noexcept
{
  VkPipelineShaderStageCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineShaderStageCreateFlags>(0);
  l_result.stage = static_cast<VkShaderStageFlagBits>(0);
  l_result.module = VK_NULL_HANDLE;
  l_result.pName = NULL;
  l_result.pSpecializationInfo = NULL;
  return l_result;
}

template <>
inline VkPipelineTessellationDomainOriginStateCreateInfo sdlxvulkan::make_default<VkPipelineTessellationDomainOriginStateCreateInfo>() noexcept
{
  VkPipelineTessellationDomainOriginStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.domainOrigin = static_cast<VkTessellationDomainOrigin>(0);
  return l_result;
}

template <>
inline VkPipelineTessellationStateCreateInfo sdlxvulkan::make_default<VkPipelineTessellationStateCreateInfo>() noexcept
{
  VkPipelineTessellationStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineTessellationStateCreateFlags>(0);
  l_result.patchControlPoints = 0;
  return l_result;
}

template <>
inline VkPipelineVertexInputStateCreateInfo sdlxvulkan::make_default<VkPipelineVertexInputStateCreateInfo>() noexcept
{
  VkPipelineVertexInputStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineVertexInputStateCreateFlags>(0);
  l_result.vertexBindingDescriptionCount = 0;
  l_result.pVertexBindingDescriptions = NULL;
  l_result.vertexAttributeDescriptionCount = 0;
  l_result.pVertexAttributeDescriptions = NULL;
  return l_result;
}

template <>
inline VkPipelineViewportStateCreateInfo sdlxvulkan::make_default<VkPipelineViewportStateCreateInfo>() noexcept
{
  VkPipelineViewportStateCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineViewportStateCreateFlags>(0);
  l_result.viewportCount = 0;
  l_result.pViewports = NULL;
  l_result.scissorCount = 0;
  l_result.pScissors = NULL;
  return l_result;
}

template <>
inline VkPipelineViewportSwizzleStateCreateInfoNV sdlxvulkan::make_default<VkPipelineViewportSwizzleStateCreateInfoNV>() noexcept
{
  VkPipelineViewportSwizzleStateCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineViewportSwizzleStateCreateFlagsNV>(0);
  l_result.viewportCount = 0;
  l_result.pViewportSwizzles = NULL;
  return l_result;
}

template <>
inline VkPipelineViewportWScalingStateCreateInfoNV sdlxvulkan::make_default<VkPipelineViewportWScalingStateCreateInfoNV>() noexcept
{
  VkPipelineViewportWScalingStateCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.viewportWScalingEnable = VK_FALSE;
  l_result.viewportCount = 0;
  l_result.pViewportWScalings = NULL;
  return l_result;
}

template <>
inline VkProtectedSubmitInfo sdlxvulkan::make_default<VkProtectedSubmitInfo>() noexcept
{
  VkProtectedSubmitInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
  l_result.pNext = NULL;
  l_result.protectedSubmit = VK_FALSE;
  return l_result;
}

template <>
inline VkPushConstantRange sdlxvulkan::make_default<VkPushConstantRange>() noexcept
{
  VkPushConstantRange l_result{};
  l_result.stageFlags = static_cast<VkShaderStageFlags>(0);
  l_result.offset = 0;
  l_result.size = 0;
  return l_result;
}

template <>
inline VkQueryPoolCreateInfo sdlxvulkan::make_default<VkQueryPoolCreateInfo>() noexcept
{
  VkQueryPoolCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkQueryPoolCreateFlags>(0);
  l_result.queryType = static_cast<VkQueryType>(0);
  l_result.queryCount = 0;
  l_result.pipelineStatistics = static_cast<VkQueryPipelineStatisticFlags>(0);
  return l_result;
}

template <>
inline VkQueueFamilyProperties sdlxvulkan::make_default<VkQueueFamilyProperties>() noexcept
{
  VkQueueFamilyProperties l_result{};
  l_result.queueFlags = static_cast<VkQueueFlags>(0);
  l_result.queueCount = 0;
  l_result.timestampValidBits = 0;
  l_result.minImageTransferGranularity = sdlxvulkan::make_default<VkExtent3D>();
  return l_result;
}

template <>
inline VkQueueFamilyProperties2 sdlxvulkan::make_default<VkQueueFamilyProperties2>() noexcept
{
  VkQueueFamilyProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.queueFamilyProperties = sdlxvulkan::make_default<VkQueueFamilyProperties>();
  return l_result;
}

template <>
inline VkRenderPassBeginInfo sdlxvulkan::make_default<VkRenderPassBeginInfo>() noexcept
{
  VkRenderPassBeginInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  l_result.pNext = NULL;
  l_result.renderPass = VK_NULL_HANDLE;
  l_result.framebuffer = VK_NULL_HANDLE;
  l_result.renderArea = sdlxvulkan::make_default<VkRect2D>();
  l_result.clearValueCount = 0;
  l_result.pClearValues = NULL;
  return l_result;
}

template <>
inline VkRenderPassCreateInfo sdlxvulkan::make_default<VkRenderPassCreateInfo>() noexcept
{
  VkRenderPassCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkRenderPassCreateFlags>(0);
  l_result.attachmentCount = 0;
  l_result.pAttachments = NULL;
  l_result.subpassCount = 0;
  l_result.pSubpasses = NULL;
  l_result.dependencyCount = 0;
  l_result.pDependencies = NULL;
  return l_result;
}

template <>
inline VkRenderPassInputAttachmentAspectCreateInfo sdlxvulkan::make_default<VkRenderPassInputAttachmentAspectCreateInfo>() noexcept
{
  VkRenderPassInputAttachmentAspectCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.aspectReferenceCount = 0;
  l_result.pAspectReferences = NULL;
  return l_result;
}

template <>
inline VkRenderPassMultiviewCreateInfo sdlxvulkan::make_default<VkRenderPassMultiviewCreateInfo>() noexcept
{
  VkRenderPassMultiviewCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.subpassCount = 0;
  l_result.pViewMasks = NULL;
  l_result.dependencyCount = 0;
  l_result.pViewOffsets = NULL;
  l_result.correlationMaskCount = 0;
  l_result.pCorrelationMasks = NULL;
  return l_result;
}

template <>
inline VkSamplerCreateInfo sdlxvulkan::make_default<VkSamplerCreateInfo>() noexcept
{
  VkSamplerCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkSamplerCreateFlags>(0);
  l_result.magFilter = static_cast<VkFilter>(0);
  l_result.minFilter = static_cast<VkFilter>(0);
  l_result.mipmapMode = static_cast<VkSamplerMipmapMode>(0);
  l_result.addressModeU = static_cast<VkSamplerAddressMode>(0);
  l_result.addressModeV = static_cast<VkSamplerAddressMode>(0);
  l_result.addressModeW = static_cast<VkSamplerAddressMode>(0);
  l_result.mipLodBias = 0.0f;
  l_result.anisotropyEnable = VK_FALSE;
  l_result.maxAnisotropy = 0.0f;
  l_result.compareEnable = VK_FALSE;
  l_result.compareOp = static_cast<VkCompareOp>(0);
  l_result.minLod = 0.0f;
  l_result.maxLod = 0.0f;
  l_result.borderColor = static_cast<VkBorderColor>(0);
  l_result.unnormalizedCoordinates = VK_FALSE;
  return l_result;
}

template <>
inline VkSamplerYcbcrConversionCreateInfo sdlxvulkan::make_default<VkSamplerYcbcrConversionCreateInfo>() noexcept
{
  VkSamplerYcbcrConversionCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.format = static_cast<VkFormat>(0);
  l_result.ycbcrModel = static_cast<VkSamplerYcbcrModelConversion>(0);
  l_result.ycbcrRange = static_cast<VkSamplerYcbcrRange>(0);
  l_result.components = sdlxvulkan::make_default<VkComponentMapping>();
  l_result.xChromaOffset = static_cast<VkChromaLocation>(0);
  l_result.yChromaOffset = static_cast<VkChromaLocation>(0);
  l_result.chromaFilter = static_cast<VkFilter>(0);
  l_result.forceExplicitReconstruction = VK_FALSE;
  return l_result;
}

template <>
inline VkSamplerYcbcrConversionImageFormatProperties sdlxvulkan::make_default<VkSamplerYcbcrConversionImageFormatProperties>() noexcept
{
  VkSamplerYcbcrConversionImageFormatProperties l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES;
  l_result.pNext = NULL;
  l_result.combinedImageSamplerDescriptorCount = 0;
  return l_result;
}

template <>
inline VkSamplerYcbcrConversionInfo sdlxvulkan::make_default<VkSamplerYcbcrConversionInfo>() noexcept
{
  VkSamplerYcbcrConversionInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
  l_result.pNext = NULL;
  l_result.conversion = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkSemaphoreCreateInfo sdlxvulkan::make_default<VkSemaphoreCreateInfo>() noexcept
{
  VkSemaphoreCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkSemaphoreCreateFlags>(0);
  return l_result;
}

template <>
inline VkShaderModuleCreateInfo sdlxvulkan::make_default<VkShaderModuleCreateInfo>() noexcept
{
  VkShaderModuleCreateInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkShaderModuleCreateFlags>(0);
  l_result.codeSize = 0;
  l_result.pCode = NULL;
  return l_result;
}

template <>
inline VkSparseBufferMemoryBindInfo sdlxvulkan::make_default<VkSparseBufferMemoryBindInfo>() noexcept
{
  VkSparseBufferMemoryBindInfo l_result{};
  l_result.buffer = VK_NULL_HANDLE;
  l_result.bindCount = 0;
  l_result.pBinds = NULL;
  return l_result;
}

template <>
inline VkSparseImageFormatProperties sdlxvulkan::make_default<VkSparseImageFormatProperties>() noexcept
{
  VkSparseImageFormatProperties l_result{};
  l_result.aspectMask = static_cast<VkImageAspectFlags>(0);
  l_result.imageGranularity = sdlxvulkan::make_default<VkExtent3D>();
  l_result.flags = static_cast<VkSparseImageFormatFlags>(0);
  return l_result;
}

template <>
inline VkSparseImageFormatProperties2 sdlxvulkan::make_default<VkSparseImageFormatProperties2>() noexcept
{
  VkSparseImageFormatProperties2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
  l_result.pNext = NULL;
  l_result.properties = sdlxvulkan::make_default<VkSparseImageFormatProperties>();
  return l_result;
}

template <>
inline VkSparseImageMemoryBind sdlxvulkan::make_default<VkSparseImageMemoryBind>() noexcept
{
  VkSparseImageMemoryBind l_result{};
  l_result.subresource = sdlxvulkan::make_default<VkImageSubresource>();
  l_result.offset = sdlxvulkan::make_default<VkOffset3D>();
  l_result.extent = sdlxvulkan::make_default<VkExtent3D>();
  l_result.memory = VK_NULL_HANDLE;
  l_result.memoryOffset = 0;
  l_result.flags = static_cast<VkSparseMemoryBindFlags>(0);
  return l_result;
}

template <>
inline VkSparseImageMemoryBindInfo sdlxvulkan::make_default<VkSparseImageMemoryBindInfo>() noexcept
{
  VkSparseImageMemoryBindInfo l_result{};
  l_result.image = VK_NULL_HANDLE;
  l_result.bindCount = 0;
  l_result.pBinds = NULL;
  return l_result;
}

template <>
inline VkSparseImageMemoryRequirements sdlxvulkan::make_default<VkSparseImageMemoryRequirements>() noexcept
{
  VkSparseImageMemoryRequirements l_result{};
  l_result.formatProperties = sdlxvulkan::make_default<VkSparseImageFormatProperties>();
  l_result.imageMipTailFirstLod = 0;
  l_result.imageMipTailSize = 0;
  l_result.imageMipTailOffset = 0;
  l_result.imageMipTailStride = 0;
  return l_result;
}

template <>
inline VkSparseImageMemoryRequirements2 sdlxvulkan::make_default<VkSparseImageMemoryRequirements2>() noexcept
{
  VkSparseImageMemoryRequirements2 l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
  l_result.pNext = NULL;
  l_result.memoryRequirements = sdlxvulkan::make_default<VkSparseImageMemoryRequirements>();
  return l_result;
}

template <>
inline VkSparseImageOpaqueMemoryBindInfo sdlxvulkan::make_default<VkSparseImageOpaqueMemoryBindInfo>() noexcept
{
  VkSparseImageOpaqueMemoryBindInfo l_result{};
  l_result.image = VK_NULL_HANDLE;
  l_result.bindCount = 0;
  l_result.pBinds = NULL;
  return l_result;
}

template <>
inline VkSparseMemoryBind sdlxvulkan::make_default<VkSparseMemoryBind>() noexcept
{
  VkSparseMemoryBind l_result{};
  l_result.resourceOffset = 0;
  l_result.size = 0;
  l_result.memory = VK_NULL_HANDLE;
  l_result.memoryOffset = 0;
  l_result.flags = static_cast<VkSparseMemoryBindFlags>(0);
  return l_result;
}

template <>
inline VkSpecializationInfo sdlxvulkan::make_default<VkSpecializationInfo>() noexcept
{
  VkSpecializationInfo l_result{};
  l_result.mapEntryCount = 0;
  l_result.pMapEntries = NULL;
  l_result.dataSize = 0;
  l_result.pData = NULL;
  return l_result;
}

template <>
inline VkSpecializationMapEntry sdlxvulkan::make_default<VkSpecializationMapEntry>() noexcept
{
  VkSpecializationMapEntry l_result{};
  l_result.constantID = 0;
  l_result.offset = 0;
  l_result.size = 0;
  return l_result;
}

template <>
inline VkStencilOpState sdlxvulkan::make_default<VkStencilOpState>() noexcept
{
  VkStencilOpState l_result{};
  l_result.failOp = static_cast<VkStencilOp>(0);
  l_result.passOp = static_cast<VkStencilOp>(0);
  l_result.depthFailOp = static_cast<VkStencilOp>(0);
  l_result.compareOp = static_cast<VkCompareOp>(0);
  l_result.compareMask = 0;
  l_result.writeMask = 0;
  l_result.reference = 0;
  return l_result;
}

template <>
inline VkSubmitInfo sdlxvulkan::make_default<VkSubmitInfo>() noexcept
{
  VkSubmitInfo l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_result.pNext = NULL;
  l_result.waitSemaphoreCount = 0;
  l_result.pWaitSemaphores = NULL;
  l_result.pWaitDstStageMask = NULL;
  l_result.commandBufferCount = 0;
  l_result.pCommandBuffers = NULL;
  l_result.signalSemaphoreCount = 0;
  l_result.pSignalSemaphores = NULL;
  return l_result;
}

template <>
inline VkSubpassDependency sdlxvulkan::make_default<VkSubpassDependency>() noexcept
{
  VkSubpassDependency l_result{};
  l_result.srcSubpass = 0;
  l_result.dstSubpass = 0;
  l_result.srcStageMask = static_cast<VkPipelineStageFlags>(0);
  l_result.dstStageMask = static_cast<VkPipelineStageFlags>(0);
  l_result.srcAccessMask = static_cast<VkAccessFlags>(0);
  l_result.dstAccessMask = static_cast<VkAccessFlags>(0);
  l_result.dependencyFlags = static_cast<VkDependencyFlags>(0);
  return l_result;
}

template <>
inline VkSubpassDescription sdlxvulkan::make_default<VkSubpassDescription>() noexcept
{
  VkSubpassDescription l_result{};
  l_result.flags = static_cast<VkSubpassDescriptionFlags>(0);
  l_result.pipelineBindPoint = static_cast<VkPipelineBindPoint>(0);
  l_result.inputAttachmentCount = 0;
  l_result.pInputAttachments = NULL;
  l_result.colorAttachmentCount = 0;
  l_result.pColorAttachments = NULL;
  l_result.pResolveAttachments = NULL;
  l_result.pDepthStencilAttachment = NULL;
  l_result.preserveAttachmentCount = 0;
  l_result.pPreserveAttachments = NULL;
  return l_result;
}

template <>
inline VkSubresourceLayout sdlxvulkan::make_default<VkSubresourceLayout>() noexcept
{
  VkSubresourceLayout l_result{};
  l_result.offset = 0;
  l_result.size = 0;
  l_result.rowPitch = 0;
  l_result.arrayPitch = 0;
  l_result.depthPitch = 0;
  return l_result;
}

template <>
inline VkVertexInputAttributeDescription sdlxvulkan::make_default<VkVertexInputAttributeDescription>() noexcept
{
  VkVertexInputAttributeDescription l_result{};
  l_result.location = 0;
  l_result.binding = 0;
  l_result.format = static_cast<VkFormat>(0);
  l_result.offset = 0;
  return l_result;
}

template <>
inline VkVertexInputBindingDescription sdlxvulkan::make_default<VkVertexInputBindingDescription>() noexcept
{
  VkVertexInputBindingDescription l_result{};
  l_result.binding = 0;
  l_result.stride = 0;
  l_result.inputRate = static_cast<VkVertexInputRate>(0);
  return l_result;
}

template <>
inline VkViewport sdlxvulkan::make_default<VkViewport>() noexcept
{
  VkViewport l_result{};
  l_result.x = 0.0f;
  l_result.y = 0.0f;
  l_result.width = 0.0f;
  l_result.height = 0.0f;
  l_result.minDepth = 0.0f;
  l_result.maxDepth = 0.0f;
  return l_result;
}

template <>
inline VkWriteDescriptorSet sdlxvulkan::make_default<VkWriteDescriptorSet>() noexcept
{
  VkWriteDescriptorSet l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  l_result.pNext = NULL;
  l_result.dstSet = VK_NULL_HANDLE;
  l_result.dstBinding = 0;
  l_result.dstArrayElement = 0;
  l_result.descriptorCount = 0;
  l_result.descriptorType = static_cast<VkDescriptorType>(0);
  l_result.pImageInfo = NULL;
  l_result.pBufferInfo = NULL;
  l_result.pTexelBufferView = NULL;
  return l_result;
}


// Extension Structs:
template <>
inline VkAcquireNextImageInfoKHR sdlxvulkan::make_default<VkAcquireNextImageInfoKHR>() noexcept
{
  VkAcquireNextImageInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.swapchain = VK_NULL_HANDLE;
  l_result.timeout = 0;
  l_result.semaphore = VK_NULL_HANDLE;
  l_result.fence = VK_NULL_HANDLE;
  l_result.deviceMask = 0;
  return l_result;
}

template <>
inline VkAttachmentSampleLocationsEXT sdlxvulkan::make_default<VkAttachmentSampleLocationsEXT>() noexcept
{
  VkAttachmentSampleLocationsEXT l_result{};
  l_result.attachmentIndex = 0;
  l_result.sampleLocationsInfo = sdlxvulkan::make_default<VkSampleLocationsInfoEXT>();
  return l_result;
}

template <>
inline VkBindImageMemorySwapchainInfoKHR sdlxvulkan::make_default<VkBindImageMemorySwapchainInfoKHR>() noexcept
{
  VkBindImageMemorySwapchainInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR;
  l_result.pNext = NULL;
  l_result.swapchain = VK_NULL_HANDLE;
  l_result.imageIndex = 0;
  return l_result;
}

template <>
inline VkCmdProcessCommandsInfoNVX sdlxvulkan::make_default<VkCmdProcessCommandsInfoNVX>() noexcept
{
  VkCmdProcessCommandsInfoNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_CMD_PROCESS_COMMANDS_INFO_NVX;
  l_result.pNext = NULL;
  l_result.objectTable = VK_NULL_HANDLE;
  l_result.indirectCommandsLayout = VK_NULL_HANDLE;
  l_result.indirectCommandsTokenCount = 0;
  l_result.pIndirectCommandsTokens = NULL;
  l_result.maxSequencesCount = 0;
  l_result.targetCommandBuffer = VK_NULL_HANDLE;
  l_result.sequencesCountBuffer = VK_NULL_HANDLE;
  l_result.sequencesCountOffset = 0;
  l_result.sequencesIndexBuffer = VK_NULL_HANDLE;
  l_result.sequencesIndexOffset = 0;
  return l_result;
}

template <>
inline VkCmdReserveSpaceForCommandsInfoNVX sdlxvulkan::make_default<VkCmdReserveSpaceForCommandsInfoNVX>() noexcept
{
  VkCmdReserveSpaceForCommandsInfoNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_CMD_RESERVE_SPACE_FOR_COMMANDS_INFO_NVX;
  l_result.pNext = NULL;
  l_result.objectTable = VK_NULL_HANDLE;
  l_result.indirectCommandsLayout = VK_NULL_HANDLE;
  l_result.maxSequencesCount = 0;
  return l_result;
}


template <>
inline VkDebugMarkerMarkerInfoEXT sdlxvulkan::make_default<VkDebugMarkerMarkerInfoEXT>() noexcept
{
  VkDebugMarkerMarkerInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
  l_result.pNext = NULL;
  l_result.pMarkerName = NULL;
  //l_result.color = { 0.0f };
  set_array(l_result.color, 0.0f);
  return l_result;
}

template <>
inline VkDebugMarkerObjectNameInfoEXT sdlxvulkan::make_default<VkDebugMarkerObjectNameInfoEXT>() noexcept
{
  VkDebugMarkerObjectNameInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
  l_result.pNext = NULL;
  l_result.objectType = static_cast<VkDebugReportObjectTypeEXT>(0);
  l_result.object = 0;
  l_result.pObjectName = NULL;
  return l_result;
}

template <>
inline VkDebugMarkerObjectTagInfoEXT sdlxvulkan::make_default<VkDebugMarkerObjectTagInfoEXT>() noexcept
{
  VkDebugMarkerObjectTagInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
  l_result.pNext = NULL;
  l_result.objectType = static_cast<VkDebugReportObjectTypeEXT>(0);
  l_result.object = 0;
  l_result.tagName = 0;
  l_result.tagSize = 0;
  l_result.pTag = NULL;
  return l_result;
}

template <>
inline VkDebugReportCallbackCreateInfoEXT sdlxvulkan::make_default<VkDebugReportCallbackCreateInfoEXT>() noexcept
{
  VkDebugReportCallbackCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDebugReportFlagsEXT>(0);
  l_result.pfnCallback = NULL;
  l_result.pUserData = NULL;
  return l_result;
}

template <>
inline VkDebugUtilsLabelEXT sdlxvulkan::make_default<VkDebugUtilsLabelEXT>() noexcept
{
  VkDebugUtilsLabelEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
  l_result.pNext = NULL;
  l_result.pLabelName = NULL;
  //l_result.color = { 0.0f };
  set_array(l_result.color, 0.0f);
  return l_result;
}

template <>
inline VkDebugUtilsMessengerCallbackDataEXT sdlxvulkan::make_default<VkDebugUtilsMessengerCallbackDataEXT>() noexcept
{
  VkDebugUtilsMessengerCallbackDataEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDebugUtilsMessengerCallbackDataFlagsEXT>(0);
  l_result.pMessageIdName = NULL;
  l_result.messageIdNumber = 0;
  l_result.pMessage = NULL;
  l_result.queueLabelCount = 0;
  l_result.pQueueLabels = NULL;
  l_result.cmdBufLabelCount = 0;
  l_result.pCmdBufLabels = NULL;
  l_result.objectCount = 0;
  l_result.pObjects = NULL;
  return l_result;
}

template <>
inline VkDebugUtilsMessengerCreateInfoEXT sdlxvulkan::make_default<VkDebugUtilsMessengerCreateInfoEXT>() noexcept
{
  VkDebugUtilsMessengerCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDebugUtilsMessengerCreateFlagsEXT>(0);
  l_result.messageSeverity = static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(0);
  l_result.messageType = static_cast<VkDebugUtilsMessageTypeFlagsEXT>(0);
  l_result.pfnUserCallback = NULL;
  l_result.pUserData = NULL;
  return l_result;
}

template <>
inline VkDebugUtilsObjectNameInfoEXT sdlxvulkan::make_default<VkDebugUtilsObjectNameInfoEXT>() noexcept
{
  VkDebugUtilsObjectNameInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
  l_result.pNext = NULL;
  l_result.objectType = static_cast<VkObjectType>(0);
  l_result.objectHandle = 0;
  l_result.pObjectName = NULL;
  return l_result;
}

template <>
inline VkDebugUtilsObjectTagInfoEXT sdlxvulkan::make_default<VkDebugUtilsObjectTagInfoEXT>() noexcept
{
  VkDebugUtilsObjectTagInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
  l_result.pNext = NULL;
  l_result.objectType = static_cast<VkObjectType>(0);
  l_result.objectHandle = 0;
  l_result.tagName = 0;
  l_result.tagSize = 0;
  l_result.pTag = NULL;
  return l_result;
}

template <>
inline VkDedicatedAllocationBufferCreateInfoNV sdlxvulkan::make_default<VkDedicatedAllocationBufferCreateInfoNV>() noexcept
{
  VkDedicatedAllocationBufferCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.dedicatedAllocation = VK_FALSE;
  return l_result;
}

template <>
inline VkDedicatedAllocationImageCreateInfoNV sdlxvulkan::make_default<VkDedicatedAllocationImageCreateInfoNV>() noexcept
{
  VkDedicatedAllocationImageCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.dedicatedAllocation = VK_FALSE;
  return l_result;
}

template <>
inline VkDedicatedAllocationMemoryAllocateInfoNV sdlxvulkan::make_default<VkDedicatedAllocationMemoryAllocateInfoNV>() noexcept
{
  VkDedicatedAllocationMemoryAllocateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.image = VK_NULL_HANDLE;
  l_result.buffer = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkDescriptorSetLayoutBindingFlagsCreateInfoEXT sdlxvulkan::make_default<VkDescriptorSetLayoutBindingFlagsCreateInfoEXT>() noexcept
{
  VkDescriptorSetLayoutBindingFlagsCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.bindingCount = 0;
  l_result.pBindingFlags = NULL;
  return l_result;
}

template <>
inline VkDescriptorSetVariableDescriptorCountAllocateInfoEXT sdlxvulkan::make_default<VkDescriptorSetVariableDescriptorCountAllocateInfoEXT>() noexcept
{
  VkDescriptorSetVariableDescriptorCountAllocateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.descriptorSetCount = 0;
  l_result.pDescriptorCounts = NULL;
  return l_result;
}

template <>
inline VkDescriptorSetVariableDescriptorCountLayoutSupportEXT sdlxvulkan::make_default<VkDescriptorSetVariableDescriptorCountLayoutSupportEXT>() noexcept
{
  VkDescriptorSetVariableDescriptorCountLayoutSupportEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT_EXT;
  l_result.pNext = NULL;
  l_result.maxVariableDescriptorCount = 0;
  return l_result;
}

template <>
inline VkDeviceEventInfoEXT sdlxvulkan::make_default<VkDeviceEventInfoEXT>() noexcept
{
  VkDeviceEventInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT;
  l_result.pNext = NULL;
  l_result.deviceEvent = static_cast<VkDeviceEventTypeEXT>(0);
  return l_result;
}

template <>
inline VkDeviceGeneratedCommandsFeaturesNVX sdlxvulkan::make_default<VkDeviceGeneratedCommandsFeaturesNVX>() noexcept
{
  VkDeviceGeneratedCommandsFeaturesNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_FEATURES_NVX;
  l_result.pNext = NULL;
  l_result.computeBindingPointSupport = VK_FALSE;
  return l_result;
}

template <>
inline VkDeviceGeneratedCommandsLimitsNVX sdlxvulkan::make_default<VkDeviceGeneratedCommandsLimitsNVX>() noexcept
{
  VkDeviceGeneratedCommandsLimitsNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GENERATED_COMMANDS_LIMITS_NVX;
  l_result.pNext = NULL;
  l_result.maxIndirectCommandsLayoutTokenCount = 0;
  l_result.maxObjectEntryCounts = 0;
  l_result.minSequenceCountBufferOffsetAlignment = 0;
  l_result.minSequenceIndexBufferOffsetAlignment = 0;
  l_result.minCommandsTokenBufferOffsetAlignment = 0;
  return l_result;
}

template <>
inline VkDeviceGroupPresentCapabilitiesKHR sdlxvulkan::make_default<VkDeviceGroupPresentCapabilitiesKHR>() noexcept
{
  VkDeviceGroupPresentCapabilitiesKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
  l_result.pNext = NULL;
  //l_result.presentMask = { 0 };
  set_array(l_result.presentMask, static_cast<uint32_t>(0u));
  l_result.modes = static_cast<VkDeviceGroupPresentModeFlagsKHR>(0);
  return l_result;
}

template <>
inline VkDeviceGroupPresentInfoKHR sdlxvulkan::make_default<VkDeviceGroupPresentInfoKHR>() noexcept
{
  VkDeviceGroupPresentInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR;
  l_result.pNext = NULL;
  l_result.swapchainCount = 0;
  l_result.pDeviceMasks = NULL;
  l_result.mode = static_cast<VkDeviceGroupPresentModeFlagBitsKHR>(0);
  return l_result;
}

template <>
inline VkDeviceGroupSwapchainCreateInfoKHR sdlxvulkan::make_default<VkDeviceGroupSwapchainCreateInfoKHR>() noexcept
{
  VkDeviceGroupSwapchainCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.modes = static_cast<VkDeviceGroupPresentModeFlagsKHR>(0);
  return l_result;
}

template <>
inline VkDeviceQueueGlobalPriorityCreateInfoEXT sdlxvulkan::make_default<VkDeviceQueueGlobalPriorityCreateInfoEXT>() noexcept
{
  VkDeviceQueueGlobalPriorityCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.globalPriority = static_cast<VkQueueGlobalPriorityEXT>(0);
  return l_result;
}

template <>
inline VkDisplayEventInfoEXT sdlxvulkan::make_default<VkDisplayEventInfoEXT>() noexcept
{
  VkDisplayEventInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT;
  l_result.pNext = NULL;
  l_result.displayEvent = static_cast<VkDisplayEventTypeEXT>(0);
  return l_result;
}

template <>
inline VkDisplayModeCreateInfoKHR sdlxvulkan::make_default<VkDisplayModeCreateInfoKHR>() noexcept
{
  VkDisplayModeCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDisplayModeCreateFlagsKHR>(0);
  l_result.parameters = sdlxvulkan::make_default<VkDisplayModeParametersKHR>();
  return l_result;
}

template <>
inline VkDisplayModeParametersKHR sdlxvulkan::make_default<VkDisplayModeParametersKHR>() noexcept
{
  VkDisplayModeParametersKHR l_result{};
  l_result.visibleRegion = sdlxvulkan::make_default<VkExtent2D>();
  l_result.refreshRate = 0;
  return l_result;
}

template <>
inline VkDisplayModePropertiesKHR sdlxvulkan::make_default<VkDisplayModePropertiesKHR>() noexcept
{
  VkDisplayModePropertiesKHR l_result{};
  l_result.displayMode = VK_NULL_HANDLE;
  l_result.parameters = sdlxvulkan::make_default<VkDisplayModeParametersKHR>();
  return l_result;
}

template <>
inline VkDisplayPlaneCapabilitiesKHR sdlxvulkan::make_default<VkDisplayPlaneCapabilitiesKHR>() noexcept
{
  VkDisplayPlaneCapabilitiesKHR l_result{};
  l_result.supportedAlpha = static_cast<VkDisplayPlaneAlphaFlagsKHR>(0);
  l_result.minSrcPosition = sdlxvulkan::make_default<VkOffset2D>();
  l_result.maxSrcPosition = sdlxvulkan::make_default<VkOffset2D>();
  l_result.minSrcExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxSrcExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.minDstPosition = sdlxvulkan::make_default<VkOffset2D>();
  l_result.maxDstPosition = sdlxvulkan::make_default<VkOffset2D>();
  l_result.minDstExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxDstExtent = sdlxvulkan::make_default<VkExtent2D>();
  return l_result;
}

template <>
inline VkDisplayPlanePropertiesKHR sdlxvulkan::make_default<VkDisplayPlanePropertiesKHR>() noexcept
{
  VkDisplayPlanePropertiesKHR l_result{};
  l_result.currentDisplay = VK_NULL_HANDLE;
  l_result.currentStackIndex = 0;
  return l_result;
}

template <>
inline VkDisplayPowerInfoEXT sdlxvulkan::make_default<VkDisplayPowerInfoEXT>() noexcept
{
  VkDisplayPowerInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
  l_result.pNext = NULL;
  l_result.powerState = static_cast<VkDisplayPowerStateEXT>(0);
  return l_result;
}

template <>
inline VkDisplayPresentInfoKHR sdlxvulkan::make_default<VkDisplayPresentInfoKHR>() noexcept
{
  VkDisplayPresentInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR;
  l_result.pNext = NULL;
  l_result.srcRect = sdlxvulkan::make_default<VkRect2D>();
  l_result.dstRect = sdlxvulkan::make_default<VkRect2D>();
  l_result.persistent = VK_FALSE;
  return l_result;
}

template <>
inline VkDisplayPropertiesKHR sdlxvulkan::make_default<VkDisplayPropertiesKHR>() noexcept
{
  VkDisplayPropertiesKHR l_result{};
  l_result.display = VK_NULL_HANDLE;
  l_result.displayName = NULL;
  l_result.physicalDimensions = sdlxvulkan::make_default<VkExtent2D>();
  l_result.physicalResolution = sdlxvulkan::make_default<VkExtent2D>();
  l_result.supportedTransforms = static_cast<VkSurfaceTransformFlagsKHR>(0);
  l_result.planeReorderPossible = VK_FALSE;
  l_result.persistentContent = VK_FALSE;
  return l_result;
}

template <>
inline VkDisplaySurfaceCreateInfoKHR sdlxvulkan::make_default<VkDisplaySurfaceCreateInfoKHR>() noexcept
{
  VkDisplaySurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkDisplaySurfaceCreateFlagsKHR>(0);
  l_result.displayMode = VK_NULL_HANDLE;
  l_result.planeIndex = 0;
  l_result.planeStackIndex = 0;
  l_result.transform = static_cast<VkSurfaceTransformFlagBitsKHR>(0);
  l_result.globalAlpha = 0.0f;
  l_result.alphaMode = static_cast<VkDisplayPlaneAlphaFlagBitsKHR>(0);
  l_result.imageExtent = sdlxvulkan::make_default<VkExtent2D>();
  return l_result;
}

template <>
inline VkExportMemoryAllocateInfoNV sdlxvulkan::make_default<VkExportMemoryAllocateInfoNV>() noexcept
{
  VkExportMemoryAllocateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalMemoryHandleTypeFlagsNV>(0);
  return l_result;
}

template <>
inline VkExternalImageFormatPropertiesNV sdlxvulkan::make_default<VkExternalImageFormatPropertiesNV>() noexcept
{
  VkExternalImageFormatPropertiesNV l_result{};
  l_result.imageFormatProperties = sdlxvulkan::make_default<VkImageFormatProperties>();
  l_result.externalMemoryFeatures = static_cast<VkExternalMemoryFeatureFlagsNV>(0);
  l_result.exportFromImportedHandleTypes = static_cast<VkExternalMemoryHandleTypeFlagsNV>(0);
  l_result.compatibleHandleTypes = static_cast<VkExternalMemoryHandleTypeFlagsNV>(0);
  return l_result;
}

template <>
inline VkExternalMemoryImageCreateInfoNV sdlxvulkan::make_default<VkExternalMemoryImageCreateInfoNV>() noexcept
{
  VkExternalMemoryImageCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.handleTypes = static_cast<VkExternalMemoryHandleTypeFlagsNV>(0);
  return l_result;
}

template <>
inline VkFenceGetFdInfoKHR sdlxvulkan::make_default<VkFenceGetFdInfoKHR>() noexcept
{
  VkFenceGetFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.fence = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalFenceHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkHdrMetadataEXT sdlxvulkan::make_default<VkHdrMetadataEXT>() noexcept
{
  VkHdrMetadataEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
  l_result.pNext = NULL;
  l_result.displayPrimaryRed = sdlxvulkan::make_default<VkXYColorEXT>();
  l_result.displayPrimaryGreen = sdlxvulkan::make_default<VkXYColorEXT>();
  l_result.displayPrimaryBlue = sdlxvulkan::make_default<VkXYColorEXT>();
  l_result.whitePoint = sdlxvulkan::make_default<VkXYColorEXT>();
  l_result.maxLuminance = 0.0f;
  l_result.minLuminance = 0.0f;
  l_result.maxContentLightLevel = 0.0f;
  l_result.maxFrameAverageLightLevel = 0.0f;
  return l_result;
}

template <>
inline VkImageFormatListCreateInfoKHR sdlxvulkan::make_default<VkImageFormatListCreateInfoKHR>() noexcept
{
  VkImageFormatListCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.viewFormatCount = 0;
  l_result.pViewFormats = NULL;
  return l_result;
}

template <>
inline VkImageSwapchainCreateInfoKHR sdlxvulkan::make_default<VkImageSwapchainCreateInfoKHR>() noexcept
{
  VkImageSwapchainCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.swapchain = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkImportFenceFdInfoKHR sdlxvulkan::make_default<VkImportFenceFdInfoKHR>() noexcept
{
  VkImportFenceFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.fence = VK_NULL_HANDLE;
  l_result.flags = static_cast<VkFenceImportFlags>(0);
  l_result.handleType = static_cast<VkExternalFenceHandleTypeFlagBits>(0);
  l_result.fd = 0;
  return l_result;
}

template <>
inline VkImportMemoryFdInfoKHR sdlxvulkan::make_default<VkImportMemoryFdInfoKHR>() noexcept
{
  VkImportMemoryFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  l_result.fd = 0;
  return l_result;
}

template <>
inline VkImportMemoryHostPointerInfoEXT sdlxvulkan::make_default<VkImportMemoryHostPointerInfoEXT>() noexcept
{
  VkImportMemoryHostPointerInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  l_result.pHostPointer = NULL;
  return l_result;
}

template <>
inline VkImportSemaphoreFdInfoKHR sdlxvulkan::make_default<VkImportSemaphoreFdInfoKHR>() noexcept
{
  VkImportSemaphoreFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.semaphore = VK_NULL_HANDLE;
  l_result.flags = static_cast<VkSemaphoreImportFlags>(0);
  l_result.handleType = static_cast<VkExternalSemaphoreHandleTypeFlagBits>(0);
  l_result.fd = 0;
  return l_result;
}

template <>
inline VkIndirectCommandsLayoutCreateInfoNVX sdlxvulkan::make_default<VkIndirectCommandsLayoutCreateInfoNVX>() noexcept
{
  VkIndirectCommandsLayoutCreateInfoNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NVX;
  l_result.pNext = NULL;
  l_result.pipelineBindPoint = static_cast<VkPipelineBindPoint>(0);
  l_result.flags = static_cast<VkIndirectCommandsLayoutUsageFlagsNVX>(0);
  l_result.tokenCount = 0;
  l_result.pTokens = NULL;
  return l_result;
}

template <>
inline VkIndirectCommandsLayoutTokenNVX sdlxvulkan::make_default<VkIndirectCommandsLayoutTokenNVX>() noexcept
{
  VkIndirectCommandsLayoutTokenNVX l_result{};
  l_result.tokenType = static_cast<VkIndirectCommandsTokenTypeNVX>(0);
  l_result.bindingUnit = 0;
  l_result.dynamicCount = 0;
  l_result.divisor = 0;
  return l_result;
}

template <>
inline VkIndirectCommandsTokenNVX sdlxvulkan::make_default<VkIndirectCommandsTokenNVX>() noexcept
{
  VkIndirectCommandsTokenNVX l_result{};
  l_result.tokenType = static_cast<VkIndirectCommandsTokenTypeNVX>(0);
  l_result.buffer = VK_NULL_HANDLE;
  l_result.offset = 0;
  return l_result;
}

template <>
inline VkMemoryFdPropertiesKHR sdlxvulkan::make_default<VkMemoryFdPropertiesKHR>() noexcept
{
  VkMemoryFdPropertiesKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
  l_result.pNext = NULL;
  l_result.memoryTypeBits = 0;
  return l_result;
}

template <>
inline VkMemoryGetFdInfoKHR sdlxvulkan::make_default<VkMemoryGetFdInfoKHR>() noexcept
{
  VkMemoryGetFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.memory = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkMultisamplePropertiesEXT sdlxvulkan::make_default<VkMultisamplePropertiesEXT>() noexcept
{
  VkMultisamplePropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.maxSampleLocationGridSize = sdlxvulkan::make_default<VkExtent2D>();
  return l_result;
}

template <>
inline VkObjectTableCreateInfoNVX sdlxvulkan::make_default<VkObjectTableCreateInfoNVX>() noexcept
{
  VkObjectTableCreateInfoNVX l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_OBJECT_TABLE_CREATE_INFO_NVX;
  l_result.pNext = NULL;
  l_result.objectCount = 0;
  l_result.pObjectEntryTypes = NULL;
  l_result.pObjectEntryCounts = NULL;
  l_result.pObjectEntryUsageFlags = NULL;
  l_result.maxUniformBuffersPerDescriptor = 0;
  l_result.maxStorageBuffersPerDescriptor = 0;
  l_result.maxStorageImagesPerDescriptor = 0;
  l_result.maxSampledImagesPerDescriptor = 0;
  l_result.maxPipelineLayouts = 0;
  return l_result;
}

template <>
inline VkObjectTableDescriptorSetEntryNVX sdlxvulkan::make_default<VkObjectTableDescriptorSetEntryNVX>() noexcept
{
  VkObjectTableDescriptorSetEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  l_result.pipelineLayout = VK_NULL_HANDLE;
  l_result.descriptorSet = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkObjectTableEntryNVX sdlxvulkan::make_default<VkObjectTableEntryNVX>() noexcept
{
  VkObjectTableEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  return l_result;
}

template <>
inline VkObjectTableIndexBufferEntryNVX sdlxvulkan::make_default<VkObjectTableIndexBufferEntryNVX>() noexcept
{
  VkObjectTableIndexBufferEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  l_result.buffer = VK_NULL_HANDLE;
  l_result.indexType = static_cast<VkIndexType>(0);
  return l_result;
}

template <>
inline VkObjectTablePipelineEntryNVX sdlxvulkan::make_default<VkObjectTablePipelineEntryNVX>() noexcept
{
  VkObjectTablePipelineEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  l_result.pipeline = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkObjectTablePushConstantEntryNVX sdlxvulkan::make_default<VkObjectTablePushConstantEntryNVX>() noexcept
{
  VkObjectTablePushConstantEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  l_result.pipelineLayout = VK_NULL_HANDLE;
  l_result.stageFlags = static_cast<VkShaderStageFlags>(0);
  return l_result;
}

template <>
inline VkObjectTableVertexBufferEntryNVX sdlxvulkan::make_default<VkObjectTableVertexBufferEntryNVX>() noexcept
{
  VkObjectTableVertexBufferEntryNVX l_result{};
  l_result.type = static_cast<VkObjectEntryTypeNVX>(0);
  l_result.flags = static_cast<VkObjectEntryUsageFlagsNVX>(0);
  l_result.buffer = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkOffset2D sdlxvulkan::make_default<VkOffset2D>() noexcept
{
  VkOffset2D l_result{};
  l_result.x = 0;
  l_result.y = 0;
  return l_result;
}

template <>
inline VkOffset3D sdlxvulkan::make_default<VkOffset3D>() noexcept
{
  VkOffset3D l_result{};
  l_result.x = 0;
  l_result.y = 0;
  l_result.z = 0;
  return l_result;
}

template <>
inline VkPastPresentationTimingGOOGLE sdlxvulkan::make_default<VkPastPresentationTimingGOOGLE>() noexcept
{
  VkPastPresentationTimingGOOGLE l_result{};
  l_result.presentID = 0;
  l_result.desiredPresentTime = 0;
  l_result.actualPresentTime = 0;
  l_result.earliestPresentTime = 0;
  l_result.presentMargin = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT sdlxvulkan::make_default<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT>() noexcept
{
  VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
  l_result.pNext = NULL;
  l_result.advancedBlendCoherentOperations = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT>() noexcept
{
  VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.advancedBlendMaxColorAttachments = 0;
  l_result.advancedBlendIndependentBlend = VK_FALSE;
  l_result.advancedBlendNonPremultipliedSrcColor = VK_FALSE;
  l_result.advancedBlendNonPremultipliedDstColor = VK_FALSE;
  l_result.advancedBlendCorrelatedOverlap = VK_FALSE;
  l_result.advancedBlendAllOperations = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceConservativeRasterizationPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceConservativeRasterizationPropertiesEXT>() noexcept
{
  VkPhysicalDeviceConservativeRasterizationPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.primitiveOverestimationSize = 0.0f;
  l_result.maxExtraPrimitiveOverestimationSize = 0.0f;
  l_result.extraPrimitiveOverestimationSizeGranularity = 0.0f;
  l_result.primitiveUnderestimation = VK_FALSE;
  l_result.conservativePointAndLineRasterization = VK_FALSE;
  l_result.degenerateTrianglesRasterized = VK_FALSE;
  l_result.degenerateLinesRasterized = VK_FALSE;
  l_result.fullyCoveredFragmentShaderInputVariable = VK_FALSE;
  l_result.conservativeRasterizationPostDepthCoverage = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceDescriptorIndexingFeaturesEXT sdlxvulkan::make_default<VkPhysicalDeviceDescriptorIndexingFeaturesEXT>() noexcept
{
  VkPhysicalDeviceDescriptorIndexingFeaturesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
  l_result.pNext = NULL;
  l_result.shaderInputAttachmentArrayDynamicIndexing = VK_FALSE;
  l_result.shaderUniformTexelBufferArrayDynamicIndexing = VK_FALSE;
  l_result.shaderStorageTexelBufferArrayDynamicIndexing = VK_FALSE;
  l_result.shaderUniformBufferArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderSampledImageArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderStorageBufferArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderStorageImageArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderInputAttachmentArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderUniformTexelBufferArrayNonUniformIndexing = VK_FALSE;
  l_result.shaderStorageTexelBufferArrayNonUniformIndexing = VK_FALSE;
  l_result.descriptorBindingUniformBufferUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingSampledImageUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingStorageImageUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingStorageBufferUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_FALSE;
  l_result.descriptorBindingUpdateUnusedWhilePending = VK_FALSE;
  l_result.descriptorBindingPartiallyBound = VK_FALSE;
  l_result.descriptorBindingVariableDescriptorCount = VK_FALSE;
  l_result.runtimeDescriptorArray = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceDescriptorIndexingPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceDescriptorIndexingPropertiesEXT>() noexcept
{
  VkPhysicalDeviceDescriptorIndexingPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.maxUpdateAfterBindDescriptorsInAllPools = 0;
  l_result.shaderUniformBufferArrayNonUniformIndexingNative = VK_FALSE;
  l_result.shaderSampledImageArrayNonUniformIndexingNative = VK_FALSE;
  l_result.shaderStorageBufferArrayNonUniformIndexingNative = VK_FALSE;
  l_result.shaderStorageImageArrayNonUniformIndexingNative = VK_FALSE;
  l_result.shaderInputAttachmentArrayNonUniformIndexingNative = VK_FALSE;
  l_result.robustBufferAccessUpdateAfterBind = VK_FALSE;
  l_result.quadDivergentImplicitLod = VK_FALSE;
  l_result.maxPerStageDescriptorUpdateAfterBindSamplers = 0;
  l_result.maxPerStageDescriptorUpdateAfterBindUniformBuffers = 0;
  l_result.maxPerStageDescriptorUpdateAfterBindStorageBuffers = 0;
  l_result.maxPerStageDescriptorUpdateAfterBindSampledImages = 0;
  l_result.maxPerStageDescriptorUpdateAfterBindStorageImages = 0;
  l_result.maxPerStageDescriptorUpdateAfterBindInputAttachments = 0;
  l_result.maxPerStageUpdateAfterBindResources = 0;
  l_result.maxDescriptorSetUpdateAfterBindSamplers = 0;
  l_result.maxDescriptorSetUpdateAfterBindUniformBuffers = 0;
  l_result.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = 0;
  l_result.maxDescriptorSetUpdateAfterBindStorageBuffers = 0;
  l_result.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = 0;
  l_result.maxDescriptorSetUpdateAfterBindSampledImages = 0;
  l_result.maxDescriptorSetUpdateAfterBindStorageImages = 0;
  l_result.maxDescriptorSetUpdateAfterBindInputAttachments = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceDiscardRectanglePropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceDiscardRectanglePropertiesEXT>() noexcept
{
  VkPhysicalDeviceDiscardRectanglePropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.maxDiscardRectangles = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceExternalMemoryHostPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceExternalMemoryHostPropertiesEXT>() noexcept
{
  VkPhysicalDeviceExternalMemoryHostPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.minImportedHostPointerAlignment = 0;
  return l_result;
}

template <>
inline VkPhysicalDevicePushDescriptorPropertiesKHR sdlxvulkan::make_default<VkPhysicalDevicePushDescriptorPropertiesKHR>() noexcept
{
  VkPhysicalDevicePushDescriptorPropertiesKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
  l_result.pNext = NULL;
  l_result.maxPushDescriptors = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceSampleLocationsPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceSampleLocationsPropertiesEXT>() noexcept
{
  VkPhysicalDeviceSampleLocationsPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.sampleLocationSampleCounts = static_cast<VkSampleCountFlags>(0);
  l_result.maxSampleLocationGridSize = sdlxvulkan::make_default<VkExtent2D>();
  //l_result.sampleLocationCoordinateRange = { 0.0f };
  set_array(l_result.sampleLocationCoordinateRange, 0.0f);
  l_result.sampleLocationSubPixelBits = 0;
  l_result.variableSampleLocations = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT>() noexcept
{
  VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.filterMinmaxSingleComponentFormats = VK_FALSE;
  l_result.filterMinmaxImageComponentMapping = VK_FALSE;
  return l_result;
}

template <>
inline VkPhysicalDeviceShaderCorePropertiesAMD sdlxvulkan::make_default<VkPhysicalDeviceShaderCorePropertiesAMD>() noexcept
{
  VkPhysicalDeviceShaderCorePropertiesAMD l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
  l_result.pNext = NULL;
  l_result.shaderEngineCount = 0;
  l_result.shaderArraysPerEngineCount = 0;
  l_result.computeUnitsPerShaderArray = 0;
  l_result.simdPerComputeUnit = 0;
  l_result.wavefrontsPerSimd = 0;
  l_result.wavefrontSize = 0;
  l_result.sgprsPerSimd = 0;
  l_result.minSgprAllocation = 0;
  l_result.maxSgprAllocation = 0;
  l_result.sgprAllocationGranularity = 0;
  l_result.vgprsPerSimd = 0;
  l_result.minVgprAllocation = 0;
  l_result.maxVgprAllocation = 0;
  l_result.vgprAllocationGranularity = 0;
  return l_result;
}

template <>
inline VkPhysicalDeviceSurfaceInfo2KHR sdlxvulkan::make_default<VkPhysicalDeviceSurfaceInfo2KHR>() noexcept
{
  VkPhysicalDeviceSurfaceInfo2KHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
  l_result.pNext = NULL;
  l_result.surface = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT sdlxvulkan::make_default<VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT>() noexcept
{
  VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
  l_result.pNext = NULL;
  l_result.maxVertexAttribDivisor = 0;
  return l_result;
}

template <>
inline VkPipelineColorBlendAdvancedStateCreateInfoEXT sdlxvulkan::make_default<VkPipelineColorBlendAdvancedStateCreateInfoEXT>() noexcept
{
  VkPipelineColorBlendAdvancedStateCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.srcPremultiplied = VK_FALSE;
  l_result.dstPremultiplied = VK_FALSE;
  l_result.blendOverlap = static_cast<VkBlendOverlapEXT>(0);
  return l_result;
}

template <>
inline VkPipelineCoverageModulationStateCreateInfoNV sdlxvulkan::make_default<VkPipelineCoverageModulationStateCreateInfoNV>() noexcept
{
  VkPipelineCoverageModulationStateCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineCoverageModulationStateCreateFlagsNV>(0);
  l_result.coverageModulationMode = static_cast<VkCoverageModulationModeNV>(0);
  l_result.coverageModulationTableEnable = VK_FALSE;
  l_result.coverageModulationTableCount = 0;
  l_result.pCoverageModulationTable = NULL;
  return l_result;
}

template <>
inline VkPipelineCoverageToColorStateCreateInfoNV sdlxvulkan::make_default<VkPipelineCoverageToColorStateCreateInfoNV>() noexcept
{
  VkPipelineCoverageToColorStateCreateInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineCoverageToColorStateCreateFlagsNV>(0);
  l_result.coverageToColorEnable = VK_FALSE;
  l_result.coverageToColorLocation = 0;
  return l_result;
}

template <>
inline VkPipelineDiscardRectangleStateCreateInfoEXT sdlxvulkan::make_default<VkPipelineDiscardRectangleStateCreateInfoEXT>() noexcept
{
  VkPipelineDiscardRectangleStateCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineDiscardRectangleStateCreateFlagsEXT>(0);
  l_result.discardRectangleMode = static_cast<VkDiscardRectangleModeEXT>(0);
  l_result.discardRectangleCount = 0;
  l_result.pDiscardRectangles = NULL;
  return l_result;
}

template <>
inline VkPipelineRasterizationConservativeStateCreateInfoEXT sdlxvulkan::make_default<VkPipelineRasterizationConservativeStateCreateInfoEXT>() noexcept
{
  VkPipelineRasterizationConservativeStateCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkPipelineRasterizationConservativeStateCreateFlagsEXT>(0);
  l_result.conservativeRasterizationMode = static_cast<VkConservativeRasterizationModeEXT>(0);
  l_result.extraPrimitiveOverestimationSize = 0.0f;
  return l_result;
}

template <>
inline VkPipelineRasterizationStateRasterizationOrderAMD sdlxvulkan::make_default<VkPipelineRasterizationStateRasterizationOrderAMD>() noexcept
{
  VkPipelineRasterizationStateRasterizationOrderAMD l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD;
  l_result.pNext = NULL;
  l_result.rasterizationOrder = static_cast<VkRasterizationOrderAMD>(0);
  return l_result;
}

template <>
inline VkPipelineSampleLocationsStateCreateInfoEXT sdlxvulkan::make_default<VkPipelineSampleLocationsStateCreateInfoEXT>() noexcept
{
  VkPipelineSampleLocationsStateCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.sampleLocationsEnable = VK_FALSE;
  l_result.sampleLocationsInfo = sdlxvulkan::make_default<VkSampleLocationsInfoEXT>();
  return l_result;
}

template <>
inline VkPipelineVertexInputDivisorStateCreateInfoEXT sdlxvulkan::make_default<VkPipelineVertexInputDivisorStateCreateInfoEXT>() noexcept
{
  VkPipelineVertexInputDivisorStateCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.vertexBindingDivisorCount = 0;
  l_result.pVertexBindingDivisors = NULL;
  return l_result;
}

template <>
inline VkPresentInfoKHR sdlxvulkan::make_default<VkPresentInfoKHR>() noexcept
{
  VkPresentInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  l_result.pNext = NULL;
  l_result.waitSemaphoreCount = 0;
  l_result.pWaitSemaphores = NULL;
  l_result.swapchainCount = 0;
  l_result.pSwapchains = NULL;
  l_result.pImageIndices = NULL;
  l_result.pResults = NULL;
  return l_result;
}

template <>
inline VkPresentRegionKHR sdlxvulkan::make_default<VkPresentRegionKHR>() noexcept
{
  VkPresentRegionKHR l_result{};
  l_result.rectangleCount = 0;
  l_result.pRectangles = NULL;
  return l_result;
}

template <>
inline VkPresentRegionsKHR sdlxvulkan::make_default<VkPresentRegionsKHR>() noexcept
{
  VkPresentRegionsKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR;
  l_result.pNext = NULL;
  l_result.swapchainCount = 0;
  l_result.pRegions = NULL;
  return l_result;
}

template <>
inline VkPresentTimeGOOGLE sdlxvulkan::make_default<VkPresentTimeGOOGLE>() noexcept
{
  VkPresentTimeGOOGLE l_result{};
  l_result.presentID = 0;
  l_result.desiredPresentTime = 0;
  return l_result;
}

template <>
inline VkPresentTimesInfoGOOGLE sdlxvulkan::make_default<VkPresentTimesInfoGOOGLE>() noexcept
{
  VkPresentTimesInfoGOOGLE l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE;
  l_result.pNext = NULL;
  l_result.swapchainCount = 0;
  l_result.pTimes = NULL;
  return l_result;
}

template <>
inline VkRect2D sdlxvulkan::make_default<VkRect2D>() noexcept
{
  VkRect2D l_result{};
  l_result.offset = sdlxvulkan::make_default<VkOffset2D>();
  l_result.extent = sdlxvulkan::make_default<VkExtent2D>();
  return l_result;
}

template <>
inline VkRectLayerKHR sdlxvulkan::make_default<VkRectLayerKHR>() noexcept
{
  VkRectLayerKHR l_result{};
  l_result.offset = sdlxvulkan::make_default<VkOffset2D>();
  l_result.extent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.layer = 0;
  return l_result;
}

template <>
inline VkRefreshCycleDurationGOOGLE sdlxvulkan::make_default<VkRefreshCycleDurationGOOGLE>() noexcept
{
  VkRefreshCycleDurationGOOGLE l_result{};
  l_result.refreshDuration = 0;
  return l_result;
}

template <>
inline VkRenderPassSampleLocationsBeginInfoEXT sdlxvulkan::make_default<VkRenderPassSampleLocationsBeginInfoEXT>() noexcept
{
  VkRenderPassSampleLocationsBeginInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT;
  l_result.pNext = NULL;
  l_result.attachmentInitialSampleLocationsCount = 0;
  l_result.pAttachmentInitialSampleLocations = NULL;
  l_result.postSubpassSampleLocationsCount = 0;
  l_result.pPostSubpassSampleLocations = NULL;
  return l_result;
}

template <>
inline VkSampleLocationEXT sdlxvulkan::make_default<VkSampleLocationEXT>() noexcept
{
  VkSampleLocationEXT l_result{};
  l_result.x = 0.0f;
  l_result.y = 0.0f;
  return l_result;
}

template <>
inline VkSampleLocationsInfoEXT sdlxvulkan::make_default<VkSampleLocationsInfoEXT>() noexcept
{
  VkSampleLocationsInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
  l_result.pNext = NULL;
  l_result.sampleLocationsPerPixel = static_cast<VkSampleCountFlagBits>(0);
  l_result.sampleLocationGridSize = sdlxvulkan::make_default<VkExtent2D>();
  l_result.sampleLocationsCount = 0;
  l_result.pSampleLocations = NULL;
  return l_result;
}

template <>
inline VkSamplerReductionModeCreateInfoEXT sdlxvulkan::make_default<VkSamplerReductionModeCreateInfoEXT>() noexcept
{
  VkSamplerReductionModeCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.reductionMode = static_cast<VkSamplerReductionModeEXT>(0);
  return l_result;
}

template <>
inline VkSemaphoreGetFdInfoKHR sdlxvulkan::make_default<VkSemaphoreGetFdInfoKHR>() noexcept
{
  VkSemaphoreGetFdInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
  l_result.pNext = NULL;
  l_result.semaphore = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalSemaphoreHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkShaderModuleValidationCacheCreateInfoEXT sdlxvulkan::make_default<VkShaderModuleValidationCacheCreateInfoEXT>() noexcept
{
  VkShaderModuleValidationCacheCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.validationCache = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkShaderResourceUsageAMD sdlxvulkan::make_default<VkShaderResourceUsageAMD>() noexcept
{
  VkShaderResourceUsageAMD l_result{};
  l_result.numUsedVgprs = 0;
  l_result.numUsedSgprs = 0;
  l_result.ldsSizePerLocalWorkGroup = 0;
  l_result.ldsUsageSizeInBytes = 0;
  l_result.scratchMemUsageInBytes = 0;
  return l_result;
}

template <>
inline VkShaderStatisticsInfoAMD sdlxvulkan::make_default<VkShaderStatisticsInfoAMD>() noexcept
{
  VkShaderStatisticsInfoAMD l_result{};
  l_result.shaderStageMask = static_cast<VkShaderStageFlags>(0);
  l_result.resourceUsage = sdlxvulkan::make_default<VkShaderResourceUsageAMD>();
  l_result.numPhysicalVgprs = 0;
  l_result.numPhysicalSgprs = 0;
  l_result.numAvailableVgprs = 0;
  l_result.numAvailableSgprs = 0;
  //l_result.computeWorkGroupSize = { 0 };
  set_array(l_result.computeWorkGroupSize, static_cast<uint32_t>(0u));
  return l_result;
}

template <>
inline VkSharedPresentSurfaceCapabilitiesKHR sdlxvulkan::make_default<VkSharedPresentSurfaceCapabilitiesKHR>() noexcept
{
  VkSharedPresentSurfaceCapabilitiesKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR;
  l_result.pNext = NULL;
  l_result.sharedPresentSupportedUsageFlags = static_cast<VkImageUsageFlags>(0);
  return l_result;
}

template <>
inline VkSubpassSampleLocationsEXT sdlxvulkan::make_default<VkSubpassSampleLocationsEXT>() noexcept
{
  VkSubpassSampleLocationsEXT l_result{};
  l_result.subpassIndex = 0;
  l_result.sampleLocationsInfo = sdlxvulkan::make_default<VkSampleLocationsInfoEXT>();
  return l_result;
}

template <>
inline VkSurfaceCapabilities2EXT sdlxvulkan::make_default<VkSurfaceCapabilities2EXT>() noexcept
{
  VkSurfaceCapabilities2EXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES2_EXT;
  l_result.pNext = NULL;
  l_result.minImageCount = 0;
  l_result.maxImageCount = 0;
  l_result.currentExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.minImageExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxImageExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxImageArrayLayers = 0;
  l_result.supportedTransforms = static_cast<VkSurfaceTransformFlagsKHR>(0);
  l_result.currentTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(0);
  l_result.supportedCompositeAlpha = static_cast<VkCompositeAlphaFlagsKHR>(0);
  l_result.supportedUsageFlags = static_cast<VkImageUsageFlags>(0);
  l_result.supportedSurfaceCounters = static_cast<VkSurfaceCounterFlagsEXT>(0);
  return l_result;
}

template <>
inline VkSurfaceCapabilities2KHR sdlxvulkan::make_default<VkSurfaceCapabilities2KHR>() noexcept
{
  VkSurfaceCapabilities2KHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
  l_result.pNext = NULL;
  l_result.surfaceCapabilities = sdlxvulkan::make_default<VkSurfaceCapabilitiesKHR>();
  return l_result;
}

template <>
inline VkSurfaceCapabilitiesKHR sdlxvulkan::make_default<VkSurfaceCapabilitiesKHR>() noexcept
{
  VkSurfaceCapabilitiesKHR l_result{};
  l_result.minImageCount = 0;
  l_result.maxImageCount = 0;
  l_result.currentExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.minImageExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxImageExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.maxImageArrayLayers = 0;
  l_result.supportedTransforms = static_cast<VkSurfaceTransformFlagsKHR>(0);
  l_result.currentTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(0);
  l_result.supportedCompositeAlpha = static_cast<VkCompositeAlphaFlagsKHR>(0);
  l_result.supportedUsageFlags = static_cast<VkImageUsageFlags>(0);
  return l_result;
}

template <>
inline VkSurfaceFormat2KHR sdlxvulkan::make_default<VkSurfaceFormat2KHR>() noexcept
{
  VkSurfaceFormat2KHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
  l_result.pNext = NULL;
  l_result.surfaceFormat = sdlxvulkan::make_default<VkSurfaceFormatKHR>();
  return l_result;
}

template <>
inline VkSurfaceFormatKHR sdlxvulkan::make_default<VkSurfaceFormatKHR>() noexcept
{
  VkSurfaceFormatKHR l_result{};
  l_result.format = static_cast<VkFormat>(0);
  l_result.colorSpace = static_cast<VkColorSpaceKHR>(0);
  return l_result;
}

template <>
inline VkSwapchainCounterCreateInfoEXT sdlxvulkan::make_default<VkSwapchainCounterCreateInfoEXT>() noexcept
{
  VkSwapchainCounterCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.surfaceCounters = static_cast<VkSurfaceCounterFlagsEXT>(0);
  return l_result;
}

template <>
inline VkSwapchainCreateInfoKHR sdlxvulkan::make_default<VkSwapchainCreateInfoKHR>() noexcept
{
  VkSwapchainCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkSwapchainCreateFlagsKHR>(0);
  l_result.surface = VK_NULL_HANDLE;
  l_result.minImageCount = 0;
  l_result.imageFormat = static_cast<VkFormat>(0);
  l_result.imageColorSpace = static_cast<VkColorSpaceKHR>(0);
  l_result.imageExtent = sdlxvulkan::make_default<VkExtent2D>();
  l_result.imageArrayLayers = 0;
  l_result.imageUsage = static_cast<VkImageUsageFlags>(0);
  l_result.imageSharingMode = static_cast<VkSharingMode>(0);
  l_result.queueFamilyIndexCount = 0;
  l_result.pQueueFamilyIndices = NULL;
  l_result.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(0);
  l_result.compositeAlpha = static_cast<VkCompositeAlphaFlagBitsKHR>(0);
  l_result.presentMode = static_cast<VkPresentModeKHR>(0);
  l_result.clipped = VK_FALSE;
  l_result.oldSwapchain = VK_NULL_HANDLE;
  return l_result;
}

template <>
inline VkTextureLODGatherFormatPropertiesAMD sdlxvulkan::make_default<VkTextureLODGatherFormatPropertiesAMD>() noexcept
{
  VkTextureLODGatherFormatPropertiesAMD l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD;
  l_result.pNext = NULL;
  l_result.supportsTextureGatherLODBiasAMD = VK_FALSE;
  return l_result;
}

template <>
inline VkValidationCacheCreateInfoEXT sdlxvulkan::make_default<VkValidationCacheCreateInfoEXT>() noexcept
{
  VkValidationCacheCreateInfoEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkValidationCacheCreateFlagsEXT>(0);
  l_result.initialDataSize = 0;
  l_result.pInitialData = NULL;
  return l_result;
}

template <>
inline VkValidationFlagsEXT sdlxvulkan::make_default<VkValidationFlagsEXT>() noexcept
{
  VkValidationFlagsEXT l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
  l_result.pNext = NULL;
  l_result.disabledValidationCheckCount = 0;
  l_result.pDisabledValidationChecks = NULL;
  return l_result;
}

template <>
inline VkViewportSwizzleNV sdlxvulkan::make_default<VkViewportSwizzleNV>() noexcept
{
  VkViewportSwizzleNV l_result{};
  l_result.x = static_cast<VkViewportCoordinateSwizzleNV>(0);
  l_result.y = static_cast<VkViewportCoordinateSwizzleNV>(0);
  l_result.z = static_cast<VkViewportCoordinateSwizzleNV>(0);
  l_result.w = static_cast<VkViewportCoordinateSwizzleNV>(0);
  return l_result;
}

template <>
inline VkViewportWScalingNV sdlxvulkan::make_default<VkViewportWScalingNV>() noexcept
{
  VkViewportWScalingNV l_result{};
  l_result.xcoeff = 0.0f;
  l_result.ycoeff = 0.0f;
  return l_result;
}

template <>
inline VkVertexInputBindingDivisorDescriptionEXT sdlxvulkan::make_default<VkVertexInputBindingDivisorDescriptionEXT>() noexcept
{
  VkVertexInputBindingDivisorDescriptionEXT l_result{};
  l_result.binding = 0;
  l_result.divisor = 0;
  return l_result;
}

template <>
inline VkXYColorEXT sdlxvulkan::make_default<VkXYColorEXT>() noexcept
{
  VkXYColorEXT l_result{};
  l_result.x = 0.0f;
  l_result.y = 0.0f;
  return l_result;
}


#ifdef VK_USE_PLATFORM_ANDROID_KHR
//Android Platform Structs:

template <>
inline VkExternalFormatANDROID sdlxvulkan::make_default<VkExternalFormatANDROID>() noexcept
{
  VkExternalFormatANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID;
  l_result.pNext = NULL;
  l_result.externalFormat = 0;
  return l_result;
}

template <>
inline VkAndroidHardwareBufferFormatPropertiesANDROID sdlxvulkan::make_default<VkAndroidHardwareBufferFormatPropertiesANDROID>() noexcept
{
  VkAndroidHardwareBufferFormatPropertiesANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID;
  l_result.pNext = NULL;
  l_result.format = static_cast<VkFormat>(0);
  l_result.externalFormat = 0;
  l_result.formatFeatures = static_cast<VkFormatFeatureFlags>(0);
  l_result.samplerYcbcrConversionComponents = sdlxvulkan::make_default<VkComponentMapping>();
  l_result.suggestedYcbcrModel = static_cast<VkSamplerYcbcrModelConversion>(0);
  l_result.suggestedYcbcrRange = static_cast<VkSamplerYcbcrRange>(0);
  l_result.suggestedXChromaOffset = static_cast<VkChromaLocation>(0);
  l_result.suggestedYChromaOffset = static_cast<VkChromaLocation>(0);
  return l_result;
}

template <>
inline VkAndroidHardwareBufferPropertiesANDROID sdlxvulkan::make_default<VkAndroidHardwareBufferPropertiesANDROID>() noexcept
{
  VkAndroidHardwareBufferPropertiesANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID;
  l_result.pNext = NULL;
  l_result.allocationSize = 0;
  l_result.memoryTypeBits = 0;
  return l_result;
}

template <>
inline VkAndroidHardwareBufferUsageANDROID sdlxvulkan::make_default<VkAndroidHardwareBufferUsageANDROID>() noexcept
{
  VkAndroidHardwareBufferUsageANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID;
  l_result.pNext = NULL;
  l_result.androidHardwareBufferUsage = 0;
  return l_result;
}

template <>
inline VkAndroidSurfaceCreateInfoKHR sdlxvulkan::make_default<VkAndroidSurfaceCreateInfoKHR>() noexcept
{
  VkAndroidSurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkAndroidSurfaceCreateFlagsKHR>(0);
  l_result.window = NULL;
  return l_result;
}

template <>
inline VkImportAndroidHardwareBufferInfoANDROID sdlxvulkan::make_default<VkImportAndroidHardwareBufferInfoANDROID>() noexcept
{
  VkImportAndroidHardwareBufferInfoANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
  l_result.pNext = NULL;
  l_result.buffer = NULL;
  return l_result;
}

template <>
inline VkMemoryGetAndroidHardwareBufferInfoANDROID sdlxvulkan::make_default<VkMemoryGetAndroidHardwareBufferInfoANDROID>() noexcept
{
  VkMemoryGetAndroidHardwareBufferInfoANDROID l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
  l_result.pNext = NULL;
  l_result.memory = VK_NULL_HANDLE;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_IOS_MVK
//IOS Platform Structs:
template <>
inline VkIOSSurfaceCreateInfoMVK sdlxvulkan::make_default<VkIOSSurfaceCreateInfoMVK>() noexcept
{
  VkIOSSurfaceCreateInfoMVK l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkIOSSurfaceCreateFlagsMVK>(0);
  l_result.pView = NULL;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_MACOS_MVK
//MacOS Platform Structs:
template <>
inline VkMacOSSurfaceCreateInfoMVK sdlxvulkan::make_default<VkMacOSSurfaceCreateInfoMVK>() noexcept
{
  VkMacOSSurfaceCreateInfoMVK l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkMacOSSurfaceCreateFlagsMVK>(0);
  l_result.pView = NULL;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
//Mir Platform Structs:
template <>
inline VkMirSurfaceCreateInfoKHR sdlxvulkan::make_default<VkMirSurfaceCreateInfoKHR>() noexcept
{
  VkMirSurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkMirSurfaceCreateFlagsKHR>(0);
  l_result.connection = NULL;
  l_result.mirSurface = NULL;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_VI_NN
//Vi Platform Structs:

template <>
inline VkViSurfaceCreateInfoNN sdlxvulkan::make_default<VkViSurfaceCreateInfoNN>() noexcept
{
  VkViSurfaceCreateInfoNN l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_N_N;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkViSurfaceCreateFlagsNN>(0);
  l_result.window = NULL;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
//Wayland Platform Structs:
template <>
inline VkWaylandSurfaceCreateInfoKHR sdlxvulkan::make_default<VkWaylandSurfaceCreateInfoKHR>() noexcept
{
  VkWaylandSurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkWaylandSurfaceCreateFlagsKHR>(0);
  l_result.wl_display* display = NULL;
  l_result.wl_surface* surface = NULL;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
//Win32 Platform Structs:

template <>
inline VkD3D12FenceSubmitInfoKHR sdlxvulkan::make_default<VkD3D12FenceSubmitInfoKHR>() noexcept
{
  VkD3D12FenceSubmitInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR;
  l_result.pNext = NULL;
  l_result.waitSemaphoreValuesCount = 0;
  l_result.pWaitSemaphoreValues = NULL;
  l_result.signalSemaphoreValuesCount = 0;
  l_result.pSignalSemaphoreValues = NULL;
  return l_result;
}

template <>
inline VkExportFenceWin32HandleInfoKHR sdlxvulkan::make_default<VkExportFenceWin32HandleInfoKHR>() noexcept
{
  VkExportFenceWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.pAttributes = NULL;
  l_result.dwAccess = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkExportMemoryWin32HandleInfoKHR sdlxvulkan::make_default<VkExportMemoryWin32HandleInfoKHR>() noexcept
{
  VkExportMemoryWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.pAttributes = NULL;
  l_result.dwAccess = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkExportMemoryWin32HandleInfoNV sdlxvulkan::make_default<VkExportMemoryWin32HandleInfoNV>() noexcept
{
  VkExportMemoryWin32HandleInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV;
  l_result.pNext = NULL;
  l_result.pAttributes = NULL;
  l_result.dwAccess = 0;
  return l_result;
}

template <>
inline VkExportSemaphoreWin32HandleInfoKHR sdlxvulkan::make_default<VkExportSemaphoreWin32HandleInfoKHR>() noexcept
{
  VkExportSemaphoreWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.pAttributes = NULL;
  l_result.dwAccess = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkFenceGetWin32HandleInfoKHR sdlxvulkan::make_default<VkFenceGetWin32HandleInfoKHR>() noexcept
{
  VkFenceGetWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.fence = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalFenceHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkImportFenceWin32HandleInfoKHR sdlxvulkan::make_default<VkImportFenceWin32HandleInfoKHR>() noexcept
{
  VkImportFenceWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.fence = VK_NULL_HANDLE;
  l_result.flags = static_cast<VkFenceImportFlags>(0);
  l_result.handleType = static_cast<VkExternalFenceHandleTypeFlagBits>(0);
  l_result.handle = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkImportMemoryWin32HandleInfoKHR sdlxvulkan::make_default<VkImportMemoryWin32HandleInfoKHR>() noexcept
{
  VkImportMemoryWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  l_result.handle = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkImportMemoryWin32HandleInfoNV sdlxvulkan::make_default<VkImportMemoryWin32HandleInfoNV>() noexcept
{
  VkImportMemoryWin32HandleInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV;
  l_result.pNext = NULL;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagsNV>(0);
  l_result.handle = 0;
  return l_result;
}

template <>
inline VkImportSemaphoreWin32HandleInfoKHR sdlxvulkan::make_default<VkImportSemaphoreWin32HandleInfoKHR>() noexcept
{
  VkImportSemaphoreWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.semaphore = VK_NULL_HANDLE;
  l_result.flags = static_cast<VkSemaphoreImportFlags>(0);
  l_result.handleType = static_cast<VkExternalSemaphoreHandleTypeFlagBits>(0);
  l_result.handle = 0;
  l_result.name = NULL;
  return l_result;
}

template <>
inline VkMemoryGetWin32HandleInfoKHR sdlxvulkan::make_default<VkMemoryGetWin32HandleInfoKHR>() noexcept
{
  VkMemoryGetWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.memory = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalMemoryHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkMemoryWin32HandlePropertiesKHR sdlxvulkan::make_default<VkMemoryWin32HandlePropertiesKHR>() noexcept
{
  VkMemoryWin32HandlePropertiesKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR;
  l_result.pNext = NULL;
  l_result.memoryTypeBits = 0;
  return l_result;
}

template <>
inline VkSemaphoreGetWin32HandleInfoKHR sdlxvulkan::make_default<VkSemaphoreGetWin32HandleInfoKHR>() noexcept
{
  VkSemaphoreGetWin32HandleInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.semaphore = VK_NULL_HANDLE;
  l_result.handleType = static_cast<VkExternalSemaphoreHandleTypeFlagBits>(0);
  return l_result;
}

template <>
inline VkWin32KeyedMutexAcquireReleaseInfoKHR sdlxvulkan::make_default<VkWin32KeyedMutexAcquireReleaseInfoKHR>() noexcept
{
  VkWin32KeyedMutexAcquireReleaseInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.acquireCount = 0;
  l_result.pAcquireSyncs = NULL;
  l_result.pAcquireKeys = NULL;
  l_result.pAcquireTimeouts = NULL;
  l_result.releaseCount = 0;
  l_result.pReleaseSyncs = NULL;
  l_result.pReleaseKeys = NULL;
  return l_result;
}

template <>
inline VkWin32KeyedMutexAcquireReleaseInfoNV sdlxvulkan::make_default<VkWin32KeyedMutexAcquireReleaseInfoNV>() noexcept
{
  VkWin32KeyedMutexAcquireReleaseInfoNV l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV;
  l_result.pNext = NULL;
  l_result.acquireCount = 0;
  l_result.pAcquireSyncs = NULL;
  l_result.pAcquireKeys = NULL;
  l_result.pAcquireTimeoutMilliseconds = NULL;
  l_result.releaseCount = 0;
  l_result.pReleaseSyncs = NULL;
  l_result.pReleaseKeys = NULL;
  return l_result;
}

template <>
inline VkWin32SurfaceCreateInfoKHR sdlxvulkan::make_default<VkWin32SurfaceCreateInfoKHR>() noexcept
{
  VkWin32SurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkWin32SurfaceCreateFlagsKHR>(0);
  l_result.hinstance = 0;
  l_result.hwnd = 0;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
//Xcb Platform Structs:
template <>
inline VkXcbSurfaceCreateInfoKHR sdlxvulkan::make_default<VkXcbSurfaceCreateInfoKHR>() noexcept
{
  VkXcbSurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkXcbSurfaceCreateFlagsKHR>(0);
  l_result.connection = NULL;
  l_result.window = 0;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
//Xlib Platform Structs:
template <>
inline VkXlibSurfaceCreateInfoKHR sdlxvulkan::make_default<VkXlibSurfaceCreateInfoKHR>() noexcept
{
  VkXlibSurfaceCreateInfoKHR l_result{};
  l_result.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
  l_result.pNext = NULL;
  l_result.flags = static_cast<VkXlibSurfaceCreateFlagsKHR>(0);
  l_result.dpy = NULL;
  l_result.window = 0;
  return l_result;
}

#endif

#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
//Xlib XRAndR Platform Structs:
#endif

#endif // SDLXVULKAN_MAKE_DEFAULT_HPP