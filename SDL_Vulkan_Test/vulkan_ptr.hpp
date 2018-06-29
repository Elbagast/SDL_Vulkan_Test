#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#define SDLXVULKAN_VULKAN_PTR_HPP

#include <stdexcept>
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

  // Once we have a Vulkan handle, we need to bind it to a destroyer so that it
  // cleans up properly regardless of whether or not the shared_ptr creation
  // fails. To do this we put it in a unique_ptr first with a noexcept 
  // constructor. Then we try and make the shared_ptr.
  template <typename T, typename Destroyer, typename...Args>
  Vulkan_Sptr<T> make_except_vulkan_sptr(T a_vkhandle, Args&&... a_args)
  {
    Vulkan_Uptr<T,Destroyer> l_capture{ a_vkhandle, Destroyer{std::forward<Args>(a_args)...} };
    return Vulkan_Sptr<T>{std::move(l_capture)};
  }
  // If we wanted to wrap this in a class that supplies new things like 
  // implicit conversion to the Vulkan handle then we have to expose
  // the deleter if we want access to it...

  // This is no longer used internally


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
    void swap(Vulkan_Sptr<T>& a_other) noexcept
    {
      std::swap(this->m_data, a_other.m_data);
    }
  };
  
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkInstance

  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------
  using Instance = Handle<VkInstance>;

  // Make a self-destroying VkInstance. 
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Instance make_instance
  (
    System const& a_system,
    Window const& a_window,
    VkInstanceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks//,
    //Global_Functions const& a_global_functions
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
  // VkPhysicalDevice

  //---------------------------------------------------------------------------
  // Physical_Device
  //---------------------------------------------------------------------------
  // Reference counting VkPhysicalDevice.
  // This doesn't do anything other than hold an Instance that it depends on.
  using Physical_Device = Handle<VkPhysicalDevice>;

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
  // Surface
  //---------------------------------------------------------------------------
  // Reference counting VkSurfaceKHR.
  using Surface = Handle<VkSurfaceKHR>;

  // Make a self-destroying VkSurfaceKHR. 
  // SDL surface is a child of instance and window, and we cannot supply 
  // allocation callbacks.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Surface make_surface_khr
  (
    Instance const& a_instance,
    Window const& a_window
  );


  bool can_present(Physical_Device const& a_physical_device, Surface const& a_surface);
  uint32_t first_present_qfi(Physical_Device const& a_physical_device, Surface const& a_surface);

  // Since these can change everytime the surface changes these shouldn't be stashed
  VkSurfaceCapabilitiesKHR get_surface_cababilites(Physical_Device const& a_physical_device, Surface const& a_surface);
  std::vector<VkSurfaceFormatKHR> get_surface_formats(Physical_Device const& a_physical_device, Surface const& a_surface);
  std::vector<VkPresentModeKHR> get_present_modes(Physical_Device const& a_physical_device, Surface const& a_surface);



  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDebugReportCallbackEXT

  //---------------------------------------------------------------------------
  // Debug_Report_Callback_Ext
  //---------------------------------------------------------------------------
  // Reference counting VkDebugReportCallbackEXT.
  using Debug_Report_Callback_Ext = Handle<VkDebugReportCallbackEXT>;

  // Make a self-destroying VkDebugReportCallbackEXT.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Debug_Report_Callback_Ext make_debug_report_callback_ext
  (
    Instance const& a_instance,
    VkDebugReportCallbackCreateInfoEXT const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkDevice
  
  //---------------------------------------------------------------------------
  // Device
  //---------------------------------------------------------------------------
  // Reference counting VkDevice.
  using Device = Handle<VkDevice>;

  // Make a self-destroying VkDevice.
  // Throws std::runtime error if the Vulkan create function fails. 
  // Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
  Device make_device
  (
    Physical_Device const& a_physical_device, 
    VkDeviceCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks
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
  // VkCommandPool
  
  //---------------------------------------------------------------------------
  // Command_Pool
  //---------------------------------------------------------------------------
  using Command_Pool = Handle<VkCommandPool>;

  // Make a self-destroying VkCommandPool.
  Command_Pool make_command_pool
  (
    Device const& a_device,
    VkCommandPoolCreateInfo const& a_create_info,
    VkAllocationCallbacks const* a_allocation_callbacks
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
  using Command_Buffer = Handle<VkCommandBuffer>;

  // Make a single self-destroying VkCommandBuffer.
  // Take note that one buffer is created regardless of 'commandBufferCount'
  // in the given allocate info.
  Command_Buffer make_command_buffer
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  // Make a batch of self-destroying VkCommandBuffer with this level. 
  // Destruction is independent for each so there's no batch freeing.
  std::vector<Command_Buffer> make_command_buffers
  (
    Command_Pool const& a_command_pool,
    VkCommandBufferAllocateInfo const& a_allocate_info
  );

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // VkQueue

  //---------------------------------------------------------------------------
  // Queue
  //---------------------------------------------------------------------------
  using Queue = Handle<VkQueue>;

  // Make a self-destroying VkQueue.
  Queue make_queue
  (
    Device const& a_device,
    uint32_t a_queue_family_index,
    uint32_t a_queue_index
  );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SDLXVULKAN_VULKAN_PTR_HPP