#ifndef SDLXVULKAN_QUEUE_HPP
#define SDLXVULKAN_QUEUE_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Device_OLD;

  //---------------------------------------------------------------------------
  // Queue
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Queue.

  class Queue_OLD
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkQueue>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    Queue_OLD
    (
      Device_OLD const& a_device,
      uint32_t a_queue_family_index,
      uint32_t a_queue_index
    );
    ~Queue_OLD();

    Queue_OLD(Queue_OLD const& a_other);
    Queue_OLD& operator=(Queue_OLD const& a_other);

    Queue_OLD(Queue_OLD && a_other);
    Queue_OLD& operator=(Queue_OLD && a_other);

    // Interface
    //============================================================
    VkQueue get() const noexcept       { return m_data.get(); }
    operator VkQueue() const noexcept  { return m_data.get(); }
    
    Device_OLD const& get_device() const noexcept;
    uint32_t get_queue_family_index() const noexcept;
    uint32_t get_queue_index() const noexcept;

    VkResult vkBindSparse(uint32_t bindInfoCount, VkBindSparseInfo const* pBindInfo, VkFence fence) const;
    VkResult vkSubmit(uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence) const;
    VkResult vkWaitIdle() const; 

    void vkBeginDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const;
    void vkEndDebugUtilsLabelEXT() const;
    void vkInsertDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const;
    VkResult vkPresentKHR(VkPresentInfoKHR const* pPresentInfo) const;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Queue
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Queue_OLD::Queue_OLD(Queue_OLD const& a_other) = default;
inline sdlxvulkan::Queue_OLD& sdlxvulkan::Queue_OLD::operator=(Queue_OLD const& a_other) = default;

inline sdlxvulkan::Queue_OLD::Queue_OLD(Queue_OLD && a_other) = default;
inline sdlxvulkan::Queue_OLD& sdlxvulkan::Queue_OLD::operator=(Queue_OLD && a_other) = default;

// Interface
//============================================================

#endif // SDLXVULKAN_QUEUE_HPP