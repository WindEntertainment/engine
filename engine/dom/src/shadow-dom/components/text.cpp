#include "wind/dom/shadow-dom/components/text.hpp"

namespace wind::dom::shadow {
  Text::Text() : UIElement(attributes::defaultTextAttributes) {};
  Text::Text(const unsigned int id)
      : UIElement(attributes::defaultTextAttributes, id) {};
} // namespace wind::dom::shadow
