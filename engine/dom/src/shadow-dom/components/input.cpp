#include "wind/dom/shadow-dom/components/input.hpp"

namespace wind::dom::shadow {
  Input::Input() : UIElement(attributes::defaultInputAttributes) {};
  Input::Input(const unsigned int id)
      : UIElement(attributes::defaultInputAttributes, id) {};
} // namespace wind::dom::shadow
