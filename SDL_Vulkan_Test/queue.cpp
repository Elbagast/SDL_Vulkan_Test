#include "queue.hpp"

#include "device.hpp"
#include "device_functions.hpp"

#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Queue_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Queue_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Device_OLD m_device;
      uint32_t m_queue_family_index;
      uint32_t m_queue_index;

      // Special 6
      //============================================================
      explicit Queue_Destroyer
      (
        Device_OLD const& a_device,
        uint32_t a_queue_family_index,
        uint32_t a_queue_index
      ) :
        m_device{ a_device },
        m_queue_family_index{ a_queue_family_index },
        m_queue_index{ a_queue_index }
      {
        std::cout << "sdlxvulkan::Queue_Destroyer::Queue_Destroyer()" << std::endl;
      }
      // Interface
      //============================================================
      void operator()(VkQueue) const noexcept
      {
        std::cout << "sdlxvulkan::Queue_Destroyer::operator() - does nothing" << std::endl;
      }
    };

    decltype(auto) make_except_queue
    (
      Device_OLD const& a_device,
      uint32_t a_queue_family_index,
      uint32_t a_queue_index
    )
    {
      VkQueue l_queue{ VK_NULL_HANDLE };
      a_device.vk_functions().vkGetDeviceQueue(a_device, a_queue_family_index, a_queue_index, &l_queue);
      if (l_queue == VK_NULL_HANDLE)
      {
        throw std::runtime_error{ "Vulkan: Failed to create a queue." };
      }
      return make_except_vulkan_sptr<VkQueue, Queue_Destroyer>(l_queue, a_device, a_queue_family_index, a_queue_index);
    }
  } // namespace  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Queue
//---------------------------------------------------------------------------
// Holds all of the information relating to a Vulkan Queue.


// Special 6
//============================================================
sdlxvulkan::Queue_OLD::Queue_OLD
(
  Device_OLD const& a_device,
  uint32_t a_queue_family_index,
  uint32_t a_queue_index
) :
  m_data{ make_except_queue(a_device, a_queue_family_index, a_queue_index) }
{
  //std::cout << "sdlxvulkan::Queue::Queue()" << std::endl;
}

sdlxvulkan::Queue_OLD::~Queue_OLD()
{
  //std::cout << "sdlxvulkan::Queue::~Queue()" << std::endl;
}

sdlxvulkan::Device_OLD const& sdlxvulkan::Queue_OLD::get_device() const noexcept
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_device;
}

uint32_t sdlxvulkan::Queue_OLD::get_queue_family_index() const noexcept
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_queue_family_index;
}

uint32_t sdlxvulkan::Queue_OLD::get_queue_index() const noexcept
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_queue_index;
}

VkResult sdlxvulkan::Queue_OLD::vkBindSparse(uint32_t bindInfoCount, VkBindSparseInfo const* pBindInfo, VkFence fence) const
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueBindSparse(get(), bindInfoCount, pBindInfo, fence);
}

VkResult sdlxvulkan::Queue_OLD::vkSubmit(uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence) const
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueSubmit(get(), submitCount, pSubmits, fence);
}

VkResult sdlxvulkan::Queue_OLD::vkWaitIdle() const
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueWaitIdle(get());
}

void sdlxvulkan::Queue_OLD::vkBeginDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const
{
  std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueBeginDebugUtilsLabelEXT(get(), pLabelInfo);
}

void sdlxvulkan::Queue_OLD::vkEndDebugUtilsLabelEXT() const
{
  std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueEndDebugUtilsLabelEXT(get());
}

void sdlxvulkan::Queue_OLD::vkInsertDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const
{
  std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueueInsertDebugUtilsLabelEXT(get(), pLabelInfo);
}

VkResult sdlxvulkan::Queue_OLD::vkPresentKHR(VkPresentInfoKHR const* pPresentInfo) const
{
  return std::get_deleter<Queue_Destroyer>(m_data)->m_device.vk_functions().vkQueuePresentKHR(get(), pPresentInfo);
}
