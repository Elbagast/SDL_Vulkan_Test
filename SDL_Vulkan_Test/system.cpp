#include "system.hpp"

#include "global_functions.hpp"
//#include "functions.hpp"
#include <SDL.h>
#include <SDL_vulkan.h>

#include <iostream>
#include <cassert>

namespace sdlxvulkan
{
  static Global_Functions s_global_functions{};

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

  s_global_functions = Global_Functions{ static_cast<PFN_vkGetInstanceProcAddr>(l_getter_address) };
  //init_global_functions(s_global_functions, static_cast<PFN_vkGetInstanceProcAddr>(l_getter_address));

  std::cout << "sdlxvulkan::System::Implementation::Implementation()" << std::endl;
}

sdlxvulkan::System::Implementation::~Implementation()
{
  // Unload SDL Vulkan
  SDL_Vulkan_UnloadLibrary();

  // Quit SDL
  SDL_Quit();
  std::cout << "sdlxvulkan::System::Implementation::~Implementation()" << std::endl;
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
  std::cout << "sdlxvulkan::System::System()" << std::endl;
}

sdlxvulkan::System::~System()
{
  std::cout << "sdlxvulkan::System::~System()" << std::endl;
}

sdlxvulkan::System::System(System const& a_other) = default;
sdlxvulkan::System& sdlxvulkan::System::operator=(System const& a_other) = default;

sdlxvulkan::System::System(System && a_other) = default;
sdlxvulkan::System& sdlxvulkan::System::operator=(System && a_other) = default;

// Interface
//============================================================
// DO NOT CALL THESE FUNCTIONS BEFORE A System OBJECT HAS BEEN 
// SUCCESSFULLY CONSTRUCTED.


sdlxvulkan::Global_Functions const& sdlxvulkan::System::vk_functions() const
{
  return s_global_functions;
}

// Simplified access to the above data.
sdlxvulkan::Result<std::vector<VkExtensionProperties>> sdlxvulkan::System::instance_extension_properties(char const* a_layer_name) const
{
  //assert(s_global_functions.vkEnumerateInstanceExtensionProperties != nullptr);

  uint32_t l_extension_count{};
  s_global_functions.vkEnumerateInstanceExtensionProperties(a_layer_name, &l_extension_count, nullptr);

  std::vector<VkExtensionProperties> l_extensions{};
  l_extensions.resize(l_extension_count);

  auto l_result = s_global_functions.vkEnumerateInstanceExtensionProperties(a_layer_name, &l_extension_count, l_extensions.data());

  return Result<std::vector<VkExtensionProperties>>{l_result, std::move(l_extensions)};
}

sdlxvulkan::Result<std::vector<VkLayerProperties>> sdlxvulkan::System::instance_layer_properties() const
{
  //assert(s_global_functions.vkEnumerateInstanceLayerProperties != nullptr);

  uint32_t l_layer_count{};
  s_global_functions.vkEnumerateInstanceLayerProperties(&l_layer_count, nullptr);

  std::vector<VkLayerProperties> l_layers{};
  l_layers.resize(l_layer_count);

  auto l_result = s_global_functions.vkEnumerateInstanceLayerProperties(&l_layer_count, l_layers.data());

  return Result<std::vector<VkLayerProperties>>{l_result, std::move(l_layers)};
}

uint32_t sdlxvulkan::System::vulkan_api_version() const
{
  //assert(s_global_functions.vkEnumerateInstanceVersion != nullptr);

  // Dump the Vulkan version for the loaded library
  uint32_t l_library_version{ 0 };
  // Always succeeds if the supplied pointer is valid
  s_global_functions.vkEnumerateInstanceVersion(&l_library_version);
  return l_library_version;
}

bool sdlxvulkan::System::supports_layer(std::string const& a_layer_name) const
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

bool sdlxvulkan::System::supports_layers(std::vector<std::string> const& a_layer_names) const
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
