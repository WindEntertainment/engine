#include "wind/input-system/keyboard-context.hpp"
#include "wind/input-system/keys.hpp"

namespace wind {
  void KeyboardContext::setCodepoint(unsigned int codepoint) {
    this->codepoint = codepoint;
  };
  void KeyboardContext::addPressedKey(Keycode keycode) {
    pressedKeys.insert(keycode);
  };
  void KeyboardContext::addHeldKey(Keycode keycode) {
    heldKeys.insert(keycode);
  };
  void KeyboardContext::addReleasedKey(Keycode keycode) {
    releasedKeys.insert(keycode);
  };

  void KeyboardContext::removeCodepoint() { this->codepoint = 0; };
  void KeyboardContext::removePressedKey(Keycode keycode) {
    pressedKeys.erase(keycode);
  };
  void KeyboardContext::removeHeldKey(Keycode keycode) {
    heldKeys.erase(keycode);
  };
  void KeyboardContext::removeReleasedKey(Keycode keycode) {
    releasedKeys.erase(keycode);
  };

} // namespace wind
