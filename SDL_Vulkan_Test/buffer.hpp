#ifndef SDLXVULKAN_BUFFER_HPP
#define SDLXVULKAN_BUFFER_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 
#include <vector>

namespace sdlxvulkan
{
  class Device_OLD;

  //---------------------------------------------------------------------------
  // Buffer
  //---------------------------------------------------------------------------
  // Holds a VkBuffer with reference counting and cleans up properly. 

  class Buffer_OLD
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkBuffer>;
    Data_Type m_data;

  public:
    /*
    enum class Create_Flags : VkFlags
    {
      None = 0,
      Sparse_Binding = VK_BUFFER_CREATE_SPARSE_BINDING_BIT,
      Sparse_Residency = VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT,
      Sparse_Aliased = VK_BUFFER_CREATE_SPARSE_ALIASED_BIT,
      Protected = VK_BUFFER_CREATE_PROTECTED_BIT,
    };

    enum class Usage_Flags : VkFlags
    {
      None = 0,
      Transfer_Source = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
      Transfer_Destination = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
      Uniform_Texel = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
      Storage_Texel = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
      Uniform = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      Storage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
      Index = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
      Vertex = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      Indirect = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
    };

    */

    // Special 6
    //============================================================
    Buffer_OLD
    (
      Device_OLD const& a_device,

      VkBufferCreateFlags a_flags,
      VkDeviceSize a_size,
      VkBufferUsageFlags a_usage,
      std::vector<uint32_t> a_queue_family_indices,
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );

    ~Buffer_OLD();

    Buffer_OLD(Buffer_OLD const& a_other);
    Buffer_OLD& operator=(Buffer_OLD const& a_other);

    Buffer_OLD(Buffer_OLD && a_other);
    Buffer_OLD& operator=(Buffer_OLD && a_other);

    // Interface
    //============================================================
    VkBuffer get() const noexcept { return m_data.get(); }
    operator VkBuffer() const noexcept { return m_data.get(); }

    Device_OLD const& get_device() const noexcept;

    uint32_t get_queue_family_index() const noexcept;
    VkCommandPoolCreateFlags get_flags() const noexcept;
    VkAllocationCallbacks const* get_allocation_callbacks() const noexcept;

    // Analagous to calling vkResetCommandPool on this.
    // Flags CAN be set to a mask of VkCommandPoolResetFlagBits values.
    void reset(VkCommandPoolResetFlags a_flags = 0);

    // Analagous to calling vkTrimCommandPool on this.
    // Vulkan 1.1.0: Flags are reserved and MUST be zero.
    void trim(VkCommandPoolTrimFlags a_flags = 0);
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Buffer
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Buffer_OLD::Buffer_OLD(Buffer_OLD const& a_other) = default;
inline sdlxvulkan::Buffer_OLD& sdlxvulkan::Buffer_OLD::operator=(Buffer_OLD const& a_other) = default;

inline sdlxvulkan::Buffer_OLD::Buffer_OLD(Buffer_OLD && a_other) = default;
inline sdlxvulkan::Buffer_OLD& sdlxvulkan::Buffer_OLD::operator=(Buffer_OLD && a_other) = default;

#endif // SDLXVULKAN_BUFFER_HPP