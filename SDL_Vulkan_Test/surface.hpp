#ifndef SDLXVULKAN_SURFACE_HPP
#define SDLXVULKAN_SURFACE_HPP

#include "vulkan_ptr.hpp"
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

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
    using Data_Type = Vulkan_Sptr<VkSurfaceKHR>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    // SDL supplies no means to use an allocator for the Vulkan surface.
    Surface(Window const& a_window, Instance const& a_instance);
    //Surface(Window const& a_window, Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks = nullptr);
    ~Surface();

    Surface(Surface const& a_other);
    Surface& operator=(Surface const& a_other);

    Surface(Surface && a_other);
    Surface& operator=(Surface && a_other);

    // Interface
    //============================================================
    VkSurfaceKHR get() const noexcept       { return m_data.get(); }
    operator VkSurfaceKHR() const noexcept  { return m_data.get(); }

    Instance const& get_instance() const noexcept;
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
