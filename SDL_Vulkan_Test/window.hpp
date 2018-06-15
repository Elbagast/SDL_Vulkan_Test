#ifndef SDLXVULKAN_WINDOW_HPP
#define SDLXVULKAN_WINDOW_HPP

#include "result.hpp"
#include <vector>
#include <memory>
#include <string>
#include <vulkan/vulkan_core.h>

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
    class Implementation;
    std::shared_ptr<Implementation> m_implementation;
    //Implementation* imp() noexcept { m_implementation.get(); }
    //Implementation const* cimp() const noexcept { m_implementation.get(); }

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
    SDL_Window * get() const;

    operator SDL_Window*() const;

    uint32_t id() const;

    int width() const;
    int height() const;

    int draw_width() const;
    int draw_height() const;
    
    std::vector<std::string> required_instance_extensions() const;
  };
}

#endif // SDLXVULKAN_WINDOW_HPP
