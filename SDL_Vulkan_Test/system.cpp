#include "system.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include <iostream>
#include <cassert>

#define DECLARE_VULKAN_FUNC(a_func_name) static PFN_##a_func_name a_func_name{nullptr};

namespace sdlxvulkan
{
  // The function that will get the others.
  DECLARE_VULKAN_FUNC(vkGetInstanceProcAddr)

  // Functions that don't need an instance to use
  DECLARE_VULKAN_FUNC(vkCreateInstance)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceExtensionProperties)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceLayerProperties)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceVersion)


  void init_vulkan_get_proc(PFN_vkGetInstanceProcAddr a_getter);
  void init_vulkan_global_functions();
}

#undef DECLARE_VULKAN_FUNC

void sdlxvulkan::init_vulkan_get_proc(PFN_vkGetInstanceProcAddr a_getter)
{
  sdlxvulkan::vkGetInstanceProcAddr = a_getter;
}

#define INIT_VULKAN_GLOBAL_FUNC(a_func_name) a_func_name = (PFN_##a_func_name)(sdlxvulkan::vkGetInstanceProcAddr(VK_NULL_HANDLE, #a_func_name));

void sdlxvulkan::init_vulkan_global_functions()
{
  INIT_VULKAN_GLOBAL_FUNC(vkCreateInstance)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceExtensionProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceLayerProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceVersion)
}

#undef INIT_VULKAN_GLOBAL_FUNC

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // System::Implementation
  //---------------------------------------------------------------------------
  // Does the actual work.

  class System::Implementation
  {
  public:
    // Special 6
    //============================================================
    explicit Implementation(uint32_t a_flags);
    ~Implementation();

    Implementation(Implementation const& a_other) = delete;
    Implementation& operator=(Implementation const& a_other) = delete;

    Implementation(Implementation && a_other) = delete;
    Implementation& operator=(Implementation && a_other) = delete;

  };
}

//---------------------------------------------------------------------------
// System::Implementation
//---------------------------------------------------------------------------
// Does the actual work.

// Special 6
//============================================================
static_assert(std::is_same_v<uint32_t, ::Uint32>, "Bad typematch on hiding the SDL type ::Uint32, it is not the same as ::uint32_t");

sdlxvulkan::System::Implementation::Implementation(uint32_t a_flags)
{
  // Initialise the system, stop if fails.
  if (SDL_Init(a_flags) != 0)
  {
    throw std::runtime_error{ "SDL: Initialisation failed." };
  }

  // Initialise Vulkan
  if (SDL_Vulkan_LoadLibrary(nullptr) != 0)
  {
    throw std::runtime_error{ "SDL: Could not load Vulkan." };
  }

  // Get the getter function
  void* l_getter_address = SDL_Vulkan_GetVkGetInstanceProcAddr();
  if (l_getter_address == nullptr)
  {
    throw std::runtime_error{ "SDL: Could not get address of vkGetInstanceProcAddr." };
  }

  // Initialise the vulcan getter function
  init_vulkan_get_proc(static_cast<PFN_vkGetInstanceProcAddr>(l_getter_address));

  // Initialise the global vulkan functions.
  init_vulkan_global_functions();

  std::cout << "sdlxvulkan::System::System()" << std::endl;
}

sdlxvulkan::System::Implementation::~Implementation()
{
  // Unload SDL Vulkan
  SDL_Vulkan_UnloadLibrary();

  // Quit SDL
  SDL_Quit();
  std::cout << "sdlxvulkan::System::~System()" << std::endl;
}


//---------------------------------------------------------------------------
// System
//---------------------------------------------------------------------------
// Manages the SDL system and Vulkan interface with reference counting so it 
// cleans up properly. Since Vulkan must be loaded by SDL, the system has 
// state that is essentially global, but also must be initalised and shut
// down properly.

// Special 6
//============================================================
sdlxvulkan::System::System(uint32_t a_flags) :
  m_implementation{ std::make_shared<Implementation>(a_flags)}
{  
}

sdlxvulkan::System::~System() = default;

