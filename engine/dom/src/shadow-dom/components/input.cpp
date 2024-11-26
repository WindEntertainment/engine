#include "wind/dom/shadow-dom/components/input.hpp"

namespace wind::dom::shadow {
  Input::Input() : id(++nextId) {};
  Input::Input(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
