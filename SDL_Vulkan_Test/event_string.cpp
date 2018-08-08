#include "event_string.hpp"
#include <cassert>

#define CASE_ENUM_STRING(a_arg) case a_arg: return u8###a_arg;

char const* sdlxvulkan::to_c_string(SDL_EventType a_event_type) noexcept
{
  switch (a_event_type)
  {
  // Application Events
  CASE_ENUM_STRING(SDL_QUIT)
  CASE_ENUM_STRING(SDL_APP_TERMINATING)
  CASE_ENUM_STRING(SDL_APP_LOWMEMORY)
  CASE_ENUM_STRING(SDL_APP_WILLENTERBACKGROUND)
  CASE_ENUM_STRING(SDL_APP_DIDENTERBACKGROUND)
  CASE_ENUM_STRING(SDL_APP_WILLENTERFOREGROUND)
  CASE_ENUM_STRING(SDL_APP_DIDENTERFOREGROUND)

  // Window Events
  CASE_ENUM_STRING(SDL_WINDOWEVENT)
  CASE_ENUM_STRING(SDL_SYSWMEVENT)

  // Keyboard Events
  CASE_ENUM_STRING(SDL_KEYDOWN)
  CASE_ENUM_STRING(SDL_KEYUP)
  CASE_ENUM_STRING(SDL_TEXTEDITING)
  CASE_ENUM_STRING(SDL_TEXTINPUT)
  CASE_ENUM_STRING(SDL_KEYMAPCHANGED)

  // Mouse Events
  CASE_ENUM_STRING(SDL_MOUSEMOTION)
  CASE_ENUM_STRING(SDL_MOUSEBUTTONDOWN)
  CASE_ENUM_STRING(SDL_MOUSEBUTTONUP)
  CASE_ENUM_STRING(SDL_MOUSEWHEEL)

  // Joystick Events
  CASE_ENUM_STRING(SDL_JOYAXISMOTION)
  CASE_ENUM_STRING(SDL_JOYBALLMOTION)
  CASE_ENUM_STRING(SDL_JOYHATMOTION)
  CASE_ENUM_STRING(SDL_JOYBUTTONDOWN)
  CASE_ENUM_STRING(SDL_JOYBUTTONUP)
  CASE_ENUM_STRING(SDL_JOYDEVICEADDED)
  CASE_ENUM_STRING(SDL_JOYDEVICEREMOVED)

  // Controller Events
  CASE_ENUM_STRING(SDL_CONTROLLERAXISMOTION)
  CASE_ENUM_STRING(SDL_CONTROLLERBUTTONDOWN)
  CASE_ENUM_STRING(SDL_CONTROLLERBUTTONUP)
  CASE_ENUM_STRING(SDL_CONTROLLERDEVICEADDED)
  CASE_ENUM_STRING(SDL_CONTROLLERDEVICEREMOVED)
  CASE_ENUM_STRING(SDL_CONTROLLERDEVICEREMAPPED)

  // Touch Events
  CASE_ENUM_STRING(SDL_FINGERDOWN)
  CASE_ENUM_STRING(SDL_FINGERUP)
  CASE_ENUM_STRING(SDL_FINGERMOTION)

  // Gesture Events
  CASE_ENUM_STRING(SDL_DOLLARGESTURE)
  CASE_ENUM_STRING(SDL_DOLLARRECORD)
  CASE_ENUM_STRING(SDL_MULTIGESTURE)

  // Clipboard Events
  CASE_ENUM_STRING(SDL_CLIPBOARDUPDATE)

  // Drag and Drop Events
  CASE_ENUM_STRING(SDL_DROPFILE)
  CASE_ENUM_STRING(SDL_DROPTEXT)
  CASE_ENUM_STRING(SDL_DROPBEGIN)
  CASE_ENUM_STRING(SDL_DROPCOMPLETE)

  // Audio Hotplug Events
  CASE_ENUM_STRING(SDL_AUDIODEVICEADDED)
  CASE_ENUM_STRING(SDL_AUDIODEVICEREMOVED)

  // Render Events
  CASE_ENUM_STRING(SDL_RENDER_TARGETS_RESET)
  CASE_ENUM_STRING(SDL_RENDER_DEVICE_RESET)

  // User Events
  // User events are pretty badly documented...or just messily so
  CASE_ENUM_STRING(SDL_USEREVENT)

  default: return u8"Bad SDL_EventType";
  }
}

