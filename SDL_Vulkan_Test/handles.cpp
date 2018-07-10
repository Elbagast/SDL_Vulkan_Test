#include "handles.hpp"

#include "global_functions.hpp"
#include "instance_functions.hpp"
#include "device_functions.hpp"
#include "window.hpp"
#include "system.hpp"
#include <SDL_vulkan.h>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <array>

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Instance_Destroyer
    //---------------------------------------------------------------------------
    // Special destroyer for VkInstance.

    class Instance_Destroyer
    {
    private:
      using Destroyer_Func_Type = PFN_vkDestroyInstance;// void(*)(VkInstance, VkAllocationCallbacks const*);

      System m_system;
      Window m_window;
      VkAllocationCallbacks const* m_allocation_callbacks;
      Instance_Functions m_functions;
    public:
      Instance_Destroyer(System const& a_system, Window const& a_window, VkAllocationCallbacks const* a_allocation_callbacks, Instance_Functions&& a_functions) :
        m_system{ a_system },
        m_window{ a_window },
        m_allocation_callbacks{ a_allocation_callbacks },
        m_functions{ a_functions }
      {
        assert(m_functions.vkDestroyInstance != nullptr);
      }
      void operator()(VkInstance a_vk_handle) const noexcept
      {
        m_functions.vkDestroyInstance(a_vk_handle, m_allocation_callbacks);
      }
      VkAllocationCallbacks const* allocation_callbacks() const noexcept
      {
        return m_allocation_callbacks;
      }
      Instance_Functions const* functions() const noexcept
      {
        return &m_functions;
      }
    };

    //---------------------------------------------------------------------------
    // Device_Destroyer
    //---------------------------------------------------------------------------
    // Special destroyer for VkDevice.

    class Device_Destroyer
    {
    private:
      using Destroyer_Func_Type = PFN_vkDestroyDevice;// void(*)(VkDevice, VkAllocationCallbacks const*);

      Handle<VkInstance> m_parent;
      VkAllocationCallbacks const* m_allocation_callbacks;
      Device_Functions m_functions;

    public:
      Device_Destroyer(Handle<VkInstance> const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks, Device_Functions&& a_functions) :
        m_parent{ a_instance },
        m_allocation_callbacks{ a_allocation_callbacks },
        m_functions{ a_functions }
      {
        assert(m_parent != nullptr);
        assert(m_functions.vkDestroyDevice != nullptr);
      }
      void operator()(VkDevice a_vk_handle) const noexcept
      {
        m_functions.vkDestroyDevice(a_vk_handle, m_allocation_callbacks);
      }
      Handle<VkInstance> const& parent() const noexcept
      {
        return m_parent;
      }
      VkAllocationCallbacks const* allocation_callbacks() const noexcept
      {
        return m_allocation_callbacks;
      }
      Device_Functions const* functions() const noexcept
      {
        return &m_functions;
      }
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------
    // Now the more general types.

    // Helper for create function type
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename T_Vk_Parent>
    class Vulkan_Creator_Function_Pointer
    {
    public:
      using Type = std::add_pointer_t<VKAPI_ATTR VkResult VKAPI_CALL(T_Vk_Parent, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*)>;
    };

    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename T_Vk_Parent>
    using Vulkan_Creator_PFN = typename Vulkan_Creator_Function_Pointer<T_Vk_Handle, T_Vk_Create_Info, T_Vk_Parent>::Type;
    //using Vulkan_Creator_PFN = std::add_pointer_t<VKAPI_ATTR VkResult VKAPI_CALL(T_Vk_Parent, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*)>;

    static_assert(std::is_same_v<Vulkan_Creator_PFN<VkDebugReportCallbackEXT, VkDebugReportCallbackCreateInfoEXT, VkInstance>, PFN_vkCreateDebugReportCallbackEXT>, "");

    // Helper for destroy function type
    template <typename T_Vk_Handle, typename T_Vk_Parent>
    class Vulkan_Destroyer_Function_Pointer
    {
    public:
      using Type = std::add_pointer_t<VKAPI_ATTR void VKAPI_CALL(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*)>;
    };

    template <typename T_Vk_Handle, typename T_Vk_Parent>
    using Vulkan_Destroyer_PFN = typename Vulkan_Destroyer_Function_Pointer<T_Vk_Handle, T_Vk_Parent>::Type;
    //using Vulkan_Destroyer_PFN = std::add_pointer_t<VKAPI_ATTR void VKAPI_CALL(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*)>;

    static_assert(std::is_same_v<Vulkan_Destroyer_PFN<VkDebugReportCallbackEXT, VkInstance>, PFN_vkDestroyDebugReportCallbackEXT>, "");


    //---------------------------------------------------------------------------
    // Vulkan_Destroyer<T_Vk_Parent, T_Vk_Handle>
    //---------------------------------------------------------------------------
    // Holds a parent raw Vulkan handle and uses it as a function arument to
    // destroy the handle. Can hold any number of smart handles.

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    class Vulkan_Destroyer
    {
    private:
      using Destroyer_Func_Type = Vulkan_Destroyer_PFN<T_Vk_Handle, T_Vk_Parent>;// void(*)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*);
      using Store_Type = std::tuple<Args...>;

      T_Vk_Parent m_parent;
      VkAllocationCallbacks const* m_allocation_callbacks;
      Destroyer_Func_Type m_destroyer;
      Store_Type m_store;

    public:
      Vulkan_Destroyer
      (
        T_Vk_Parent a_parent,
        VkAllocationCallbacks const* a_allocation_callbacks,
        Destroyer_Func_Type a_destroyer,
        Store_Type&& a_args
      ) :
        m_parent{ a_parent },
        m_allocation_callbacks{ a_allocation_callbacks },
        m_destroyer{ a_destroyer },
        m_store{ std::move(a_args) }
      {
        assert(m_parent != nullptr);
        assert(m_destroyer != nullptr);
      }
      void operator()(T_Vk_Handle a_vk_handle) const noexcept
      {
        m_destroyer(m_parent, a_vk_handle, m_allocation_callbacks);
      }
      T_Vk_Parent parent() const noexcept
      {
        return m_parent;
      }
      VkAllocationCallbacks const* allocation_callbacks() const noexcept
      {
        return m_allocation_callbacks;
      }
      Destroyer_Func_Type destroyer() const noexcept
      {
        return m_destroyer;
      }
      template <std::size_t N>
      decltype(auto) get() const noexcept
      {
        return std::get<N>(m_store);
      }
    };

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    Vulkan_Uptr<T_Vk_Handle, Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>> make_unique_vk
    (
      T_Vk_Handle a_handle,
      T_Vk_Parent a_parent,
      VkAllocationCallbacks const* a_allocation_callbacks,
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*),
      std::tuple<Args...>&& a_args
    )
    {
      using Destroyer_Type = Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>;
      using Uptr_Type = Vulkan_Uptr<T_Vk_Handle, Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>>;

      return Uptr_Type{ a_handle, Destroyer_Type{ a_parent, a_allocation_callbacks, a_destroyer, std::move(a_args) } };
    }

    // There's a thing going on with the template type deductions here:
    // If the arguments are the types, it can deduce them, but if the types
    // are in a template, it can't because T_Vk_Handle doesn't appear outside
    // the template types so it can't be deduced.

    // Factory function for any Vulkan types. It could be hidden if it's only used
    // by named functions that call this, using it as an implementation aid.
    // Things are also simpler if we don't want to reveal the Destroyers...
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename T_Vk_Parent, typename...Args>
    Handle<T_Vk_Handle> make_handle_vk
    (
      T_Vk_Parent a_parent,
      T_Vk_Create_Info const& a_create_info,
      VkAllocationCallbacks const* a_allocation_callbacks,
      //Vulkan_Creator_PFN<T_Vk_Handle, T_Vk_Create_Info, T_Vk_Parent> a_creator,
      //Vulkan_Destroyer_PFN<T_Vk_Handle, T_Vk_Parent> a_destroyer
      VKAPI_ATTR VkResult(VKAPI_CALL *a_creator)(T_Vk_Parent, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*),
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      assert(a_parent != nullptr);
      assert(a_creator != nullptr);
      assert(a_destroyer != nullptr);
      T_Vk_Handle l_handle{ VK_NULL_HANDLE };
      if (a_creator(a_parent, &a_create_info, a_allocation_callbacks, &l_handle) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Bad creation of a Vulkan handle for Vulkan_Sptr" };
      }

      auto l_capture = make_unique_vk(l_handle, a_parent, a_allocation_callbacks, a_destroyer, std::make_tuple(a_args...));
      return Handle<T_Vk_Handle>{Vulkan_Sptr<T_Vk_Handle>{std::move(l_capture)}};
    }


    // Simplify creation of VkInstance children.
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename...Args>
    Handle<T_Vk_Handle> make_instance_child
    (
      Handle<VkInstance> const& a_instance,
      T_Vk_Create_Info const& a_create_info,
      VkAllocationCallbacks const* a_allocation_callbacks,
      //Vulkan_Creator_PFN<T_Vk_Handle, T_Vk_Create_Info, VkInstance> a_creator,
      //Vulkan_Destroyer_PFN<T_Vk_Handle, VkInstance> a_destroyer
      VKAPI_ATTR VkResult(VKAPI_CALL *a_creator)(VkInstance, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*),
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(VkInstance, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      return make_handle_vk(a_instance.get(), a_create_info, a_allocation_callbacks, a_creator, a_destroyer, a_instance, std::forward<Args>(a_args)...);
    }

    //template <typename T_Vk_Handle, typename...Args>
    //using Instance_Child_Destroyer = Vulkan_Destroyer<T_Vk_Handle, VkInstance, Instance, Args...>;

    // Simplify creation of VkDevice children.
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename...Args>
    Handle<T_Vk_Handle> make_device_child
    (
      Handle<VkDevice> const& a_device,
      T_Vk_Create_Info const& a_create_info,
      VkAllocationCallbacks const* a_allocation_callbacks,
      //Vulkan_Creator_PFN<T_Vk_Handle, T_Vk_Create_Info, VkDevice> a_creator,
      //Vulkan_Destroyer_PFN<T_Vk_Handle, VkDevice> a_destroyer
      VKAPI_ATTR VkResult(VKAPI_CALL *a_creator)(VkDevice, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*),
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(VkDevice, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      return make_handle_vk(a_device.get(), a_create_info, a_allocation_callbacks, a_creator, a_destroyer, a_device, std::forward<Args>(a_args)...);
    }

    //template <typename T_Vk_Handle, typename...Args>
    //using Device_Child_Destroyer = Vulkan_Destroyer<T_Vk_Handle, VkDevice, Device, Args...>;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Vulkan_Blank_Destroyer<T_Vk_Parent, T_Vk_Handle>
    //---------------------------------------------------------------------------
    // Holds any number of parent Vulkan handles and carries out no destruction.

    template <typename T_Vk_Handle, typename...Args>
    class Vulkan_Blank_Destroyer
    {
    private:
      using Store_Type = std::tuple<Args...>;

      Store_Type m_store;

    public:
      explicit Vulkan_Blank_Destroyer
      (
        std::tuple<Args...>&& a_args
      ) :
        m_store{ std::move(a_args) }
      {
      }
      void operator()(T_Vk_Handle) const noexcept
      {
      }
      template <std::size_t N>
      decltype(auto) get() const noexcept
      {
        return std::get<N>(m_store);
      }
    };
    /*
    template <typename T_Vk_Handle, typename...Args>
    decltype(auto) make_vulkan_blank_destroyer
    (
      Args&&...a_args
    )
    {
      return Vulkan_Blank_Destroyer<T_Vk_Handle, std::decay_t<Args>...>(std::forward<Args>(a_args)...);
    }
    */

    template <typename T_Vk_Handle, typename...Args>
    decltype(auto) make_blank_unique_vk
    (
      T_Vk_Handle a_handle,
      std::tuple<Args...>&& a_args
    )
    {
      using Destroyer_Type = Vulkan_Blank_Destroyer<T_Vk_Handle, Args...>;
      using Uptr_Type = Vulkan_Uptr<T_Vk_Handle, Destroyer_Type>;

      return Uptr_Type{ a_handle, Destroyer_Type{ std::move(a_args) } };
    }

    // There's a thing going on with the template type deductions here:
    // If the arguments are the types, it can deduce them, but if the types
    // are in a template, it can't because T_Vk_Handle doesn't appear outside
    // the template types so it can't be deduced.

    // Factory function for any Vulkan types. It could be hidden if it's only used
    // by named functions that call this, using it as an implementation aid.
    // Things are also simpler if we don't want to reveal the Destroyers...
    template <typename T_Vk_Handle, typename...Args>
    Handle<T_Vk_Handle> make_blank_handle_vk
    (
      T_Vk_Handle a_handle,
      Args&&...a_args
    )
    {
      assert(a_handle != VK_NULL_HANDLE);
      T_Vk_Handle l_handle{ VK_NULL_HANDLE };

      auto l_capture = make_blank_unique_vk<T_Vk_Handle, std::decay_t<Args>...>(a_handle, std::make_tuple(a_args...));
      return Handle<T_Vk_Handle>{Vulkan_Sptr<T_Vk_Handle>{std::move(l_capture)}};
    }

    template <typename T_Vk_Handle, typename...Args>
    using Blank_Instance_Destroyer = Vulkan_Blank_Destroyer<T_Vk_Handle, Handle<VkInstance>, Args...>;

    // Simplify creation of VkInstance children.
    template <typename T_Vk_Handle, typename...Args>
    Handle<T_Vk_Handle> make_blank_instance_child
    (
      T_Vk_Handle a_handle,
      Handle<VkInstance> const& a_instance,
      Args&&...a_args
    )
    {
      return make_blank_handle_vk(a_handle, a_instance, std::forward<Args>(a_args)...);
    }

    
    template <typename T_Vk_Handle, typename...Args>
    using Blank_Device_Destroyer = Vulkan_Blank_Destroyer<T_Vk_Handle, Handle<VkDevice>, Args...>;

    // Simplify creation of VkDevice children.
    template <typename T_Vk_Handle, typename...Args>
    Handle<T_Vk_Handle> make_blank_device_child
    (
      T_Vk_Handle a_handle,
      Handle<VkDevice> const& a_device,
      Args&&...a_args
    )
    {
      return make_blank_handle_vk(a_handle, a_device, std::forward<Args>(a_args)...);
    }


  } //namespace
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkInstance


//---------------------------------------------------------------------------
// Instance
//---------------------------------------------------------------------------
// Make a self-destroying VkInstance. 
// Throws std::runtime error if the Vulkan create function fails. 
// Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
sdlxvulkan::Handle<VkInstance> sdlxvulkan::make_instance
(
  System const& a_system,
  Window const& a_window,
  VkInstanceCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks//,
  //Global_Functions const& a_global_functions
)
{
  auto const& l_global_functions = a_system.vk_functions();
  assert(l_global_functions.vkGetInstanceProcAddr != nullptr);
  assert(l_global_functions.vkCreateInstance != nullptr);
  VkInstance l_instance{ VK_NULL_HANDLE };
  if (l_global_functions.vkCreateInstance(&a_create_info, a_allocation_callbacks, &l_instance) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Bad creation of a VkInstance." };
  }
  Instance_Functions l_functions{ l_instance, l_global_functions };
  using Deleter_Type = Instance_Destroyer;
  Vulkan_Uptr<VkInstance, Deleter_Type> l_caught{ l_instance, Deleter_Type{ a_system, a_window, a_allocation_callbacks, std::move(l_functions) } };
  return Handle<VkInstance>{ Vulkan_Sptr<VkInstance>{std::move(l_caught)} };
}


// Get the functions for a VkInstance. If the shared_ptr is nullptr this 
// returns nullptr, otherwise it returns the corresponding functions.
sdlxvulkan::Instance_Functions const* sdlxvulkan::get_instance_functions(Handle<VkInstance> const& a_instance) noexcept
{
  if (a_instance)
  {
    return std::get_deleter<Instance_Destroyer>(a_instance.get_data())->functions();
  }
  else
  {
    return nullptr;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDebugReportCallbackEXT

//---------------------------------------------------------------------------
// Handle<VkDebugReportCallbackEXT>
//---------------------------------------------------------------------------

sdlxvulkan::Handle<VkDebugReportCallbackEXT> sdlxvulkan::make_debug_report_callback_ext
(
  Handle<VkInstance> const& a_instance,
  VkDebugReportCallbackCreateInfoEXT const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_instance != nullptr);
  auto l_functions = get_instance_functions(a_instance);
  assert(l_functions != nullptr);
  return make_instance_child(a_instance, a_create_info, a_allocation_callbacks, l_functions->vkCreateDebugReportCallbackEXT, l_functions->vkDestroyDebugReportCallbackEXT);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDebugUtilsMessengerEXT

//---------------------------------------------------------------------------
// Debug_Utils_Messenger_EXT
//---------------------------------------------------------------------------

// Make a self-destroying VkDebugUtilsMessengerEXT.
// Throws std::runtime error if the Vulkan create function fails. 
// Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
sdlxvulkan::Handle<VkDebugUtilsMessengerEXT> sdlxvulkan::make_debug_utils_messenger_ext
(
  Handle<VkInstance> const& a_instance,
  VkDebugUtilsMessengerCreateInfoEXT const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_instance != nullptr);
  auto l_functions = get_instance_functions(a_instance);
  assert(l_functions != nullptr);
  return make_instance_child(a_instance, a_create_info, a_allocation_callbacks, l_functions->vkCreateDebugUtilsMessengerEXT, l_functions->vkDestroyDebugUtilsMessengerEXT);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkPhysicalDevice

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------

// Physical_Device imp helpers
namespace sdlxvulkan
{
  namespace
  {
    //using Physical_Device_Deleter = Blank_Instance_Destroyer<VkPhysicalDevice>;
    using Physical_Device_Deleter = Vulkan_Blank_Destroyer<VkPhysicalDevice, Handle<VkInstance>>;

    Handle<VkInstance> const& get_instance(Handle<VkPhysicalDevice> const& a_physical_device) noexcept
    {
      auto l_deleter = std::get_deleter<Physical_Device_Deleter>(a_physical_device.get_data());
      assert(l_deleter);
      return l_deleter->get<0>();
    }

    bool imp_is_graphics_capable(VkQueueFamilyProperties const& a_qf)
    {
      return a_qf.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    }

    bool imp_can_graphics(std::vector<VkQueueFamilyProperties> const& a_queue_familiy_properties)
    {
      auto l_found = std::find_if(a_queue_familiy_properties.cbegin(), a_queue_familiy_properties.cend(), imp_is_graphics_capable);
      if (l_found != a_queue_familiy_properties.cend())
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    uint32_t imp_count_physical_device_queue_familiy_properties(Handle<VkPhysicalDevice> const& a_physical_device, Instance_Functions const* a_functions)
    {
      uint32_t l_count{ 0 };
      a_functions->vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, nullptr);
      return l_count;
    }

  }
}
// How many physcial devices does Instance have? 
// Returns zero if Instance is null.
uint32_t sdlxvulkan::get_physical_device_count(Handle<VkInstance> const& a_instance) noexcept
{
  uint32_t l_count{ 0 };
  if (a_instance)
  {
    auto l_functions = get_instance_functions(a_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkEnumeratePhysicalDevices != nullptr);
    l_functions->vkEnumeratePhysicalDevices(a_instance, &l_count, nullptr);
  }
  return l_count;
}

// Get all the physcial devices that Instance has. 
// Returns an empty vector if Instance is null. 
// Throws std::bad_alloc if the vector fails to be allocated.
// Throws std::bad_alloc if any Handle std::shared_ptr fails to be allocated.
std::vector<sdlxvulkan::Handle<VkPhysicalDevice>> sdlxvulkan::get_physical_devices(Handle<VkInstance> const& a_instance)
{
  std::vector<Handle<VkPhysicalDevice>> l_result{};
  if (a_instance)
  {
    auto l_functions = get_instance_functions(a_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkEnumeratePhysicalDevices != nullptr);

    uint32_t l_count{ 0 };
    l_functions->vkEnumeratePhysicalDevices(a_instance, &l_count, nullptr);

    std::vector<VkPhysicalDevice> l_handles{};
    l_handles.resize(l_count);

    l_functions->vkEnumeratePhysicalDevices(a_instance, &l_count, l_handles.data());

    l_result.reserve(l_count);
    for (auto l_handle : l_handles)
    {
      //auto l_pd = make_blank_instance_child(l_handle, a_instance);
      auto l_pd = make_blank_handle_vk(l_handle, a_instance);
      assert(l_pd);
      assert(l_pd.get() == l_handle);
      assert(get_instance(l_pd));
      l_result.push_back(std::move(l_pd));
    }
  }
  return l_result;
}



// Throws std::runtime_error if physical device is null.
VkPhysicalDeviceProperties sdlxvulkan::get_physical_device_properties(Handle<VkPhysicalDevice> const& a_physical_device)
{
  if (!a_physical_device)
  {
    std::runtime_error{"Null Physical_Device"};
  }
  assert(a_physical_device);
  auto const& l_instance = get_instance(a_physical_device);
  assert(l_instance);
  auto l_functions = get_instance_functions(l_instance);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceProperties != nullptr);

  VkPhysicalDeviceProperties l_result{};
  l_functions->vkGetPhysicalDeviceProperties(a_physical_device, &l_result);
  return l_result;
}

// Throws std::runtime_error if physical device is null.
VkPhysicalDeviceMemoryProperties sdlxvulkan::get_physical_device_memory_properties(Handle<VkPhysicalDevice> const& a_physical_device)
{
  if (!a_physical_device)
  {
    std::runtime_error{ "Null VkPhysicalDevice" };
  }
  assert(a_physical_device);
  auto const& l_instance = get_instance(a_physical_device);
  assert(l_instance);
  auto l_functions = get_instance_functions(l_instance);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceMemoryProperties != nullptr);

  VkPhysicalDeviceMemoryProperties l_result{};
  l_functions->vkGetPhysicalDeviceMemoryProperties(a_physical_device, &l_result);
  return l_result;
}

// Throws std::runtime_error if physical device is null.
VkPhysicalDeviceFeatures sdlxvulkan::get_physical_device_features(Handle<VkPhysicalDevice> const& a_physical_device)
{
  if (!a_physical_device)
  {
    std::runtime_error{ "Null VkPhysicalDevice" };
  }
  assert(a_physical_device);
  auto const& l_instance = get_instance(a_physical_device);
  assert(l_instance);
  auto l_functions = get_instance_functions(l_instance);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceFeatures != nullptr);

  VkPhysicalDeviceFeatures l_result{};
  l_functions->vkGetPhysicalDeviceFeatures(a_physical_device, &l_result);
  return l_result;
}

