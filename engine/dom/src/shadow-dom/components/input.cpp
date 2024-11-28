#include "wind/dom/shadow-dom/components/input.hpp"

namespace wind::dom::shadow {
  Input::Input() : id(++nextId) { attributes.position = {0, 0}; };
  Input::Input(unsigned int id) : id(id) { attributes.position = {0, 0}; };
} // namespace wind::dom::shadow
