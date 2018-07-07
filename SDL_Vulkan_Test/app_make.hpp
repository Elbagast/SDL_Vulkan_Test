#ifndef SDLXVULKAN_APP_MAKE_HPP
#define SDLXVULKAN_APP_MAKE_HPP

#include "handles.hpp"

namespace sdlxvulkan
{
  Handle<VkInstance> app_make_instance
  (
    System const& a_system,
    Window const& a_window,
    std::vector<std::string> const& a_extension_names,
    std::vector<std::string> const& a_layer_names,
    std::string const& a_application_name,
    uint32_t a_application_version,
    std::string const& a_engine_name,
    uint32_t a_engine_version,
    uint32_t a_vulkan_version,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Handle<VkDebugReportCallbackEXT> app_make_debug_report_callback_ext
  (
    Handle<VkInstance> const& a_instance,
    VkDebugReportFlagsEXT a_flags,
    PFN_vkDebugReportCallbackEXT a_callback,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Handle<VkDevice> app_make_device
  (
    Handle<VkPhysicalDevice> const& a_physical_device,
    uint32_t a_graphics_qfi,
    uint32_t a_present_qfi,
    std::vector<std::string> const& a_extensions,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Initialise with a VkSharingMode value of VK_SHARING_MODE_EXCLUSIVE.
  Handle<VkBuffer> app_make_buffer_exclusive
  (
    Handle<VkDevice> const& a_device,
    VkDeviceSize a_size,
    VkBufferUsageFlags a_usage,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Initialise with a VkSharingMode value of VK_SHARING_MODE_CONCURRENT. 
  // a_queue_family_indicies must have at least 2 unique values, which are
  // each less than the queue family property count of the physical device
  // this is used with.
  Handle<VkBuffer> app_make_buffer_concurrent
  (
    Handle<VkDevice> const& a_device,
    VkDeviceSize a_size,
    VkBufferUsageFlags a_usage,
    std::vector<uint32_t> a_queue_family_indicies,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  struct Buffer_Pair
  {
    Handle<VkBuffer> buffer;
    Handle<VkDeviceMemory> memory;
  };

  Buffer_Pair app_make_buffer_memory_exclusive_pair
  (
    Handle<VkPhysicalDevice> const& a_physical_device,
    Handle<VkDevice> const& a_device,
    VkDeviceSize a_size, 
    VkBufferUsageFlags a_usage, 
    VkMemoryPropertyFlags a_properties
  );

  void app_copy_buffer
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    Handle<VkQueue> const& a_queue,
    Handle<VkBuffer> const& a_source,
    Handle<VkBuffer> const& a_dest,
    VkDeviceSize a_size
  );

  Handle<VkCommandPool> app_make_command_pool
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_queue_family_index,
    VkCommandPoolCreateFlags a_flags = 0,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Handle<VkCommandBuffer>> app_make_command_buffers
  (
    Handle<VkCommandPool> const& a_command_pool,
    VkCommandBufferLevel a_level,
    uint32_t a_count
  );

  Handle<VkDeviceMemory> app_make_device_memory
  (
    Handle<VkDevice> const& a_device,
    VkDeviceSize  a_size,
    uint32_t a_memory_type_index,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Handle<VkShaderModule> app_make_shader_module_from_file
  (
    Handle<VkDevice> const& a_device,
    std::string const& a_exepath,
    std::string const& a_filepath
  );
} //namespace sdlxvulkan

#endif SDLXVULKAN_APP_MAKE_HPP
