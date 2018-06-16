#include "surface.hpp"

#include "instance.hpp"
#include "window.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>


namespace sdlxvulkan
{
  namespace
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
    // Surface_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Surface_Destroyer
    {
    private:
      // Member Data
      //============================================================
      Window m_window;
      mutable Instance m_instance;

    public:
      // Special 6
      //============================================================
      Surface_Destroyer(Window const& a_window, Instance const& a_instance) :
        m_window{ a_window },
        m_instance{ a_instance }
      {
      }
      ~Surface_Destroyer() = default;

      Surface_Destroyer(Surface_Destroyer const& a_other) = default;
      Surface_Destroyer& operator=(Surface_Destroyer const& a_other) = default;

      Surface_Destroyer(Surface_Destroyer && a_other) = default;
      Surface_Destroyer& operator=(Surface_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(VkSurfaceKHR a_surface) const noexcept
      {
        m_instance.vkDestroySurfaceKHR(a_surface, nullptr);
        std::cout << "sdlxvulkan::Surface_Destroyer::operator()" << std::endl;
      }
    };
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

// Special 6
//============================================================

sdlxvulkan::Surface::Surface(Window const& a_window, Instance const& a_instance) :
  Inherited_Type{ make_except_surface(a_window, a_instance), Surface_Destroyer{ a_window, a_instance } }
{
  std::cout << "sdlxvulkan::Surface::Surface()" << std::endl;
}

sdlxvulkan::Surface::~Surface()
{
  std::cout << "sdlxvulkan::Surface::~Surface()" << std::endl;
}