//uint32_t get_physical_device_queue_familiy_properties_count(Physical_Device const& a_physcial_device) noexcept;

// Throws std::runtime_error if physical device is null.
// Throws std::bad_alloc if the vector fails to be allocated.
std::vector<VkQueueFamilyProperties> sdlxvulkan::get_physical_device_queue_familiy_properties(Handle<VkPhysicalDevice> const& a_physical_device)
{
  std::vector<VkQueueFamilyProperties> l_result{};
  if (a_physical_device)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkGetPhysicalDeviceQueueFamilyProperties != nullptr);

    //uint32_t l_count{ 0 };
    //l_functions->vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, nullptr);

    uint32_t l_count = imp_count_physical_device_queue_familiy_properties(a_physical_device, l_functions);
    l_result.resize(l_count);

    l_functions->vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, l_result.data());
  }
  return l_result;
}

// Throws std::runtime_error if physical device is null.
// Throws std::bad_alloc if the vector fails to be allocated.
std::vector<VkExtensionProperties> sdlxvulkan::get_physical_device_extension_properties(Handle<VkPhysicalDevice> const& a_physical_device)
{
  std::vector<VkExtensionProperties> l_result{};
  if (a_physical_device)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkEnumerateDeviceExtensionProperties != nullptr);

    uint32_t l_count{ 0 };
    if (l_functions->vkEnumerateDeviceExtensionProperties(a_physical_device, nullptr, &l_count, nullptr) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get physical device extension properties count." };
    }
    l_result.resize(l_count);
    if (l_functions->vkEnumerateDeviceExtensionProperties(a_physical_device, nullptr, &l_count, l_result.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get physical device extension properties." };
    }
  }
  return l_result;
}

