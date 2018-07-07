#ifndef SDLXVULKAN_HANDLES_HPP
#define SDLXVULKAN_HANDLES_HPP

#include <type_traits>
#include <memory>
#include <vector>
#include <cassert>
#include <vulkan/vulkan.h>

namespace sdlxvulkan
{
  class Global_Functions;
  class Instance_Functions;
  class Device_Functions;
  class Window;
  class System;

  namespace internal
  {
    //---------------------------------------------------------------------------
    // Vulkan_Handle_Typechecker<T>
    //---------------------------------------------------------------------------
    // When supplied with a Vulkan handle type, chop off the pointer, and make 
    // sure the conversion all works.

    template <typename T>
    class Vulkan_Handle_Typechecker
    {
    public:
      static_assert(std::is_pointer_v<T>, "Supplied Vulkan Type is not a pointer type, cannot use.");
      using Type = std::remove_pointer_t<T>;
      static_assert(std::is_same_v<T, std::add_pointer_t<Type>>, "Bad conversion reversal.");
    };

    template <typename T>
    using Vulkan_Handle_Typechecker_T = typename Vulkan_Handle_Typechecker<T>::Type;
  }
  
  // Helper for implemenation of smart Vulkan handles. Ties a type to a Destroyer
  // object that will hold the parent smart handle(s) and clean up the Vulkan
  // handle properly.
  template <typename T, typename Destroyer>
  using Vulkan_Uptr = std::unique_ptr<internal::Vulkan_Handle_Typechecker_T<T>, Destroyer>;

  // The pimpl data type for a given Vulkan handle. The Destroyer is present but
  // not publically available, allowing the smart handle to reveal what it wants.
  template <typename T>
  using Vulkan_Sptr = std::shared_ptr<internal::Vulkan_Handle_Typechecker_T<T>>;
  

  //---------------------------------------------------------------------------
  // Handle<T>
  //---------------------------------------------------------------------------
  // Holds a Vulkan_Sptr and supplies implicit conversion to the Vulkan type.

  template <typename T>
  class Handle
  {
  private:
    Vulkan_Sptr<T> m_data;
  public:
    Handle() noexcept :
      m_data{}
    {}

    explicit Handle(Vulkan_Sptr<T> const& a_data) noexcept :
      m_data{ a_data }
    {}
    explicit Handle(Vulkan_Sptr<T> && a_data) noexcept :
      m_data{ std::move(a_data) }
    {}
    Vulkan_Sptr<T> const& get_data()  const noexcept
    {
      assert(m_data);
      return m_data;
    }
    T get() const noexcept
    {
      assert(m_data);
      return m_data.get();
    }
    void reset() noexcept
    {
      m_data = Vulkan_Sptr<T>{};
    }
    operator T() const noexcept
    {
      //assert(m_data);
      return m_data.get();
    }
    explicit operator bool()  const noexcept
    {
      return static_cast<bool>(m_data);
    }
    void swap(Handle<T>& a_other) noexcept
    {
      std::swap(this->m_data, a_other.m_data);
    }
  };

  template <typename T>
  void swap(Handle<T>& a_lhs, Handle<T>& a_rhs) noexcept
  {
    a_lhs.swap(a_rhs);
  }
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // Handle Typedefs

  // For the sake of sanity, most handles will only hold that which is required for destruction.
  
  
  //  Vulkan type stored                  Handle Parent               Lifetime Required           Construction Reliance

  //Handle<VkInstance>;                   System, Window 
  
  //Handle<VkDebugReportCallbackEXT>;     VkInstance                  VkInstance
  //Handle<VkDebugUtilsMessengerEXT>;     VkInstance                  VkInstance
  //Handle<VkPhysicalDevice>;             VkInstance                  VkInstance
  //Handle<VkSurfaceKHR>;                 VkInstance, Window          VkInstance

  //Handle<VkDevice>;                     VkPhysicalDevice            VkInstance