char const* sdlxvulkan::to_c_string(SDL_WindowEventID a_event_id) noexcept
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
/*
char const* sdlxvulkan::to_c_string(SDL_Keycode a_keycode) noexcept
{

}
*/
char const* sdlxvulkan::to_c_string(SDL_Keymod a_keymod) noexcept
{

  switch (a_keymod)
  {
  CASE_ENUM_STRING(KMOD_NONE)
  CASE_ENUM_STRING(KMOD_LSHIFT)
  CASE_ENUM_STRING(KMOD_RSHIFT)
  CASE_ENUM_STRING(KMOD_LCTRL)
  CASE_ENUM_STRING(KMOD_RCTRL)
  CASE_ENUM_STRING(KMOD_LALT)
  CASE_ENUM_STRING(KMOD_RALT)
  CASE_ENUM_STRING(KMOD_LGUI)
  CASE_ENUM_STRING(KMOD_RGUI)
  CASE_ENUM_STRING(KMOD_NUM)
  CASE_ENUM_STRING(KMOD_CAPS)
  CASE_ENUM_STRING(KMOD_MODE)
  CASE_ENUM_STRING(KMOD_RESERVED)

  default: return u8"Bad SDL_WindowEventID";
  }
}

char const* sdlxvulkan::to_c_string(SDL_Scancode a_scancode) noexcept
{
  switch(a_scancode)
  {
  CASE_ENUM_STRING(SDL_SCANCODE_UNKNOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_A)
  CASE_ENUM_STRING(SDL_SCANCODE_B)
  CASE_ENUM_STRING(SDL_SCANCODE_C)
  CASE_ENUM_STRING(SDL_SCANCODE_D)
  CASE_ENUM_STRING(SDL_SCANCODE_E)
  CASE_ENUM_STRING(SDL_SCANCODE_F)
  CASE_ENUM_STRING(SDL_SCANCODE_G)
  CASE_ENUM_STRING(SDL_SCANCODE_H)
  CASE_ENUM_STRING(SDL_SCANCODE_I)
  CASE_ENUM_STRING(SDL_SCANCODE_J)
  CASE_ENUM_STRING(SDL_SCANCODE_K)
  CASE_ENUM_STRING(SDL_SCANCODE_L)
  CASE_ENUM_STRING(SDL_SCANCODE_M)
  CASE_ENUM_STRING(SDL_SCANCODE_N)
  CASE_ENUM_STRING(SDL_SCANCODE_O)
  CASE_ENUM_STRING(SDL_SCANCODE_P)
  CASE_ENUM_STRING(SDL_SCANCODE_Q)
  CASE_ENUM_STRING(SDL_SCANCODE_R)
  CASE_ENUM_STRING(SDL_SCANCODE_S)
  CASE_ENUM_STRING(SDL_SCANCODE_T)
  CASE_ENUM_STRING(SDL_SCANCODE_U)
  CASE_ENUM_STRING(SDL_SCANCODE_V)
  CASE_ENUM_STRING(SDL_SCANCODE_W)
  CASE_ENUM_STRING(SDL_SCANCODE_X)
  CASE_ENUM_STRING(SDL_SCANCODE_Y)
  CASE_ENUM_STRING(SDL_SCANCODE_Z)
  CASE_ENUM_STRING(SDL_SCANCODE_1)
  CASE_ENUM_STRING(SDL_SCANCODE_2)
  CASE_ENUM_STRING(SDL_SCANCODE_3)
  CASE_ENUM_STRING(SDL_SCANCODE_4)
  CASE_ENUM_STRING(SDL_SCANCODE_5)
  CASE_ENUM_STRING(SDL_SCANCODE_6)
  CASE_ENUM_STRING(SDL_SCANCODE_7)
  CASE_ENUM_STRING(SDL_SCANCODE_8)
  CASE_ENUM_STRING(SDL_SCANCODE_9)
  CASE_ENUM_STRING(SDL_SCANCODE_0)
  CASE_ENUM_STRING(SDL_SCANCODE_RETURN)
  CASE_ENUM_STRING(SDL_SCANCODE_ESCAPE)
  CASE_ENUM_STRING(SDL_SCANCODE_BACKSPACE)
  CASE_ENUM_STRING(SDL_SCANCODE_TAB)
  CASE_ENUM_STRING(SDL_SCANCODE_SPACE)
  CASE_ENUM_STRING(SDL_SCANCODE_MINUS)
  CASE_ENUM_STRING(SDL_SCANCODE_EQUALS)
  CASE_ENUM_STRING(SDL_SCANCODE_LEFTBRACKET)
  CASE_ENUM_STRING(SDL_SCANCODE_RIGHTBRACKET)
  CASE_ENUM_STRING(SDL_SCANCODE_BACKSLASH)
  CASE_ENUM_STRING(SDL_SCANCODE_NONUSHASH)
  CASE_ENUM_STRING(SDL_SCANCODE_SEMICOLON)
  CASE_ENUM_STRING(SDL_SCANCODE_APOSTROPHE)
  CASE_ENUM_STRING(SDL_SCANCODE_GRAVE)
  CASE_ENUM_STRING(SDL_SCANCODE_COMMA)
  CASE_ENUM_STRING(SDL_SCANCODE_PERIOD)
  CASE_ENUM_STRING(SDL_SCANCODE_SLASH)
  CASE_ENUM_STRING(SDL_SCANCODE_CAPSLOCK)
  CASE_ENUM_STRING(SDL_SCANCODE_F1)
  CASE_ENUM_STRING(SDL_SCANCODE_F2)
  CASE_ENUM_STRING(SDL_SCANCODE_F3)
  CASE_ENUM_STRING(SDL_SCANCODE_F4)
  CASE_ENUM_STRING(SDL_SCANCODE_F5)
  CASE_ENUM_STRING(SDL_SCANCODE_F6)
  CASE_ENUM_STRING(SDL_SCANCODE_F7)
  CASE_ENUM_STRING(SDL_SCANCODE_F8)
  CASE_ENUM_STRING(SDL_SCANCODE_F9)
  CASE_ENUM_STRING(SDL_SCANCODE_F10)
  CASE_ENUM_STRING(SDL_SCANCODE_F11)
  CASE_ENUM_STRING(SDL_SCANCODE_F12)
  CASE_ENUM_STRING(SDL_SCANCODE_PRINTSCREEN)
  CASE_ENUM_STRING(SDL_SCANCODE_SCROLLLOCK)
  CASE_ENUM_STRING(SDL_SCANCODE_PAUSE)
  CASE_ENUM_STRING(SDL_SCANCODE_INSERT)
  CASE_ENUM_STRING(SDL_SCANCODE_HOME)
  CASE_ENUM_STRING(SDL_SCANCODE_PAGEUP)
  CASE_ENUM_STRING(SDL_SCANCODE_DELETE)
  CASE_ENUM_STRING(SDL_SCANCODE_END)
  CASE_ENUM_STRING(SDL_SCANCODE_PAGEDOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_RIGHT)
  CASE_ENUM_STRING(SDL_SCANCODE_LEFT)
  CASE_ENUM_STRING(SDL_SCANCODE_DOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_UP)
  CASE_ENUM_STRING(SDL_SCANCODE_NUMLOCKCLEAR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_DIVIDE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MULTIPLY)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MINUS)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_PLUS)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_ENTER)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_1)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_2)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_3)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_4)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_5)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_6)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_7)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_8)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_9)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_0)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_PERIOD)
  CASE_ENUM_STRING(SDL_SCANCODE_NONUSBACKSLASH)
  CASE_ENUM_STRING(SDL_SCANCODE_APPLICATION)
  CASE_ENUM_STRING(SDL_SCANCODE_POWER)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_EQUALS)
  CASE_ENUM_STRING(SDL_SCANCODE_F13)
  CASE_ENUM_STRING(SDL_SCANCODE_F14)
  CASE_ENUM_STRING(SDL_SCANCODE_F15)
  CASE_ENUM_STRING(SDL_SCANCODE_F16)
  CASE_ENUM_STRING(SDL_SCANCODE_F17)
  CASE_ENUM_STRING(SDL_SCANCODE_F18)
  CASE_ENUM_STRING(SDL_SCANCODE_F19)
  CASE_ENUM_STRING(SDL_SCANCODE_F20)
  CASE_ENUM_STRING(SDL_SCANCODE_F21)
  CASE_ENUM_STRING(SDL_SCANCODE_F22)
  CASE_ENUM_STRING(SDL_SCANCODE_F23)
  CASE_ENUM_STRING(SDL_SCANCODE_F24)
  CASE_ENUM_STRING(SDL_SCANCODE_EXECUTE)
  CASE_ENUM_STRING(SDL_SCANCODE_HELP)
  CASE_ENUM_STRING(SDL_SCANCODE_MENU)
  CASE_ENUM_STRING(SDL_SCANCODE_SELECT)
  CASE_ENUM_STRING(SDL_SCANCODE_STOP)
  CASE_ENUM_STRING(SDL_SCANCODE_AGAIN)
  CASE_ENUM_STRING(SDL_SCANCODE_UNDO)
  CASE_ENUM_STRING(SDL_SCANCODE_CUT)
  CASE_ENUM_STRING(SDL_SCANCODE_COPY)
  CASE_ENUM_STRING(SDL_SCANCODE_PASTE)
  CASE_ENUM_STRING(SDL_SCANCODE_FIND)
  CASE_ENUM_STRING(SDL_SCANCODE_MUTE)
  CASE_ENUM_STRING(SDL_SCANCODE_VOLUMEUP)
  CASE_ENUM_STRING(SDL_SCANCODE_VOLUMEDOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_COMMA)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_EQUALSAS400)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL1)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL2)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL3)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL4)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL5)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL6)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL7)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL8)
  CASE_ENUM_STRING(SDL_SCANCODE_INTERNATIONAL9)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG1)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG2)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG3)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG4)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG5)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG6)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG7)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG8)
  CASE_ENUM_STRING(SDL_SCANCODE_LANG9)
  CASE_ENUM_STRING(SDL_SCANCODE_ALTERASE)
  CASE_ENUM_STRING(SDL_SCANCODE_SYSREQ)
  CASE_ENUM_STRING(SDL_SCANCODE_CANCEL)
  CASE_ENUM_STRING(SDL_SCANCODE_CLEAR)
  CASE_ENUM_STRING(SDL_SCANCODE_PRIOR)
  CASE_ENUM_STRING(SDL_SCANCODE_RETURN2)
  CASE_ENUM_STRING(SDL_SCANCODE_SEPARATOR)
  CASE_ENUM_STRING(SDL_SCANCODE_OUT)
  CASE_ENUM_STRING(SDL_SCANCODE_OPER)
  CASE_ENUM_STRING(SDL_SCANCODE_CLEARAGAIN)
  CASE_ENUM_STRING(SDL_SCANCODE_CRSEL)
  CASE_ENUM_STRING(SDL_SCANCODE_EXSEL)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_00)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_000)
  CASE_ENUM_STRING(SDL_SCANCODE_THOUSANDSSEPARATOR)
  CASE_ENUM_STRING(SDL_SCANCODE_DECIMALSEPARATOR)
  CASE_ENUM_STRING(SDL_SCANCODE_CURRENCYUNIT)
  CASE_ENUM_STRING(SDL_SCANCODE_CURRENCYSUBUNIT)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_LEFTPAREN)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_RIGHTPAREN)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_LEFTBRACE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_RIGHTBRACE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_TAB)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_BACKSPACE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_A)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_B)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_C)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_D)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_E)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_F)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_XOR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_POWER)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_PERCENT)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_LESS)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_GREATER)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_AMPERSAND)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_DBLAMPERSAND)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_VERTICALBAR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_DBLVERTICALBAR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_COLON)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_HASH)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_SPACE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_AT)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_EXCLAM)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMSTORE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMRECALL)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMCLEAR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMADD)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMSUBTRACT)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMMULTIPLY)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_MEMDIVIDE)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_PLUSMINUS)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_CLEAR)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_CLEARENTRY)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_BINARY)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_OCTAL)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_DECIMAL)
  CASE_ENUM_STRING(SDL_SCANCODE_KP_HEXADECIMAL)
  CASE_ENUM_STRING(SDL_SCANCODE_LCTRL)
  CASE_ENUM_STRING(SDL_SCANCODE_LSHIFT)
  CASE_ENUM_STRING(SDL_SCANCODE_LALT)
  CASE_ENUM_STRING(SDL_SCANCODE_LGUI)
  CASE_ENUM_STRING(SDL_SCANCODE_RCTRL)
  CASE_ENUM_STRING(SDL_SCANCODE_RSHIFT)
  CASE_ENUM_STRING(SDL_SCANCODE_RALT)
  CASE_ENUM_STRING(SDL_SCANCODE_RGUI)
  CASE_ENUM_STRING(SDL_SCANCODE_MODE)
  CASE_ENUM_STRING(SDL_SCANCODE_AUDIONEXT)
  CASE_ENUM_STRING(SDL_SCANCODE_AUDIOPREV)
  CASE_ENUM_STRING(SDL_SCANCODE_AUDIOSTOP)
  CASE_ENUM_STRING(SDL_SCANCODE_AUDIOPLAY)
  CASE_ENUM_STRING(SDL_SCANCODE_AUDIOMUTE)
  CASE_ENUM_STRING(SDL_SCANCODE_MEDIASELECT)
  CASE_ENUM_STRING(SDL_SCANCODE_WWW)
  CASE_ENUM_STRING(SDL_SCANCODE_MAIL)
  CASE_ENUM_STRING(SDL_SCANCODE_CALCULATOR)
  CASE_ENUM_STRING(SDL_SCANCODE_COMPUTER)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_SEARCH)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_HOME)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_BACK)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_FORWARD)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_STOP)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_REFRESH)
  CASE_ENUM_STRING(SDL_SCANCODE_AC_BOOKMARKS)
  CASE_ENUM_STRING(SDL_SCANCODE_BRIGHTNESSDOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_BRIGHTNESSUP)
  CASE_ENUM_STRING(SDL_SCANCODE_DISPLAYSWITCH)
  CASE_ENUM_STRING(SDL_SCANCODE_KBDILLUMTOGGLE)
  CASE_ENUM_STRING(SDL_SCANCODE_KBDILLUMDOWN)
  CASE_ENUM_STRING(SDL_SCANCODE_KBDILLUMUP)
  CASE_ENUM_STRING(SDL_SCANCODE_EJECT)
  CASE_ENUM_STRING(SDL_SCANCODE_SLEEP)
  CASE_ENUM_STRING(SDL_SCANCODE_APP1)
  CASE_ENUM_STRING(SDL_SCANCODE_APP2)

  default: return u8"Bad SDL_Scancode";
  }
}