// Can this physical device do graphics?
// Returns false if physical device is null.
bool sdlxvulkan::can_graphics(Handle<VkPhysicalDevice> const& a_physical_device) noexcept
{
  if (a_physical_device)
  {
    auto l_qfps = get_physical_device_queue_familiy_properties(a_physical_device);
    auto l_found = std::find_if(l_qfps.cbegin(), l_qfps.cend(), imp_is_graphics_capable);
    if (l_found != l_qfps.cend())
    {
      return true;
    }
  }
  return false;
}

// Simple search for a queue family that can do graphics in this physical device.
// Returns std::numeric_limits<uint32_t>::max() if physical device is null.
uint32_t sdlxvulkan::first_graphics_qfi(Handle<VkPhysicalDevice> const& a_physical_device) noexcept
{
  if (a_physical_device)
  {
    auto l_qfps = get_physical_device_queue_familiy_properties(a_physical_device);
    auto l_found = std::find_if(l_qfps.cbegin(), l_qfps.cend(), imp_is_graphics_capable);
    if (l_found != l_qfps.cend())
    {
      return static_cast<uint32_t>(std::distance(l_qfps.cbegin(), l_found));
    }
  }
  return std::numeric_limits<uint32_t>::max();
}

// Using the supplied properties, determine the right kind of memory to allocate.
// Success returns the index to the value required to allocate the right type of memory. 
// Failure throws if no matching memory found.
uint32_t sdlxvulkan::get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags a_requirements)
{
  // Search memtypes to find first index with those properties
  for (uint32_t i = 0; i < a_properties.memoryTypeCount; i++)
  {
    // If has 
    if (a_typebits & (1 << i))
    {
      // Type is available, does it match user properties?
      if ((a_properties.memoryTypes[i].propertyFlags & a_requirements) == a_requirements)
      {
        return i;
      }
    }
    a_typebits >>= 1;
  }
  // No memory types matched, return failure
  throw std::runtime_error{ "Vulkan: Failed to find a suitable memory type." };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkSurfaceKHR

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Surface_KHR_Deleter = Vulkan_Destroyer<VkSurfaceKHR, VkInstance, Handle<VkInstance>, Window>;

    Handle<VkInstance> const& get_instance(Handle<VkSurfaceKHR> const& a_surface) noexcept
    {
      auto l_deleter = std::get_deleter<Surface_KHR_Deleter>(a_surface.get_data());
      assert(l_deleter);
      return l_deleter->get<0>();
    }

    Window const& get_window(Handle<VkSurfaceKHR> const& a_surface) noexcept
    {
      auto l_deleter = std::get_deleter<Surface_KHR_Deleter>(a_surface.get_data());
      assert(l_deleter);
      return l_deleter->get<1>();
    }

    bool is_present_capable(Handle<VkPhysicalDevice> const& a_physical_device, uint32_t a_qfi, Handle<VkSurfaceKHR> const& a_surface, Instance_Functions const* a_functions)
    {
      assert(a_physical_device != nullptr);
      assert(a_surface != nullptr);
      assert(a_functions != nullptr);
      assert(a_functions->vkGetPhysicalDeviceSurfaceSupportKHR != nullptr);
      VkBool32 l_qf_can_present{ VK_FALSE };
      if (a_functions->vkGetPhysicalDeviceSurfaceSupportKHR(a_physical_device, a_qfi, a_surface, &l_qf_can_present) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: vkGetPhysicalDeviceSurfaceSupportKHR failed." };
      }

      return l_qf_can_present == VK_TRUE;
    }
  }
}

