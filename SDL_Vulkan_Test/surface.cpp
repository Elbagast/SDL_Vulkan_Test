#include "surface.hpp"

#include "instance.hpp"
#include "window.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>


namespace sdlxvulkan
{
  VkSurfaceKHR make_except_surface(Window const& a_window, Instance const& a_instance)
  {
    VkSurfaceKHR l_surface{};
    if (SDL_Vulkan_CreateSurface(a_window, a_instance, &l_surface) != SDL_TRUE)
    {
      throw std::runtime_error("SDL: Failed to create a Vulkan surface.");
    }
    return l_surface;
  }
  

  //---------------------------------------------------------------------------
  // Window::Implementation
  //---------------------------------------------------------------------------
  // Does the actual work.

  class Surface::Implementation
  {
  public:
    // Member Data
    //============================================================
    Window m_window;
    Instance m_instance;
    VkSurfaceKHR m_surface;

    // Special 6
    //============================================================
    Implementation(Window const& a_window, Instance const& a_instance) :
      m_window{ a_window },
      m_instance{ a_instance },
      m_surface{ make_except_surface(m_window, m_instance) }
    {
      std::cout << "sdlxvulkan::Surface::Surface()" << std::endl;
    }
    ~Implementation()
    {
      // Destroy the Vulkan surface.
      m_instance.vkDestroySurfaceKHR(m_surface, nullptr);
      std::cout << "sdlxvulkan::Surface::~Surface()" << std::endl;
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

// Special 6
//============================================================

sdlxvulkan::Surface::Surface(Window const& a_window, Instance const& a_instance) :
  m_implementation{ std::make_shared<Implementation>(a_window, a_instance) }
{
}

sdlxvulkan::Surface::~Surface() = default;

sdlxvulkan::Surface::Surface(Surface const& a_other) = default;
sdlxvulkan::Surface& sdlxvulkan::Surface::operator=(Surface const& a_other) = default;

sdlxvulkan::Surface::Surface(Surface && a_other) = default;
sdlxvulkan::Surface& sdlxvulkan::Surface::operator=(Surface && a_other) = default;


// Interface
//============================================================
// Explcitly get the VkInstance.
VkSurfaceKHR sdlxvulkan::Surface::get() const
{
  return m_implementation->m_surface;
}

// Implicitly convert to VkInstance.
sdlxvulkan::Surface::operator VkSurfaceKHR() const
{
  return m_implementation->m_surface;
}
