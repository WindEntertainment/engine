#include "wind/dom/shadow-dom/components/select.hpp"

namespace wind::dom::shadow {
  Select::Select() : id(++nextId) { attributes.position = {0, 0}; };
  Select::Select(unsigned int id) : id(id) { attributes.position = {0, 0}; };
} // namespace wind::dom::shadow
