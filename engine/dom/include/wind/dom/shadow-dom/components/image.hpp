#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Image : public UIElementCRTP<Image, dom::Image, attributes::Image>,
                public std::enable_shared_from_this<Image> {
  public:
    Image();
    Image(const unsigned int id);

    // DEEP_COPY(Image, attributes::Image);
    GET_PTR(Image);
    // COMPARE(Image);
    // ATTRIBUTES(Image, defaultImageAttributes);

    // dom::UIElement::Ptr toReal() {};
    // void updateReal(dom::UIElement::Ptr element) {};
    // std::shared_ptr<attributes::Image> mergeAttributes();
  };
} // namespace wind::dom::shadow
