#include "command_buffer.hpp"

#include "command_pool.hpp"
#include "device.hpp"
#include "device_functions.hpp"

#include <iostream>
#include <cassert>


namespace sdlxvulkan
{
  namespace
  {
    std::vector<VkCommandBuffer> make_except_command_buffers
    (
      uint32_t a_count, 
      Command_Pool const& a_command_pool, 
      VkCommandBufferLevel a_level
    )
    {
      VkCommandBufferAllocateInfo l_alloc_info{};
      l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
      l_alloc_info.pNext = nullptr;
      l_alloc_info.commandPool = a_command_pool;
      l_alloc_info.level = a_level;
      l_alloc_info.commandBufferCount = a_count;

      // Construct with size and all null handle
      std::vector<VkCommandBuffer> l_result{ a_count, VK_NULL_HANDLE };

      auto const& l_device = a_command_pool.get_device();

      if (l_device.vk_functions().vkAllocateCommandBuffers(l_device, &l_alloc_info, l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to create command buffers." };
      }

      return l_result;
    }

    VkCommandBuffer make_except_command_buffer
    (
      Command_Pool const& a_command_pool,
      VkCommandBufferLevel a_level
    )
    {
      return make_except_command_buffers(1, a_command_pool, a_level).front();
    }


    //---------------------------------------------------------------------------
    // Command_Buffer_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Command_Buffer_Destroyer
    {
    private:
      // Member Data
      //============================================================
      Command_Pool m_command_pool;

    public:
      // Special 6
      //============================================================
      explicit Command_Buffer_Destroyer(Command_Pool const& a_command_pool) :
        m_command_pool{ a_command_pool }
      {
      }
      ~Command_Buffer_Destroyer() = default;

      Command_Buffer_Destroyer(Command_Buffer_Destroyer const& a_other) = default;
      Command_Buffer_Destroyer& operator=(Command_Buffer_Destroyer const& a_other) = default;

      Command_Buffer_Destroyer(Command_Buffer_Destroyer && a_other) = default;
      Command_Buffer_Destroyer& operator=(Command_Buffer_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(VkCommandBuffer a_command_buffer) const noexcept
      {
        auto const& l_device = m_command_pool.get_device();
        l_device.vk_functions().vkFreeCommandBuffers(l_device, m_command_pool, 1, std::addressof(a_command_buffer));
        std::cout << "sdlxvulkan::Command_Buffer_Destroyer::operator()" << std::endl;
      }

      Command_Pool const& get_pool() const
      {
        return m_command_pool;
      }
    };
  } // namespace  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Command_Buffer
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Create using for a given device and queue family, setting its create 
// flags. Refer to VkCommandPoolCreateFlagBits documentation.
// Special 6
//============================================================
// Make using an externally made VkCommandBuffer. This MUST have
// been created using the supplied Command_Pool.
sdlxvulkan::Command_Buffer::Command_Buffer
(
  VkCommandBuffer a_command_buffer,
  Command_Pool const& a_command_pool
) :
  m_data{ a_command_buffer, Command_Buffer_Destroyer{ a_command_pool } }
{
  std::cout << "sdlxvulkan::Command_Buffer::Command_Buffer( raw )" << std::endl;
}


// Allocate a single command buffer for this command pool, with the
// supplied level.
sdlxvulkan::Command_Buffer::Command_Buffer
(
  Command_Pool const& a_command_pool,
  VkCommandBufferLevel a_level
) :
  m_data{ make_except_command_buffer(a_command_pool, a_level), Command_Buffer_Destroyer{ a_command_pool } }
{
  std::cout << "sdlxvulkan::Command_Buffer::Command_Buffer()" << std::endl;
}

sdlxvulkan::Command_Buffer::~Command_Buffer()
{
  std::cout << "sdlxvulkan::Command_Buffer::~Command_Buffer()" << std::endl;
}


// Interface
//============================================================
sdlxvulkan::Command_Pool const& sdlxvulkan::Command_Buffer::get_pool() const noexcept
{
  return m_data.get_destroyer<Command_Buffer_Destroyer>()->get_pool();
}



// Non-Member Interface
//============================================================

// Create a batch of Command_Buffer in one go.
std::vector<sdlxvulkan::Command_Buffer> sdlxvulkan::make_command_buffer_vector(uint32_t a_count, Command_Pool const& a_command_pool, VkCommandBufferLevel a_level)
{
  assert(a_count != 0);
  std::vector<Command_Buffer> l_result{};

  auto l_raw_command_buffers = make_except_command_buffers(a_count, a_command_pool, a_level); // if this breaks no resources leak
  
  try
  {
    l_result.reserve(a_count);
    // allocation could fail here......  
    for (auto l_raw_command_buffer : l_raw_command_buffers)
    {
      assert(l_raw_command_buffer != VK_NULL_HANDLE);
      Command_Buffer l_buffer{ l_raw_command_buffer, a_command_pool };
      l_result.push_back(std::move(l_buffer));
    }
  }
  catch (std::bad_alloc& a_exception)
  {
    // if a bad alloc occured it was in the construction of a Command_Buffer.
    // We have to clean up all raw command buffers not yet inside l_result.
    // Those inside l_result will be cleaned by the destructors.
    std::size_t l_count = l_raw_command_buffers.size() - l_result.size();

    auto const& l_device = a_command_pool.get_device();
    VkCommandBuffer* l_raw_ptr = l_raw_command_buffers.data() + l_count;
    l_device.vk_functions().vkFreeCommandBuffers(l_device, a_command_pool, l_count, l_raw_ptr);

    throw a_exception;
  }
  assert(l_result.size() == a_count);
  return l_result;
}
