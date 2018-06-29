#ifndef SDLXVULKAN_SURFACE_HPP
#define SDLXVULKAN_SURFACE_HPP

#include "vulkan_ptr.hpp"
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Window;
  class Instance_OLD;
  
  //---------------------------------------------------------------------------
  // Surface
  //---------------------------------------------------------------------------
  // Manages the Vulkan surface with reference counting.

  class Surface_OLD
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
    Surface_OLD(Window const& a_window, Instance_OLD const& a_instance);
    //Surface(Window const& a_window, Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks = nullptr);
    ~Surface_OLD();

    Surface_OLD(Surface_OLD const& a_other);
    Surface_OLD& operator=(Surface_OLD const& a_other);

    Surface_OLD(Surface_OLD && a_other);
    Surface_OLD& operator=(Surface_OLD && a_other);

    // Interface
    //============================================================
    VkSurfaceKHR get() const noexcept       { return m_data.get(); }
    operator VkSurfaceKHR() const noexcept  { return m_data.get(); }

    Instance_OLD const& get_instance() const noexcept;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

// Special 6
//============================================================

inline sdlxvulkan::Surface_OLD::Surface_OLD(Surface_OLD const& a_other) = default;
inline sdlxvulkan::Surface_OLD& sdlxvulkan::Surface_OLD::operator=(Surface_OLD const& a_other) = default;

inline sdlxvulkan::Surface_OLD::Surface_OLD(Surface_OLD && a_other) = default;
inline sdlxvulkan::Surface_OLD& sdlxvulkan::Surface_OLD::operator=(Surface_OLD && a_other) = default;


#endif // SDLXVULKAN_SURFACE_HPP
