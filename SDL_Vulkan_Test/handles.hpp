#ifndef SDLXVULKAN_HANDLES_HPP
#define SDLXVULKAN_HANDLES_HPP

//#include <stdexcept>
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
      return m_data;
    }
    T get() const noexcept
    {
      return m_data.get();
    }
    operator T() const noexcept
    {
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
  
  //---------------------------------------------------------------------------
  // Handle_Array<T>
  //---------------------------------------------------------------------------
  // Holds a std::shared_ptr<T[]> and supplies access to the Vulkan type values.
  // Size is fixed on construction.

  template <typename T>
  class Handle_Array
  {
  private:
    uint32_t m_size;
    std::shared_ptr<T[]> m_data;
  public:
    Handle_Array() noexcept :
      m_size{0},
      m_data{}
    {}
    Handle_Array(uint32_t a_size, std::shared_ptr<T[]> const& a_data) noexcept :
      m_size{ a_size },
      m_data{ a_data }
    {}
    Handle_Array(uint32_t a_size, std::shared_ptr<T[]> && a_data) noexcept :
      m_size{ a_size },
      m_data{ std::move(a_data) }
    {}
    std::shared_ptr<T[]> const& get_data()  const noexcept
    {
      return m_data;
    }
    T* get() const noexcept
    {
      return m_data.get();
    }
    operator T*() const noexcept
    {
      return m_data.get();
    }
    T operator[](std::ptrdiff_t a_index)
    {
      return m_data[a_index];
    }
    explicit operator bool() const noexcept
    {
      return static_cast<bool>(m_data);
    }
    uint32_t size() const noexcept
    {
      return m_data ? m_size : 0;
    }
    void swap(Handle_Array<T>& a_other) noexcept
    {
      std::swap(this->m_data, a_other.m_data);
    }
  };

  template <typename T>
  void swap(Handle_Array<T>& a_lhs, Handle_Array<T>& a_rhs) noexcept
  {
    a_lhs.swap(a_rhs);
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // Handle Typedefs

  //    Name                              Handle Type   Vulkan Type                   Parent(s)
  using Instance =                        Handle<       VkInstance>;                  // System, Window

  using Debug_Report_Callback_EXT =       Handle<       VkDebugReportCallbackEXT>;    // Instance
  using Debug_Utils_Messenger_EXT =       Handle<       VkDebugUtilsMessengerEXT>;    // Instance
  using Physical_Device =                 Handle<       VkPhysicalDevice>;            // Instance
  using Surface_KHR =                     Handle<       VkSurfaceKHR>;                // Instance, Window

  using Device =                          Handle<       VkDevice>;                    // (Instance), Physical_Device

  using Buffer =                          Handle<       VkBuffer>;                    // Device
  using Buffer_View =                     Handle<       VkBufferView>;                // (Device), Buffer
  using Command_Pool =                    Handle<       VkCommandPool>;               // Device
  using Command_Buffer =                  Handle<       VkCommandBuffer>;             // (Device), Command_Pool
  using Command_Buffer_Array =            Handle_Array< VkCommandBuffer>;             // (Device), Command_Pool
  using Descriptor_Pool =                 Handle<       VkDescriptorPool>;            // Device
  using Descriptor_Set =                  Handle<       VkDescriptorSet>;             // (Device), Descriptor_Pool, Descriptor_Set_Layout
  using Descriptor_Set_Array =            Handle_Array< VkDescriptorSet>;             // (Device), Descriptor_Pool, Descriptor_Set_Layout
  using Descriptor_Set_Layout =           Handle<       VkDescriptorSetLayout>;       // Device
  using Descriptor_Update_Template =      Handle<       VkDescriptorUpdateTemplate>;  // Device
  using Device_Memory =                   Handle<       VkDeviceMemory>;              // Device
  //using Display_KHR =                     Handle<       VkDisplayKHR>;                // Physical_Device
  //using Display_Mode_KHR =                Handle<       VkDisplayModeKHR>;            // Display_KHR
  using Event =                           Handle<       VkEvent>;                     // Device
  using Fence =                           Handle<       VkFence>;                     // Device
  using Framebuffer =                     Handle<       VkFramebuffer>;               // (Device), Render_Pass, Image_View(s)
  using Image =                           Handle<       VkImage>;                     // Device
  using Image_View =                      Handle<       VkImageView>;                 // (Device), Image
  //using Indirect_Commands_Layout_NVX =    Handle<       VkIndirectCommandsLayoutNVX>; //  
  //using Object_Table_NVX =                Handle<       VkObjectTableNVX>;            //  
  using Pipeline =                        Handle<       VkPipeline>;                  // (Device), Pipeline_Cache(Opt), Pipeline_Layout, Render_Pass
  using Pipeline_Cache =                  Handle<       VkPipelineCache>;             // Device
  using Pipeline_Layout =                 Handle<       VkPipelineLayout>;            // Device
  using Query_Pool =                      Handle<       VkQueryPool>;                 // Device
  using Render_Pass =                     Handle<       VkRenderPass>;                // Device
  using Sampler =                         Handle<       VkSampler>;                   // Device
  using Sampler_Ycbcr_Conversion =        Handle<       VkSamplerYcbcrConversion>;    // Device
  using Semaphore =                       Handle<       VkSemaphore>;                 // Device
  using Shader_Module =                   Handle<       VkShaderModule>;              // Device
  using Swapchain_KHR =                   Handle<       VkSwapchainKHR>;              // Device
  using Queue =                           Handle<       VkQueue>;                     // Device
  using Validation_Cache_EXT =            Handle<       VkValidationCacheEXT>;        // Device
  

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkInstance

  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------

  // Make a self-destroying VkInstance. 
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Instance make_instance
  (
    System const& a_system,
    Window const& a_window,
    VkInstanceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Instance make_instance_limited
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

  // Get the functions for a VkInstance. If the shared_ptr is nullptr this 
  // returns nullptr, otherwise it returns the corresponding functions.
  Instance_Functions const* get_instance_functions(Instance const& a_instance) noexcept;

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDebugReportCallbackEXT

  //---------------------------------------------------------------------------
  // Debug_Report_Callback_Ext
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDebugReportCallbackEXT.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Debug_Report_Callback_EXT make_debug_report_callback_ext
  (
    Instance const& a_instance,
    VkDebugReportCallbackCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Debug_Report_Callback_EXT make_debug_report_callback_ext_limited
  (
    Instance const& a_instance,
    VkDebugReportFlagsEXT a_flags,
    PFN_vkDebugReportCallbackEXT a_callback,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDebugUtilsMessengerEXT

  //---------------------------------------------------------------------------
  // Debug_Utils_Messenger_EXT
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDebugUtilsMessengerEXT.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Debug_Utils_Messenger_EXT make_debug_utils_messenger_ext
  (
    Instance const& a_instance,
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
  uint32_t get_physical_device_count(Instance const& a_instance) noexcept;

  // Get all the physcial devices that Instance has. 
  // Returns an empty vector if Instance is null. 
  // Throws std::bad_alloc if the vector fails to be allocated.
  // Throws std::bad_alloc if any Handle std::shared_ptr fails to be allocated.
  std::vector<Physical_Device> get_physical_devices(Instance const& a_instance);
  
  // Throws std::runtime_error if physical device is null.
  VkPhysicalDeviceProperties get_physical_device_properties(Physical_Device const& a_physical_device);

  // Throws std::runtime_error if physical device is null.
  VkPhysicalDeviceMemoryProperties get_physical_device_memory_properties(Physical_Device const& a_physical_device);


  //uint32_t get_physical_device_queue_familiy_properties_count(Physical_Device const& a_physcial_device) noexcept;

  // Throws std::runtime_error if physical device is null.
  // Throws std::bad_alloc if the vector fails to be allocated.
  std::vector<VkQueueFamilyProperties> get_physical_device_queue_familiy_properties(Physical_Device const& a_physical_device);

  // Throws std::runtime_error if physical device is null.
  // Throws std::bad_alloc if the vector fails to be allocated.
  std::vector<VkExtensionProperties> get_physical_device_extension_properties(Physical_Device const& a_physical_device);

  // Can this physical device do graphics?
  // Returns false if physical device is null.
  bool can_graphics(Physical_Device const& a_physical_device) noexcept;

  // Simple search for a queue family that can do graphics in this physical device.
  // Returns std::numeric_limits<uint32_t>::max() if physical device is null.
  uint32_t first_graphics_qfi(Physical_Device const& a_physical_device) noexcept;
  
  // Using the supplied properties, determine the right kind of memory to allocate.
  // Success returns the index to the value required to allocate the right type of memory. 
  // Failure throws if no matching memory found.
  uint32_t get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags a_requirements);
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSurfaceKHR
  
  //---------------------------------------------------------------------------
  // Surface_KHR
  //---------------------------------------------------------------------------
  // Reference counting VkSurfaceKHR.

  // Make a self-destroying VkSurfaceKHR. 
  // SDL surface is a child of instance and window, and we cannot supply 
  // allocation callbacks.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Surface_KHR make_surface_khr
  (
    Instance const& a_instance,
    Window const& a_window
  );

  // Can this physical device present to this surface?
  // Returns false it either are null.
  bool can_present(Physical_Device const& a_physical_device, Surface_KHR const& a_surface) noexcept;

  // Get the index of the first queue family that can present to this surface.
  // Returns std::numeric_limits<uint32_t>::max() if either are null.
  // Returns std::numeric_limits<uint32_t>::max() if no present queue family is
  // found.
  uint32_t first_present_qfi(Physical_Device const& a_physical_device, Surface_KHR const& a_surface);


  VkSurfaceCapabilitiesKHR get_surface_cababilites(Physical_Device const& a_physical_device, Surface_KHR const& a_surface);
  std::vector<VkSurfaceFormatKHR> get_surface_formats(Physical_Device const& a_physical_device, Surface_KHR const& a_surface);
  std::vector<VkPresentModeKHR> get_present_modes(Physical_Device const& a_physical_device, Surface_KHR const& a_surface);




  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDevice
  
  //---------------------------------------------------------------------------
  // Device
  //---------------------------------------------------------------------------
  // Reference counting VkDevice.

  // Make a self-destroying VkDevice.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Device make_device
  (
    Physical_Device const& a_physical_device, 
    VkDeviceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  Device make_device_limited
  (
    Physical_Device const& a_physical_device,
    uint32_t a_graphics_qfi,
    uint32_t a_present_qfi,
    std::vector<std::string> const& a_extensions,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Get the functions for a VkDevice. If the shared_ptr is nullptr this 
  // returns nullptr, otherwise it returns the corresponding functions.
  Device_Functions const* get_device_functions(Device const& a_device) noexcept;

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkBuffer

  //---------------------------------------------------------------------------
  // Buffer
  //---------------------------------------------------------------------------

  // Make a self-destroying VkBuffer.
  Buffer make_buffer
  (
    Device const& a_device,
    VkBufferCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Initialise with a VkSharingMode value of VK_SHARING_MODE_EXCLUSIVE.
  Buffer make_buffer_exclusive_limited
  (
    Device const& a_device, 
    VkDeviceSize a_size, 
    VkBufferUsageFlags a_usage,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Initialise with a VkSharingMode value of VK_SHARING_MODE_CONCURRENT. 
  // a_queue_family_indicies must have at least 2 unique values, which are
  // each less than the queue family property count of the physical device
  // this is used with.
  Buffer make_buffer_concurrent_limited
  (
    Device const& a_device,
    VkDeviceSize a_size,
    VkBufferUsageFlags a_usage,
    std::vector<uint32_t> a_queue_family_indicies,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkBufferView

  //---------------------------------------------------------------------------
  // Buffer_View
  //---------------------------------------------------------------------------

  // Make a self-destroying VkBuffer.
  Buffer_View make_buffer_view
  (
    Buffer const& a_buffer,
    VkBufferViewCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkCommandPool
  
  //---------------------------------------------------------------------------
  // Command_Pool
  //---------------------------------------------------------------------------

  // Make a self-destroying VkCommandPool.
  Command_Pool make_command_pool
  (
    Device const& a_device,
    VkCommandPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  ); 
  
  Command_Pool make_command_pool_limited
  (
    Device const& a_device,
    uint32_t a_queue_family_index,
    VkCommandPoolCreateFlags a_flags = 0,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkCommandBuffer

  //---------------------------------------------------------------------------
  // Command_Buffer
  //---------------------------------------------------------------------------

  // Make a single self-destroying VkCommandBuffer.
  // Take note that one buffer is created regardless of 'commandBufferCount'
  // in the given allocate info.
  Command_Buffer make_command_buffer
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Command_Buffer> make_command_buffers
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is of the entire array.
  Command_Buffer_Array make_command_buffer_array
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkCommandBuffer.
  // Destruction is of the entire array.
  Command_Buffer_Array make_command_buffer_array_limited
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferLevel a_level,
    uint32_t a_count
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorPool

  //---------------------------------------------------------------------------
  // Descriptor_Pool
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorPool.
  Descriptor_Pool make_descriptor_pool
  (
    Device const& a_device,
    VkDescriptorPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorSet

  //---------------------------------------------------------------------------
  // Descriptor_Set
  //---------------------------------------------------------------------------


  // Make a self-destroying VkDescriptorSet.
  Descriptor_Set make_descriptor_set
  (
    Descriptor_Pool const& a_descriptor_pool,
    Descriptor_Set_Layout const& a_descriptor_set_layout,
    VkDescriptorSetAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkDescriptorSet.
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Descriptor_Set> make_descriptor_sets
  (
    Descriptor_Pool const& a_descriptor_pool,
    Descriptor_Set_Layout const& a_descriptor_set_layout,
    VkDescriptorSetAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkDescriptorSet.
  // Destruction is of the entire array.
  Descriptor_Set_Array make_descriptor_set_array
  (
    Descriptor_Pool const& a_descriptor_pool,
    Descriptor_Set_Layout const& a_descriptor_set_layout,
    VkDescriptorSetAllocateInfo const& a_allocate_info
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorSetLayout

  //---------------------------------------------------------------------------
  // Descriptor_Set_Layout
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorSetLayout.
  Descriptor_Set_Layout make_descriptor_set_layout
  (
    Device const& a_device,
    VkDescriptorSetLayoutCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDescriptorUpdateTemplate

  //---------------------------------------------------------------------------
  // Descriptor_Update_Template
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDescriptorSetLayout.
  Descriptor_Update_Template make_descriptor_update_template
  (
    Device const& a_device,
    VkDescriptorUpdateTemplateCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDeviceMemory

  //---------------------------------------------------------------------------
  // Device_Memory
  //---------------------------------------------------------------------------

  // Make a self-destroying VkDeviceMemory.
  Device_Memory make_device_memory
  (
    Device const& a_device,
    VkMemoryAllocateInfo const& a_allocate_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  ); 
  
  Device_Memory make_device_memory_limited
  (
    Device const& a_device,
    VkDeviceSize  a_size,
    uint32_t a_memory_type_index,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkEvent

  //---------------------------------------------------------------------------
  // Event
  //---------------------------------------------------------------------------

  // Make a self-destroying VkEvent.
  Event make_event
  (
    Device const& a_device,
    VkEventCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkFence

  //---------------------------------------------------------------------------
  // Fence
  //---------------------------------------------------------------------------

  // Make a self-destroying VkImage.
  Fence make_fence
  (
    Device const& a_device,
    VkFenceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkFramebuffer

  //---------------------------------------------------------------------------
  // Framebuffer
  //---------------------------------------------------------------------------
  
  // Make a self-destroying VkImage.
  Framebuffer make_framebuffer
  (
    Render_Pass const& a_render_pass,
    std::vector<Image_View> const& a_image_views,
    VkFramebufferCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkImage

  //---------------------------------------------------------------------------
  // Image
  //---------------------------------------------------------------------------

  // Make a self-destroying VkImage.
  Image_View make_image
  (
    Device const& a_device,
    VkImageCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkImageView

  //---------------------------------------------------------------------------
  // Image_View
  //---------------------------------------------------------------------------

  // Make a self-destroying VkImageView.
  Image_View make_image_view
  (
    Image const& a_image,
    VkImageViewCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipeline

  //---------------------------------------------------------------------------
  // Pipeline
  //---------------------------------------------------------------------------

  // Make a self-destroying VkPipelineCache.
  Pipeline make_graphics_pipeline
  (
    Pipeline_Cache const* a_cache,    // optional
    Pipeline_Layout const& a_layout,  // must match a_create_info.layout
    Render_Pass const& a_render_pass, // must match a_create_info.renderPass
    VkGraphicsPipelineCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Make a batch of self-destroying VkPipelineCache.
  std::vector<Pipeline> make_graphics_pipelines
  (
    Pipeline_Cache const* a_cache,
    Pipeline_Layout const& a_layout,
    Render_Pass const& a_render_pass,
    std::vector<VkGraphicsPipelineCreateInfo> const& a_create_infos,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipelineCache

  //---------------------------------------------------------------------------
  // Pipeline_Cache
  //---------------------------------------------------------------------------

  // Make a self-destroying VkPipelineCache.
  Pipeline_Cache make_pipeline_cache
  (
    Device const& a_device,
    VkPipelineLayoutCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkPipelineLayout

  //---------------------------------------------------------------------------
  // Pipeline_Layout
  //---------------------------------------------------------------------------
  // Actually relies on N Descriptor_Set_Layouts...

  // Make a self-destroying VkPipelineLayout.
  Pipeline_Layout make_pipeline_layout
  (
    Device const& a_device,
    VkPipelineLayoutCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkQueryPool

  //---------------------------------------------------------------------------
  // Query_Pool
  //---------------------------------------------------------------------------

  // Make a self-destroying VkRenderPass.
  Query_Pool make_query_pool
  (
    Device const& a_device,
    VkQueryPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkRenderPass

  //---------------------------------------------------------------------------
  // Render_Pass
  //---------------------------------------------------------------------------

  // Make a self-destroying VkRenderPass.
  Render_Pass make_render_pass
  (
    Device const& a_device,
    VkRenderPassCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSampler

  //---------------------------------------------------------------------------
  // Sampler
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSampler.
  Sampler make_sampler
  (
    Device const& a_device,
    VkSamplerCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSamplerYcbcrConversion

  //---------------------------------------------------------------------------
  // Sampler_Ycbcr_Conversion
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSamplerYcbcrConversion.
  Sampler_Ycbcr_Conversion make_sampler_ycbcr_conversion
  (
    Device const& a_device,
    VkSamplerYcbcrConversionCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSemaphore

  //---------------------------------------------------------------------------
  // Semaphore
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSemaphore.
  Semaphore make_semaphore
  (
    Device const& a_device,
    VkSemaphoreCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkShaderModule

  //---------------------------------------------------------------------------
  // Shader_Module
  //---------------------------------------------------------------------------

  // Make a self-destroying VkShaderModule.
  Shader_Module make_shader_module
  (
    Device const& a_device,
    VkShaderModuleCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkSwapchainKHR

  //---------------------------------------------------------------------------
  // Swapchain_KHR
  //---------------------------------------------------------------------------

  // Make a self-destroying VkSwapchainKHR.
  Swapchain_KHR make_swapchain_khr
  (
    Device const& a_device,
    VkSwapchainCreateInfoKHR const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

  // Shared Swapchains???????

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkQueue

  //---------------------------------------------------------------------------
  // Queue
  //---------------------------------------------------------------------------

  // Make a self-destroying VkQueue.
  Queue make_queue
  (
    Device const& a_device,
    uint32_t a_queue_family_index,
    uint32_t a_queue_index
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkValidationCacheEXT

  //---------------------------------------------------------------------------
  // Validation_Cache_EXT
  //---------------------------------------------------------------------------

  // Make a self-destroying VkValidationCacheEXT.
  Validation_Cache_EXT make_validation_cache_ext
  (
    Device const& a_device,
    VkValidationCacheCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks = nullptr
  );

} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SDLXVULKAN_HANDLES_HPP