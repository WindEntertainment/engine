#pragma once
#include "keyboard-context.hpp"
#include "mouse-context.hpp"
#include "utils/includes.hpp"

namespace wind {

  struct InputSystemContext {
    KeyboardContext keyboardContext;
    MouseContext mouseContext;
  };
} // namespace wind
