#ifndef SDLXVULKAN_SURFACE_HPP
#define SDLXVULKAN_SURFACE_HPP

#include "result.hpp"
#include <vector>
#include <memory>
#include <string>
#include <vulkan/vulkan_core.h>

namespace sdlxvulkan
{
  class Window;
  class Instance;


  //---------------------------------------------------------------------------
  // Surface
  //---------------------------------------------------------------------------
  // Manages the Vulkan surface with reference counting.

  class Surface
  {
  private:
    // Member Data
    //============================================================
    class Implementation;
    std::shared_ptr<Implementation> m_implementation;
    //Implementation* imp() noexcept { m_implementation.get(); }
    //Implementation const* cimp() const noexcept { m_implementation.get(); }

  public:
    // Special 6
    //============================================================
    Surface(Window const& a_window, Instance const& a_instance);
    ~Surface();

    Surface(Surface const& a_other);
    Surface& operator=(Surface const& a_other);

    Surface(Surface && a_other);
    Surface& operator=(Surface && a_other);

    // Interface
    //============================================================
    VkSurfaceKHR get() const;

    operator VkSurfaceKHR() const;
  };
}

#endif // SDLXVULKAN_SURFACE_HPP
