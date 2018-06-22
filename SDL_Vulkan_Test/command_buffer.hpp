#ifndef SDLXVULKAN_COMMAND_BUFFER_HPP
#define SDLXVULKAN_COMMAND_BUFFER_HPP

#include "handle.hpp"
#include <array>
#include <vector>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Command_Pool;

  //---------------------------------------------------------------------------
  // Command_Buffer
  //---------------------------------------------------------------------------
  // Ok this thing is a bit complicated. Proper usage locks would need different
  // types for primary and secondary command buffers...

  // class Primary_Command_Buffer;
  // class Secondary_Command_Buffer;


  class Command_Buffer
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Handle<VkCommandBuffer>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    // Make using an externally made VkCommandBuffer. This MUST have
    // been created using the supplied Command_Pool.
    Command_Buffer
    (
      VkCommandBuffer a_command_buffer,
      Command_Pool const& a_command_pool
    );

    // Allocate a single command buffer for this command pool, with the
    // supplied level.
    Command_Buffer
    (
      Command_Pool const& a_command_pool,
      VkCommandBufferLevel a_level
    );

    ~Command_Buffer();

    Command_Buffer(Command_Buffer const& a_other);
    Command_Buffer& operator=(Command_Buffer const& a_other);

    Command_Buffer(Command_Buffer && a_other);
    Command_Buffer& operator=(Command_Buffer && a_other);

    // Interface
    //============================================================
    Data_Type::Pointer get() const noexcept { return m_data.get(); }
    operator Data_Type::Pointer() const noexcept { return m_data.get(); }

    Command_Pool const& get_pool() const noexcept;

    /*
    // Analagous to calling vkBeginCommandBuffer on this.
    // Flags CAN be set to a mask of VkCommandPoolResetFlagBits values.

    // Ok this would need to be a bunch of overloads if you want to make sure
    // the arguments are valid for all the inputs...
    VkResult begin(VkCommandBufferBeginInfo const* pBeginInfo);

    // Analagous to calling vkEndCommandBuffer on this.
    VkResult end();
    // Analagous to calling vkResetCommandBuffer on this.
    // Flags CAN be set to a mask of VkCommandBufferResetFlagBits values.
    VkResult reset(VkCommandBufferResetFlags a_flags = 0);



    // Core Functions
    void vkCmdBeginQuery(VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) const noexcept;
    void vkCmdBeginRenderPass(VkRenderPassBeginInfo const* pRenderPassBegin, VkSubpassContents contents) const noexcept;
    void vkCmdBindDescriptorSets(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets, uint32_t dynamicOffsetCount, uint32_t const* pDynamicOffsets) const noexcept;
    void vkCmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const noexcept;
    void vkCmdBindPipeline(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) const noexcept;
    void vkCmdBindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, VkBuffer const* pBuffers, VkDeviceSize const* pOffsets) const noexcept;
    void vkCmdBlitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageBlit const* pRegions, VkFilter filter) const noexcept;
    void vkCmdClearAttachments(uint32_t attachmentCount, VkClearAttachment const* pAttachments, uint32_t rectCount, VkClearRect const* pRects) const noexcept;
    void vkCmdClearColorImage(VkImage image, VkImageLayout imageLayout, VkClearColorValue const* pColor, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept;
    void vkCmdClearDepthStencilImage(VkImage image, VkImageLayout imageLayout, VkClearDepthStencilValue const* pDepthStencil, uint32_t rangeCount, VkImageSubresourceRange const* pRanges) const noexcept;
    void vkCmdCopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, VkBufferCopy const* pRegions) const noexcept;
    void vkCmdCopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept;
    void vkCmdCopyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageCopy const* pRegions) const noexcept;
    void vkCmdCopyImageToBuffer(VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, VkBufferImageCopy const* pRegions) const noexcept;
    void vkCmdCopyQueryPoolResults(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) const noexcept;
    void vkCmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDispatchBase(uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDispatchIndirect(VkBuffer buffer, VkDeviceSize offset) const noexcept;
    void vkCmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const noexcept;
    void vkCmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const noexcept;
    void vkCmdDrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept;
    void vkCmdDrawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const noexcept;
    void vkCmdEndQuery(VkQueryPool queryPool, uint32_t query) const noexcept;
    void vkCmdEndRenderPass() const noexcept;
    void vkCmdExecuteCommands(uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept;
    void vkCmdFillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const noexcept;
    void vkCmdNextSubpass(VkSubpassContents contents) const noexcept;
    void vkCmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept;
    void vkCmdPushConstants(VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, void const* pValues) const noexcept;
    void vkCmdResetEvent(VkEvent event, VkPipelineStageFlags stageMask) const noexcept;
    void vkCmdResetQueryPool(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const noexcept;
    void vkCmdResolveImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkImageResolve const* pRegions) const noexcept;
    void vkCmdSetBlendConstants(float const blendConstants[4]) const noexcept;
    void vkCmdSetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const noexcept;
    void vkCmdSetDepthBounds(float minDepthBounds, float maxDepthBounds) const noexcept;
    void vkCmdSetDeviceMask(uint32_t deviceMask) const noexcept;
    void vkCmdSetEvent(VkEvent event, VkPipelineStageFlags stageMask) const noexcept;
    void vkCmdSetLineWidth(float lineWidth) const noexcept;
    void vkCmdSetScissor(uint32_t firstScissor, uint32_t scissorCount, VkRect2D const* pScissors) const noexcept;
    void vkCmdSetStencilCompareMask(VkStencilFaceFlags faceMask, uint32_t compareMask) const noexcept;
    void vkCmdSetStencilReference(VkStencilFaceFlags faceMask, uint32_t reference) const noexcept;
    void vkCmdSetStencilWriteMask(VkStencilFaceFlags faceMask, uint32_t writeMask) const noexcept;
    void vkCmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, VkViewport const* pViewports) const noexcept;
    void vkCmdUpdateBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, void const* pData) const noexcept;
    void vkCmdWaitEvents(uint32_t eventCount, VkEvent const* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers) const noexcept;
    void vkCmdWriteTimestamp(VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) const noexcept;

    // Extension Functions
    void vkCmdBeginDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    void vkCmdDebugMarkerBeginEXT(VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept;
    void vkCmdDebugMarkerEndEXT() const noexcept;
    void vkCmdDebugMarkerInsertEXT(VkDebugMarkerMarkerInfoEXT const* pMarkerInfo) const noexcept;
    void vkCmdDispatchBaseKHR(uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const noexcept;
    void vkCmdDrawIndexedIndirectCountAMD(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept;
    void vkCmdDrawIndirectCountAMD(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const noexcept;
    void vkCmdEndDebugUtilsLabelEXT() const noexcept;
    void vkCmdInsertDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const noexcept;
    void vkCmdProcessCommandsNVX(VkCmdProcessCommandsInfoNVX const* pProcessCommandsInfo) const noexcept;
    void vkCmdPushDescriptorSetKHR(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites) const noexcept;
    void vkCmdPushDescriptorSetWithTemplateKHR(VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, void const* pData) const noexcept;
    void vkCmdReserveSpaceForCommandsNVX(VkCmdReserveSpaceForCommandsInfoNVX const* pReserveSpaceInfo) const noexcept;
    void vkCmdSetDeviceMaskKHR(uint32_t deviceMask) const noexcept;
    void vkCmdSetDiscardRectangleEXT(uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, VkRect2D const* pDiscardRectangles) const noexcept;
    void vkCmdSetSampleLocationsEXT(VkSampleLocationsInfoEXT const* pSampleLocationsInfo) const noexcept;
    void vkCmdWriteBufferMarkerAMD(VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) const noexcept;
  
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    //Android Platform Functions:
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
    void vkCmdSetViewportWScalingNV(uint32_t firstViewport, uint32_t viewportCount, VkViewportWScalingNV const* pViewportWScalings) const noexcept;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
    //Wayland Platform Functions:
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
    //Win32 Platform Functions:
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
*/
  };

  // Non-Member Interface
  //============================================================
  // Create a batch of Command_Buffer in one go.
  std::vector<Command_Buffer> make_command_buffer_vector(uint32_t a_count, Command_Pool const& a_command_pool, VkCommandBufferLevel a_level);
  
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Buffer
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Command_Buffer::Command_Buffer(Command_Buffer const& a_other) = default;
inline sdlxvulkan::Command_Buffer& sdlxvulkan::Command_Buffer::operator=(Command_Buffer const& a_other) = default;

inline sdlxvulkan::Command_Buffer::Command_Buffer(Command_Buffer && a_other) = default;
inline sdlxvulkan::Command_Buffer& sdlxvulkan::Command_Buffer::operator=(Command_Buffer && a_other) = default;


// Non-Member Interface
//============================================================


#endif // SDLXVULKAN_COMMAND_BUFFER_HPP