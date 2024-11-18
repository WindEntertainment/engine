#include "wind/dom/shadow-dom/components/text.hpp"

namespace wind::dom::shadow {
  Text::Text() : UIElementCRTP(attributes::defaultTextAttributes) {};
  Text::Text(const unsigned int id)
      : UIElementCRTP(attributes::defaultTextAttributes, id) {};
} // namespace wind::dom::shadow
