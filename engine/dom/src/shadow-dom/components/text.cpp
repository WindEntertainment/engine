#include "wind/dom/shadow-dom/components/text.hpp"

namespace wind::dom::shadow {
  Text::Text() : id(++nextId) {};
  Text::Text(unsigned int id) : id(id) {};
} // namespace wind::dom::shadow
