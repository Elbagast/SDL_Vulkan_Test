#ifndef SDLXVULKAN_WINDOW_HPP
#define SDLXVULKAN_WINDOW_HPP

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
    using Data_Type = std::shared_ptr<SDL_Window>;
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
    SDL_Window* get() const noexcept       { return m_data.get(); }
    operator SDL_Window*() const noexcept  { return m_data.get(); }

    System const& get_system() const noexcept;

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
