#include "wind/dom/shadow-dom/components/select.hpp"

namespace wind::dom::shadow {
  Select::Select() : id(++nextId) {};
  Select::Select(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