sdlxvulkan::System::System(System const& a_other) = default;
sdlxvulkan::System& sdlxvulkan::System::operator=(System const& a_other) = default;

sdlxvulkan::System::System(System && a_other) = default;
sdlxvulkan::System& sdlxvulkan::System::operator=(System && a_other) = default;

// Interface
//============================================================
// DO NOT CALL THESE FUNCTIONS BEFORE A System OBJECT HAS BEEN 
// SUCCESSFULLY CONSTRUCTED.

PFN_vkGetInstanceProcAddr sdlxvulkan::System::get_vkGetInstanceProcAddr()
{
  return sdlxvulkan::vkGetInstanceProcAddr;
}

// Direct access to the Vulkan functions, as in the Vulkan documentation.
PFN_vkVoidFunction sdlxvulkan::System::vkGetInstanceProcAddr(VkInstance instance, char const* pName)
{
  return sdlxvulkan::vkGetInstanceProcAddr(instance, pName);
}

VkResult sdlxvulkan::System::vkCreateInstance(VkInstanceCreateInfo const*  pCreateInfo, VkAllocationCallbacks const* pAllocator, VkInstance* pInstance)
{
  assert(sdlxvulkan::vkCreateInstance != nullptr);
  return sdlxvulkan::vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}

VkResult sdlxvulkan::System::vkEnumerateInstanceExtensionProperties(char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
  return sdlxvulkan::vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}

VkResult sdlxvulkan::System::vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
  return sdlxvulkan::vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

VkResult sdlxvulkan::System::vkEnumerateInstanceVersion(uint32_t* pApiVersion)
{
  return sdlxvulkan::vkEnumerateInstanceVersion(pApiVersion);
}


// Simplified access to the above data.
sdlxvulkan::Result<std::vector<VkExtensionProperties>> sdlxvulkan::System::instance_extension_properties(char const* a_layer_name)
{
  uint32_t l_extension_count{};
  vkEnumerateInstanceExtensionProperties(a_layer_name, &l_extension_count, nullptr);

  std::vector<VkExtensionProperties> l_extensions{};
  l_extensions.resize(l_extension_count);

  auto l_result = vkEnumerateInstanceExtensionProperties(a_layer_name, &l_extension_count, l_extensions.data());

  return Result<std::vector<VkExtensionProperties>>{l_result, std::move(l_extensions)};
}

sdlxvulkan::Result<std::vector<VkLayerProperties>> sdlxvulkan::System::instance_layer_properties()
{
  uint32_t l_layer_count{};
  vkEnumerateInstanceLayerProperties(&l_layer_count, nullptr);

  std::vector<VkLayerProperties> l_layers{};
  l_layers.resize(l_layer_count);

  auto l_result = vkEnumerateInstanceLayerProperties(&l_layer_count, l_layers.data());

  return Result<std::vector<VkLayerProperties>>{l_result, std::move(l_layers)};
}

uint32_t sdlxvulkan::System::vulkan_api_version()
{
  // Dump the Vulkan version for the loaded library
  uint32_t l_library_version{ 0 };
  // Always succeeds if the supplied pointer is valid
  vkEnumerateInstanceVersion(&l_library_version);
  return l_library_version;
}

bool sdlxvulkan::System::supports_layer(std::string const& a_layer_name)
{
  auto const l_available_layers = instance_layer_properties().data;

  for (auto const& l_layer_properties : l_available_layers)
  {
    if (a_layer_name == l_layer_properties.layerName)
    {
      return true;
    }
  }
  return false;
}

bool sdlxvulkan::System::supports_layers(std::vector<std::string> const& a_layer_names)
{
  auto const l_available_layers = instance_layer_properties().data;

  for (auto const& l_layer_name : a_layer_names)
  {
    bool l_layer_found = false;

    for (auto const& l_layer_properties : l_available_layers)
    {
      if (l_layer_name == l_layer_properties.layerName)
      {
        l_layer_found = true;
        break;
      }
    }

    if (!l_layer_found)
    {
      return false;
    }
  }

  return true;
}
