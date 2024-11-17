#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Image : public UIElement, public std::enable_shared_from_this<Image> {
  public:
    Image();
    Image(const unsigned int id);

    DEEP_COPY(Image, attributes::Image);
    GET_PTR();
    COMPARE(Image);
    ATTRIBUTES(Image, defaultImageAttributes);
  };
} // namespace wind::dom::shadow
