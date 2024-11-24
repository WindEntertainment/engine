#include "wind/dom/shadow-dom/components/select.hpp"

namespace wind::dom::shadow {
  Select::Select() : UIElement(attributes::defaultSelectAttributes) {};
  Select::Select(const unsigned int id)
      : UIElement(attributes::defaultSelectAttributes, id) {};
} // namespace wind::dom::shadow
