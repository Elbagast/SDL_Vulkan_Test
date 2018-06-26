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
  class Device;

  //---------------------------------------------------------------------------
  // Queue
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Queue.

  class Queue
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkQueue>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    Queue
    (
      Device const& a_device,
      uint32_t a_queue_family_index,
      uint32_t a_queue_index
    );
    ~Queue();

    Queue(Queue const& a_other);
    Queue& operator=(Queue const& a_other);

    Queue(Queue && a_other);
    Queue& operator=(Queue && a_other);

    // Interface
    //============================================================
    VkQueue get() const noexcept       { return m_data.get(); }
    operator VkQueue() const noexcept  { return m_data.get(); }
    
    Device const& get_device() const noexcept;
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
inline sdlxvulkan::Queue::Queue(Queue const& a_other) = default;
inline sdlxvulkan::Queue& sdlxvulkan::Queue::operator=(Queue const& a_other) = default;

inline sdlxvulkan::Queue::Queue(Queue && a_other) = default;
inline sdlxvulkan::Queue& sdlxvulkan::Queue::operator=(Queue && a_other) = default;

// Interface
//============================================================

#endif // SDLXVULKAN_QUEUE_HPP