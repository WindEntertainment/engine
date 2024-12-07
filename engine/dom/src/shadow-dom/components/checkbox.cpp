#include "wind/dom/shadow-dom/components/checkbox.hpp"

namespace wind::dom::shadow {
  Checkbox::Checkbox() : id(++nextId) { attributes.position = {0, 0}; };
  Checkbox::Checkbox(unsigned int id) : id(id) {
    attributes.position = {0, 0};
  };
} // namespace wind::dom::shadow
