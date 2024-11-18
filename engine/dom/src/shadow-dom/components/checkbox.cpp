#include "wind/dom/shadow-dom/components/checkbox.hpp"

namespace wind::dom::shadow {
  Checkbox::Checkbox()
      : UIElementCRTP(attributes::defaultCheckboxAttributes) {};
  Checkbox::Checkbox(const unsigned int id)
      : UIElementCRTP(attributes::defaultCheckboxAttributes, id) {};
} // namespace wind::dom::shadow
