#include "instance.hpp"

#include "system.hpp"
#include "window.hpp"
#include "functions.hpp"

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  static Instance_Functions s_instance_functions{};

  namespace
  {
    VkInstance make_except_instance
    (
      System const& a_system,
      Window const& a_window,
      std::vector<std::string> const& a_extension_names,
      std::vector<std::string> const& a_layer_names,
      std::string const& a_application_name,
      uint32_t a_application_version,
      std::string const& a_engine_name,
      uint32_t a_engine_version,
      uint32_t a_vulkan_version
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

      //d::cout << "create instance...";

      if (a_system.vk_functions().vkCreateInstance(&l_create_info, nullptr, &l_instance) != VK_SUCCESS)
      {
        throw std::runtime_error{ "sdlxvulkan::Instance: Failed to create VkInstance." };
      }
      //std::cout << "done" << std::endl;

      std::cout << l_instance << std::endl;

      return l_instance;
    }

    PFN_vkDestroyInstance get_destroy_func(System const& a_system, VkInstance a_instance)
    {
      auto l_destroy_func = reinterpret_cast<PFN_vkDestroyInstance>(a_system.vk_functions().vkGetInstanceProcAddr(a_instance, "vkDestroyInstance"));
      assert(l_destroy_func != nullptr);
      return l_destroy_func;
    }
  }

  //---------------------------------------------------------------------------
  // Instance_Destroyer
  //---------------------------------------------------------------------------
  // Hold the state that must be destroyed after this and supply a means of 
  // destroying this. This would probably have to hold the allocator too.

  class Instance_Destroyer
  {
  private:
    // Member Data
    //============================================================
    System m_system;
    Window m_window;

  public:
    // Special 6
    //============================================================
    Instance_Destroyer
    (
      System const& a_system,
      Window const& a_window
    ) :
      m_system{ a_system },
      m_window{ a_window }
    {
    }
    ~Instance_Destroyer() = default;

    Instance_Destroyer(Instance_Destroyer const& a_other) = default;
    Instance_Destroyer& operator=(Instance_Destroyer const& a_other) = default;

    Instance_Destroyer(Instance_Destroyer && a_other) = default;
    Instance_Destroyer& operator=(Instance_Destroyer && a_other) = default;

    // Interface
    //============================================================
    void operator()(VkInstance a_instance) const
    {
      // Could use system to get the destroy proc and execute it.
      // This means if Instance hides the Vulkan functions this one
      // can still be accessed without needing friend status.
      s_instance_functions.vkDestroyInstance(a_instance, nullptr);
      std::cout << "sdlxvulkan::Instance_Destroyer::operator()" << std::endl;
    }
  };
  
}


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
  uint32_t a_vulkan_version
) :
  Inherited_Type{ make_except_instance(a_system, a_window, a_extension_names, a_layer_names, a_application_name, a_application_version, a_engine_name, a_engine_version, a_vulkan_version), Instance_Destroyer{ a_system, a_window } }
{
  init_instance_functions(s_instance_functions, get(), a_system.vk_functions());
  std::cout << "sdlxvulkan::Instance::Instance()" << std::endl;
}

sdlxvulkan::Instance::~Instance()
{
  std::cout << "sdlxvulkan::Instance::~Instance()" << std::endl;
}

// Interface
//============================================================
sdlxvulkan::Instance_Functions const& sdlxvulkan::Instance::vk_functions()
{
  return s_instance_functions;
}



std::vector<VkPhysicalDevice> sdlxvulkan::Instance::get_physical_devices() const
{
  assert(s_instance_functions.vkEnumeratePhysicalDevices != nullptr);

  uint32_t l_count{ 0 };
  s_instance_functions.vkEnumeratePhysicalDevices(get(), &l_count, nullptr);

  std::vector<VkPhysicalDevice> l_result{};
  l_result.resize(l_count);

  s_instance_functions.vkEnumeratePhysicalDevices(get(), &l_count, l_result.data());

  return l_result;
}

VkPhysicalDevice sdlxvulkan::Instance::get_first_physical_device() const
{
  auto l_devices = get_physical_devices();
  assert(l_devices.size() >= 1);
  return l_devices.front();
}