char const* sdlxvulkan::to_c_string(SDL_GameControllerButton a_game_controller_button) noexcept
{
  switch (a_game_controller_button)
  {
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_INVALID)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_A)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_B)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_X)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_Y)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_BACK)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_GUIDE)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_START)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_LEFTSTICK)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_RIGHTSTICK)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_DPAD_UP)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_DPAD_DOWN)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_DPAD_LEFT)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
  CASE_ENUM_STRING(SDL_CONTROLLER_BUTTON_MAX)

  default:  return u8"Bad SDL_GameControllerButton";
  }
}

char const* sdlxvulkan::mouse_button_to_c_string(Uint8 a_button) noexcept
{
  // not an enum, macro values....
  switch (a_button)
  {
  case SDL_BUTTON_LEFT: return u8"SDL_BUTTON_LEFT";
  case SDL_BUTTON_MIDDLE: return u8"SDL_BUTTON_MIDDLE";
  case SDL_BUTTON_RIGHT: return u8"SDL_BUTTON_RIGHT";
  case SDL_BUTTON_X1: return u8"SDL_BUTTON_X1";
  case SDL_BUTTON_X2: return u8"SDL_BUTTON_X2";

  default:
    assert(false); 
    return u8"Bad Mouse Button";
  }
}

char const* sdlxvulkan::mouse_button_mask_to_c_string(Uint32 a_button) noexcept
{
  // not an enum, macro values....
  switch (a_button)
  {
  case SDL_BUTTON_LMASK: return u8"SDL_BUTTON_LEFT";
  case SDL_BUTTON_MMASK: return u8"SDL_BUTTON_MIDDLE";
  case SDL_BUTTON_RMASK: return u8"SDL_BUTTON_RIGHT";
  case SDL_BUTTON_X1MASK: return u8"SDL_BUTTON_X1";
  case SDL_BUTTON_X2MASK: return u8"SDL_BUTTON_X2";

  default:  
    assert(false);
    return u8"Bad Mouse Button";
  }
}