  //Handle<VkBuffer>;                     VkDevice                    VkDevice
  //Handle<VkBufferView>;                 VkBuffer                    VkDevice
  //Handle<VkCommandPool>;                VkDevice                    VkDevice
  //Handle<VkCommandBuffer>;              VkCommandPool               VkDevice, VkCommandPool
  //Handle<VkDescriptorPool>;             VkDevice                    VkDevice
  //Handle<VkDescriptorSet>;              VkDescriptorPool                                 VkDescriptorSetLayout
  //Handle<VkDescriptorSetLayout>;        VkDevice                    VkDevice
  //Handle<VkDescriptorUpdateTemplate>;   VkDevice                    VkDevice
  //Handle<VkDeviceMemory>;               VkDevice                    VkDevice
  //Handle<VkDisplayKHR>;                 VkPhysicalDevice
  //Handle<VkDisplayModeKHR>;             VkDisplayKHR
  //Handle<VkEvent>;                      VkDevice                    VkDevice
  //Handle<VkFence>;                      VkDevice                    VkDevice
  //Handle<VkFramebuffer>;                VkDevice                    VkDevice
  //Handle<VkImage>;                      VkDevice or VkSwapchainKHR  VkDevice or nothing
  //Handle<VkImageView>;                  VkImage                     VkDevice
  //Handle<VkIndirectCommandsLayoutNVX>;   
  //Handle<VkObjectTableNVX>;              
  //Handle<VkPipeline>;                   VkDevice                    VkDevice                   VkPipelineCache(Opt), VkPipelineLayout, VkRenderPass
  //Handle<VkPipelineCache>;              VkDevice                    VkDevice
  //Handle<VkPipelineLayout>;             VkDevice                    VkDevice
  //Handle<VkQueryPool>;                  VkDevice                    VkDevice
  //Handle<VkRenderPass>;                 VkDevice                    VkDevice
  //Handle<VkSampler>;                    VkDevice                    VkDevice
  //Handle<VkSamplerYcbcrConversion>;     VkDevice                    VkDevice
  //Handle<VkSemaphore>;                  VkDevice                    VkDevice
  //Handle<VkShaderModule>;               VkDevice                    VkDevice
  //Handle<VkSwapchainKHR>;               VkDevice                    VkDevice
  //Handle<VkQueue>;                      VkDevice                    VkDevice
  //Handle<VkValidationCacheEXT>;         VkDevice                    VkDevice
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkInstance

  //---------------------------------------------------------------------------
  // Handle<VkInstance>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkInstance. 
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Handle<VkInstance> make_instance
  (
    System const& a_system,
    Window const& a_window,
    VkInstanceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );


  // Get the functions for a VkInstance. If the shared_ptr is nullptr this 
  // returns nullptr, otherwise it returns the corresponding functions.
  Instance_Functions const* get_instance_functions(Handle<VkInstance> const& a_instance) noexcept;

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDebugReportCallbackEXT

  //---------------------------------------------------------------------------
  // Handle<VkDebugReportCallbackEXT>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDebugReportCallbackEXT.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Handle<VkDebugReportCallbackEXT> make_debug_report_callback_ext
  (
    Handle<VkInstance> const& a_instance,
    VkDebugReportCallbackCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );


  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDebugUtilsMessengerEXT

  //---------------------------------------------------------------------------
  //  Handle<VkDebugUtilsMessengerEXT>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDebugUtilsMessengerEXT.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Handle<VkDebugUtilsMessengerEXT> make_debug_utils_messenger_ext
  (
    Handle<VkInstance> const& a_instance,
    VkDebugUtilsMessengerCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPhysicalDevice

  //---------------------------------------------------------------------------
  // Physical_Device
  //---------------------------------------------------------------------------
  // Reference counting VkPhysicalDevice.
  // This doesn't do anything other than hold an Instance that it depends on.

  // How many physcial devices does Instance have? 
  // Returns zero if Instance is null.
  uint32_t get_physical_device_count(Handle<VkInstance> const& a_instance) noexcept;

  // Get all the physcial devices that Instance has. 
  // Returns an empty vector if Instance is null. 
  // Throws std::bad_alloc if the vector fails to be allocated.
  // Throws std::bad_alloc if any Handle std::shared_ptr fails to be allocated.
  std::vector<Handle<VkPhysicalDevice>> get_physical_devices(Handle<VkInstance> const& a_instance);
  
  // Throws std::runtime_error if physical device is null.
  VkPhysicalDeviceProperties get_physical_device_properties(Handle<VkPhysicalDevice> const& a_physical_device);

  // Throws std::runtime_error if physical device is null.
  VkPhysicalDeviceMemoryProperties get_physical_device_memory_properties(Handle<VkPhysicalDevice> const& a_physical_device);


  //uint32_t get_physical_device_queue_familiy_properties_count(Physical_Device const& a_physcial_device) noexcept;

  // Throws std::runtime_error if physical device is null.
  // Throws std::bad_alloc if the vector fails to be allocated.
  std::vector<VkQueueFamilyProperties> get_physical_device_queue_familiy_properties(Handle<VkPhysicalDevice> const& a_physical_device);

  // Throws std::runtime_error if physical device is null.
  // Throws std::bad_alloc if the vector fails to be allocated.
  std::vector<VkExtensionProperties> get_physical_device_extension_properties(Handle<VkPhysicalDevice> const& a_physical_device);

  // Can this physical device do graphics?
  // Returns false if physical device is null.
  bool can_graphics(Handle<VkPhysicalDevice> const& a_physical_device) noexcept;

  // Simple search for a queue family that can do graphics in this physical device.
  // Returns std::numeric_limits<uint32_t>::max() if physical device is null.
  uint32_t first_graphics_qfi(Handle<VkPhysicalDevice> const& a_physical_device) noexcept;
  
  // Using the supplied properties, determine the right kind of memory to allocate.
  // Success returns the index to the value required to allocate the right type of memory. 
  // Failure throws if no matching memory found.
  uint32_t get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags a_requirements);
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSurfaceKHR
  