// SDL surface is a child of instance and window, and we cannot supply 
// allocation callbacks.
sdlxvulkan::Handle<VkSurfaceKHR> sdlxvulkan::make_surface_khr
(
  Handle<VkInstance> const& a_instance,
  Window const& a_window
)
{
  assert(a_instance != nullptr);
  auto l_functions = get_instance_functions(a_instance);
  assert(l_functions != nullptr);
  assert(l_functions->vkDestroySurfaceKHR != nullptr);
  
  VkSurfaceKHR l_surface{};
  if (SDL_Vulkan_CreateSurface(a_window, a_instance.get(), &l_surface) != SDL_TRUE)
  {
    throw std::runtime_error("SDL: Failed to create a VkSurfaceKHR.");
  }
  auto l_caught = make_unique_vk( l_surface, a_instance.get(), nullptr, l_functions->vkDestroySurfaceKHR, std::make_tuple(a_instance, a_window) );
  return Handle<VkSurfaceKHR>{ Vulkan_Sptr<VkSurfaceKHR>{std::move(l_caught)} };
}

// Can this physical device present to this surface?
// Returns false it either are null.
bool sdlxvulkan::can_present(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface) noexcept
{
  if (a_physical_device && a_surface)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    // probably should just ge the count...
    auto l_count = imp_count_physical_device_queue_familiy_properties(a_physical_device, l_functions);
    for (uint32_t l_index = 0; l_index != l_count; ++l_index)
    {
      if (is_present_capable(a_physical_device, l_index, a_surface, l_functions))
      {
        return true;
      }
    }
  }
  return false;
}

// Get the index of the first queue family that can present to this surface.
// Returns std::numeric_limits<uint32_t>::max() if either are null.
// Returns std::numeric_limits<uint32_t>::max() if no present queue family is
// found.
uint32_t sdlxvulkan::first_present_qfi(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface)
{
  if (a_physical_device && a_surface)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    auto l_count = imp_count_physical_device_queue_familiy_properties(a_physical_device, l_functions);
    for (uint32_t l_index = 0; l_index != l_count; ++l_index)
    {
      if (is_present_capable(a_physical_device, l_index, a_surface, l_functions))
      {
        return l_index;
      }
    }
  }
  return std::numeric_limits<uint32_t>::max();
}

VkSurfaceCapabilitiesKHR sdlxvulkan::get_surface_cababilites(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface)
{
  if (!a_physical_device || !a_surface)
  {
    std::runtime_error{ "Null argument supplied" };
  }
  assert(a_physical_device);
  auto const& l_instance = get_instance(a_physical_device);
  assert(l_instance);
  auto l_functions = get_instance_functions(l_instance);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceSurfaceCapabilitiesKHR != nullptr);

  VkSurfaceCapabilitiesKHR l_result{};
  if (l_functions->vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_physical_device, a_surface, &l_result) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get surface capabilites." };
  }
  return l_result;
}

std::vector<VkSurfaceFormatKHR> sdlxvulkan::get_surface_formats(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface)
{
  std::vector<VkSurfaceFormatKHR> l_result{};
  if (a_physical_device && a_surface)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkGetPhysicalDeviceSurfaceFormatsKHR != nullptr);

    uint32_t l_count{ 0 };
    if (l_functions->vkGetPhysicalDeviceSurfaceFormatsKHR(a_physical_device, a_surface, &l_count, nullptr) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get surface format count." };
    }
    l_result.resize(l_count);
    if (l_functions->vkGetPhysicalDeviceSurfaceFormatsKHR(a_physical_device, a_surface, &l_count, l_result.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get surface formats." };
    }
  }
  return l_result;
}

std::vector<VkPresentModeKHR> sdlxvulkan::get_present_modes(Handle<VkPhysicalDevice> const& a_physical_device, Handle<VkSurfaceKHR> const& a_surface)
{
  std::vector<VkPresentModeKHR> l_result{};
  if (a_physical_device && a_surface)
  {
    assert(a_physical_device);
    auto const& l_instance = get_instance(a_physical_device);
    assert(l_instance);
    auto l_functions = get_instance_functions(l_instance);
    assert(l_functions != nullptr);
    assert(l_functions->vkGetPhysicalDeviceSurfacePresentModesKHR != nullptr);

    uint32_t l_count{ 0 };
    if (l_functions->vkGetPhysicalDeviceSurfacePresentModesKHR(a_physical_device, a_surface, &l_count, nullptr) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get surface present modes." };
    }
    l_result.resize(l_count);
    if (l_functions->vkGetPhysicalDeviceSurfacePresentModesKHR(a_physical_device, a_surface, &l_count, l_result.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get surface present modes." };
    }
  }
  return l_result;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDevice

//---------------------------------------------------------------------------
// Handle<VkDevice>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    Handle<VkInstance> const& get_instance(Handle<VkDevice> const& a_handle) noexcept
    {
      assert(a_handle);
      auto l_deleter = std::get_deleter<Device_Destroyer>(a_handle.get_data());
      assert(l_deleter);
      return l_deleter->parent();
    }
  }
}


// Make a self-destroying VkDevice.
// Throws std::runtime error if the Vulkan create function fails. 
// Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
sdlxvulkan::Handle<VkDevice> sdlxvulkan::make_device
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  VkDeviceCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_physical_device != nullptr);
  auto const& l_instance = std::get_deleter<Physical_Device_Deleter>(a_physical_device.get_data())->get<0>();
  assert(l_instance);
  auto l_instance_funcs = get_instance_functions(l_instance);
  assert(l_instance_funcs != nullptr);
  assert(l_instance_funcs->vkCreateDevice != nullptr);
  assert(l_instance_funcs->vkGetDeviceProcAddr != nullptr);
  VkDevice l_device{ VK_NULL_HANDLE };
  if (l_instance_funcs->vkCreateDevice(a_physical_device, &a_create_info, a_allocation_callbacks, &l_device) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Bad creation of VkDevice." };
  }
  Device_Functions l_functions{ l_device, *l_instance_funcs };

  using Deleter_Type = Device_Destroyer;
  Vulkan_Uptr<VkDevice, Deleter_Type> l_caught{ l_device, Deleter_Type{ l_instance, a_allocation_callbacks, std::move(l_functions) } };
  return Handle<VkDevice>{ Vulkan_Sptr<VkDevice>{std::move(l_caught)} };
}


