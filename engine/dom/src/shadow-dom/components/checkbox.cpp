#include "wind/dom/shadow-dom/components/checkbox.hpp"

namespace wind::dom::shadow {
  Checkbox::Checkbox() : UIElement(attributes::defaultCheckboxAttributes) {};
  Checkbox::Checkbox(const unsigned int id)
      : UIElement(attributes::defaultCheckboxAttributes, id) {};
} // namespace wind::dom::shadow
