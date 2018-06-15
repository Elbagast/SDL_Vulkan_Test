#include "window.hpp"

#include "system.hpp"
#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Window::Implementation
  //---------------------------------------------------------------------------
  // Does the actual work.

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


  class Window::Implementation
  {
  public:
    // Member Data
    //============================================================
    System m_system;
    SDL_Window* m_window;

    // Special 6
    //============================================================
    Implementation(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags) :
      m_system{ a_system },
      m_window{ make_except_window(m_system, a_title, a_xpos, a_ypos, a_width, a_height, a_flags) }
    {
      assert(m_window != nullptr);
      std::cout << "sdlxvulkan::Window::Window()" << std::endl;
    }
    ~Implementation()
    {
      SDL_DestroyWindow(m_window);
      std::cout << "sdlxvulkan::Window::~Window()" << std::endl;
    }

    Implementation(Implementation const& a_other) = delete;
    Implementation& operator=(Implementation const& a_other) = delete;

    Implementation(Implementation && a_other) = delete;
    Implementation& operator=(Implementation && a_other) = delete;

  };
}

//---------------------------------------------------------------------------
// Window
//---------------------------------------------------------------------------
// Manages the SDL window with reference counting.

// Special 6
//============================================================
sdlxvulkan::Window::Window(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags) :
  m_implementation{ std::make_shared<Implementation>(a_system,a_title, a_xpos, a_ypos, a_width, a_height, a_flags)}
{
}
sdlxvulkan::Window::~Window() = default;

sdlxvulkan::Window::Window(Window const& a_other) = default;
sdlxvulkan::Window& sdlxvulkan::Window::operator=(Window const& a_other) = default;

sdlxvulkan::Window::Window(Window && a_other) = default;
sdlxvulkan::Window& sdlxvulkan::Window::operator=(Window && a_other) = default;

// Interface
//============================================================
SDL_Window* sdlxvulkan::Window::get() const
{
  return m_implementation->m_window;
}

sdlxvulkan::Window::operator SDL_Window*() const
{
  return m_implementation->m_window;
}

uint32_t sdlxvulkan::Window::id() const
{
  return SDL_GetWindowID(m_implementation->m_window);
}

int sdlxvulkan::Window::width() const
{
  int l_width{ 0 };
  SDL_GetWindowSize(m_implementation->m_window, &l_width, nullptr);
  return l_width;
}

int sdlxvulkan::Window::height() const
{
  int l_height{ 0 };
  SDL_GetWindowSize(m_implementation->m_window, nullptr, &l_height);
  return l_height;
}

int sdlxvulkan::Window::draw_width() const
{
  int l_width{ 0 };
  SDL_Vulkan_GetDrawableSize(m_implementation->m_window, &l_width, nullptr);
  return l_width;
}

int sdlxvulkan::Window::draw_height() const
{
  int l_height{ 0 };
  SDL_Vulkan_GetDrawableSize(m_implementation->m_window, nullptr, &l_height);
  return l_height;
}

std::vector<std::string> sdlxvulkan::Window::required_instance_extensions() const
{
  // get the number of extensions 
  uint32_t l_extension_count{ 0 };
  if (SDL_Vulkan_GetInstanceExtensions(m_implementation->m_window, &l_extension_count, nullptr) != SDL_TRUE)
  {
    // failed to get extension count...
    throw std::runtime_error("SDL: Could not get Vulkan extension count for a window.");
  }

  // make a vector of nullptr big enough to store the extension names
  std::vector<char const*> l_extension_names{ l_extension_count, nullptr };
  if (SDL_Vulkan_GetInstanceExtensions(m_implementation->m_window, &l_extension_count, l_extension_names.data()) != SDL_TRUE)
  {
    // failed to get all the extension names...
    throw std::runtime_error("SDL: Could not get all Vulkan extension names for a window.");
  }
  std::vector<std::string> l_result{};
  l_result.reserve(l_extension_names.size());
  for (auto l_ext : l_extension_names)
  {
    l_result.push_back(l_ext);
  }
  return l_result;
}
