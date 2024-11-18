#include "wind/dom/shadow-dom/components/select.hpp"

namespace wind::dom::shadow {
  Select::Select() : UIElementCRTP(attributes::defaultSelectAttributes) {};
  Select::Select(const unsigned int id)
      : UIElementCRTP(attributes::defaultSelectAttributes, id) {};
} // namespace wind::dom::shadow
