#include "wind/input-system/keys.hpp"
#include "wind/utils/includes.hpp"

namespace wind {

  KeyAction mapStringToKeyAction(std::string action) {
    static std::map<std::string, KeyAction> const table = {
      {"Released", KeyAction::Released},
      {"Pressed", KeyAction::Pressed},
      {"Held", KeyAction::Held},
    };

    if (table.contains(action))
      return table.at(action);

    return KeyAction::Unknown;
  };

  Keycode mapStringToKeycode(std::string key) {
    static std::map<std::string, Keycode> const table = {
      {"Unknown", Keycode::Unknown},
      {"Return", Keycode::K_Return},
      {"Escape", Keycode::K_Escape},
      {"Backspace", Keycode::K_Backspace},
      {"Tab", Keycode::K_Tab},
      {"Space", Keycode::K_Space},
      {"Exclaim", Keycode::K_Exclaim},
      {"QuoteDbl", Keycode::K_QuoteDbl},
      {"Hash", Keycode::K_Hash},
      {"Percent", Keycode::K_Percent},
      {"Dollar", Keycode::K_Dollar},
      {"Ampersand", Keycode::K_Ampersand},
      {"Quote", Keycode::K_Quote},
      {"LeftParen", Keycode::K_LeftParen},
      {"RightParen", Keycode::K_RightParen},
      {"Asterisk", Keycode::K_Asterisk},
      {"Plus", Keycode::K_Plus},
      {"Comma", Keycode::K_Comma},
      {"Minus", Keycode::K_Minus},
      {"Period", Keycode::K_Period},
      {"Slash", Keycode::K_Slash},
      {"Num0", Keycode::K_0},
      {"Num1", Keycode::K_1},
      {"Num2", Keycode::K_2},
      {"Num3", Keycode::K_3},
      {"Num4", Keycode::K_4},
      {"Num5", Keycode::K_5},
      {"Num6", Keycode::K_6},
      {"Num7", Keycode::K_7},
      {"Num8", Keycode::K_8},
      {"Num9", Keycode::K_9},
      {"Colon", Keycode::K_Colon},
      {"Semicolon", Keycode::K_Semicolon},
      {"Less", Keycode::K_Less},
      {"Equals", Keycode::K_Equals},
      {"Greater", Keycode::K_Greater},
      {"Question", Keycode::K_Question},
      {"At", Keycode::K_At},
      {"LeftBracket", Keycode::K_LeftBracket},
      {"Backslash", Keycode::K_Backslash},
      {"RightBracket", Keycode::K_RightBracket},
      {"Caret", Keycode::K_Caret},
      {"Underscore", Keycode::K_Underscore},
      {"BackQuote", Keycode::K_BackQuote},
      {"A", Keycode::K_A},
      {"B", Keycode::K_B},
      {"C", Keycode::K_C},
      {"D", Keycode::K_D},
      {"E", Keycode::K_E},
      {"F", Keycode::K_F},
      {"G", Keycode::K_G},
      {"H", Keycode::K_H},
      {"I", Keycode::K_I},
      {"J", Keycode::K_J},
      {"K", Keycode::K_K},
      {"L", Keycode::K_L},
      {"M", Keycode::K_M},
      {"N", Keycode::K_N},
      {"O", Keycode::K_O},
      {"P", Keycode::K_P},
      {"Q", Keycode::K_Q},
      {"R", Keycode::K_R},
      {"S", Keycode::K_S},
      {"T", Keycode::K_T},
      {"U", Keycode::K_U},
      {"V", Keycode::K_V},
      {"W", Keycode::K_W},
      {"X", Keycode::K_X},
      {"Y", Keycode::K_Y},
      {"Z", Keycode::K_Z},
      {"CapsLock", Keycode::K_CapsLock},
      {"F1", Keycode::K_F1},
      {"F2", Keycode::K_F2},
      {"F3", Keycode::K_F3},
      {"F4", Keycode::K_F4},
      {"F5", Keycode::K_F5},
      {"F6", Keycode::K_F6},
      {"F7", Keycode::K_F7},
      {"F8", Keycode::K_F8},
      {"F9", Keycode::K_F9},
      {"F10", Keycode::K_F10},
      {"F11", Keycode::K_F11},
      {"F12", Keycode::K_F12},
      {"PrintScreen", Keycode::K_PrintScreen},
      {"ScrollLock", Keycode::K_ScrollLock},
      {"Pause", Keycode::K_Pause},
      {"Insert", Keycode::K_Insert},
      {"Home", Keycode::K_Home},
      {"PageUp", Keycode::K_PageUp},
      {"Delete", Keycode::K_Delete},
      {"End", Keycode::K_End},
      {"PageDown", Keycode::K_PageDown},
      {"Right", Keycode::K_Right},
      {"Left", Keycode::K_Left},
      {"Down", Keycode::K_Down},
      {"Up", Keycode::K_Up},
      {"NumLockClear", Keycode::K_NumLockClear},
      {"KpDivide", Keycode::K_KpDivide},
      {"KpMultiply", Keycode::K_KpMultiply},
      {"KpMinus", Keycode::K_KpMinus},
      {"KpPlus", Keycode::K_KpPlus},
      {"KpEnter", Keycode::K_KpEnter},
      {"Kp1", Keycode::K_Kp1},
      {"Kp2", Keycode::K_Kp2},
      {"Kp3", Keycode::K_Kp3},
      {"Kp4", Keycode::K_Kp4},
      {"Kp5", Keycode::K_Kp5},
      {"Kp6", Keycode::K_Kp6},
      {"Kp7", Keycode::K_Kp7},
      {"Kp8", Keycode::K_Kp8},
      {"Kp9", Keycode::K_Kp9},
      {"Kp0", Keycode::K_Kp0},
      {"KpPeriod", Keycode::K_KpPeriod},
      {"Application", Keycode::K_Application},
      {"Power", Keycode::K_Power},
      {"KpEquals", Keycode::K_KpEquals},
      {"F13", Keycode::K_F13},
      {"F14", Keycode::K_F14},
      {"F15", Keycode::K_F15},
      {"F16", Keycode::K_F16},
      {"F17", Keycode::K_F17},
      {"F18", Keycode::K_F18},
      {"F19", Keycode::K_F19},
      {"F20", Keycode::K_F20},
      {"F21", Keycode::K_F21},
      {"F22", Keycode::K_F22},
      {"F23", Keycode::K_F23},
      {"F24", Keycode::K_F24},
      {"Execute", Keycode::K_Execute},
      {"Help", Keycode::K_Help},
      {"Menu", Keycode::K_Menu},
      {"Select", Keycode::K_Select},
      {"Stop", Keycode::K_Stop},
      {"Again", Keycode::K_Again},
      {"Undo", Keycode::K_Undo},
      {"Cut", Keycode::K_Cut},
      {"Copy", Keycode::K_Copy},
      {"Paste", Keycode::K_Paste},
      {"Find", Keycode::K_Find},
      {"Mute", Keycode::K_Mute},
      {"VolumeUp", Keycode::K_VolumeUp},
      {"VolumeDown", Keycode::K_VolumeDown},
      {"KpComma", Keycode::K_KpComma},
      {"KpEqualsAs400", Keycode::K_KpEqualsAs400},
      {"AltErase", Keycode::K_AltErase},
      {"SysReq", Keycode::K_SysReq},
      {"Cancel", Keycode::K_Cancel},
      {"Clear", Keycode::K_Clear},
      {"Prior", Keycode::K_Prior},
      {"Return2", Keycode::K_Return2},
      {"Separator", Keycode::K_Separator},
      {"Out", Keycode::K_Out},
      {"Oper", Keycode::K_Oper},
      {"ClearAgain", Keycode::K_ClearAgain},
      {"Crsel", Keycode::K_Crsel},
      {"Exsel", Keycode::K_Exsel},
      {"Kp00", Keycode::K_Kp00},
      {"Kp000", Keycode::K_Kp000},
      {"ThousandsSeparator", Keycode::K_ThousandsSeparator},
      {"DecimalSeparator", Keycode::K_DecimalSeparator},
      {"CurrencyUnit", Keycode::K_CurrencyUnit},
      {"CurrencySubUnit", Keycode::K_CurrencySubUnit},
      {"KpLeftParen", Keycode::K_KpLeftParen},
      {"KpRightParen", Keycode::K_KpRightParen},
      {"KpLeftBrace", Keycode::K_KpLeftBrace},
      {"KpRightBrace", Keycode::K_KpRightBrace},
      {"KpTab", Keycode::K_KpTab},
      {"KpBackspace", Keycode::K_KpBackspace},
      {"KpA", Keycode::K_KpA},
      {"KpB", Keycode::K_KpB},
      {"KpC", Keycode::K_KpC},
      {"KpD", Keycode::K_KpD},
      {"KpE", Keycode::K_KpE},
      {"KpF", Keycode::K_KpF},
      {"KpXor", Keycode::K_KpXor},
      {"KpPower", Keycode::K_KpPower},
      {"KpPercent", Keycode::K_KpPercent},
      {"KpLess", Keycode::K_KpLess},
      {"KpGreater", Keycode::K_KpGreater},
      {"KpAmpersand", Keycode::K_KpAmpersand},
      {"KpDblAmpersand", Keycode::K_KpDblAmpersand},
      {"KpVerticalBar", Keycode::K_KpVerticalBar},
      {"KpDblVerticalBar", Keycode::K_KpDblVerticalBar},
      {"KpColon", Keycode::K_KpColon},
      {"KpHash", Keycode::K_KpHash},
      {"KpSpace", Keycode::K_KpSpace},
      {"KpAt", Keycode::K_KpAt},
      {"KpExclam", Keycode::K_KpExclam},
      {"KpMemStore", Keycode::K_KpMemStore},
      {"KpMemRecall", Keycode::K_KpMemRecall},
      {"KpMemClear", Keycode::K_KpMemClear},
      {"KpMemAdd", Keycode::K_KpMemAdd},
      {"KpMemSubtract", Keycode::K_KpMemSubtract},
      {"KpMemMultiply", Keycode::K_KpMemMultiply},
      {"KpMemDivide", Keycode::K_KpMemDivide},
      {"KpPlusMinus", Keycode::K_KpPlusMinus},
      {"KpClear", Keycode::K_KpClear},
      {"KpClearEntry", Keycode::K_KpClearEntry},
      {"KpBinary", Keycode::K_KpBinary},
      {"KpOctal", Keycode::K_KpOctal},
      {"KpDecimal", Keycode::K_KpDecimal},
      {"KpHexadecimal", Keycode::K_KpHexadecimal},
      {"LeftCtrl", Keycode::K_LeftCtrl},
      {"LeftShift", Keycode::K_LeftShift},
      {"LeftAlt", Keycode::K_LeftAlt},
      {"LeftGui", Keycode::K_LeftGui},
      {"RightCtrl", Keycode::K_RightCtrl},
      {"RightShift", Keycode::K_RightShift},
      {"RightAlt", Keycode::K_RightAlt},
      {"RightGui", Keycode::K_RightGui},
      {"Mode", Keycode::K_Mode},
      {"AudioNext", Keycode::K_AudioNext},
      {"AudioPrev", Keycode::K_AudioPrev},
      {"AudioStop", Keycode::K_AudioStop},
      {"AudioPlay", Keycode::K_AudioPlay},
      {"AudioMute", Keycode::K_AudioMute},
      {"MediaSelect", Keycode::K_MediaSelect},
      {"Www", Keycode::K_Www},
      {"Mail", Keycode::K_Mail},
      {"Calculator", Keycode::K_Calculator},
      {"Computer", Keycode::K_Computer},
      {"AcSearch", Keycode::K_AcSearch},
      {"AcHome", Keycode::K_AcHome},
      {"AcBack", Keycode::K_AcBack},
      {"AcForward", Keycode::K_AcForward},
      {"AcStop", Keycode::K_AcStop},
      {"AcRefresh", Keycode::K_AcRefresh},
      {"AcBookmarks", Keycode::K_AcBookmarks},
      {"BrightnessDown", Keycode::K_BrightnessDown},
      {"BrightnessUp", Keycode::K_BrightnessUp},
      {"DisplaySwitch", Keycode::K_DisplaySwitch},
      {"KbdillumToggle", Keycode::K_KbdillumToggle},
      {"KbdillumDown", Keycode::K_KbdillumDown},
      {"KbdillumuUp", Keycode::K_KbdillumuUp},
      {"Eject", Keycode::K_Eject},
      {"Sleep", Keycode::K_Sleep}
    };

    if (table.contains(key))
      return table.at(key);

    return Keycode::Unknown;
  }

