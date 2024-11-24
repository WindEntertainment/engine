#include "wind/dom/shadow-dom/components/image.hpp"

namespace wind::dom::shadow {
  Image::Image() : UIElement(attributes::defaultImageAttributes) {};
  Image::Image(const unsigned int id)
      : UIElement(attributes::defaultImageAttributes, id) {};
} // namespace wind::dom::shadow
