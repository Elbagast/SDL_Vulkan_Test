#include "instance.hpp"

#include "system.hpp"
#include "global_functions.hpp"
#include "window.hpp"
#include "instance_functions.hpp"
#include "physical_device.hpp"

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    // Hiding this entirely.
    static Instance_Functions s_instance_functions{};

    //---------------------------------------------------------------------------
    // Instance_Destroyer
    //---------------------------------------------------------------------------
    // Hold the state that must be destroyed after this and supply a means of 
    // destroying this. 

    class Instance_Destroyer
    {
    public:
      // Member Data
      //============================================================
      System m_system;
      Window m_window;
      VkAllocationCallbacks const* m_allocation_callbacks;

      // Special 6
      //============================================================
      Instance_Destroyer
      (
        System const& a_system,
        Window const& a_window,
        VkAllocationCallbacks const* a_allocation_callbacks
      ) noexcept :
        m_system{ a_system },
        m_window{ a_window },
        m_allocation_callbacks{ a_allocation_callbacks }
      {
        std::cout << "sdlxvulkan::Instance_Destroyer::Instance_Destroyer()" << std::endl;
      }

      // Interface
      //============================================================
      void operator()(VkInstance a_instance) const noexcept
      {
        // Could use system to get the destroy proc and execute it.
        // This means if Instance hides the Vulkan functions this one
        // can still be accessed without needing friend status.
        s_instance_functions.vkDestroyInstance(a_instance, m_allocation_callbacks);
        std::cout << "sdlxvulkan::Instance_Destroyer::operator()" << std::endl;
      }
    };


    decltype(auto) make_except_instance
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

      VkInstance l_instance{ VK_NULL_HANDLE };

      if (a_system.vk_functions().vkCreateInstance(&l_create_info, a_allocation_callbacks, &l_instance) != VK_SUCCESS)
      {
        throw std::runtime_error{ "sdlxvulkan::Instance: Failed to create VkInstance." };
      }

      // got to initialise these before the destroyer might use it
      s_instance_functions = Instance_Functions{ l_instance, a_system.vk_functions() };

      return make_except_vulkan_sptr<VkInstance, Instance_Destroyer>(l_instance, a_system, a_window, a_allocation_callbacks);
    }
    

  } // namespace  
} // namespace sdlxvulkan


// Special 6
//============================================================
sdlxvulkan::Instance::Instance
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
) :
  m_data{ make_except_instance(a_system, a_window, a_extension_names, a_layer_names, a_application_name, a_application_version, a_engine_name, a_engine_version, a_vulkan_version, a_allocation_callbacks) }
{
  //init_instance_functions(s_instance_functions, get(), a_system.vk_functions());
  //std::cout << "sdlxvulkan::Instance::Instance()" << std::endl;
}

sdlxvulkan::Instance::~Instance()
{
  //std::cout << "sdlxvulkan::Instance::~Instance()" << std::endl;
}

// Interface
//============================================================
sdlxvulkan::Instance_Functions const& sdlxvulkan::Instance::vk_functions() const
{
  return s_instance_functions;
}

sdlxvulkan::System const& sdlxvulkan::Instance::get_system() const noexcept
{
  return std::get_deleter<Instance_Destroyer>(m_data)->m_system;
}

sdlxvulkan::Window const& sdlxvulkan::Instance::get_window() const noexcept
{
  return std::get_deleter<Instance_Destroyer>(m_data)->m_window;
}

VkAllocationCallbacks const* sdlxvulkan::Instance::get_allocation_callbacks() const noexcept
{
  return std::get_deleter<Instance_Destroyer>(m_data)->m_allocation_callbacks;
}

uint32_t sdlxvulkan::Instance::get_physical_device_count() const noexcept
{
  uint32_t l_count{ 0 };
  s_instance_functions.vkEnumeratePhysicalDevices(get(), &l_count, nullptr);
  return l_count;
}

std::vector<sdlxvulkan::Physical_Device> sdlxvulkan::Instance::get_physical_devices() const
{
  auto l_count = get_physical_device_count();

  std::vector<VkPhysicalDevice> l_handles{};
  l_handles.resize(l_count);

  s_instance_functions.vkEnumeratePhysicalDevices(get(), &l_count, l_handles.data());

  std::vector<Physical_Device> l_result{};
  l_result.reserve(l_count);
  for (auto l_handle : l_handles)
  {
    l_result.emplace_back(l_handle, *this);
  }

  return l_result;
}