  KeyAction mapSDLActionToKeyAction(int action) {
    static std::map<int, KeyAction> const table = {
      {SDL_KEYUP, KeyAction::Released}, {SDL_KEYDOWN, KeyAction::Pressed}
    };

    if (table.contains(action))
      return table.at(action);

    return KeyAction::Unknown;
  };

  Key mapSDLMouseCodeToKey(int key, int action) {
    static std::map<int, Keycode> const table = {
      {SDL_BUTTON_LEFT, Keycode::M_ButtonLeft},
      {SDL_BUTTON_MIDDLE, Keycode::M_ButtonMiddle},
      {SDL_BUTTON_RIGHT, Keycode::M_ButtonRight}
    };

    if (table.contains(key))
      return Key{
        .keycode = table.at(key), .action = mapSDLActionToKeyAction(action)
      };

    return Key{.keycode = Keycode::Unknown, .action = KeyAction::Unknown};
  }

  wind::Keycode mapSdlButtonToKeyCode(Uint8 button) {
    static std::map<SDL_Keycode, wind::Keycode> sdlButtonToKeycode = {
      {SDL_BUTTON_LEFT, wind::Keycode::M_ButtonLeft},
      {SDL_BUTTON_RIGHT, wind::Keycode::M_ButtonRight},
      {SDL_BUTTON_MIDDLE, wind::Keycode::M_ButtonMiddle},
    };

    if (sdlButtonToKeycode.contains(button))
      return sdlButtonToKeycode[button];
    return wind::Keycode::Unknown;
  }

