#include "window.hpp"

#include "system.hpp"
#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    // Factory function for the actual window.
    SDL_Window* make_except_window(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags)
    {
      // make sure we have this flag
      auto l_flags = a_flags | SDL_WINDOW_VULKAN;
      SDL_Window* l_result = SDL_CreateWindow(a_title.c_str(), a_xpos, a_ypos, a_width, a_height, l_flags);
      if (l_result == nullptr)
      {
        throw std::runtime_error{ "SDL: Failed to create window." };
      }
      return l_result;
    }


    //---------------------------------------------------------------------------
    // Window_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Window_Destroyer
    {
    private:
      // Member Data
      //============================================================
      System m_system;

    public:
      // Special 6
      //============================================================
      explicit Window_Destroyer(System const& a_system) :
        m_system{ a_system }
      {
      }
      ~Window_Destroyer() = default;

      Window_Destroyer(Window_Destroyer const& a_other) = default;
      Window_Destroyer& operator=(Window_Destroyer const& a_other) = default;

      Window_Destroyer(Window_Destroyer && a_other) = default;
      Window_Destroyer& operator=(Window_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(SDL_Window* a_window) const noexcept
      {
        SDL_DestroyWindow(a_window);
        std::cout << "sdlxvulkan::Window_Destroyer::operator()" << std::endl;
      }
    };
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Window
//---------------------------------------------------------------------------
// Manages the SDL window with reference counting.

// Special 6
//============================================================
sdlxvulkan::Window::Window(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags) :
  Inherited_Type{ make_except_window(a_system,a_title, a_xpos, a_ypos, a_width, a_height, a_flags), Window_Destroyer{ a_system } }
{
  std::cout << "sdlxvulkan::Window::Window()" << std::endl;
}
sdlxvulkan::Window::~Window()
{
  std::cout << "sdlxvulkan::Window::~Window()" << std::endl;
}


// Interface
//============================================================

uint32_t sdlxvulkan::Window::id() const
{
  return SDL_GetWindowID(get());
}

int sdlxvulkan::Window::width() const
{
  int l_width{ 0 };
  SDL_GetWindowSize(get(), &l_width, nullptr);
  return l_width;
}

int sdlxvulkan::Window::height() const
{
  int l_height{ 0 };
  SDL_GetWindowSize(get(), nullptr, &l_height);
  return l_height;
}

int sdlxvulkan::Window::draw_width() const
{
  int l_width{ 0 };
  SDL_Vulkan_GetDrawableSize(get(), &l_width, nullptr);
  return l_width;
}

int sdlxvulkan::Window::draw_height() const
{
  int l_height{ 0 };
  SDL_Vulkan_GetDrawableSize(get(), nullptr, &l_height);
  return l_height;
}

std::vector<std::string> sdlxvulkan::Window::required_instance_extensions() const
{
  // get the number of extensions 
  uint32_t l_extension_count{ 0 };
  if (SDL_Vulkan_GetInstanceExtensions(get(), &l_extension_count, nullptr) != SDL_TRUE)
  {
    // failed to get extension count...
    throw std::runtime_error{ "SDL: Could not get Vulkan extension count for a window." };
  }

  // make a vector of nullptr big enough to store the extension names
  std::vector<char const*> l_extension_names{ l_extension_count, nullptr };
  if (SDL_Vulkan_GetInstanceExtensions(get(), &l_extension_count, l_extension_names.data()) != SDL_TRUE)
  {
    // failed to get all the extension names...
    throw std::runtime_error{ "SDL: Could not get all Vulkan extension names for a window." };
  }
  std::vector<std::string> l_result{};
  l_result.reserve(l_extension_names.size());
  for (auto l_ext : l_extension_names)
  {
    l_result.push_back(l_ext);
  }
  return l_result;
}
