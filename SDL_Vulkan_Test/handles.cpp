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
        return std::addressof(m_functions);
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

      Instance m_parent;
      VkAllocationCallbacks const* m_allocation_callbacks;
      Device_Functions m_functions;

    public:
      Device_Destroyer(Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks, Device_Functions&& a_functions) :
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
      Instance const& parent() const noexcept
      {
        return m_parent;
      }
      VkAllocationCallbacks const* allocation_callbacks() const noexcept
      {
        return m_allocation_callbacks;
      }
      Device_Functions const* functions() const noexcept
      {
        return std::addressof(m_functions);
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
    // Holds a parent Vulkan handle in a shared pointer and destroys any supplied
    // handles with the destroy function it was constructed with.

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    class Vulkan_Destroyer
    {
    private:
      using Destroyer_Func_Type = Vulkan_Destroyer_PFN<T_Vk_Handle, T_Vk_Parent>;// void(*)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*);
      using Store_Type = std::tuple<std::remove_reference_t<Args>...>;

      Handle<T_Vk_Parent> m_parent;
      VkAllocationCallbacks const* m_allocation_callbacks;
      Destroyer_Func_Type m_destroyer;
      Store_Type m_store;

    public:
      Vulkan_Destroyer
      (
        Handle<T_Vk_Parent> const& a_parent,
        VkAllocationCallbacks const* a_allocation_callbacks,
        Destroyer_Func_Type a_destroyer,
        Args&&...a_args
      ) :
        m_parent{ a_parent },
        m_allocation_callbacks{ a_allocation_callbacks },
        m_destroyer{ a_destroyer },
        m_store{ std::forward<Args>(a_args)... }
      {
        assert(m_parent != nullptr);
        assert(m_destroyer != nullptr);
      }
      void operator()(T_Vk_Handle a_vk_handle) const noexcept
      {
        m_destroyer(m_parent.get(), a_vk_handle, m_allocation_callbacks);
      }
      Handle<T_Vk_Parent> const& parent() const noexcept
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
      Store_Type const& store()  const noexcept
      {
        return m_store;
      }
    };

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...> make_vulkan_destroyer
    (
      Handle<T_Vk_Parent> const& a_parent,
      VkAllocationCallbacks const* a_allocation_callbacks,
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      return Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>(a_parent, a_allocation_callbacks, a_destroyer, std::forward<Args>(a_args)...);
    }

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    Vulkan_Uptr<T_Vk_Handle, Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>> make_unique_vk
    (
      T_Vk_Handle a_handle,
      Handle<T_Vk_Parent> const& a_parent,
      VkAllocationCallbacks const* a_allocation_callbacks,
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(T_Vk_Parent, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      using Destroyer_Type = Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>;
      using Uptr_Type = Vulkan_Uptr<T_Vk_Handle, Vulkan_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>>;

      return Uptr_Type{ a_handle, Destroyer_Type{ a_parent, a_allocation_callbacks, a_destroyer, std::forward<Args>(a_args)... } };
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
      Handle<T_Vk_Parent> const& a_parent,
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
      if (a_creator(a_parent.get(), std::addressof(a_create_info), a_allocation_callbacks, std::addressof(l_handle)) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Bad creation of a Vulkan handle for Vulkan_Sptr" };
      }

      auto l_capture = make_unique_vk(l_handle, a_parent, a_allocation_callbacks, a_destroyer, std::forward<Args>(a_args)...);
      return Handle<T_Vk_Handle>{Vulkan_Sptr<T_Vk_Handle>{std::move(l_capture)}};
    }


    // Simplify creation of VkInstance children.
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename...Args>
    Handle<T_Vk_Handle> make_instance_child
    (
      Instance const& a_instance,
      T_Vk_Create_Info const& a_create_info,
      VkAllocationCallbacks const* a_allocation_callbacks,
      //Vulkan_Creator_PFN<T_Vk_Handle, T_Vk_Create_Info, VkInstance> a_creator,
      //Vulkan_Destroyer_PFN<T_Vk_Handle, VkInstance> a_destroyer
      VKAPI_ATTR VkResult(VKAPI_CALL *a_creator)(VkInstance, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*),
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(VkInstance, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      return make_handle_vk<T_Vk_Handle, T_Vk_Create_Info, VkInstance>(a_instance, a_create_info, a_allocation_callbacks, a_creator, a_destroyer, std::forward<Args>(a_args)...);
    }


    // Simplify creation of VkDevice children.
    template <typename T_Vk_Handle, typename T_Vk_Create_Info, typename...Args>
    Handle<T_Vk_Handle> make_device_child
    (
      Device const& a_device,
      T_Vk_Create_Info const& a_create_info,
      VkAllocationCallbacks const* a_allocation_callbacks,
      //Vulkan_Creator_PFN<T_Vk_Handle, T_Vk_Create_Info, VkDevice> a_creator,
      //Vulkan_Destroyer_PFN<T_Vk_Handle, VkDevice> a_destroyer
      VKAPI_ATTR VkResult(VKAPI_CALL *a_creator)(VkDevice, T_Vk_Create_Info const*, VkAllocationCallbacks const*, T_Vk_Handle*),
      VKAPI_ATTR void(VKAPI_CALL *a_destroyer)(VkDevice, T_Vk_Handle, VkAllocationCallbacks const*),
      Args&&...a_args
    )
    {
      return make_handle_vk<T_Vk_Handle, T_Vk_Create_Info, VkDevice>(a_device, a_create_info, a_allocation_callbacks, a_creator, a_destroyer, std::forward<Args>(a_args)...);
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Vulkan_Blank_Destroyer<T_Vk_Parent, T_Vk_Handle>
    //---------------------------------------------------------------------------
    // Holds a parent Vulkan handle in a shared pointer but carries out no 
    // destruction.

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    class Vulkan_Blank_Destroyer
    {
    private:
      using Store_Type = std::tuple<std::remove_reference_t<Args>...>;

      Handle<T_Vk_Parent> m_parent;
      Store_Type m_store;

    public:
      Vulkan_Blank_Destroyer
      (
        Handle<T_Vk_Parent> const& a_parent,
        Args&&...a_args
      ) :
        m_parent{ a_parent },
        m_store{ std::forward<Args>(a_args)... }
      {
        assert(m_parent != nullptr);
      }
      void operator()(T_Vk_Handle) const noexcept
      {
      }
      Handle<T_Vk_Parent> const& parent() const noexcept
      {
        return m_parent;
      }
      Store_Type const& store()  const noexcept
      {
        return m_store;
      }
    };

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    decltype(auto) make_vulkan_blank_destroyer
    (
      Handle<T_Vk_Parent> const& a_parent,
      Args&&...a_args
    )
    {
      return Vulkan_Blank_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>(a_parent, std::forward<Args>(a_args)...);
    }

    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    decltype(auto) make_blank_unique_vk
    (
      T_Vk_Handle a_handle,
      Handle<T_Vk_Parent> const& a_parent,
      Args&&...a_args
    )
    {
      using Destroyer_Type = Vulkan_Blank_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>;
      using Uptr_Type = Vulkan_Uptr<T_Vk_Handle, Vulkan_Blank_Destroyer<T_Vk_Handle, T_Vk_Parent, Args...>>;

      return Uptr_Type{ a_handle, Destroyer_Type{ a_parent, std::forward<Args>(a_args)... } };
    }

    // There's a thing going on with the template type deductions here:
    // If the arguments are the types, it can deduce them, but if the types
    // are in a template, it can't because T_Vk_Handle doesn't appear outside
    // the template types so it can't be deduced.

    // Factory function for any Vulkan types. It could be hidden if it's only used
    // by named functions that call this, using it as an implementation aid.
    // Things are also simpler if we don't want to reveal the Destroyers...
    template <typename T_Vk_Handle, typename T_Vk_Parent, typename...Args>
    Handle<T_Vk_Handle> make_blank_handle_vk
    (
      Handle<T_Vk_Parent> const& a_parent,
      T_Vk_Handle a_handle,
      Args&&...a_args
    )
    {
      assert(a_parent != nullptr);
      assert(a_handle != VK_NULL_HANDLE);
      T_Vk_Handle l_handle{ VK_NULL_HANDLE };

      auto l_capture = make_blank_unique_vk(a_handle, a_parent, std::forward<Args>(a_args)...);
      return Handle<T_Vk_Handle>{Vulkan_Sptr<T_Vk_Handle>{std::move(l_capture)}};
    }


    // Simplify creation of VkInstance children.
    template <typename T_Vk_Handle, typename...Args>
    Handle<T_Vk_Handle> make_blank_instance_child
    (
      Instance const& a_instance,
      T_Vk_Handle a_handle,
      Args&&...a_args
    )
    {
      return make_blank_handle_vk<T_Vk_Handle, VkInstance>(a_instance, a_handle, std::forward<Args>(a_args)...);
    }


    // Simplify creation of VkDevice children.
    template <typename T_Vk_Handle, typename...Args>
    Handle<T_Vk_Handle> make_blank_device_child
    (
      Device const& a_device,
      T_Vk_Handle a_handle,
      Args&&...a_args
    )
    {
      return make_blank_handle_vk<T_Vk_Handle, VkDevice>(a_device, a_handle, std::forward<Args>(a_args)...);
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
sdlxvulkan::Instance sdlxvulkan::make_instance
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
  if (l_global_functions.vkCreateInstance(std::addressof(a_create_info), a_allocation_callbacks, std::addressof(l_instance)) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Bad creation of a VkInstance." };
  }
  Instance_Functions l_functions{ l_instance, l_global_functions };
  using Deleter_Type = Instance_Destroyer;
  Vulkan_Uptr<VkInstance, Deleter_Type> l_caught{ l_instance, Deleter_Type{ a_system, a_window, a_allocation_callbacks, std::move(l_functions) } };
  return Instance{ Vulkan_Sptr<VkInstance>{std::move(l_caught)} };
}

sdlxvulkan::Instance sdlxvulkan::make_instance_limited
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
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  // If validation layers supplied, and the ones requested are not available, stop.
  if (!a_layer_names.empty() && !a_system.supports_layers(a_layer_names))
  {
    throw std::runtime_error{ "sdlxvulkan::Instance: Validation layers requested, but not available." };
  }

  std::cout << "Requested Instance Layers:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_layer : a_layer_names)
  {
    std::cout << l_layer << std::endl;

  }
  std::cout << std::endl;


  std::cout << "Requested Instance Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : a_extension_names)
  {
    std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;

  // get all the extensions required
  auto l_required_extensions = a_window.required_instance_extensions();

  std::cout << "Required Instance Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : l_required_extensions)
  {
    std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;


  // add the specified ones to these if they are not already present
  for (auto const& l_ext : a_extension_names)
  {
    if (std::find(l_required_extensions.cbegin(), l_required_extensions.cend(), l_ext) == l_required_extensions.cend())
    {
      l_required_extensions.push_back(l_ext);
    }
  }
  /*
  std::cout << "Final Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : l_required_extensions)
  {
  std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;
  */

  // Initialise an application info structure
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkApplicationInfo l_app_info{};
  l_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  l_app_info.pNext = nullptr;
  l_app_info.pApplicationName = a_application_name.c_str();
  l_app_info.applicationVersion = a_application_version;
  l_app_info.pEngineName = a_engine_name.c_str();
  l_app_info.engineVersion = a_engine_version;
  l_app_info.apiVersion = a_vulkan_version;

  // need to change the type of these
  std::vector<char const*> l_final_layers{};
  l_final_layers.reserve(a_layer_names.size());
  for (auto const& l_layer : a_layer_names)
  {
    l_final_layers.push_back(l_layer.c_str());
  }


  // and these
  std::vector<char const*> l_final_extensions{};
  l_final_extensions.reserve(l_required_extensions.size());
  for (auto const& l_ext : l_required_extensions)
  {
    l_final_extensions.push_back(l_ext.c_str());
  }

  // Initialise a create info struct.
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkInstanceCreateInfo l_create_info{};
  l_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  l_create_info.pNext = nullptr;
  l_create_info.flags = 0;
  l_create_info.pApplicationInfo = &l_app_info;
  // if there are no layer names there are no layers.
  if (a_layer_names.empty())
  {
    l_create_info.enabledLayerCount = 0;
    l_create_info.ppEnabledLayerNames = nullptr;

  }
  // else there are.
  else
  {
    l_create_info.enabledLayerCount = static_cast<uint32_t>(l_final_layers.size());
    l_create_info.ppEnabledLayerNames = l_final_layers.data();
  }
  l_create_info.enabledExtensionCount = static_cast<uint32_t>(l_final_extensions.size());
  l_create_info.ppEnabledExtensionNames = l_final_extensions.data();

  return make_instance(a_system, a_window, l_create_info, a_allocation_callbacks);
}

// Get the functions for a VkInstance. If the shared_ptr is nullptr this 
// returns nullptr, otherwise it returns the corresponding functions.
sdlxvulkan::Instance_Functions const* sdlxvulkan::get_instance_functions(Instance const& a_instance) noexcept
{
  if (a_instance != nullptr)
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
// Debug_Report_Callback_Ext
//---------------------------------------------------------------------------

sdlxvulkan::Debug_Report_Callback_EXT sdlxvulkan::make_debug_report_callback_ext
(
  Instance const& a_instance,
  VkDebugReportCallbackCreateInfoEXT const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_instance != nullptr);
  auto l_functions = get_instance_functions(a_instance);
  assert(l_functions != nullptr);
  return make_instance_child(a_instance, a_create_info, a_allocation_callbacks, l_functions->vkCreateDebugReportCallbackEXT, l_functions->vkDestroyDebugReportCallbackEXT);
}

sdlxvulkan::Debug_Report_Callback_EXT sdlxvulkan::make_debug_report_callback_ext_limited
(
  Instance const& a_instance,
  VkDebugReportFlagsEXT a_flags,
  PFN_vkDebugReportCallbackEXT a_callback,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkDebugReportCallbackCreateInfoEXT l_callback_info{};
  l_callback_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  l_callback_info.pNext = nullptr;
  l_callback_info.flags = a_flags;
  l_callback_info.pfnCallback = a_callback;
  l_callback_info.pUserData = nullptr;

  return make_debug_report_callback_ext(a_instance, l_callback_info, a_allocation_callbacks);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDebugUtilsMessengerEXT

//---------------------------------------------------------------------------
// Debug_Utils_Messenger_EXT
//---------------------------------------------------------------------------

// Make a self-destroying VkDebugUtilsMessengerEXT.
// Throws std::runtime error if the Vulkan create function fails. 
// Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
sdlxvulkan::Debug_Utils_Messenger_EXT sdlxvulkan::make_debug_utils_messenger_ext
(
  Instance const& a_instance,
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

// How many physcial devices does Instance have? 
// Returns zero if Instance is null.
uint32_t sdlxvulkan::get_physical_device_count(Instance const& a_instance) noexcept
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
std::vector<sdlxvulkan::Physical_Device> sdlxvulkan::get_physical_devices(Instance const& a_instance)
{
  std::vector<Physical_Device> l_result{};
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
      auto l_pd = make_blank_instance_child(a_instance, l_handle);
      l_result.push_back(std::move(l_pd));
    }
  }
  return l_result;
}


// Physical_Device imp helpers
namespace sdlxvulkan
{
  namespace
  {
    using Physical_Device_Deleter = Vulkan_Blank_Destroyer<VkPhysicalDevice, VkInstance>;

    Instance_Functions const* get_instance_functions(Physical_Device const& a_physical_device) noexcept
    {
      return get_instance_functions(std::get_deleter<Physical_Device_Deleter>(a_physical_device.get_data())->parent());
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

    uint32_t imp_count_physical_device_queue_familiy_properties(Physical_Device const& a_physical_device, Instance_Functions const* a_functions)
    {
      uint32_t l_count{ 0 };
      a_functions->vkGetPhysicalDeviceQueueFamilyProperties(a_physical_device, &l_count, nullptr);
      return l_count;
    }

  }
}

// Throws std::runtime_error if physical device is null.
VkPhysicalDeviceProperties sdlxvulkan::get_physical_device_properties(Physical_Device const& a_physical_device)
{
  if (!a_physical_device)
  {
    std::runtime_error{"Null Physical_Device"};
  }
  auto l_functions = get_instance_functions(a_physical_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceProperties != nullptr);

  VkPhysicalDeviceProperties l_result{};
  l_functions->vkGetPhysicalDeviceProperties(a_physical_device, &l_result);
  return l_result;
}

// Throws std::runtime_error if physical device is null.
VkPhysicalDeviceMemoryProperties sdlxvulkan::get_physical_device_memory_properties(Physical_Device const& a_physical_device)
{
  if (!a_physical_device)
  {
    std::runtime_error{ "Null Physical_Device" };
  }
  auto l_functions = get_instance_functions(a_physical_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceMemoryProperties != nullptr);

  VkPhysicalDeviceMemoryProperties l_result{};
  l_functions->vkGetPhysicalDeviceMemoryProperties(a_physical_device, &l_result);
  return l_result;
}


//uint32_t get_physical_device_queue_familiy_properties_count(Physical_Device const& a_physcial_device) noexcept;

// Throws std::runtime_error if physical device is null.
// Throws std::bad_alloc if the vector fails to be allocated.
std::vector<VkQueueFamilyProperties> sdlxvulkan::get_physical_device_queue_familiy_properties(Physical_Device const& a_physical_device)
{
  std::vector<VkQueueFamilyProperties> l_result{};
  if (a_physical_device)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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
std::vector<VkExtensionProperties> sdlxvulkan::get_physical_device_extension_properties(Physical_Device const& a_physical_device)
{
  std::vector<VkExtensionProperties> l_result{};
  if (a_physical_device)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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
bool sdlxvulkan::can_graphics(Physical_Device const& a_physical_device) noexcept
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
uint32_t sdlxvulkan::first_graphics_qfi(Physical_Device const& a_physical_device) noexcept
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

// SDL surface is a child of instance and window, and we cannot supply 
// allocation callbacks.
sdlxvulkan::Surface_KHR sdlxvulkan::make_surface_khr
(
  Instance const& a_instance,
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
  auto l_caught = make_unique_vk( l_surface, a_instance, nullptr, l_functions->vkDestroySurfaceKHR, a_window );
  return Surface_KHR{ Vulkan_Sptr<VkSurfaceKHR>{std::move(l_caught)} };
}

// Surface imp helpers
namespace sdlxvulkan
{
  namespace
  {
    bool is_present_capable(Physical_Device const& a_physical_device, uint32_t a_qfi, Surface_KHR const& a_surface, Instance_Functions const* a_functions)
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

// Can this physical device present to this surface?
// Returns false it either are null.
bool sdlxvulkan::can_present(Physical_Device const& a_physical_device, Surface_KHR const& a_surface) noexcept
{
  if (a_physical_device && a_surface)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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
uint32_t sdlxvulkan::first_present_qfi(Physical_Device const& a_physical_device, Surface_KHR const& a_surface)
{
  if (a_physical_device && a_surface)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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

VkSurfaceCapabilitiesKHR sdlxvulkan::get_surface_cababilites(Physical_Device const& a_physical_device, Surface_KHR const& a_surface)
{
  if (!a_physical_device || !a_surface)
  {
    std::runtime_error{ "Null argument supplied" };
  }
  auto l_functions = get_instance_functions(a_physical_device);
  assert(l_functions != nullptr);
  assert(l_functions->vkGetPhysicalDeviceSurfaceCapabilitiesKHR != nullptr);

  VkSurfaceCapabilitiesKHR l_result{};
  if (l_functions->vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_physical_device, a_surface, &l_result) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get surface capabilites." };
  }
  return l_result;
}

std::vector<VkSurfaceFormatKHR> sdlxvulkan::get_surface_formats(Physical_Device const& a_physical_device, Surface_KHR const& a_surface)
{
  std::vector<VkSurfaceFormatKHR> l_result{};
  if (a_physical_device && a_surface)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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

std::vector<VkPresentModeKHR> sdlxvulkan::get_present_modes(Physical_Device const& a_physical_device, Surface_KHR const& a_surface)
{
  std::vector<VkPresentModeKHR> l_result{};
  if (a_physical_device && a_surface)
  {
    auto l_functions = get_instance_functions(a_physical_device);
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
// Device
//---------------------------------------------------------------------------
// Make a self-destroying VkDevice.
// Throws std::runtime error if the Vulkan create function fails. 
// Throws std::bad_alloc if the Handle std::shared_ptr fails to be allocated.
sdlxvulkan::Device sdlxvulkan::make_device
(
  Physical_Device const& a_physical_device,
  VkDeviceCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_physical_device != nullptr);
  auto const& l_instance = std::get_deleter<Physical_Device_Deleter>(a_physical_device.get_data())->parent();
  assert(l_instance);
  auto l_instance_funcs = get_instance_functions(l_instance);
  assert(l_instance_funcs != nullptr);
  assert(l_instance_funcs->vkCreateDevice != nullptr);
  assert(l_instance_funcs->vkGetDeviceProcAddr != nullptr);
  VkDevice l_device{ VK_NULL_HANDLE };
  if (l_instance_funcs->vkCreateDevice(a_physical_device, std::addressof(a_create_info), a_allocation_callbacks, std::addressof(l_device)) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Bad creation of VkDevice." };
  }
  Device_Functions l_functions{ l_device, *l_instance_funcs };

  using Deleter_Type = Device_Destroyer;
  Vulkan_Uptr<VkDevice, Deleter_Type> l_caught{ l_device, Deleter_Type{ l_instance, a_allocation_callbacks, std::move(l_functions) } };
  return Device{ Vulkan_Sptr<VkDevice>{std::move(l_caught)} };
}

sdlxvulkan::Device sdlxvulkan::make_device_limited
(
  Physical_Device const& a_physical_device,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  std::vector<std::string> const& a_extensions,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  float l_queue_priorities[1] = { 0.0 };

  VkDeviceQueueCreateInfo l_queue_infos[2]{};

  // first is graphics
  l_queue_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[0].pNext = nullptr;
  l_queue_infos[0].flags = 0;
  l_queue_infos[0].queueFamilyIndex = a_graphics_qfi;
  l_queue_infos[0].queueCount = 1;
  l_queue_infos[0].pQueuePriorities = l_queue_priorities;

  // second is presenting
  l_queue_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[1].pNext = nullptr;
  l_queue_infos[1].flags = 0;
  l_queue_infos[1].queueFamilyIndex = a_present_qfi;
  l_queue_infos[1].queueCount = 1;
  l_queue_infos[1].pQueuePriorities = l_queue_priorities;

  // Logical Device
  //-------------

  // Configure our queue info
  VkDeviceQueueCreateInfo l_queue_info{};
  l_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_info.pNext = nullptr;
  l_queue_info.flags = 0;
  l_queue_info.queueFamilyIndex = a_graphics_qfi;
  l_queue_info.queueCount = 1;
  l_queue_info.pQueuePriorities = l_queue_priorities;


  std::vector<char const*> l_device_extensions{};
  uint32_t l_device_extension_count = static_cast<uint32_t>(a_extensions.size());
  std::vector<char const*> l_extensions{};
  l_device_extensions.reserve(a_extensions.size());
  for (auto const& l_ext : a_extensions)
  {
    l_device_extensions.push_back(l_ext.c_str());
  }

  // Make some device info
  VkDeviceCreateInfo l_device_info = {};
  l_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  l_device_info.pNext = nullptr;
  l_device_info.flags = 0;

  if (a_graphics_qfi == a_present_qfi)
  {
    l_device_info.queueCreateInfoCount = 1;
  }
  else
  {
    l_device_info.queueCreateInfoCount = 2;
  }
  l_device_info.pQueueCreateInfos = l_queue_infos;
  l_device_info.enabledLayerCount = 0;          // Deprecated, IGNORE
  l_device_info.ppEnabledLayerNames = nullptr;  // Deprecated, IGNORE
  l_device_info.enabledExtensionCount = l_device_extension_count;
  l_device_info.ppEnabledExtensionNames = l_device_extensions.data();
  l_device_info.pEnabledFeatures = nullptr;

  return make_device(a_physical_device, l_device_info, a_allocation_callbacks);
}


// Get the functions for a VkDevice. If the shared_ptr is nullptr this 
// returns nullptr, otherwise it returns the corresponding functions.
sdlxvulkan::Device_Functions const* sdlxvulkan::get_device_functions(Device const& a_device) noexcept
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
// Buffer
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Buffer_Deleter = Vulkan_Destroyer<VkBuffer, VkDevice>;

    Device const& get_device(Buffer const& a_command_pool) noexcept
    {
      return std::get_deleter<Buffer_Deleter>(a_command_pool.get_data())->parent();
    }
  }
}


// Make a self-destroying VkBuffer.
sdlxvulkan::Buffer sdlxvulkan::make_buffer
(
  Device const& a_device,
  VkBufferCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateBuffer, l_functions->vkDestroyBuffer);
}

// Initialise with a VkSharingMode value of VK_SHARING_MODE_EXCLUSIVE.
sdlxvulkan::Buffer sdlxvulkan::make_buffer_exclusive_limited
(
  Device const& a_device,
  VkDeviceSize a_size,
  VkBufferUsageFlags a_usage,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkBufferCreateInfo l_buffer_info{};
  l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  l_buffer_info.pNext = nullptr;
  l_buffer_info.flags = 0;
  l_buffer_info.size = a_size;
  l_buffer_info.usage = a_usage;
  l_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  l_buffer_info.queueFamilyIndexCount = 0;
  l_buffer_info.pQueueFamilyIndices = nullptr;

  return make_buffer(a_device, l_buffer_info, a_allocation_callbacks);
}

// Initialise with a VkSharingMode value of VK_SHARING_MODE_CONCURRENT. 
// a_queue_family_indicies must have at least 2 unique values, which are
// each less than the queue family property count of the physical device
// this is used with.
sdlxvulkan::Buffer sdlxvulkan::make_buffer_concurrent_limited
(
  Device const& a_device,
  VkDeviceSize a_size,
  VkBufferUsageFlags a_usage,
  std::vector<uint32_t> a_queue_family_indicies,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_queue_family_indicies.size() > 1);

  VkBufferCreateInfo l_buffer_info{};
  l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  l_buffer_info.pNext = nullptr;
  l_buffer_info.flags = 0;
  l_buffer_info.size = a_size;
  l_buffer_info.usage = a_usage;
  l_buffer_info.sharingMode = VK_SHARING_MODE_CONCURRENT;
  l_buffer_info.queueFamilyIndexCount = static_cast<uint32_t>(a_queue_family_indicies.size());
  l_buffer_info.pQueueFamilyIndices = a_queue_family_indicies.data();

  return make_buffer(a_device, l_buffer_info, a_allocation_callbacks);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkBufferView

//---------------------------------------------------------------------------
// Buffer_View
//---------------------------------------------------------------------------


// Make a self-destroying VkBuffer.
sdlxvulkan::Buffer_View sdlxvulkan::make_buffer_view
(
  Buffer const& a_buffer,
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
// Command_Pool
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Command_Pool_Deleter = Vulkan_Destroyer<VkCommandPool, VkDevice>;

    Device const& get_device(Command_Pool const& a_command_pool) noexcept
    {
      return std::get_deleter<Command_Pool_Deleter>(a_command_pool.get_data())->parent();
    }
  }
}

// Make a self-destroying VkCommandPool.
sdlxvulkan::Command_Pool sdlxvulkan::make_command_pool
(
  Device const& a_device,
  VkCommandPoolCreateInfo const& a_create_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_create_info, a_allocation_callbacks, l_functions->vkCreateCommandPool, l_functions->vkDestroyCommandPool);
}

sdlxvulkan::Command_Pool sdlxvulkan::make_command_pool_limited
(
  Device const& a_device,
  uint32_t a_queue_family_index,
  VkCommandPoolCreateFlags a_flags,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  // Initialise some creation info
  VkCommandPoolCreateInfo l_command_pool_info{};
  l_command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  l_command_pool_info.pNext = nullptr;
  l_command_pool_info.flags = a_flags;
  l_command_pool_info.queueFamilyIndex = a_queue_family_index;

  return make_command_pool(a_device, l_command_pool_info, a_allocation_callbacks);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkCommandBuffer

//---------------------------------------------------------------------------
// Command_Buffer
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
      Command_Pool m_command_pool;

      // Special 6
      //============================================================
      explicit Single_Command_Buffer_Destroyer(Command_Pool const& a_command_pool) :
        m_command_pool{ a_command_pool }
      {
        assert(m_command_pool);
      }

      // Interface
      //============================================================
      void operator()(VkCommandBuffer a_command_buffer) const noexcept
      {
        auto const& l_device = std::get_deleter<Vulkan_Destroyer<VkCommandPool, VkDevice>>(m_command_pool.get_data())->parent();
        auto l_functions = get_device_functions(l_device);
        assert(l_functions);
        assert(l_functions->vkFreeCommandBuffers != nullptr);
        l_functions->vkFreeCommandBuffers(l_device, m_command_pool, 1, std::addressof(a_command_buffer));
      }
    };

    template <typename T_Vk_Handle, typename T_Vk_Parent>//, typename...Args>
    class Vulkan_Array_Destroyer
    {
    public:
      using Destroyer_Func_Type = void(VKAPI_PTR *)(VkDevice, T_Vk_Parent, uint32_t, T_Vk_Handle const*);
      //using Destroyer_Func_Type = PFN_vkFreeCommandBuffers;
      //using Store_Type = std::tuple<std::remove_reference_t<Args>...>;

      Handle<T_Vk_Parent> m_parent;
      uint32_t m_size;
      Destroyer_Func_Type m_destroyer;
      //Store_Type m_store;

    public:
      Vulkan_Array_Destroyer
      (
        Handle<T_Vk_Parent> const& a_parent,
        uint32_t a_size,
        Destroyer_Func_Type a_destroyer//,
        //Args&&...a_args
      ) :
        m_parent{ a_parent },
        m_size{ a_size },
        m_destroyer{ a_destroyer }//,
        //m_store{ std::forward<Args>(a_args)... }
      {
        assert(m_parent != nullptr);
        assert(m_destroyer != nullptr);
      }
      void operator()(T_Vk_Handle* a_vk_handles) const noexcept
      {
        Device const& l_device = get_device(m_parent);
        m_destroyer(l_device.get(), m_parent.get(), m_size, a_vk_handles);
        delete[] a_vk_handles;
      }
      Handle<T_Vk_Parent> const& parent() const noexcept
      {
        return m_parent;
      }
      uint32_t size() const noexcept
      {
        return m_size;
      }
      Destroyer_Func_Type destroyer() const noexcept
      {
        return m_destroyer;
      }
      //Store_Type const& store()  const noexcept
      //{
      //  return m_store;
      //}
    };

    std::vector<VkCommandBuffer> imp_make_except_command_buffers
    (
      Command_Pool const& a_command_pool,
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

      if (l_functions->vkAllocateCommandBuffers(l_device, std::addressof(a_allocate_info), l_result.data()) != VK_SUCCESS)
      {
        throw std::runtime_error{ "Vulkan: Failed to create command buffers." };
      }

      return l_result;
    }

    VkCommandBuffer imp_make_except_command_buffer
    (
      Command_Pool const& a_command_pool,
      VkCommandBufferAllocateInfo const& a_allocate_info
    )
    {
      VkCommandBufferAllocateInfo l_allocate_info  = a_allocate_info;
      l_allocate_info.commandBufferCount = 1;
      return imp_make_except_command_buffers(a_command_pool, l_allocate_info).front();
    }

  }
}
// Make a single self-destroying VkCommandBuffer.
// Take note that one buffer is created regardless of 'commandBufferCount'
// in the given allocate info.
sdlxvulkan::Command_Buffer sdlxvulkan::make_command_buffer
(
  Command_Pool const& a_command_pool,
  VkCommandBufferAllocateInfo const& a_allocate_info
)
{
  assert(a_command_pool);
  assert(a_allocate_info.commandPool == a_command_pool.get());
  auto const& l_device = std::get_deleter<Vulkan_Destroyer<VkCommandPool, VkDevice>>(a_command_pool.get_data())->parent();
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateCommandBuffers != nullptr);
  assert(l_functions->vkFreeCommandBuffers != nullptr);

  VkCommandBuffer l_handle = imp_make_except_command_buffer(a_command_pool, a_allocate_info);

  using Deleter_Type = Single_Command_Buffer_Destroyer;
  Vulkan_Uptr<VkCommandBuffer, Deleter_Type> l_caught{ l_handle, Single_Command_Buffer_Destroyer{ a_command_pool } };
  return Command_Buffer{ Vulkan_Sptr<VkCommandBuffer>{std::move(l_caught)} };
}

// Make a batch of self-destroying VkCommandBuffer.
// Destruction is independent for each so there's no batch freeing.
std::vector<sdlxvulkan::Command_Buffer> sdlxvulkan::make_command_buffers
(
  Command_Pool const& a_command_pool,
  VkCommandBufferAllocateInfo const& a_allocate_info
)
{
  assert(a_command_pool);
  assert(a_allocate_info.commandPool == a_command_pool.get());
  auto const& l_device = std::get_deleter<Vulkan_Destroyer<VkCommandPool, VkDevice>>(a_command_pool.get_data())->parent();
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateCommandBuffers != nullptr);
  assert(l_functions->vkFreeCommandBuffers != nullptr);

  auto l_raw_command_buffers = imp_make_except_command_buffers(a_command_pool, a_allocate_info); // if this breaks no resources leak

  std::vector<Command_Buffer> l_result{};
  try
  {
    l_result.reserve(a_allocate_info.commandBufferCount); // allocation could fail here......  
    
    for (auto l_raw_command_buffer : l_raw_command_buffers)
    {
      assert(l_raw_command_buffer != VK_NULL_HANDLE);
      using Deleter_Type = Single_Command_Buffer_Destroyer;
      Vulkan_Uptr<VkCommandBuffer, Deleter_Type> l_caught{ l_raw_command_buffer, Single_Command_Buffer_Destroyer{ a_command_pool } };
      Command_Buffer l_buffer{ Vulkan_Sptr<VkCommandBuffer>{std::move(l_caught)} };
      l_result.push_back(std::move(l_buffer));
    }
  }
  catch (std::bad_alloc& a_exception)
  {
    // if a bad alloc occured it was in the vector allocation or construction of a Command_Buffer.
    // We have to clean up all raw command buffers not yet inside l_result.
    // Those inside l_result will be cleaned by the destructors.
    auto l_count = static_cast<int32_t>(l_raw_command_buffers.size() - l_result.size());

    VkCommandBuffer* l_raw_ptr = l_raw_command_buffers.data() + l_count;
    l_functions->vkFreeCommandBuffers(l_device, a_command_pool, l_count, l_raw_ptr);

    throw a_exception;
  }
  assert(l_result.size() == a_allocate_info.commandBufferCount);
  return l_result;
}

// Make a batch of self-destroying VkCommandBuffer.
// Destruction is of the entire array.
sdlxvulkan::Command_Buffer_Array sdlxvulkan::make_command_buffer_array
(
  Command_Pool const& a_command_pool,
  VkCommandBufferAllocateInfo const& a_allocate_info
)
{
  assert(a_command_pool);
  assert(a_allocate_info.commandPool == a_command_pool.get());
  auto const& l_device = std::get_deleter<Vulkan_Destroyer<VkCommandPool, VkDevice>>(a_command_pool.get_data())->parent();
  auto l_functions = get_device_functions(l_device);
  assert(l_functions);
  assert(l_functions->vkAllocateCommandBuffers != nullptr);
  assert(l_functions->vkFreeCommandBuffers != nullptr);

  auto l_raw_command_buffers = imp_make_except_command_buffers(a_command_pool, a_allocate_info); // if this breaks no resources leak
  
  VkCommandBuffer* l_raw{ nullptr };
  uint32_t l_size = static_cast<uint32_t>(l_raw_command_buffers.size());
  uint32_t l_reached = 0;
  try
  {
    // make a new, raw pointer array
    l_raw = new VkCommandBuffer[l_size]{VK_NULL_HANDLE}; // if this breaks then resources leak
  }
  catch (std::bad_alloc& a_exception)
  {
    // clean up all the vector, we couldn't make a pointer to capture the data.
    l_functions->vkFreeCommandBuffers(l_device, a_command_pool, l_size, l_raw_command_buffers.data());

    // Tell the world it failed.
    throw a_exception;
  }
  // copy the data from the vector to the raw pointer
  for (uint32_t l_index = 0; l_index != l_size; ++l_index)
  {
    assert(l_raw_command_buffers[l_index] != VK_NULL_HANDLE);
    l_raw[l_index] = l_raw_command_buffers[l_index];
  }
  
  using Deleter_Type = Vulkan_Array_Destroyer<VkCommandBuffer, VkCommandPool>;
  static_assert(std::is_same_v<typename Deleter_Type::Destroyer_Func_Type, PFN_vkFreeCommandBuffers>, "Bad function pointer type");
  Deleter_Type l_deleter{ a_command_pool, l_size, l_functions->vkFreeCommandBuffers };
  std::unique_ptr<VkCommandBuffer[], Deleter_Type> l_caught{ l_raw, std::move(l_deleter) };
  assert(l_caught[0] == l_raw_command_buffers[0]);
  // If this throws it was the shared_ptr, and the resources should clean up fine.
  return Command_Buffer_Array{ l_size, std::shared_ptr<VkCommandBuffer[]>{ std::move(l_caught) } };
}

// Make a batch of self-destroying VkCommandBuffer.
// Destruction is of the entire array.
sdlxvulkan::Command_Buffer_Array sdlxvulkan::make_command_buffer_array_limited
(
  Command_Pool const& a_command_pool,
  VkCommandBufferLevel a_level,
  uint32_t a_count
)
{
  VkCommandBufferAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.commandPool = a_command_pool.get();
  l_alloc_info.level = a_level;
  l_alloc_info.commandBufferCount = a_count;

  return make_command_buffer_array(a_command_pool, l_alloc_info);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkDeviceMemory

//---------------------------------------------------------------------------
// Device_Memory
//---------------------------------------------------------------------------

namespace sdlxvulkan
{
  namespace
  {
    using Device_Memory_Deleter = Vulkan_Destroyer<VkDeviceMemory, VkDevice>;

    Device const& get_device(Device_Memory const& a_handle) noexcept
    {
      return std::get_deleter<Device_Memory_Deleter>(a_handle.get_data())->parent();
    }
  }
}

// Make a self-destroying VkDeviceMemory.
sdlxvulkan::Device_Memory sdlxvulkan::make_device_memory
(
  Device const& a_device,
  VkMemoryAllocateInfo const& a_allocate_info,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_device != nullptr);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions != nullptr);
  return make_device_child(a_device, a_allocate_info, a_allocation_callbacks, l_functions->vkAllocateMemory, l_functions->vkFreeMemory);
}

sdlxvulkan::Device_Memory sdlxvulkan::make_device_memory_limited
(
  Device const& a_device,
  VkDeviceSize  a_size,
  uint32_t a_memory_type_index,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkMemoryAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.allocationSize = a_size;
  l_alloc_info.memoryTypeIndex = a_memory_type_index;

  return make_device_memory(a_device, l_alloc_info, a_allocation_callbacks);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// VkQueue

//---------------------------------------------------------------------------
// Queue
//---------------------------------------------------------------------------

// Make a self-destroying VkQueue.
sdlxvulkan::Queue sdlxvulkan::make_queue
(
  Device const& a_device,
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

  return make_blank_device_child(a_device, l_queue);
}