#include "surface.hpp"

#include "instance.hpp"
#include "instance_functions.hpp"
#include "window.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Surface_Destroyer
    //---------------------------------------------------------------------------
    // Does the actual work.

    class Surface_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Window m_window;
      Instance m_instance;
      VkAllocationCallbacks const* m_allocation_callbacks;

      // Special 6
      //============================================================
      Surface_Destroyer(Window const& a_window, Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks) noexcept:
        m_window{ a_window },
        m_instance{ a_instance },
        m_allocation_callbacks{ a_allocation_callbacks }
      {
        std::cout << "sdlxvulkan::Surface_Destroyer::Surface_Destroyer()" << std::endl;
      }
      // Interface
      //============================================================
      void operator()(VkSurfaceKHR a_surface) const noexcept
      {
        m_instance.vk_functions().vkDestroySurfaceKHR(m_instance, a_surface, m_allocation_callbacks);
        std::cout << "sdlxvulkan::Surface_Destroyer::operator()" << std::endl;
      }
    };  


    decltype(auto) make_except_surface(Window const& a_window, Instance const& a_instance)//, VkAllocationCallbacks const* a_allocation_callbacks)
    {
      VkSurfaceKHR l_surface{};
      if (SDL_Vulkan_CreateSurface(a_window, a_instance, &l_surface) != SDL_TRUE)
      {
        throw std::runtime_error("SDL: Failed to create a Vulkan surface.");
      }

      return make_except_vulkan_sptr<VkSurfaceKHR, Surface_Destroyer>(l_surface, a_window, a_instance, nullptr);

      //Surface_Uptr l_capture{ l_surface, Surface_Destroyer{ a_window, a_instance, nullptr } };

      //return Surface_Sptr{ std::move(l_capture) };
    }


  } // namespace  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

// Special 6
//============================================================

sdlxvulkan::Surface::Surface(Window const& a_window, Instance const& a_instance):
  m_data{ make_except_surface(a_window, a_instance) }
{
  //std::cout << "sdlxvulkan::Surface::Surface()" << std::endl;
}
/*
sdlxvulkan::Surface::Surface(Window const& a_window, Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks) :
  m_data{ make_except_surface(a_window, a_instance), a_allocation_callbacks) }
{
  //std::cout << "sdlxvulkan::Surface::Surface()" << std::endl;
}
*/
sdlxvulkan::Surface::~Surface()
{
  //std::cout << "sdlxvulkan::Surface::~Surface()" << std::endl;
}

sdlxvulkan::Instance const& sdlxvulkan::Surface::get_instance() const noexcept
{
  return std::get_deleter<Surface_Destroyer>(m_data)->m_instance;
}