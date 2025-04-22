#include "wind/dom/shadow-dom/components/checkbox.hpp"

namespace wind::dom::shadow {
  Checkbox::Checkbox() : id(++nextId) {};
  Checkbox::Checkbox(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
