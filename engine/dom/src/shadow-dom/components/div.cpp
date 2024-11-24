#include "wind/dom/shadow-dom/components/div.hpp"

namespace wind::dom::shadow {
  Div::Div() : UIElement(attributes::defaultDivAttributes) {};
  Div::Div(const unsigned int id)
      : UIElement(attributes::defaultDivAttributes, id) {};
} // namespace wind::dom::shadow
