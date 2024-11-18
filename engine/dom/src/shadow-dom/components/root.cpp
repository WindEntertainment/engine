#include "wind/dom/shadow-dom/components/root.hpp"

namespace wind::dom::shadow {
  Root::Root() {};
  Root::Root(const unsigned int id) : UIElement(id) {};
} // namespace wind::dom::shadow

// namespace wind::dom::shadow {
//   Root::Root() : UIElementCRTP(attributes::defaultRootAttributes) {};
//   Root::Root(const unsigned int id)
//       : UIElementCRTP(attributes::defaultRootAttributes, id) {};
// } // namespace wind::dom::shadow
