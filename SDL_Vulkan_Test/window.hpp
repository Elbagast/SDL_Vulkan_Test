#ifndef SDLXVULKAN_WINDOW_HPP
#define SDLXVULKAN_WINDOW_HPP

#include "handle.hpp"
#include <vector>
#include <string>

struct SDL_Window;

namespace sdlxvulkan
{
  class System;

  //---------------------------------------------------------------------------
  // Window
  //---------------------------------------------------------------------------
  // Manages the SDL window with reference counting.

  class Window
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Handle<SDL_Window>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    Window(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags);
    ~Window();

    Window(Window const& a_other);
    Window& operator=(Window const& a_other);

    Window(Window && a_other);
    Window& operator=(Window && a_other);
    
    // Interface
    //============================================================
    Data_Type::Pointer get() const noexcept       { return m_data.get(); }
    operator Data_Type::Pointer() const noexcept  { return m_data.get(); }

    uint32_t id() const;

    int width() const;
    int height() const;

    int draw_width() const;
    int draw_height() const;
    
    std::vector<std::string> required_instance_extensions() const;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Window
//---------------------------------------------------------------------------
// Manages the SDL window with reference counting.

// Special 6
//============================================================

inline sdlxvulkan::Window::Window(Window const& a_other) = default;
inline sdlxvulkan::Window& sdlxvulkan::Window::operator=(Window const& a_other) = default;

inline sdlxvulkan::Window::Window(Window && a_other) = default;
inline sdlxvulkan::Window& sdlxvulkan::Window::operator=(Window && a_other) = default;

// Interface
//============================================================

#endif // SDLXVULKAN_WINDOW_HPP
