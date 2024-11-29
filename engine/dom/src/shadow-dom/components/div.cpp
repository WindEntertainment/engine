#include "wind/dom/shadow-dom/components/div.hpp"

namespace wind::dom::shadow {
  Div::Div() : id(++nextId) { attributes.position = {0, 0}; };
  Div::Div(unsigned int id) : id(id) { attributes.position = {0, 0}; };
} // namespace wind::dom::shadow
