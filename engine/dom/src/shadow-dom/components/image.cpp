#include "wind/dom/shadow-dom/components/image.hpp"

namespace wind::dom::shadow {
  Image::Image() : UIElementCRTP(attributes::defaultImageAttributes) {};
  Image::Image(const unsigned int id)
      : UIElementCRTP(attributes::defaultImageAttributes, id) {};
} // namespace wind::dom::shadow