  wind::Keycode mapSdlKeyToKeycode(SDL_Keycode key) {
    static std::map<SDL_Keycode, wind::Keycode> sdlKeyToKeycode = {
      {SDLK_UNKNOWN, wind::Keycode::Unknown},
      {SDLK_RETURN, wind::Keycode::K_Return},
      {SDLK_ESCAPE, wind::Keycode::K_Escape},
      {SDLK_BACKSPACE, wind::Keycode::K_Backspace},
      {SDLK_TAB, wind::Keycode::K_Tab},
      {SDLK_SPACE, wind::Keycode::K_Space},
      {SDLK_EXCLAIM, wind::Keycode::K_Exclaim},
      {SDLK_QUOTEDBL, wind::Keycode::K_QuoteDbl},
      {SDLK_HASH, wind::Keycode::K_Hash},
      {SDLK_PERCENT, wind::Keycode::K_Percent},
      {SDLK_DOLLAR, wind::Keycode::K_Dollar},
      {SDLK_AMPERSAND, wind::Keycode::K_Ampersand},
      {SDLK_QUOTE, wind::Keycode::K_Quote},
      {SDLK_LEFTPAREN, wind::Keycode::K_LeftParen},
      {SDLK_RIGHTPAREN, wind::Keycode::K_RightParen},
      {SDLK_ASTERISK, wind::Keycode::K_Asterisk},
      {SDLK_PLUS, wind::Keycode::K_Plus},
      {SDLK_COMMA, wind::Keycode::K_Comma},
      {SDLK_MINUS, wind::Keycode::K_Minus},
      {SDLK_PERIOD, wind::Keycode::K_Period},
      {SDLK_SLASH, wind::Keycode::K_Slash},
      {SDLK_0, wind::Keycode::K_0},
      {SDLK_1, wind::Keycode::K_1},
      {SDLK_2, wind::Keycode::K_2},
      {SDLK_3, wind::Keycode::K_3},
      {SDLK_4, wind::Keycode::K_4},
      {SDLK_5, wind::Keycode::K_5},
      {SDLK_6, wind::Keycode::K_6},
      {SDLK_7, wind::Keycode::K_7},
      {SDLK_8, wind::Keycode::K_8},
      {SDLK_9, wind::Keycode::K_9},
      {SDLK_COLON, wind::Keycode::K_Colon},
      {SDLK_SEMICOLON, wind::Keycode::K_Semicolon},
      {SDLK_LESS, wind::Keycode::K_Less},
      {SDLK_EQUALS, wind::Keycode::K_Equals},
      {SDLK_GREATER, wind::Keycode::K_Greater},
      {SDLK_QUESTION, wind::Keycode::K_Question},
      {SDLK_AT, wind::Keycode::K_At},
      {SDLK_LEFTBRACKET, wind::Keycode::K_LeftBracket},
      {SDLK_BACKSLASH, wind::Keycode::K_Backslash},
      {SDLK_RIGHTBRACKET, wind::Keycode::K_RightBracket},
      {SDLK_CARET, wind::Keycode::K_Caret},
      {SDLK_UNDERSCORE, wind::Keycode::K_Underscore},
      {SDLK_BACKQUOTE, wind::Keycode::K_BackQuote},
      {SDLK_a, wind::Keycode::K_A},
      {SDLK_b, wind::Keycode::K_B},
      {SDLK_c, wind::Keycode::K_C},
      {SDLK_d, wind::Keycode::K_D},
      {SDLK_e, wind::Keycode::K_E},
      {SDLK_f, wind::Keycode::K_F},
      {SDLK_g, wind::Keycode::K_G},
      {SDLK_h, wind::Keycode::K_H},
      {SDLK_i, wind::Keycode::K_I},
      {SDLK_j, wind::Keycode::K_J},
      {SDLK_k, wind::Keycode::K_K},
      {SDLK_l, wind::Keycode::K_L},
      {SDLK_m, wind::Keycode::K_M},
      {SDLK_n, wind::Keycode::K_N},
      {SDLK_o, wind::Keycode::K_O},
      {SDLK_p, wind::Keycode::K_P},
      {SDLK_q, wind::Keycode::K_Q},
      {SDLK_r, wind::Keycode::K_R},
      {SDLK_s, wind::Keycode::K_S},
      {SDLK_t, wind::Keycode::K_T},
      {SDLK_u, wind::Keycode::K_U},
      {SDLK_v, wind::Keycode::K_V},
      {SDLK_w, wind::Keycode::K_W},
      {SDLK_x, wind::Keycode::K_X},
      {SDLK_y, wind::Keycode::K_Y},
      {SDLK_z, wind::Keycode::K_Z},
      {SDLK_CAPSLOCK, wind::Keycode::K_CapsLock},
      {SDLK_F1, wind::Keycode::K_F1},
      {SDLK_F2, wind::Keycode::K_F2},
      {SDLK_F3, wind::Keycode::K_F3},
      {SDLK_F4, wind::Keycode::K_F4},
      {SDLK_F5, wind::Keycode::K_F5},
      {SDLK_F6, wind::Keycode::K_F6},
      {SDLK_F7, wind::Keycode::K_F7},
      {SDLK_F8, wind::Keycode::K_F8},
      {SDLK_F9, wind::Keycode::K_F9},
      {SDLK_F10, wind::Keycode::K_F10},
      {SDLK_F11, wind::Keycode::K_F11},
      {SDLK_F12, wind::Keycode::K_F12},
      {SDLK_PRINTSCREEN, wind::Keycode::K_PrintScreen},
      {SDLK_SCROLLLOCK, wind::Keycode::K_ScrollLock},
      {SDLK_PAUSE, wind::Keycode::K_Pause},
      {SDLK_INSERT, wind::Keycode::K_Insert},
      {SDLK_HOME, wind::Keycode::K_Home},
      {SDLK_PAGEUP, wind::Keycode::K_PageUp},
      {SDLK_DELETE, wind::Keycode::K_Delete},
      {SDLK_END, wind::Keycode::K_End},
      {SDLK_PAGEDOWN, wind::Keycode::K_PageDown},
      {SDLK_RIGHT, wind::Keycode::K_Right},
      {SDLK_LEFT, wind::Keycode::K_Left},
      {SDLK_DOWN, wind::Keycode::K_Down},
      {SDLK_UP, wind::Keycode::K_Up},
      {SDLK_NUMLOCKCLEAR, wind::Keycode::K_NumLockClear},
      {SDLK_KP_DIVIDE, wind::Keycode::K_KpDivide},
      {SDLK_KP_MULTIPLY, wind::Keycode::K_KpMultiply},
      {SDLK_KP_MINUS, wind::Keycode::K_KpMinus},
      {SDLK_KP_PLUS, wind::Keycode::K_KpPlus},
      {SDLK_KP_ENTER, wind::Keycode::K_KpEnter},
      {SDLK_KP_1, wind::Keycode::K_Kp1},
      {SDLK_KP_2, wind::Keycode::K_Kp2},
      {SDLK_KP_3, wind::Keycode::K_Kp3},
      {SDLK_KP_4, wind::Keycode::K_Kp4},
      {SDLK_KP_5, wind::Keycode::K_Kp5},
      {SDLK_KP_6, wind::Keycode::K_Kp6},
      {SDLK_KP_7, wind::Keycode::K_Kp7},
      {SDLK_KP_8, wind::Keycode::K_Kp8},
      {SDLK_KP_9, wind::Keycode::K_Kp9},
      {SDLK_KP_0, wind::Keycode::K_Kp0},
      {SDLK_KP_PERIOD, wind::Keycode::K_KpPeriod},
      {SDLK_APPLICATION, wind::Keycode::K_Application},
      {SDLK_POWER, wind::Keycode::K_Power},
      {SDLK_KP_EQUALS, wind::Keycode::K_KpEquals},
      {SDLK_F13, wind::Keycode::K_F13},
      {SDLK_F14, wind::Keycode::K_F14},
      {SDLK_F15, wind::Keycode::K_F15},
      {SDLK_F16, wind::Keycode::K_F16},
      {SDLK_F17, wind::Keycode::K_F17},
      {SDLK_F18, wind::Keycode::K_F18},
      {SDLK_F19, wind::Keycode::K_F19},
      {SDLK_F20, wind::Keycode::K_F20},
      {SDLK_F21, wind::Keycode::K_F21},
      {SDLK_F22, wind::Keycode::K_F22},
      {SDLK_F23, wind::Keycode::K_F23},
      {SDLK_F24, wind::Keycode::K_F24},
      {SDLK_EXECUTE, wind::Keycode::K_Execute},
      {SDLK_HELP, wind::Keycode::K_Help},
      {SDLK_MENU, wind::Keycode::K_Menu},
      {SDLK_SELECT, wind::Keycode::K_Select},
      {SDLK_STOP, wind::Keycode::K_Stop},
      {SDLK_AGAIN, wind::Keycode::K_Again},
      {SDLK_UNDO, wind::Keycode::K_Undo},
      {SDLK_CUT, wind::Keycode::K_Cut},
      {SDLK_COPY, wind::Keycode::K_Copy},
      {SDLK_PASTE, wind::Keycode::K_Paste},
      {SDLK_FIND, wind::Keycode::K_Find},
      {SDLK_MUTE, wind::Keycode::K_Mute},
      {SDLK_VOLUMEUP, wind::Keycode::K_VolumeUp},
      {SDLK_VOLUMEDOWN, wind::Keycode::K_VolumeDown},
      {SDLK_KP_COMMA, wind::Keycode::K_KpComma},
      {SDLK_KP_EQUALSAS400, wind::Keycode::K_KpEqualsAs400},
      {SDLK_ALTERASE, wind::Keycode::K_AltErase},
      {SDLK_SYSREQ, wind::Keycode::K_SysReq},
      {SDLK_CANCEL, wind::Keycode::K_Cancel},
      {SDLK_CLEAR, wind::Keycode::K_Clear},
      {SDLK_PRIOR, wind::Keycode::K_Prior},
      {SDLK_RETURN2, wind::Keycode::K_Return2},
      {SDLK_SEPARATOR, wind::Keycode::K_Separator},
      {SDLK_OUT, wind::Keycode::K_Out},
      {SDLK_OPER, wind::Keycode::K_Oper},
      {SDLK_CLEARAGAIN, wind::Keycode::K_ClearAgain},
      {SDLK_CRSEL, wind::Keycode::K_Crsel},
      {SDLK_EXSEL, wind::Keycode::K_Exsel},
      {SDLK_KP_00, wind::Keycode::K_Kp00},
      {SDLK_KP_000, wind::Keycode::K_Kp000},
      {SDLK_THOUSANDSSEPARATOR, wind::Keycode::K_ThousandsSeparator},
      {SDLK_DECIMALSEPARATOR, wind::Keycode::K_DecimalSeparator},
      {SDLK_CURRENCYUNIT, wind::Keycode::K_CurrencyUnit},
      {SDLK_CURRENCYSUBUNIT, wind::Keycode::K_CurrencySubUnit},
      {SDLK_KP_LEFTPAREN, wind::Keycode::K_KpLeftParen},
      {SDLK_KP_RIGHTPAREN, wind::Keycode::K_KpRightParen},
      {SDLK_KP_LEFTBRACE, wind::Keycode::K_KpLeftBrace},
      {SDLK_KP_RIGHTBRACE, wind::Keycode::K_KpRightBrace},
      {SDLK_KP_TAB, wind::Keycode::K_KpTab},
      {SDLK_KP_BACKSPACE, wind::Keycode::K_KpBackspace},
      {SDLK_KP_A, wind::Keycode::K_KpA},
      {SDLK_KP_B, wind::Keycode::K_KpB},
      {SDLK_KP_C, wind::Keycode::K_KpC},
      {SDLK_KP_D, wind::Keycode::K_KpD},
      {SDLK_KP_E, wind::Keycode::K_KpE},
      {SDLK_KP_F, wind::Keycode::K_KpF},
      {SDLK_KP_XOR, wind::Keycode::K_KpXor},
      {SDLK_KP_POWER, wind::Keycode::K_KpPower},
      {SDLK_KP_PERCENT, wind::Keycode::K_KpPercent},
      {SDLK_KP_LESS, wind::Keycode::K_KpLess},
      {SDLK_KP_GREATER, wind::Keycode::K_KpGreater},
      {SDLK_KP_AMPERSAND, wind::Keycode::K_KpAmpersand},
      {SDLK_KP_DBLAMPERSAND, wind::Keycode::K_KpDblAmpersand},
      {SDLK_KP_VERTICALBAR, wind::Keycode::K_KpVerticalBar},
      {SDLK_KP_DBLVERTICALBAR, wind::Keycode::K_KpDblVerticalBar},
      {SDLK_KP_COLON, wind::Keycode::K_KpColon},
      {SDLK_KP_HASH, wind::Keycode::K_KpHash},
      {SDLK_KP_SPACE, wind::Keycode::K_KpSpace},
      {SDLK_KP_AT, wind::Keycode::K_KpAt},
      {SDLK_KP_EXCLAM, wind::Keycode::K_KpExclam},
      {SDLK_KP_MEMSTORE, wind::Keycode::K_KpMemStore},
      {SDLK_KP_MEMRECALL, wind::Keycode::K_KpMemRecall},
      {SDLK_KP_MEMCLEAR, wind::Keycode::K_KpMemClear},
      {SDLK_KP_MEMADD, wind::Keycode::K_KpMemAdd},
      {SDLK_KP_MEMSUBTRACT, wind::Keycode::K_KpMemSubtract},
      {SDLK_KP_MEMMULTIPLY, wind::Keycode::K_KpMemMultiply},
      {SDLK_KP_MEMDIVIDE, wind::Keycode::K_KpMemDivide},
      {SDLK_KP_PLUSMINUS, wind::Keycode::K_KpPlusMinus},
      {SDLK_KP_CLEAR, wind::Keycode::K_KpClear},
      {SDLK_KP_CLEARENTRY, wind::Keycode::K_KpClearEntry},
      {SDLK_KP_BINARY, wind::Keycode::K_KpBinary},
      {SDLK_KP_OCTAL, wind::Keycode::K_KpOctal},
      {SDLK_KP_DECIMAL, wind::Keycode::K_KpDecimal},
      {SDLK_KP_HEXADECIMAL, wind::Keycode::K_KpHexadecimal},
      {SDLK_LCTRL, wind::Keycode::K_LeftCtrl},
      {SDLK_LSHIFT, wind::Keycode::K_LeftShift},
      {SDLK_LALT, wind::Keycode::K_LeftAlt},
      {SDLK_LGUI, wind::Keycode::K_LeftGui},
      {SDLK_RCTRL, wind::Keycode::K_RightCtrl},
      {SDLK_RSHIFT, wind::Keycode::K_RightShift},
      {SDLK_RALT, wind::Keycode::K_RightAlt},
      {SDLK_RGUI, wind::Keycode::K_RightGui},
      {SDLK_MODE, wind::Keycode::K_Mode},
      {SDLK_AUDIONEXT, wind::Keycode::K_AudioNext},
      {SDLK_AUDIOPREV, wind::Keycode::K_AudioPrev},
      {SDLK_AUDIOSTOP, wind::Keycode::K_AudioStop},
      {SDLK_AUDIOPLAY, wind::Keycode::K_AudioPlay},
      {SDLK_AUDIOMUTE, wind::Keycode::K_AudioMute},
      {SDLK_MEDIASELECT, wind::Keycode::K_MediaSelect},
      {SDLK_WWW, wind::Keycode::K_Www},
      {SDLK_MAIL, wind::Keycode::K_Mail},
      {SDLK_CALCULATOR, wind::Keycode::K_Calculator},
      {SDLK_COMPUTER, wind::Keycode::K_Computer},
      {SDLK_AC_SEARCH, wind::Keycode::K_AcSearch},
      {SDLK_AC_HOME, wind::Keycode::K_AcHome},
      {SDLK_AC_BACK, wind::Keycode::K_AcBack},
      {SDLK_AC_FORWARD, wind::Keycode::K_AcForward},
      {SDLK_AC_STOP, wind::Keycode::K_AcStop},
      {SDLK_AC_REFRESH, wind::Keycode::K_AcRefresh},
      {SDLK_AC_BOOKMARKS, wind::Keycode::K_AcBookmarks},
      {SDLK_BRIGHTNESSDOWN, wind::Keycode::K_BrightnessDown},
      {SDLK_BRIGHTNESSUP, wind::Keycode::K_BrightnessUp},
      {SDLK_DISPLAYSWITCH, wind::Keycode::K_DisplaySwitch},
      {SDLK_KBDILLUMTOGGLE, wind::Keycode::K_KbdillumToggle},
      {SDLK_KBDILLUMDOWN, wind::Keycode::K_KbdillumDown},
      {SDLK_KBDILLUMUP, wind::Keycode::K_KbdillumuUp},
      {SDLK_EJECT, wind::Keycode::K_Eject},
      {SDLK_SLEEP, wind::Keycode::K_Sleep},
    };

    if (sdlKeyToKeycode.contains(key))
      return sdlKeyToKeycode[key];
    return wind::Keycode::Unknown;
  }

