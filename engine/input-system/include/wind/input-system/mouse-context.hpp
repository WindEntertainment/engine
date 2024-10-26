#pragma once
#include "wind/input-system/keys.hpp"
#include <set>
#include "wind/utils/includes.hpp"

namespace wind {
  struct MouseContext {
    double cursorX;
    double cursorY;
    double scrollX;
    double scrollY;

    std::set<Keycode> pressedButtons;
    std::set<Keycode> heldButtons;
    std::set<Keycode> releasedButtons;

    void addPressedButton(Keycode keycode);
    void addHeldButton(Keycode keycode);
    void addReleasedButton(Keycode keycode);

    void removePressedButton(Keycode keycode);
    void removeHeldButton(Keycode keycode);
    void removeReleasedButton(Keycode keycode);

    void moveCursor(double nextX, double nextY);
    void moveScroll(double nextX, double nextY);
  };
} // namespace wind