std::string sdlxvulkan::to_std_string(SDL_EventType a_event_type)
{
  return std::string{ to_c_string(a_event_type) };
}

std::string sdlxvulkan::to_std_string(SDL_WindowEventID a_event_id)
{
  return std::string{ to_c_string(a_event_id) };
}
/*
std::string sdlxvulkan::to_std_string(SDL_Keycode a_keycode)
{
  return std::string{ to_c_string(a_keycode) };
}
*/
std::string sdlxvulkan::to_std_string(SDL_Keymod a_keymod)
{
  return std::string{ to_c_string(a_keymod) };
}

std::string sdlxvulkan::to_std_string(SDL_Scancode a_scancode)
{
  return std::string{ to_c_string(a_scancode) };
}

std::string sdlxvulkan::to_std_string(SDL_GameControllerButton a_game_controller_button)
{
  return std::string{ to_c_string(a_game_controller_button) };
}

//#define FLAG_TEST_CONCAT(a_arg, a_flag)

#define KEYMOD_FLAG_TEST(a_flag) \
if (a_keymod & a_flag) \
{ \
  l_result += to_c_string(a_flag); \
  l_result.push_back(u8' '); \
}

std::string sdlxvulkan::all_keymods(Uint16 a_keymod)
{
  std::string l_result{};

  KEYMOD_FLAG_TEST(KMOD_LSHIFT)
  KEYMOD_FLAG_TEST(KMOD_RSHIFT)
  KEYMOD_FLAG_TEST(KMOD_LCTRL)
  KEYMOD_FLAG_TEST(KMOD_RCTRL)
  KEYMOD_FLAG_TEST(KMOD_LALT)
  KEYMOD_FLAG_TEST(KMOD_RALT)
  KEYMOD_FLAG_TEST(KMOD_LGUI)
  KEYMOD_FLAG_TEST(KMOD_RGUI)
  KEYMOD_FLAG_TEST(KMOD_NUM)
  KEYMOD_FLAG_TEST(KMOD_CAPS)
  KEYMOD_FLAG_TEST(KMOD_MODE)

  return l_result;
}

#define MOUSE_BUTTON_MASK_TEST(a_mask) \
if (a_state & a_mask) \
{ \
  l_result += mouse_button_mask_to_c_string(a_mask); \
  l_result.push_back(u8' '); \
}

std::string sdlxvulkan::all_mouse_buttons(Uint32 a_state)
{
  std::string l_result{};

  MOUSE_BUTTON_MASK_TEST(SDL_BUTTON_LMASK)
  MOUSE_BUTTON_MASK_TEST(SDL_BUTTON_MMASK)
  MOUSE_BUTTON_MASK_TEST(SDL_BUTTON_RMASK)
  MOUSE_BUTTON_MASK_TEST(SDL_BUTTON_X1MASK)
  MOUSE_BUTTON_MASK_TEST(SDL_BUTTON_X2MASK)

  return l_result;
}