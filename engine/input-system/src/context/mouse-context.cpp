#include "wind/input-system/mouse-context.hpp"
#include "wind/input-system/keys.hpp"

namespace wind {
  void MouseContext::addPressedButton(Keycode keycode) {
    pressedButtons.insert(keycode);
  };
  void MouseContext::addHeldButton(Keycode keycode) {
    heldButtons.insert(keycode);
  };
  void MouseContext::addReleasedButton(Keycode keycode) {
    releasedButtons.insert(keycode);
  };

  void MouseContext::removePressedButton(Keycode keycode) {
    pressedButtons.erase(keycode);
  };
  void MouseContext::removeHeldButton(Keycode keycode) {
    heldButtons.erase(keycode);
  };
  void MouseContext::removeReleasedButton(Keycode keycode) {
    releasedButtons.erase(keycode);
  };

  void MouseContext::moveCursor(double nextX, double nextY) {
    cursorX = nextX;
    cursorY = nextY;
  }

  void MouseContext::moveScroll(double nextX, double nextY) {
    scrollX = nextX;
    scrollY = nextY;
  }

} // namespace wind
