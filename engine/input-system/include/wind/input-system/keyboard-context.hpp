#pragma once
#include "wind/input-system/keys.hpp"
#include <set>
#include "wind/utils/includes.hpp"

namespace wind {
  struct KeyboardContext {
    std::set<Keycode> pressedKeys;
    std::set<Keycode> heldKeys;
    std::set<Keycode> releasedKeys;
    unsigned int codepoint;

    void setCodepoint(unsigned int codepoint);
    void addPressedKey(Keycode key);
    void addHeldKey(Keycode key);
    void addReleasedKey(Keycode key);

    void removeCodepoint();
    void removePressedKey(Keycode key);
    void removeHeldKey(Keycode key);
    void removeReleasedKey(Keycode key);
  };
} // namespace wind