// Get the functions for a VkDevice. If the shared_ptr is nullptr this 
// returns nullptr, otherwise it returns the corresponding functions.
sdlxvulkan::Device_Functions const* sdlxvulkan::get_device_functions(Handle<VkDevice> const& a_device) noexcept
{
  if (a_device != nullptr)
  {
    return std::get_deleter<Device_Destroyer>(a_device.get_data())->functions();
  }
  else
  {
    return nullptr;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkBuffer

//---------------------------------------------------------------------------
// Handle<VkBuffer>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Buffer_Deleter = Vulkan_Destroyer<VkBuffer, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkBuffer> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Buffer_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}


// Make a self-destroying VkBuffer.
sdlxvulkan::Handle<VkBuffer> sdlxvulkan::make_buffer
(
  Handle<VkDevice> const& a_device,
  VkBufferCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateBuffer, l_functions->vkDestroyBuffer);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkBufferView

//---------------------------------------------------------------------------
// Handle<VkBufferView>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Buffer_View_Deleter = Vulkan_Destroyer<VkBufferView, VkDevice, Handle<VkBuffer>>;

    Handle<VkBuffer> const& getbuffer(Handle<VkBufferView> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Buffer_View_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkBuffer.
sdlxvulkan::Handle<VkBufferView> sdlxvulkan::make_buffer_view
(
  Handle<VkBuffer> const& a_buffer,
  VkBufferViewCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_buffer != nullptr);
  auto const& l_device = get_device(a_buffer);
  assert(l_device != nullptr);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions != nullptr);

  // How are we going to convert from buffer to device...
  return make_device_child(l_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateBufferView, l_functions->vkDestroyBufferView, a_buffer); 
  // for now just stuff buffer in here for now
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkCommandPool

//---------------------------------------------------------------------------
// Handle<VkCommandPool>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Command_Pool_Deleter = Vulkan_Destroyer<VkCommandPool, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkCommandPool> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Command_Pool_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkCommandPool.
sdlxvulkan::Handle<VkCommandPool> sdlxvulkan::make_command_pool
(
  Handle<VkDevice> const& a_device,
  VkCommandPoolCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateCommandPool, l_functions->vkDestroyCommandPool);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkCommandBuffer

//---------------------------------------------------------------------------
// Handle<VkCommandBuffer>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Single_Command_Buffer_Destroyer
    //---------------------------------------------------------------------------
    class Single_Command_Buffer_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Handle<VkCommandPool> m_command_pool;

      // Special 6
      //============================================================
      explicit Single_Command_Buffer_Destroyer(Handle<VkCommandPool> const& a_command_pool) :
        m_command_pool{ a_command_pool }
      {
        assert(m_command_pool);
      }

      // Interface
      //============================================================
      void operator()(VkCommandBuffer a_command_buffer) const noexcept
      {
        auto const& l_device = get_device(m_command_pool);
        auto l_functions = get_device_functions(l_device);
        assert(l_functions);
        assert(l_functions->vkFreeCommandBuffers != nullptr);
        l_functions->vkFreeCommandBuffers(l_device, m_command_pool, 1, &a_command_buffer);
      }
    };

    //---------------------------------------------------------------------------
    // Vulkan_Array_Destroyer
    //---------------------------------------------------------------------------
    // Destroys an array of device children

    template <typename T_Vk_Handle, typename T_Vk_Parent_1, typename T_Vk_Parent_2, typename T_Return, typename...Args>
    class Vulkan_Array_Single_Destroyer
    {
    public:
      using Destroyer_Func_Type = T_Return(VKAPI_PTR *)(T_Vk_Parent_1, T_Vk_Parent_2, uint32_t, T_Vk_Handle const*);
      //using Destroyer_Func_Type = PFN_vkFreeCommandBuffers;
      using Store_Type = std::tuple<Args...>;

      T_Vk_Parent_1 m_parent_1;
      T_Vk_Parent_2 m_parent_2;
      Destroyer_Func_Type m_destroyer;
      Store_Type m_store;

    public:
      Vulkan_Array_Single_Destroyer
      (
        T_Vk_Parent_1 a_parent_1,
        T_Vk_Parent_2 a_parent_2,
        Destroyer_Func_Type a_destroyer,
        std::tuple<Args...>&& a_args
      ) :
        m_parent_1{ a_parent_1 },
        m_parent_2{ a_parent_2 },
        m_destroyer{ a_destroyer },
        m_store{ std::move(a_args) }
      {
        assert(a_parent_1 != VK_NULL_HANDLE);
        assert(a_parent_2 != VK_NULL_HANDLE);
        assert(m_destroyer != nullptr);
      }
      void operator()(T_Vk_Handle a_vk_handles) const noexcept
      {
        m_destroyer(m_parent_1, m_parent_2, 1, &a_vk_handles);
        //delete[] a_vk_handles;
      }
      T_Vk_Parent_1 parent_1() const noexcept
      {
        return m_parent_1;
      }
      T_Vk_Parent_2 parent_2() const noexcept
      {
        return m_parent_2;
      }
      uint32_t size() const noexcept
      {
        return m_size;
      }
      Destroyer_Func_Type destroyer() const noexcept
      {
        return m_destroyer;
      }
      template <std::size_t N>
      decltype(auto) get() const noexcept
      {
        std::get<N>(m_store);
      }
    };

    std::vector<VkCommandBuffer> imp_make_except_command_buffers
    (
      Handle<VkCommandPool> const& a_command_pool,
      VkCommandBufferAllocateInfo const& a_allocate_info
    )
    {
      assert(a_command_pool);
      auto const& l_device = get_device(a_command_pool);
      assert(l_device);
      auto l_functions = get_device_functions(l_device);
      assert(l_functions != nullptr);
      assert(l_functions->vkAllocateCommandBuffers != nullptr);
      assert(l_functions->vkFreeCommandBuffers != nullptr);
      // Construct with size and all null handle
      std::vector<VkCommandBuffer> l_result{ a_allocate_info.commandBufferCount, VK_NULL_HANDLE };

      if (l_functions->vkAllocateCommandBuffers(l_device, &a_allocate_info, l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to create command buffers." };
      }

      return l_result;
    }

    VkCommandBuffer imp_make_except_command_buffer
    (
      Handle<VkCommandPool> const& a_command_pool,
      VkCommandBufferAllocateInfo const& a_allocate_info
    )
    {
      VkCommandBufferAllocateInfo l_allocate_info = a_allocate_info;
      l_allocate_info.commandBufferCount = 1;
      return imp_make_except_command_buffers(a_command_pool, l_allocate_info).front();
    }

  }
}

namespace sdlxvulkan
{
  namespace
  {
    using Command_Buffer_Destroyer = Vulkan_Array_Single_Destroyer<VkCommandBuffer, VkDevice, VkCommandPool, void, Handle<VkCommandPool>>;
  }
}


// Make a single self-destroying VkCommandBuffer.
// Take note that one buffer is created regardless of 'commandBufferCount'
// in the given allocate info.
sdlxvulkan::Handle<VkCommandBuffer> sdlxvulkan::make_command_buffer
(
  Handle<VkCommandPool> const& a_command_pool,
  VkCommandBufferAllocateInfo const& a_allocate_info
)
{
  assert(a_command_pool);
  assert(a_allocate_info.commandPool == a_command_pool.get());
  auto const& l_device = get_device(a_command_pool);
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateCommandBuffers != nullptr);
  assert(l_functions->vkFreeCommandBuffers != nullptr);

  VkCommandBuffer l_handle = imp_make_except_command_buffer(a_command_pool, a_allocate_info);

  //using Deleter_Type = Single_Command_Buffer_Destroyer;
  
  Vulkan_Uptr<VkCommandBuffer, Command_Buffer_Destroyer> l_caught{ l_handle, Command_Buffer_Destroyer{ l_device.get(), a_command_pool.get(), l_functions->vkFreeCommandBuffers, std::make_tuple(a_command_pool) } };
  return Handle<VkCommandBuffer>{ Vulkan_Sptr<VkCommandBuffer>{std::move(l_caught)} };
}

// Make a batch of self-destroying VkCommandBuffer.
// Destruction is independent for each so there's no batch freeing.
std::vector<sdlxvulkan::Handle<VkCommandBuffer>> sdlxvulkan::make_command_buffers
(
  Handle<VkCommandPool> const& a_command_pool,
  VkCommandBufferAllocateInfo const& a_allocate_info
)
{
  assert(a_command_pool);
  assert(a_allocate_info.commandPool == a_command_pool.get());
  auto const& l_device = get_device(a_command_pool);
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateCommandBuffers != nullptr);
  assert(l_functions->vkFreeCommandBuffers != nullptr);

  // Start by making sure we have aquired enough memory to capture the Vulkan handles.
  using Deleter_Type = Single_Command_Buffer_Destroyer;
  std::vector<Vulkan_Uptr<VkCommandBuffer, Deleter_Type>> l_caught_ptrs{ };

  // This allocation could throw, if it does there's nothing special to clean up.
  l_caught_ptrs.reserve(a_allocate_info.commandBufferCount);

  // If this breaks no resources leak
  auto l_raw_command_buffers = imp_make_except_command_buffers(a_command_pool, a_allocate_info); 

  // Now  put them all in the unique_ptr, none of this should throw.
  for (auto l_raw_command_buffer : l_raw_command_buffers)
  {
    assert(l_raw_command_buffer != VK_NULL_HANDLE);
    Vulkan_Uptr<VkCommandBuffer, Deleter_Type> l_caught{ l_raw_command_buffer, Single_Command_Buffer_Destroyer{ a_command_pool } };
    l_caught_ptrs.push_back(std::move(l_caught));
  }
  // Now every handle has a deleter.

  // Now make the handles and shared_ptr
  std::vector<Handle<VkCommandBuffer>> l_result{};
  // allocation could fail here, but the handles will clean up.
  l_result.reserve(a_allocate_info.commandBufferCount); 
    
  for (auto& l_caught : l_caught_ptrs)
  {
    // The shared_ptr could fail and throw. 
    // In the case of an exception, we are relying on the constructor NOT altering
    // the unique_ptr until it has aquired any necessary resources. This is because 
    // the Vulkan handles will be cleaned up properly when they are inside the 
    // unique_ptr and the shared_ptr, but not if they are in limbo between these.
    Handle<VkCommandBuffer> l_buffer{ Vulkan_Sptr<VkCommandBuffer>{std::move(l_caught)} };
    assert(l_buffer);
    l_result.push_back(std::move(l_buffer));
  }

  assert(l_result.size() == a_allocate_info.commandBufferCount);
  return l_result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDescriptorPool

