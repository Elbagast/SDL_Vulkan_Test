#include "queue.hpp"

#include "device.hpp"
#include "device_functions.hpp"

#include <iostream>


namespace sdlxvulkan
{
  namespace
  {
    VkQueue make_except_queue
    (
      Device const& a_device,
      uint32_t a_queue_family_index,
      uint32_t a_queue_index
    )
    {
      VkQueue l_queue{ VK_NULL_HANDLE};
      a_device.vk_functions().vkGetDeviceQueue(a_device, a_queue_family_index, a_queue_index, &l_queue);
      if (l_queue == VK_NULL_HANDLE)
      {
        throw std::runtime_error{ "Vulkan: Failed to create a queue." };
      }
      return l_queue;
    }


    //---------------------------------------------------------------------------
    // Queue
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Queue_Destroyer
    {
    private:
      // Member Data
      //============================================================
      Device m_device;

    public:
      // Special 6
      //============================================================
      explicit Queue_Destroyer(Device const& a_device) :
        m_device{ a_device }
      {
      }
      ~Queue_Destroyer() = default;

      Queue_Destroyer(Queue_Destroyer const& a_other) = default;
      Queue_Destroyer& operator=(Queue_Destroyer const& a_other) = default;

      Queue_Destroyer(Queue_Destroyer && a_other) = default;
      Queue_Destroyer& operator=(Queue_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(VkQueue) const noexcept
      {
        std::cout << "sdlxvulkan::Queue_Destroyer::operator() - does nothing" << std::endl;
      }

      Device const& get_device() const
      {
        return m_device;
      }
    };
  } // namespace  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Queue
//---------------------------------------------------------------------------
// Holds all of the information relating to a Vulkan Queue.


// Special 6
//============================================================
sdlxvulkan::Queue::Queue
(
  Device const& a_device,
  uint32_t a_queue_family_index,
  uint32_t a_queue_index
) :
  m_data{ make_except_queue(a_device, a_queue_family_index, a_queue_index), Queue_Destroyer{ a_device } }
{
  std::cout << "sdlxvulkan::Queue::Queue()" << std::endl;
}

sdlxvulkan::Queue::~Queue()
{
  std::cout << "sdlxvulkan::Queue::~Queue()" << std::endl;
}

sdlxvulkan::Device const& sdlxvulkan::Queue::get_device() const noexcept
{
  return m_data.get_destroyer<Queue_Destroyer>()->get_device();
}


VkResult sdlxvulkan::Queue::vkBindSparse(uint32_t bindInfoCount, VkBindSparseInfo const* pBindInfo, VkFence fence) const
{
  return m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueBindSparse(get(), bindInfoCount, pBindInfo, fence);
}

VkResult sdlxvulkan::Queue::vkSubmit(uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence) const
{
  return m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueSubmit(get(), submitCount, pSubmits, fence);
}

VkResult sdlxvulkan::Queue::vkWaitIdle() const
{
  return m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueWaitIdle(get());
}

void sdlxvulkan::Queue::vkBeginDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const
{
  m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueBeginDebugUtilsLabelEXT(get(), pLabelInfo);
}

void sdlxvulkan::Queue::vkEndDebugUtilsLabelEXT() const
{
  m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueEndDebugUtilsLabelEXT(get());
}

void sdlxvulkan::Queue::vkInsertDebugUtilsLabelEXT(VkDebugUtilsLabelEXT const* pLabelInfo) const
{
  m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueueInsertDebugUtilsLabelEXT(get(), pLabelInfo);
}

VkResult sdlxvulkan::Queue::vkPresentKHR(VkPresentInfoKHR const* pPresentInfo) const
{
  return m_data.get_destroyer<Queue_Destroyer>()->get_device().vk_functions().vkQueuePresentKHR(get(), pPresentInfo);
}
