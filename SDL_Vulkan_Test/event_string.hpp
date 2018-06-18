#ifndef SDLXVULKAN_EVENT_STRING_HPP
#define SDLXVULKAN_EVENT_STRING_HPP

#include <SDL.h>
#include <string>

namespace sdlxvulkan
{
#define CASE_ENUM_STRING(a_arg) case a_arg: return u8###a_arg;

  char const* sdl_event_c_string(SDL_EventType a_event_type)
  {
    switch (a_event_type)
    {
      CASE_ENUM_STRING(SDL_QUIT)
      CASE_ENUM_STRING(SDL_APP_TERMINATING)
      CASE_ENUM_STRING(SDL_APP_LOWMEMORY)
      CASE_ENUM_STRING(SDL_APP_WILLENTERBACKGROUND)
      CASE_ENUM_STRING(SDL_APP_DIDENTERBACKGROUND)
      CASE_ENUM_STRING(SDL_APP_WILLENTERFOREGROUND)
      CASE_ENUM_STRING(SDL_APP_DIDENTERFOREGROUND)
      CASE_ENUM_STRING(SDL_WINDOWEVENT)
      CASE_ENUM_STRING(SDL_SYSWMEVENT)

    default: return u8"Bad SDL_EventType";
    }
  }
  std::string sdl_event_string(SDL_EventType a_event_type)
  {
    return std::string{ sdl_event_c_string(a_event_type) };
  }

  char const* sdl_window_event_c_string(SDL_WindowEventID a_event_id)
  {
    switch (a_event_id)
    {
      CASE_ENUM_STRING(SDL_WINDOWEVENT_NONE)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_SHOWN)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_HIDDEN)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_EXPOSED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_MOVED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_RESIZED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_SIZE_CHANGED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_MINIMIZED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_MAXIMIZED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_RESTORED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_ENTER)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_LEAVE)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_FOCUS_GAINED)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_FOCUS_LOST)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_CLOSE)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_TAKE_FOCUS)
      CASE_ENUM_STRING(SDL_WINDOWEVENT_HIT_TEST)

    default: return u8"Bad SDL_WindowEventID";
    }
  }
  std::string sdl_window_event_string(SDL_WindowEventID a_event_id)
  {
    return std::string{ sdl_window_event_c_string(a_event_id) };
  }
#undef CASE_ENUM_STRING
}

#endif // SDLXVULKAN_EVENT_STRING_HPP