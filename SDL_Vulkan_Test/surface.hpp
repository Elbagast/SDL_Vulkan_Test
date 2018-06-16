#ifndef SDLXVULKAN_SURFACE_HPP
#define SDLXVULKAN_SURFACE_HPP

#include "handle.hpp"
#include <vulkan/vulkan_core.h>

namespace sdlxvulkan
{
  class Window;
  class Instance;
  
  //---------------------------------------------------------------------------
  // Surface
  //---------------------------------------------------------------------------
  // Manages the Vulkan surface with reference counting.

  class Surface :
    private Vulkan_Handle<VkSurfaceKHR>
  {
  private:
    using Inherited_Type = Vulkan_Handle<VkSurfaceKHR>;
  public:
    using Inherited_Type::get;
    using Inherited_Type::operator Pointer;

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
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

// Special 6
//============================================================

inline sdlxvulkan::Surface::Surface(Surface const& a_other) = default;
inline sdlxvulkan::Surface& sdlxvulkan::Surface::operator=(Surface const& a_other) = default;

inline sdlxvulkan::Surface::Surface(Surface && a_other) = default;
inline sdlxvulkan::Surface& sdlxvulkan::Surface::operator=(Surface && a_other) = default;


#endif // SDLXVULKAN_SURFACE_HPP