//---------------------------------------------------------------------------
// Handle<VkDescriptorPool>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Descriptor_Pool_Deleter = Vulkan_Destroyer<VkDescriptorPool, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkDescriptorPool> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Descriptor_Pool_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkDescriptorPool.
sdlxvulkan::Handle<VkDescriptorPool> sdlxvulkan::make_descriptor_pool
(
  Handle<VkDevice> const& a_device,
  VkDescriptorPoolCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateDescriptorPool, l_functions->vkDestroyDescriptorPool);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDescriptorSet

//---------------------------------------------------------------------------
// Descriptor_Set
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Descriptor_Set_Destroyer = Vulkan_Blank_Destroyer<VkDescriptorSet, Handle<VkDescriptorPool>>;

    std::vector<VkDescriptorSet> imp_make_descriptor_sets
    (
      Handle<VkDescriptorPool> const& a_descriptor_pool,
      VkDescriptorSetAllocateInfo const& a_allocate_info
    )
    {
      assert(a_descriptor_pool);
      auto const& l_device = get_device(a_descriptor_pool);
      assert(l_device);
      auto l_functions = get_device_functions(l_device);
      assert(l_functions != nullptr);
      assert(l_functions->vkAllocateDescriptorSets != nullptr);
      assert(l_functions->vkFreeDescriptorSets != nullptr);
      // Construct with size and all null handle
      std::vector<VkDescriptorSet> l_result{ a_allocate_info.descriptorSetCount, VK_NULL_HANDLE };

      if (l_functions->vkAllocateDescriptorSets(l_device, &a_allocate_info, l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to create descriptor sets." };
      }

      return l_result;
    }
    
  }
}


// Make a self-destroying VkDescriptorSet.
sdlxvulkan::Handle<VkDescriptorSet> sdlxvulkan::make_descriptor_set
(
  Handle<VkDescriptorPool> const& a_descriptor_pool,
  VkDescriptorSetAllocateInfo const& a_allocate_info
)
{
  assert(a_descriptor_pool);
  assert(a_allocate_info.descriptorPool == a_descriptor_pool.get());
  assert(a_allocate_info.descriptorSetCount == 1);
  auto const& l_device = get_device(a_descriptor_pool);
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateDescriptorSets != nullptr);
  assert(l_functions->vkFreeDescriptorSets != nullptr); // not actually used? or sometimes used?....erk

  VkDescriptorSet l_raw_handle = imp_make_descriptor_sets(a_descriptor_pool, a_allocate_info).front();
  //static_assert(std::is_same_v<PFN_vkFreeDescriptorSets, typename Descriptor_Set_Destroyer::Destroyer_Func_Type>,"Bad function type match.");

  //Vulkan_Uptr<VkDescriptorSet, Descriptor_Set_Destroyer> l_caught{ l_handle, Descriptor_Set_Destroyer{ l_device.get(), a_descriptor_pool.get(), l_functions->vkFreeDescriptorSets, std::make_tuple(a_descriptor_pool) } };
  Vulkan_Uptr<VkDescriptorSet, Descriptor_Set_Destroyer> l_caught{ l_raw_handle, Descriptor_Set_Destroyer{ std::make_tuple(a_descriptor_pool) } };
  return Handle<VkDescriptorSet>{ Vulkan_Sptr<VkDescriptorSet>{std::move(l_caught)} };
}

// Make a batch of self-destroying VkDescriptorSet.
// Destruction is independent for each so there's no batch freeing.
std::vector<sdlxvulkan::Handle<VkDescriptorSet>> sdlxvulkan::make_descriptor_sets
(
  Handle<VkDescriptorPool> const& a_descriptor_pool,
  VkDescriptorSetAllocateInfo const& a_allocate_info
)
{
  assert(a_descriptor_pool);
  assert(a_allocate_info.descriptorPool == a_descriptor_pool.get());
  auto const& l_device = get_device(a_descriptor_pool);
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateDescriptorSets != nullptr);
  assert(l_functions->vkFreeDescriptorSets != nullptr);
  
  // Start by making sure we have aquired enough memory to capture the Vulkan handles.
  using Deleter_Type = Descriptor_Set_Destroyer;
  std::vector<Vulkan_Uptr<VkDescriptorSet, Deleter_Type>> l_caught_ptrs{};

  // This allocation could throw, if it does there's nothing special to clean up.
  l_caught_ptrs.reserve(a_allocate_info.descriptorSetCount);

  // If this breaks no resources leak
  auto l_raw_handles = imp_make_descriptor_sets(a_descriptor_pool, a_allocate_info);

  // Now  put them all in the unique_ptr, none of this should throw.
  for (auto l_raw_handle : l_raw_handles)
  {
    assert(l_raw_handle != VK_NULL_HANDLE);
    Vulkan_Uptr<VkDescriptorSet, Deleter_Type> l_caught{ l_raw_handle, Deleter_Type{ a_descriptor_pool } };
    l_caught_ptrs.push_back(std::move(l_caught));
  }
  // Now every handle has a deleter.

  // Now make the handles and shared_ptr
  std::vector<Handle<VkDescriptorSet>> l_result{};
  // allocation could fail here, but the handles will clean up.
  l_result.reserve(a_allocate_info.descriptorSetCount);

  for (auto& l_caught : l_caught_ptrs)
  {
    // The shared_ptr could fail and throw. 
    // In the case of an exception, we are relying on the constructor NOT altering
    // the unique_ptr until it has aquired any necessary resources. This is because 
    // the Vulkan handles will be cleaned up properly when they are inside the 
    // unique_ptr and the shared_ptr, but not if they are in limbo between these.
    Handle<VkDescriptorSet> l_buffer{ Vulkan_Sptr<VkDescriptorSet>{std::move(l_caught)} };
    l_result.push_back(std::move(l_buffer));
  }

  assert(l_result.size() == a_allocate_info.descriptorSetCount);
  return l_result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDescriptorSetLayout

//---------------------------------------------------------------------------
// Handle<VkDescriptorSetLayout>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Descriptor_Set_Layout_Deleter = Vulkan_Destroyer<VkDescriptorSetLayout, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkDescriptorSetLayout> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Descriptor_Set_Layout_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkDescriptorSetLayout.
sdlxvulkan::Handle<VkDescriptorSetLayout> sdlxvulkan::make_descriptor_set_layout
(
  Handle<VkDevice> const& a_device,
  VkDescriptorSetLayoutCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateDescriptorSetLayout, l_functions->vkDestroyDescriptorSetLayout);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDescriptorUpdateTemplate

//---------------------------------------------------------------------------
// Handle<VkDescriptorUpdateTemplate>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Descriptor_Update_Template_Deleter = Vulkan_Destroyer<VkDescriptorUpdateTemplate, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkDescriptorUpdateTemplate> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Descriptor_Update_Template_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkDescriptorSetLayout.
sdlxvulkan::Handle<VkDescriptorUpdateTemplate> sdlxvulkan::make_descriptor_update_template
(
  Handle<VkDevice> const& a_device,
  VkDescriptorUpdateTemplateCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateDescriptorUpdateTemplate, l_functions->vkDestroyDescriptorUpdateTemplate);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDeviceMemory

//---------------------------------------------------------------------------
// Handle<VkDeviceMemory>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Device_Memory_Deleter = Vulkan_Destroyer<VkDeviceMemory, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkDeviceMemory> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Device_Memory_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkDeviceMemory.
sdlxvulkan::Handle<VkDeviceMemory> sdlxvulkan::make_device_memory
(
  Handle<VkDevice> const& a_device,
  VkMemoryAllocateInfo const& a_allocate_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_allocate_info, a_allocation_callbacks, l_functions->vkAllocateMemory, l_functions->vkFreeMemory);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkEvent

//---------------------------------------------------------------------------
// Handle<VkEvent>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Event_Deleter = Vulkan_Destroyer<VkEvent, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkEvent> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Event_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}
// Make a self-destroying VkEvent.
sdlxvulkan::Handle<VkEvent> sdlxvulkan::make_event
(
  Handle<VkDevice> const& a_device,
  VkEventCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateEvent, l_functions->vkDestroyEvent);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkFence

//---------------------------------------------------------------------------
// Handle<VkFence>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Fence_Deleter = Vulkan_Destroyer<VkFence, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkFence> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Fence_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkImage.
sdlxvulkan::Handle<VkFence> sdlxvulkan::make_fence
(
  Handle<VkDevice> const& a_device,
  VkFenceCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateFence, l_functions->vkDestroyFence);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkFramebuffer

