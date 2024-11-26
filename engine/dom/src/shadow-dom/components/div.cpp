#include "wind/dom/shadow-dom/components/div.hpp"

namespace wind::dom::shadow {
  Div::Div() : id(++nextId) {};
  Div::Div(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
