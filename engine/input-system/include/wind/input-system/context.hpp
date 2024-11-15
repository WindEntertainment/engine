#pragma once
#include "keyboard-context.hpp"
#include "mouse-context.hpp"
#include "wind/utils/includes.hpp"

namespace wind {

  struct InputSystemContext {
    KeyboardContext keyboardContext;
    MouseContext mouseContext;
    Key key;
  };
} // namespace wind
