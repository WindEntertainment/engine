#include "wind/dom/shadow-dom/components/input.hpp"

namespace wind::dom::shadow {
  Input::Input() : UIElementCRTP(attributes::defaultInputAttributes) {};
  Input::Input(const unsigned int id)
      : UIElementCRTP(attributes::defaultInputAttributes, id) {};
} // namespace wind::dom::shadow