//---------------------------------------------------------------------------
// Handle<VkFramebuffer>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Framebuffer_Deleter = Vulkan_Destroyer<VkFramebuffer, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkFramebuffer> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Framebuffer_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkImage.
sdlxvulkan::Handle<VkFramebuffer> sdlxvulkan::make_framebuffer
(
  Handle<VkDevice> const& a_device,
  VkFramebufferCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateFramebuffer, l_functions->vkDestroyFramebuffer);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkImage

//---------------------------------------------------------------------------
// Handle<VkImage>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Image_Deleter = Vulkan_Destroyer<VkImage, VkDevice, Handle<VkDevice>>;

    using Swapchain_Image_Deleter = Vulkan_Blank_Destroyer<VkImage, Handle<VkSwapchainKHR>>;
    /*
    Handle<VkDevice> const& get_image_device(Handle<VkImage> const& a_handle) noexcept
    {
      assert(a_handle);
      auto l_deleter = std::get_deleter<Image_Deleter>(a_handle.get_data());
      assert(l_deleter);
      return l_deleter->get<0>();
    }
    */
    decltype(auto) get_image_device_deleter(Handle<VkImage> const& a_image) noexcept
    {
      return std::get_deleter<Image_Deleter>(a_image.get_data());
    }

    decltype(auto) get_image_swapchain_deleter(Handle<VkImage> const& a_image) noexcept
    {
      return std::get_deleter<Swapchain_Image_Deleter>(a_image.get_data());
    }
  }
}

bool sdlxvulkan::is_image_device(Handle<VkImage> const& a_image) noexcept
{
  return get_image_device_deleter(a_image) != nullptr;
}

bool sdlxvulkan::is_image_swapchain_khr(Handle<VkImage> const& a_image) noexcept
{
  return get_image_swapchain_deleter(a_image) != nullptr;
}


sdlxvulkan::Handle<VkDevice> sdlxvulkan::get_image_device(Handle<VkImage> const& a_image) noexcept
{
  auto l_deleter = get_image_device_deleter(a_image);
  if (l_deleter)
  {
    return l_deleter->get<0>();
  }
  else
  {
    return Handle<VkDevice>{};
  }
}

sdlxvulkan::Handle<VkSwapchainKHR> sdlxvulkan::get_image_swapchain_khr(Handle<VkImage> const& a_image) noexcept
{

  auto l_deleter = get_image_swapchain_deleter(a_image);
  if (l_deleter)
  {
    return l_deleter->get<0>();
  }
  else
  {
    return Handle<VkSwapchainKHR>{};
  }
}


// Make a self-destroying VkImage.
sdlxvulkan::Handle<VkImage> sdlxvulkan::make_image
(
  Handle<VkDevice> const& a_device,
  VkImageCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateImage, l_functions->vkDestroyImage);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkImageView

//---------------------------------------------------------------------------
// Image_View
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Image_View_Deleter = Vulkan_Destroyer<VkImageView, VkDevice, Handle<VkImage>>;

    Handle<VkImage> const& get_image(Handle<VkImageView> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Image_View_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkImageView.
sdlxvulkan::Handle<VkImageView> sdlxvulkan::make_image_view
(
  Handle<VkImage> const& a_image,
  VkImageViewCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_image);
  auto l_device = get_image_device(a_image);
  if (!l_device)
  {
    auto l_swapchain = get_image_swapchain_khr(a_image);
    assert(l_swapchain);
    l_device = get_swapchain_device_khr(l_swapchain);
  }
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions != nullptr);
  return make_device_child(l_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateImageView, l_functions->vkDestroyImageView, a_image);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkPipeline

//---------------------------------------------------------------------------
// Pipeline
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Pipeline_Deleter = Vulkan_Destroyer<VkPipeline, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkPipeline> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Pipeline_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkPipelineCache.
sdlxvulkan::Handle<VkPipeline> sdlxvulkan::make_graphics_pipeline
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  VkGraphicsPipelineCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkCreateGraphicsPipelines != nullptr);
  assert(l_functions->vkDestroyPipeline != nullptr);

  std::array<VkPipeline,1> l_pipeline{VK_NULL_HANDLE};
  if (vkCreateGraphicsPipelines(a_device, a_pipeline_cache, 1, &a_create_info, a_allocation_callbacks, l_pipeline.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{"Vulkan: Failed to create a graphics VkPipeline."};
  }
  auto l_caught = make_unique_vk(l_pipeline[0], a_device.get(), a_allocation_callbacks, l_functions->vkDestroyPipeline, std::make_tuple(a_device));
  return Handle<VkPipeline>{ Vulkan_Sptr<VkPipeline>{std::move(l_caught)} };
}

// Make a batch of self-destroying VkPipelineCache.
std::vector<sdlxvulkan::Handle<VkPipeline>> sdlxvulkan::make_graphics_pipelines
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  std::vector<VkGraphicsPipelineCreateInfo> const& a_create_infos,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkCreateGraphicsPipelines != nullptr);
  assert(l_functions->vkDestroyPipeline != nullptr);

  auto const l_count = a_create_infos.size();
  std::vector<VkPipeline> l_raw_pipelines{ l_count, VK_NULL_HANDLE };
  std::vector<Vulkan_Uptr<VkPipeline, Pipeline_Deleter>> l_caught_pipelines{};
  l_caught_pipelines.reserve(l_count);
  std::vector<Handle<VkPipeline>> l_final_pipelines{ l_count };
  // Now we have allocated all the vectors we need BEFORE making the Vulkan handles
  if (vkCreateGraphicsPipelines(a_device, a_pipeline_cache, static_cast<uint32_t>(l_count), a_create_infos.data(), a_allocation_callbacks, l_raw_pipelines.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create a graphics VkPipelines." };
  }
  // Make sure all the pipelines are paired with deleter.
  // This should not throw.
  for(std::size_t l_index = 0; l_index != l_count; ++l_index)
  {
    auto l_caught = make_unique_vk(l_raw_pipelines[l_index], a_device.get(), a_allocation_callbacks, l_functions->vkDestroyPipeline, std::make_tuple(a_device));
    l_caught_pipelines.push_back(std::move(l_caught));
  }
  // Now put them in the handles.
  for (std::size_t l_index = 0; l_index != l_count; ++l_index)
  {
    Handle<VkPipeline> l_final{ Vulkan_Sptr<VkPipeline>{std::move(l_caught_pipelines[l_index])} };
    std::swap(l_final_pipelines[l_index], l_final);
  }
  return l_final_pipelines;
}


// Make a self-destroying VkPipelineCache.
sdlxvulkan::Handle<VkPipeline> sdlxvulkan::make_compute_pipeline
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  VkComputePipelineCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkCreateComputePipelines != nullptr);
  assert(l_functions->vkDestroyPipeline != nullptr);

  std::array<VkPipeline, 1> l_pipeline{ VK_NULL_HANDLE };
  if (vkCreateComputePipelines(a_device, a_pipeline_cache, 1, &a_create_info, a_allocation_callbacks, l_pipeline.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create a graphics VkPipeline." };
  }
  auto l_caught = make_unique_vk(l_pipeline[0], a_device.get(), a_allocation_callbacks, l_functions->vkDestroyPipeline, std::make_tuple(a_device));
  return Handle<VkPipeline>{ Vulkan_Sptr<VkPipeline>{std::move(l_caught)} };
}