  Key mapSDLKeycodeToKey(SDL_Keycode key, int action) {
    static std::unordered_map<SDL_Keycode, Keycode> const table = {
      {SDLK_UNKNOWN, Keycode::Unknown},
      {SDLK_RETURN, Keycode::K_Return},
      {SDLK_ESCAPE, Keycode::K_Escape},
      {SDLK_BACKSPACE, Keycode::K_Backspace},
      {SDLK_TAB, Keycode::K_Tab},
      {SDLK_SPACE, Keycode::K_Space},
      {SDLK_EXCLAIM, Keycode::K_Exclaim},
      {SDLK_QUOTEDBL, Keycode::K_QuoteDbl},
      {SDLK_HASH, Keycode::K_Hash},
      {SDLK_PERCENT, Keycode::K_Percent},
      {SDLK_DOLLAR, Keycode::K_Dollar},
      {SDLK_AMPERSAND, Keycode::K_Ampersand},
      {SDLK_QUOTE, Keycode::K_Quote},
      {SDLK_LEFTPAREN, Keycode::K_LeftParen},
      {SDLK_RIGHTPAREN, Keycode::K_RightParen},
      {SDLK_ASTERISK, Keycode::K_Asterisk},
      {SDLK_PLUS, Keycode::K_Plus},
      {SDLK_COMMA, Keycode::K_Comma},
      {SDLK_MINUS, Keycode::K_Minus},
      {SDLK_PERIOD, Keycode::K_Period},
      {SDLK_SLASH, Keycode::K_Slash},
      {SDLK_0, Keycode::K_0},
      {SDLK_1, Keycode::K_1},
      {SDLK_2, Keycode::K_2},
      {SDLK_3, Keycode::K_3},
      {SDLK_4, Keycode::K_4},
      {SDLK_5, Keycode::K_5},
      {SDLK_6, Keycode::K_6},
      {SDLK_7, Keycode::K_7},
      {SDLK_8, Keycode::K_8},
      {SDLK_9, Keycode::K_9},
      {SDLK_COLON, Keycode::K_Colon},
      {SDLK_SEMICOLON, Keycode::K_Semicolon},
      {SDLK_LESS, Keycode::K_Less},
      {SDLK_EQUALS, Keycode::K_Equals},
      {SDLK_GREATER, Keycode::K_Greater},
      {SDLK_QUESTION, Keycode::K_Question},
      {SDLK_AT, Keycode::K_At},
      {SDLK_LEFTBRACKET, Keycode::K_LeftBracket},
      {SDLK_BACKSLASH, Keycode::K_Backslash},
      {SDLK_RIGHTBRACKET, Keycode::K_RightBracket},
      {SDLK_CARET, Keycode::K_Caret},
      {SDLK_UNDERSCORE, Keycode::K_Underscore},
      {SDLK_BACKQUOTE, Keycode::K_BackQuote},
      {SDLK_a, Keycode::K_A},
      {SDLK_b, Keycode::K_B},
      {SDLK_c, Keycode::K_C},
      {SDLK_d, Keycode::K_D},
      {SDLK_e, Keycode::K_E},
      {SDLK_f, Keycode::K_F},
      {SDLK_g, Keycode::K_G},
      {SDLK_h, Keycode::K_H},
      {SDLK_i, Keycode::K_I},
      {SDLK_j, Keycode::K_J},
      {SDLK_k, Keycode::K_K},
      {SDLK_l, Keycode::K_L},
      {SDLK_m, Keycode::K_M},
      {SDLK_n, Keycode::K_N},
      {SDLK_o, Keycode::K_O},
      {SDLK_p, Keycode::K_P},
      {SDLK_q, Keycode::K_Q},
      {SDLK_r, Keycode::K_R},
      {SDLK_s, Keycode::K_S},
      {SDLK_t, Keycode::K_T},
      {SDLK_u, Keycode::K_U},
      {SDLK_v, Keycode::K_V},
      {SDLK_w, Keycode::K_W},
      {SDLK_x, Keycode::K_X},
      {SDLK_y, Keycode::K_Y},
      {SDLK_z, Keycode::K_Z},
      {SDLK_CAPSLOCK, Keycode::K_CapsLock},
      {SDLK_F1, Keycode::K_F1},
      {SDLK_F2, Keycode::K_F2},
      {SDLK_F3, Keycode::K_F3},
      {SDLK_F4, Keycode::K_F4},
      {SDLK_F5, Keycode::K_F5},
      {SDLK_F6, Keycode::K_F6},
      {SDLK_F7, Keycode::K_F7},
      {SDLK_F8, Keycode::K_F8},
      {SDLK_F9, Keycode::K_F9},
      {SDLK_F10, Keycode::K_F10},
      {SDLK_F11, Keycode::K_F11},
      {SDLK_F12, Keycode::K_F12},
      {SDLK_PRINTSCREEN, Keycode::K_PrintScreen},
      {SDLK_SCROLLLOCK, Keycode::K_ScrollLock},
      {SDLK_PAUSE, Keycode::K_Pause},
      {SDLK_INSERT, Keycode::K_Insert},
      {SDLK_HOME, Keycode::K_Home},
      {SDLK_PAGEUP, Keycode::K_PageUp},
      {SDLK_DELETE, Keycode::K_Delete},
      {SDLK_END, Keycode::K_End},
      {SDLK_PAGEDOWN, Keycode::K_PageDown},
      {SDLK_RIGHT, Keycode::K_Right},
      {SDLK_LEFT, Keycode::K_Left},
      {SDLK_DOWN, Keycode::K_Down},
      {SDLK_UP, Keycode::K_Up},
      {SDLK_NUMLOCKCLEAR, Keycode::K_NumLockClear},
      {SDLK_KP_DIVIDE, Keycode::K_KpDivide},
      {SDLK_KP_MULTIPLY, Keycode::K_KpMultiply},
      {SDLK_KP_MINUS, Keycode::K_KpMinus},
      {SDLK_KP_PLUS, Keycode::K_KpPlus},
      {SDLK_KP_ENTER, Keycode::K_KpEnter},
      {SDLK_KP_1, Keycode::K_Kp1},
      {SDLK_KP_2, Keycode::K_Kp2},
      {SDLK_KP_3, Keycode::K_Kp3},
      {SDLK_KP_4, Keycode::K_Kp4},
      {SDLK_KP_5, Keycode::K_Kp5},
      {SDLK_KP_6, Keycode::K_Kp6},
      {SDLK_KP_7, Keycode::K_Kp7},
      {SDLK_KP_8, Keycode::K_Kp8},
      {SDLK_KP_9, Keycode::K_Kp9},
      {SDLK_KP_0, Keycode::K_Kp0},
      {SDLK_KP_PERIOD, Keycode::K_KpPeriod},
      {SDLK_APPLICATION, Keycode::K_Application},
      {SDLK_POWER, Keycode::K_Power},
      {SDLK_KP_EQUALS, Keycode::K_KpEquals},
      {SDLK_F13, Keycode::K_F13},
      {SDLK_F14, Keycode::K_F14},
      {SDLK_F15, Keycode::K_F15},
      {SDLK_F16, Keycode::K_F16},
      {SDLK_F17, Keycode::K_F17},
      {SDLK_F18, Keycode::K_F18},
      {SDLK_F19, Keycode::K_F19},
      {SDLK_F20, Keycode::K_F20},
      {SDLK_F21, Keycode::K_F21},
      {SDLK_F22, Keycode::K_F22},
      {SDLK_F23, Keycode::K_F23},
      {SDLK_F24, Keycode::K_F24},
      {SDLK_EXECUTE, Keycode::K_Execute},
      {SDLK_HELP, Keycode::K_Help},
      {SDLK_MENU, Keycode::K_Menu},
      {SDLK_SELECT, Keycode::K_Select},
      {SDLK_STOP, Keycode::K_Stop},
      {SDLK_AGAIN, Keycode::K_Again},
      {SDLK_UNDO, Keycode::K_Undo},
      {SDLK_CUT, Keycode::K_Cut},
      {SDLK_COPY, Keycode::K_Copy},
      {SDLK_PASTE, Keycode::K_Paste},
      {SDLK_FIND, Keycode::K_Find},
      {SDLK_MUTE, Keycode::K_Mute},
      {SDLK_VOLUMEUP, Keycode::K_VolumeUp},
      {SDLK_VOLUMEDOWN, Keycode::K_VolumeDown},
      {SDLK_KP_COMMA, Keycode::K_KpComma},
      {SDLK_KP_EQUALSAS400, Keycode::K_KpEqualsAs400},
      {SDLK_ALTERASE, Keycode::K_AltErase},
      {SDLK_SYSREQ, Keycode::K_SysReq},
      {SDLK_CANCEL, Keycode::K_Cancel},
      {SDLK_CLEAR, Keycode::K_Clear},
      {SDLK_PRIOR, Keycode::K_Prior},
      {SDLK_RETURN2, Keycode::K_Return2},
      {SDLK_SEPARATOR, Keycode::K_Separator},
      {SDLK_OUT, Keycode::K_Out},
      {SDLK_OPER, Keycode::K_Oper},
      {SDLK_CLEARAGAIN, Keycode::K_ClearAgain},
      {SDLK_CRSEL, Keycode::K_Crsel},
      {SDLK_EXSEL, Keycode::K_Exsel},
      {SDLK_KP_00, Keycode::K_Kp00},
      {SDLK_KP_000, Keycode::K_Kp000},
      {SDLK_THOUSANDSSEPARATOR, Keycode::K_ThousandsSeparator},
      {SDLK_DECIMALSEPARATOR, Keycode::K_DecimalSeparator},
      {SDLK_CURRENCYUNIT, Keycode::K_CurrencyUnit},
      {SDLK_CURRENCYSUBUNIT, Keycode::K_CurrencySubUnit},
      {SDLK_KP_LEFTPAREN, Keycode::K_KpLeftParen},
      {SDLK_KP_RIGHTPAREN, Keycode::K_KpRightParen},
      {SDLK_KP_LEFTBRACE, Keycode::K_KpLeftBrace},
      {SDLK_KP_RIGHTBRACE, Keycode::K_KpRightBrace},
      {SDLK_KP_TAB, Keycode::K_KpTab},
      {SDLK_KP_BACKSPACE, Keycode::K_KpBackspace},
      {SDLK_KP_A, Keycode::K_KpA},
      {SDLK_KP_B, Keycode::K_KpB},
      {SDLK_KP_C, Keycode::K_KpC},
      {SDLK_KP_D, Keycode::K_KpD},
      {SDLK_KP_E, Keycode::K_KpE},
      {SDLK_KP_F, Keycode::K_KpF},
      {SDLK_KP_XOR, Keycode::K_KpXor},
      {SDLK_KP_POWER, Keycode::K_KpPower},
      {SDLK_KP_PERCENT, Keycode::K_KpPercent},
      {SDLK_KP_LESS, Keycode::K_KpLess},
      {SDLK_KP_GREATER, Keycode::K_KpGreater},
      {SDLK_KP_AMPERSAND, Keycode::K_KpAmpersand},
      {SDLK_KP_DBLAMPERSAND, Keycode::K_KpDblAmpersand},
      {SDLK_KP_VERTICALBAR, Keycode::K_KpVerticalBar},
      {SDLK_KP_DBLVERTICALBAR, Keycode::K_KpDblVerticalBar},
      {SDLK_KP_COLON, Keycode::K_KpColon},
      {SDLK_KP_HASH, Keycode::K_KpHash},
      {SDLK_KP_SPACE, Keycode::K_KpSpace},
      {SDLK_KP_AT, Keycode::K_KpAt},
      {SDLK_KP_EXCLAM, Keycode::K_KpExclam},
      {SDLK_KP_MEMSTORE, Keycode::K_KpMemStore},
      {SDLK_KP_MEMRECALL, Keycode::K_KpMemRecall},
      {SDLK_KP_MEMCLEAR, Keycode::K_KpMemClear},
      {SDLK_KP_MEMADD, Keycode::K_KpMemAdd},
      {SDLK_KP_MEMSUBTRACT, Keycode::K_KpMemSubtract},
      {SDLK_KP_MEMMULTIPLY, Keycode::K_KpMemMultiply},
      {SDLK_KP_MEMDIVIDE, Keycode::K_KpMemDivide},
      {SDLK_KP_PLUSMINUS, Keycode::K_KpPlusMinus},
      {SDLK_KP_CLEAR, Keycode::K_KpClear},
      {SDLK_KP_CLEARENTRY, Keycode::K_KpClearEntry},
      {SDLK_KP_BINARY, Keycode::K_KpBinary},
      {SDLK_KP_OCTAL, Keycode::K_KpOctal},
      {SDLK_KP_DECIMAL, Keycode::K_KpDecimal},
      {SDLK_KP_HEXADECIMAL, Keycode::K_KpHexadecimal},
      {SDLK_LCTRL, Keycode::K_LeftCtrl},
      {SDLK_LSHIFT, Keycode::K_LeftShift},
      {SDLK_LALT, Keycode::K_LeftAlt},
      {SDLK_LGUI, Keycode::K_LeftGui},
      {SDLK_RCTRL, Keycode::K_RightCtrl},
      {SDLK_RSHIFT, Keycode::K_RightShift},
      {SDLK_RALT, Keycode::K_RightAlt},
      {SDLK_RGUI, Keycode::K_RightGui},
      {SDLK_MODE, Keycode::K_Mode},
      {SDLK_AUDIONEXT, Keycode::K_AudioNext},
      {SDLK_AUDIOPREV, Keycode::K_AudioPrev},
      {SDLK_AUDIOSTOP, Keycode::K_AudioStop},
      {SDLK_AUDIOPLAY, Keycode::K_AudioPlay},
      {SDLK_AUDIOMUTE, Keycode::K_AudioMute},
      {SDLK_MEDIASELECT, Keycode::K_MediaSelect},
      {SDLK_WWW, Keycode::K_Www},
      {SDLK_MAIL, Keycode::K_Mail},
      {SDLK_CALCULATOR, Keycode::K_Calculator},
      {SDLK_COMPUTER, Keycode::K_Computer},
      {SDLK_AC_SEARCH, Keycode::K_AcSearch},
      {SDLK_AC_HOME, Keycode::K_AcHome},
      {SDLK_AC_BACK, Keycode::K_AcBack},
      {SDLK_AC_FORWARD, Keycode::K_AcForward},
      {SDLK_AC_STOP, Keycode::K_AcStop},
      {SDLK_AC_REFRESH, Keycode::K_AcRefresh},
      {SDLK_AC_BOOKMARKS, Keycode::K_AcBookmarks},
      {SDLK_BRIGHTNESSDOWN, Keycode::K_BrightnessDown},
      {SDLK_BRIGHTNESSUP, Keycode::K_BrightnessUp},
      {SDLK_DISPLAYSWITCH, Keycode::K_DisplaySwitch},
      {SDLK_KBDILLUMTOGGLE, Keycode::K_KbdillumToggle},
      {SDLK_KBDILLUMDOWN, Keycode::K_KbdillumDown},
      {SDLK_KBDILLUMUP, Keycode::K_KbdillumuUp},
      {SDLK_EJECT, Keycode::K_Eject},
      {SDLK_SLEEP, Keycode::K_Sleep},
    };

    if (table.contains(key))
      return Key{
        .keycode = table.at(key), .action = mapSDLActionToKeyAction(action)
      };

    return Key{.keycode = Keycode::Unknown, .action = KeyAction::Unknown};
  }
} // namespace wind
