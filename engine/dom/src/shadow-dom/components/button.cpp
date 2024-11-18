#include "wind/dom/shadow-dom/components/button.hpp"

namespace wind::dom::shadow {
  Button::Button() {};
  Button::Button(const unsigned int id) : UIElement(id) {};

} // namespace wind::dom::shadow

// namespace wind::dom::shadow {
//   Button::Button() : UIElementCRTP(attributes::defaultButtonAttributes) {};
//   Button::Button(const unsigned int id)
//       : UIElementCRTP(attributes::defaultButtonAttributes, id) {};

// } // namespace wind::dom::shadow