// Make a batch of self-destroying VkPipelineCache.
std::vector<sdlxvulkan::Handle<VkPipeline>> sdlxvulkan::make_compute_pipelines
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  std::vector<VkComputePipelineCreateInfo> const& a_create_infos,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkCreateComputePipelines != nullptr);
  assert(l_functions->vkDestroyPipeline != nullptr);

  auto const l_count = a_create_infos.size();
  std::vector<VkPipeline> l_raw_pipelines{ l_count, VK_NULL_HANDLE };
  std::vector<Vulkan_Uptr<VkPipeline, Pipeline_Deleter>> l_caught_pipelines{};
  l_caught_pipelines.reserve(l_count);
  std::vector<Handle<VkPipeline>> l_final_pipelines{ l_count };
  // Now we have allocated all the vectors we need BEFORE making the Vulkan handles
  if (vkCreateComputePipelines(a_device, a_pipeline_cache, static_cast<uint32_t>(l_count), a_create_infos.data(), a_allocation_callbacks, l_raw_pipelines.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create a graphics VkPipelines." };
  }
  // Make sure all the pipelines are paired with deleter.
  // This should not throw.
  for (std::size_t l_index = 0; l_index != l_count; ++l_index)
  {
    auto l_caught = make_unique_vk(l_raw_pipelines[l_index], a_device.get(), a_allocation_callbacks, l_functions->vkDestroyPipeline, std::make_tuple(a_device));
    l_caught_pipelines.push_back(std::move(l_caught));
  }
  // Now put them in the handles.
  for (std::size_t l_index = 0; l_index != l_count; ++l_index)
  {
    Handle<VkPipeline> l_final{ Vulkan_Sptr<VkPipeline>{std::move(l_caught_pipelines[l_index])} };
    std::swap(l_final_pipelines[l_index], l_final);
  }
  return l_final_pipelines;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkPipelineCache

//---------------------------------------------------------------------------
// Handle<VkPipelineCache>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Pipeline_Cache_Deleter = Vulkan_Destroyer<VkPipelineCache, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkPipelineCache> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Pipeline_Cache_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkPipelineCache.
sdlxvulkan::Handle<VkPipelineCache> sdlxvulkan::make_pipeline_cache
(
  Handle<VkDevice> const& a_device,
  VkPipelineCacheCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreatePipelineCache, l_functions->vkDestroyPipelineCache, a_device);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkPipelineLayout

//---------------------------------------------------------------------------
// Handle<VkPipelineLayout>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Pipeline_Layout_Deleter = Vulkan_Destroyer<VkPipelineLayout, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkPipelineLayout> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Pipeline_Layout_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}
// Actually relies on N Descriptor_Set_Layouts...

// Make a self-destroying VkPipelineLayout.
sdlxvulkan::Handle<VkPipelineLayout> sdlxvulkan::make_pipeline_layout
(
  Handle<VkDevice> const& a_device,
  VkPipelineLayoutCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreatePipelineLayout, l_functions->vkDestroyPipelineLayout, a_device);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkQueryPool

//---------------------------------------------------------------------------
// Handle<VkQueryPool>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Query_Pool_Deleter = Vulkan_Destroyer<VkQueryPool, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkQueryPool> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Query_Pool_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkRenderPass.
sdlxvulkan::Handle<VkQueryPool> sdlxvulkan::make_query_pool
(
  Handle<VkDevice> const& a_device,
  VkQueryPoolCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateQueryPool, l_functions->vkDestroyQueryPool, a_device);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkQueue

//---------------------------------------------------------------------------
// Handle<VkQueue>
//---------------------------------------------------------------------------

// Make a self-destroying VkQueue.
sdlxvulkan::Handle<VkQueue> sdlxvulkan::make_queue
(
  Handle<VkDevice> const& a_device,
  uint32_t a_queue_family_index,
  uint32_t a_queue_index
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetDeviceQueue != nullptr);

  VkQueue l_queue{ VK_NULL_HANDLE };
  l_functions->vkGetDeviceQueue(a_device, a_queue_family_index, a_queue_index, &l_queue);
  if (l_queue == VK_NULL_HANDLE)
  {
    throw std::runtime_error{ "Vulkan: Failed to create a queue." };
  }

  return make_blank_device_child(l_queue, a_device);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkRenderPass

//---------------------------------------------------------------------------
// Handle<VkRenderPass>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Render_Pass_Deleter = Vulkan_Destroyer<VkRenderPass, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkRenderPass> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Render_Pass_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkRenderPass.
sdlxvulkan::Handle<VkRenderPass> sdlxvulkan::make_render_pass
(
  Handle<VkDevice> const& a_device,
  VkRenderPassCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateRenderPass, l_functions->vkDestroyRenderPass);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkSampler

//---------------------------------------------------------------------------
// Handle<VkSampler>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Sampler_Deleter = Vulkan_Destroyer<VkSampler, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkSampler> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Sampler_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkSampler.
sdlxvulkan::Handle<VkSampler> sdlxvulkan::make_sampler
(
  Handle<VkDevice> const& a_device,
  VkSamplerCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateSampler, l_functions->vkDestroySampler);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkSamplerYcbcrConversion

//---------------------------------------------------------------------------
// Handle<VkSamplerYcbcrConversion>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Sampler_Ycbcr_Conversion_Deleter = Vulkan_Destroyer<VkSamplerYcbcrConversion, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkSamplerYcbcrConversion> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Sampler_Ycbcr_Conversion_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkSamplerYcbcrConversion.
sdlxvulkan::Handle<VkSamplerYcbcrConversion> sdlxvulkan::make_sampler_ycbcr_conversion
(
  Handle<VkDevice> const& a_device,
  VkSamplerYcbcrConversionCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateSamplerYcbcrConversion, l_functions->vkDestroySamplerYcbcrConversion);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkSemaphore

//---------------------------------------------------------------------------
// Handle<VkSemaphore>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Semaphore_Deleter = Vulkan_Destroyer<VkSemaphore, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkSemaphore> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Semaphore_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkSemaphore.
sdlxvulkan::Handle<VkSemaphore> sdlxvulkan::make_semaphore
(
  Handle<VkDevice> const& a_device,
  VkSemaphoreCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateSemaphore, l_functions->vkDestroySemaphore);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkShaderModule

//---------------------------------------------------------------------------
// Handle<VkShaderModule>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Shader_Module_Deleter = Vulkan_Destroyer<VkShaderModule, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkShaderModule> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Shader_Module_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkShaderModule.
sdlxvulkan::Handle<VkShaderModule> sdlxvulkan::make_shader_module
(
  Handle<VkDevice> const& a_device,
  VkShaderModuleCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateShaderModule, l_functions->vkDestroyShaderModule);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkSwapchainKHR

//---------------------------------------------------------------------------
// Handle<VkSwapchainKHR>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Swapchain_KHR_Deleter = Vulkan_Destroyer<VkSwapchainKHR, VkDevice, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkSwapchainKHR> const& a_handle) noexcept
    {
      assert(a_handle);
      return std::get_deleter<Swapchain_KHR_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

sdlxvulkan::Handle<VkDevice> sdlxvulkan::get_swapchain_device_khr(Handle<VkSwapchainKHR> const& a_swapchain) noexcept
{
  if (a_swapchain)
  {
    return std::get_deleter<Swapchain_KHR_Deleter>(a_swapchain.get_data())->get<0>();
  }
  else
  {
    return Handle<VkDevice>{};
  }
}

// Make a self-destroying VkSwapchainKHR.
sdlxvulkan::Handle<VkSwapchainKHR> sdlxvulkan::make_swapchain_khr
(
  Handle<VkDevice> const& a_device,
  VkSwapchainCreateInfoKHR const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateSwapchainKHR, l_functions->vkDestroySwapchainKHR);
}

uint32_t sdlxvulkan::get_swapchain_image_count_khr
(
  Handle<VkSwapchainKHR> const& a_swapchain
)
{
  assert(a_swapchain);
  auto const& l_device = get_device(a_swapchain);
  assert(l_device != nullptr);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions->vkGetSwapchainImagesKHR != nullptr);

  uint32_t l_count{ 0 };
  if (l_functions->vkGetSwapchainImagesKHR(l_device, a_swapchain, &l_count, nullptr) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain image count." };
  }
  return l_count;
}

std::vector<sdlxvulkan::Handle<VkImage>> sdlxvulkan::get_swapchain_images_khr
(
  Handle<VkSwapchainKHR> const& a_swapchain
)
{
  assert(a_swapchain);
  auto const& l_device = get_device(a_swapchain);
  assert(l_device);
  auto l_functions = get_device_functions(l_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetSwapchainImagesKHR != nullptr);

  uint32_t l_count{ 0 };
  if (l_functions->vkGetSwapchainImagesKHR(l_device, a_swapchain, &l_count, nullptr) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain image count." };
  }
  assert(l_count != 0);
  std::vector<VkImage> l_raw_image_vector{};
  // REMEMBER: resize when dealing with a vector to catch Vulkan handles...
  l_raw_image_vector.resize(l_count);

  // Now make the images. These have no special cleanup.
  if (l_functions->vkGetSwapchainImagesKHR(l_device, a_swapchain, &l_count, l_raw_image_vector.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain images." };
  }
  std::vector<sdlxvulkan::Handle<VkImage>> l_image_vector{};
  l_image_vector.reserve(l_count);

  for (auto l_raw_image : l_raw_image_vector)
  {
    assert(l_raw_image != VK_NULL_HANDLE);
    auto l_image = make_blank_handle_vk(l_raw_image, a_swapchain);
    assert(l_image);
    assert(l_raw_image == l_image.get());
    l_image_vector.push_back(std::move(l_image));
    assert(l_image_vector.back());
    assert(l_raw_image == l_image_vector.back().get());
  }

  assert(l_image_vector.size() == l_count);
  return l_image_vector;
}

// Shared Swapchains???????

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkValidationCacheEXT

//---------------------------------------------------------------------------
// Handle<VkValidationCacheEXT>
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Validation_Cache_EXT_Deleter = Vulkan_Destroyer<VkEvent, VkValidationCacheEXT, Handle<VkDevice>>;

    Handle<VkDevice> const& get_device(Handle<VkValidationCacheEXT> const& a_handle) noexcept
    {
      return std::get_deleter<Validation_Cache_EXT_Deleter>(a_handle.get_data())->get<0>();
    }
  }
}

// Make a self-destroying VkValidationCacheEXT.
sdlxvulkan::Handle<VkValidationCacheEXT> sdlxvulkan::make_validation_cache_ext
(
  Handle<VkDevice> const& a_device,
  VkValidationCacheCreateInfoEXT const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateValidationCacheEXT, l_functions->vkDestroyValidationCacheEXT);
}
