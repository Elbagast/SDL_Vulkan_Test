#ifndef SDLXVULKAN_APP_MAKE_HPP
#define SDLXVULKAN_APP_MAKE_HPP

#include "handles.hpp"
#include <array>

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

  VkPhysicalDeviceFeatures app_make_required_device_features  
  (
    VkPhysicalDeviceFeatures const& a_supported_features
  );
  
  Handle<VkDevice> app_make_device
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    uint32_t a_graphics_qfi,
    uint32_t a_present_qfi,
    VkPhysicalDeviceFeatures const& a_features,
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
    std::vector<uint32_t> const& a_queue_family_indicies,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  struct Buffer_Pair
  {
    Handle<VkBuffer> buffer;
    Handle<VkDeviceMemory> memory;
  };

  Buffer_Pair app_make_buffer_memory_exclusive_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    VkDeviceSize a_size, 
    VkBufferUsageFlags a_usage, 
    VkMemoryPropertyFlags a_properties
  );

  void app_copy_buffer
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
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

  Handle<VkCommandBuffer> app_make_primary_command_buffer
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Handle<VkCommandBuffer>> app_make_primary_command_buffers
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    uint32_t a_count
  );

  Handle<VkCommandBuffer> app_make_begin_one_time_primary_command_buffer
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool
  );

  void app_end_submit_one_time_primary_command_buffer
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandBuffer> const& a_command_buffer,
    VkQueue a_queue
  );

  Handle<VkDeviceMemory> app_make_device_memory
  (
    Handle<VkDevice> const& a_device,
    VkDeviceSize  a_size,
    uint32_t a_memory_type_index,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Handle<VkPipelineCache> app_make_pipeline_cache
  (
    Handle<VkDevice> const& a_device
  );

  Handle<VkImage> app_make_image
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_width,
    uint32_t a_height,
    VkFormat a_format,
    VkImageTiling a_tiling,
    VkImageUsageFlags a_usage
  );

  Handle<VkDeviceMemory> app_make_bind_image_memory
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkImage> const& a_image,
    VkMemoryPropertyFlags a_properties
  );

  Handle<VkImageView> app_make_image_view
  (
    Handle<VkDevice> const& a_device,
    VkImage a_image,
    VkFormat a_format,
    VkImageAspectFlags a_aspect_flags
  );


  struct Image_Pair
  {
    Handle<VkImage> image;
    Handle<VkDeviceMemory> memory;
  };

  struct Image_Trio
  {
    Handle<VkImage> image;
    Handle<VkDeviceMemory> memory;
    Handle<VkImageView> view;
  };


  Image_Pair app_make_image_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    uint32_t a_width,
    uint32_t a_height,
    VkFormat a_format,
    VkImageTiling a_tiling,
    VkImageUsageFlags a_usage,
    VkMemoryPropertyFlags a_properties
  );

  Image_Trio app_make_image_trio
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    uint32_t a_width,
    uint32_t a_height,
    VkFormat a_format,
    VkImageTiling a_tiling,
    VkImageUsageFlags a_usage,
    VkMemoryPropertyFlags a_properties,
    VkImageAspectFlags a_aspect_flags
  );


  Image_Pair app_make_texture_image_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    std::string const& a_filepath
  );


  Image_Trio app_make_texture_image_trio
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    std::string const& a_filepath
  );

  void app_transition_image_layout
  (    
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    Handle<VkImage> const& a_image,
    VkFormat a_format, 
    VkImageLayout a_old_layout, 
    VkImageLayout a_new_layout
  );

  void app_copy_buffer_to_image
  (
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    Handle<VkBuffer> const& a_buffer,
    Handle<VkImage> const& a_image,
    uint32_t a_width,
    uint32_t a_height
  );

  // Since each sampler has mipmap info we need one for each texture...
  Handle<VkSampler> app_make_sampler
  (
    Handle<VkDevice> const& a_device,
    VkPhysicalDeviceFeatures const& a_features
  );



  bool has_stencil_component(VkFormat a_format);


  Image_Trio app_make_depth_image_trio
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    uint32_t a_width,
    uint32_t a_height
  );

  Handle<VkDescriptorSetLayout> app_make_descriptor_set_layout
  (
    Handle<VkDevice> const& a_device
  );

  Handle<VkShaderModule> app_make_shader_module_from_file
  (
    Handle<VkDevice> const& a_device,
    std::string const& a_exepath,
    std::string const& a_filepath
  );

  struct Shader_Pair
  {
    Handle<VkShaderModule> shader_module;
    VkPipelineShaderStageCreateInfo pipeline_info;
  };

  struct Shader_Group
  {
    Shader_Pair fragment;
    Shader_Pair vertex;
    std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_infos;
  };

  Shader_Pair app_make_shader_pair
  (
    Handle<VkDevice> const& a_device,
    VkShaderStageFlagBits a_stage,
    std::string const& a_exepath,
    std::string const& a_filename
  );
  
  Shader_Group app_make_shader_group
  (
    Handle<VkDevice> const& a_device,
    std::string const& a_exepath
  );


  struct Swapchain
  {
    // Caching...
    VkSurfaceCapabilitiesKHR surface_cababilites;
    std::vector<VkSurfaceFormatKHR> surface_formats;
    std::vector<VkPresentModeKHR> present_modes;

    // Configure then cache...
    VkFormat format;
    VkPresentModeKHR present_mode;
    VkExtent2D extent;
    uint32_t image_count;
    Handle<VkSwapchainKHR> handle;

    // Swapchain Images
    std::vector<VkImage> images;
    std::vector<Handle<VkImageView>> image_views;
  };

  Swapchain app_make_swapchain
  (
    Window const& a_window,
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkSurfaceKHR> const& a_surface,
    uint32_t a_graphics_qfi,
    uint32_t a_present_qfi,
    uint32_t a_frame_count,
    Swapchain const& a_old_swapchain = Swapchain{}
  );

  VkViewport app_make_viewport
  (
    Swapchain const& a_swapchain
  );

  VkRect2D app_make_scissor
  (
    Swapchain const& a_swapchain
  );

  // use the swapchain format
  Handle<VkRenderPass> app_make_render_pass
  (
    Handle<VkDevice> const& a_device,
    VkFormat a_colour_format,
    VkFormat a_depth_format
  );

  // Push constant setup would need to go in here
  Handle<VkPipelineLayout> app_make_pipeline_layout
  (
    Handle<VkDevice> const& a_device,
    Handle<VkDescriptorSetLayout> const& a_descriptor_set_layout
  );
  
  // Dynamic pipeline that needs to be supplied with a viewport and a scissor 
  Handle<VkPipeline> app_make_dynamic_pipeline
  (
    Handle<VkDevice> const& a_device,
    Handle<VkPipelineCache> const& a_pipeline_cache,
    Handle<VkPipelineLayout> const& a_pipeline_layout,
    Handle<VkRenderPass> const& a_render_pass,
    Shader_Group const& a_shader_group,
    std::vector<VkVertexInputBindingDescription> const& a_vertex_binding_descs,
    std::vector<VkVertexInputAttributeDescription> const& a_vertex_attribute_descs
  );
  
  std::vector<Handle<VkFramebuffer>> app_make_swapchain_framebuffers
  (
    Handle<VkDevice> const& a_device,
    Swapchain const& a_swapchain,
    Handle<VkRenderPass> const& a_render_pass,
    Image_Trio const& a_depth_trio
  );

  std::vector<Buffer_Pair> app_make_uniforms
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    uint32_t a_count,
    VkDeviceSize a_size
  );


  Handle<VkDescriptorPool> app_make_descriptor_pool
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_count // can be Swapchain::image_count or more
  );

  std::vector<VkDescriptorSet> app_make_descriptor_sets
  (
    Handle<VkDevice> const& a_device,
    Handle<VkDescriptorSetLayout> const& a_descriptor_set_layout,
    Handle<VkDescriptorPool> const& a_descriptor_pool,
    Image_Trio const& a_texture,
    Handle<VkSampler> const& a_sampler,
    std::vector<Buffer_Pair> const& a_uniforms,
    VkDeviceSize a_uniform_size,
    uint32_t a_frame_count
  );

  std::vector<Handle<VkSemaphore>> app_make_semaphores
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_count
  );

  std::vector<Handle<VkFence>> app_make_fences
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_count,
    VkFenceCreateFlags a_flags
  );


  Buffer_Pair app_make_load_staging_buffer_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    VkDeviceSize a_size,
    void const* a_data
  );


  Buffer_Pair app_make_vertex_buffer_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    VkDeviceSize a_size,
    void const* a_data
  );

  Buffer_Pair app_make_index_buffer_pair
  (
    Handle<VkInstance> const& a_instance,
    VkPhysicalDevice a_physical_device,
    Handle<VkDevice> const& a_device,
    Handle<VkCommandPool> const& a_command_pool,
    VkQueue a_queue,
    VkDeviceSize a_size,
    void const* a_data
  );

} //namespace sdlxvulkan

#endif // SDLXVULKAN_APP_MAKE_HPP
