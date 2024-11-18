#include "wind/dom/shadow-dom/components/div.hpp"

namespace wind::dom::shadow {
  Div::Div() : UIElementCRTP(attributes::defaultDivAttributes) {};
  Div::Div(const unsigned int id)
      : UIElementCRTP(attributes::defaultDivAttributes, id) {};
} // namespace wind::dom::shadow
