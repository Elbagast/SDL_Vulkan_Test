#ifndef SDLXVULKAN_EVENT_STRING_HPP
#define SDLXVULKAN_EVENT_STRING_HPP

#include <SDL.h>
#include <string>

namespace sdlxvulkan
{
  char const* to_c_string(SDL_EventType a_event_type) noexcept;
  char const* to_c_string(SDL_WindowEventID a_event_id) noexcept;
  //char const* to_c_string(SDL_Keycode a_keycode) noexcept;
  char const* to_c_string(SDL_Keymod a_keymod) noexcept;
  char const* to_c_string(SDL_Scancode a_scancode) noexcept;
  char const* to_c_string(SDL_GameControllerButton a_game_controller_button) noexcept;

  char const* mouse_button_to_c_string(Uint8 a_button) noexcept;
  char const* mouse_button_mask_to_c_string(Uint32 a_button) noexcept;
  
  std::string to_std_string(SDL_EventType a_event_type);
  std::string to_std_string(SDL_WindowEventID a_event_id);
  //std::string to_std_string(SDL_Keycode a_keycode);
  std::string to_std_string(SDL_Keymod a_keymod);
  std::string to_std_string(SDL_Scancode a_scancode);
  std::string to_std_string(SDL_GameControllerButton a_game_controller_button);

  std::string mouse_button_to_std_string(Uint8 a_button);

  std::string all_keymods(Uint16 a_keymod);
  std::string all_mouse_buttons(Uint32 a_state);
  
}

#endif // SDLXVULKAN_EVENT_STRING_HPP