  //---------------------------------------------------------------------------
  // Handle<VkSurfaceKHR>
  //---------------------------------------------------------------------------
  // Reference counting VkSurfaceKHR.

  // Make a self-destroying VkSurfaceKHR. 
  // SDL surface is a child of instance and window, and we cannot supply 
  // allocation callbacks.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Handle<VkSurfaceKHR> make_surface_khr
  (
    Handle<VkInstance> const& a_instance,
    Window const& a_window
  );

  // Can this physical device present to this surface?
  // Returns false it either are null.
  bool can_present(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface) noexcept;

  // Get the index of the first queue family that can present to this surface.
  // Returns std::numeric_limits<uint32_t>::max() if either are null.
  // Returns std::numeric_limits<uint32_t>::max() if no present queue family is
  // found.
  uint32_t first_present_qfi(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface);


  VkSurfaceCapabilitiesKHR get_surface_cababilites(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface);
  std::vector<VkSurfaceFormatKHR> get_surface_formats(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface);
  std::vector<VkPresentModeKHR> get_present_modes(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface);




  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDevice
  
  //---------------------------------------------------------------------------
  // Handle<VkDevice>
  //---------------------------------------------------------------------------
  // Reference counting VkDevice.

  // Make a self-destroying VkDevice.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Handle<VkDevice> make_device
  (
    Handle<VkPhysicalDevice> const& a_physical_device,
    VkDeviceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Get the functions for a VkDevice. If the shared_ptr is nullptr this 
  // returns nullptr, otherwise it returns the corresponding functions.
  Device_Functions const* get_device_functions(Handle<VkDevice> const& a_device) noexcept;

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkBuffer

  //---------------------------------------------------------------------------
  // Handle<VkBuffer>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkBuffer.
  Handle<VkBuffer> make_buffer
  (
    Handle<VkDevice> const& a_device,
    VkBufferCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkBufferView

  //---------------------------------------------------------------------------
  // Handle<VkBufferView>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkBuffer.
  Handle<VkBufferView> make_buffer_view
  (
    Handle<VkBuffer> const& a_buffer,
    VkBufferViewCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkCommandPool
  
  //---------------------------------------------------------------------------
  // Handle<VkCommandPool>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkCommandPool.
  Handle<VkCommandPool> make_command_pool
  (
    Handle<VkDevice> const& a_device,
    VkCommandPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  ); 
  

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkCommandBuffer

  //---------------------------------------------------------------------------
  // Handle<VkCommandBuffer>
  //---------------------------------------------------------------------------

  // Make a single self-destroying VkCommandBuffer.
  // Take note that one buffer is created regardless of 'commandBufferCount'
  // in the given allocate info.
  Handle<VkCommandBuffer> make_command_buffer
  (
    Handle<VkCommandPool> const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Handle<VkCommandBuffer>> make_command_buffers
  (
    Handle<VkCommandPool> const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorPool

  //---------------------------------------------------------------------------
  // Handle<VkDescriptorPool>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorPool.
  Handle<VkDescriptorPool> make_descriptor_pool
  (
    Handle<VkDevice> const& a_device,
    VkDescriptorPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorSet

  //---------------------------------------------------------------------------
  // Handle<VkDescriptorSet>
  //---------------------------------------------------------------------------
  // It seems handles won't really work with these without type-guards on the 
  // Descriptor_Pool

  // Make a self-destroying VkDescriptorSet.
  Handle<VkDescriptorSet> make_descriptor_set
  (
    Handle<VkDescriptorPool> const& a_descriptor_pool,
    VkDescriptorSetAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkDescriptorSet.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Handle<VkDescriptorSet>> make_descriptor_sets
  (
    Handle<VkDescriptorPool> const& a_descriptor_pool,
    VkDescriptorSetAllocateInfo const& a_allocate_info
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorSetLayout

  //---------------------------------------------------------------------------
  // Handle<VkDescriptorSetLayout>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorSetLayout.
  Handle<VkDescriptorSetLayout> make_descriptor_set_layout
  (
    Handle<VkDevice> const& a_device,
    VkDescriptorSetLayoutCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorUpdateTemplate

  //---------------------------------------------------------------------------
  // Handle<VkDescriptorUpdateTemplate>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorSetLayout.
  Handle<VkDescriptorUpdateTemplate> make_descriptor_update_template
  (
    Handle<VkDevice> const& a_device,
    VkDescriptorUpdateTemplateCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDeviceMemory

  //---------------------------------------------------------------------------
  // Handle<VkDeviceMemory>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDeviceMemory.
  Handle<VkDeviceMemory> make_device_memory
  (
    Handle<VkDevice> const& a_device,
    VkMemoryAllocateInfo const& a_allocate_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  ); 
  

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkEvent

  //---------------------------------------------------------------------------
  // Handle<VkEvent>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkEvent.
  Handle<VkEvent> make_event
  (
    Handle<VkDevice> const& a_device,
    VkEventCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkFence

  //---------------------------------------------------------------------------
  // Handle<VkFence>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkFence.
  Handle<VkFence> make_fence
  (
    Handle<VkDevice> const& a_device,
    VkFenceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkFramebuffer

  //---------------------------------------------------------------------------
  // Handle<VkFramebuffer>
  //---------------------------------------------------------------------------
  
  // Make a self-destroying VkFramebuffer.
  Handle<VkFramebuffer> make_framebuffer
  (
    Handle<VkDevice> const& a_device,
    VkFramebufferCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkImage

  //---------------------------------------------------------------------------
  // Handle<VkImage>
  //---------------------------------------------------------------------------

  // An image may be parented by either a device or a swapchain. Use these to 
  // determine which if not known beforehand.
  bool is_image_device(Handle<VkImage> const& a_image) noexcept;
  bool is_image_swapchain_khr(Handle<VkImage> const& a_image) noexcept;

  // Get the parent handle. 
  // Returns a null handle if the supplied handle is null, or is the wrong
  // kind of image.
  Handle<VkDevice> get_image_device(Handle<VkImage> const& a_image) noexcept;
  Handle<VkSwapchainKHR> get_image_swapchain_khr(Handle<VkImage> const& a_image) noexcept;

  // Make a self-destroying VkImage.
  Handle<VkImage> make_image
  (
    Handle<VkDevice> const& a_device,
    VkImageCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkImageView

  //---------------------------------------------------------------------------
  // Handle<VkImageView>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkImageView.
  Handle<VkImageView> make_image_view
  (
    Handle<VkImage> const& a_image,
    VkImageViewCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipeline

  //---------------------------------------------------------------------------
  // Handle<VkPipeline>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkPipeline.
  Handle<VkPipeline> make_graphics_pipeline
  (
    Handle<VkDevice> const& a_device,
    Handle<VkPipelineCache> const& a_pipeline_cache,
    VkGraphicsPipelineCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Make a batch of self-destroying VkPipeline.
  std::vector<Handle<VkPipeline>> make_graphics_pipelines
  (
    Handle<VkDevice> const& a_device,
    Handle<VkPipelineCache> const& a_pipeline_cache,
    std::vector<VkGraphicsPipelineCreateInfo> const& a_create_infos,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Make a self-destroying VkPipeline.
  Handle<VkPipeline> make_compute_pipeline
  (
    Handle<VkDevice> const& a_device,
    Handle<VkPipelineCache> const& a_pipeline_cache,
    VkComputePipelineCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Make a batch of self-destroying VkPipeline.
  std::vector<Handle<VkPipeline>> make_compute_pipelines
  (
    Handle<VkDevice> const& a_device,
    Handle<VkPipelineCache> const& a_pipeline_cache,
    std::vector<VkComputePipelineCreateInfo> const& a_create_infos,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipelineCache

  //---------------------------------------------------------------------------
  // Handle<VkPipelineCache>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkPipelineCache.
  Handle<VkPipelineCache> make_pipeline_cache
  (
    Handle<VkDevice> const& a_device,
    VkPipelineCacheCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipelineLayout

  //---------------------------------------------------------------------------
  // Handle<VkPipelineLayout>
  //---------------------------------------------------------------------------
  // Actually relies on N Descriptor_Set_Layouts...

  // Make a self-destroying VkPipelineLayout.
  Handle<VkPipelineLayout> make_pipeline_layout
  (
    Handle<VkDevice> const& a_device,
    VkPipelineLayoutCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkQueryPool

  //---------------------------------------------------------------------------
  // Handle<VkQueryPool>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkRenderPass.
  Handle<VkQueryPool> make_query_pool
  (
    Handle<VkDevice> const& a_device,
    VkQueryPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkQueue

  //---------------------------------------------------------------------------
  // Handle<VkQueue>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkQueue.
  Handle<VkQueue> make_queue
  (
    Handle<VkDevice> const& a_device,
    uint32_t a_queue_family_index,
    uint32_t a_queue_index
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkRenderPass

  //---------------------------------------------------------------------------
  // Handle<VkRenderPass>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkRenderPass.
  Handle<VkRenderPass> make_render_pass
  (
    Handle<VkDevice> const& a_device,
    VkRenderPassCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSampler

  //---------------------------------------------------------------------------
  // Handle<VkSampler>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSampler.
  Handle<VkSampler> make_sampler
  (
    Handle<VkDevice> const& a_device,
    VkSamplerCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSamplerYcbcrConversion

  //---------------------------------------------------------------------------
  // Handle<VkSamplerYcbcrConversion>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSamplerYcbcrConversion.
  Handle<VkSamplerYcbcrConversion> make_sampler_ycbcr_conversion
  (
    Handle<VkDevice> const& a_device,
    VkSamplerYcbcrConversionCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSemaphore

  //---------------------------------------------------------------------------
  // Handle<VkSemaphore>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSemaphore.
  Handle<VkSemaphore> make_semaphore
  (
    Handle<VkDevice> const& a_device,
    VkSemaphoreCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkShaderModule

  //---------------------------------------------------------------------------
  // Handle<VkShaderModule>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkShaderModule.
  Handle<VkShaderModule> make_shader_module
  (
    Handle<VkDevice> const& a_device,
    VkShaderModuleCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSwapchainKHR

  //---------------------------------------------------------------------------
  // Handle<VkSwapchainKHR>
  //---------------------------------------------------------------------------

  Handle<VkDevice> get_swapchain_device_khr(Handle<VkSwapchainKHR> const& a_swapchain) noexcept;

  // Make a self-destroying VkSwapchainKHR.
  Handle<VkSwapchainKHR> make_swapchain_khr
  (
    Handle<VkDevice> const& a_device,
    VkSwapchainCreateInfoKHR const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  uint32_t get_swapchain_image_count_khr
  (
    Handle<VkSwapchainKHR> const& a_swapchain
  );

  std::vector<Handle<VkImage>> get_swapchain_images_khr
  (
    Handle<VkSwapchainKHR> const& a_swapchain
  );
    
  // Shared Swapchains???????

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkValidationCacheEXT

  //---------------------------------------------------------------------------
  // Handle<VkValidationCacheEXT>
  //---------------------------------------------------------------------------

  // Make a self-destroying VkValidationCacheEXT.
  Handle<VkValidationCacheEXT> make_validation_cache_ext
  (
    Handle<VkDevice> const& a_device,
    VkValidationCacheCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SDLXVULKAN_HANDLES_HPP