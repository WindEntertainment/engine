#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include "element.hpp"

namespace wind::dom::shadow {
  class Checkbox : public UIElement,
                   public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox();
    Checkbox(const unsigned int id);

    DEEP_COPY(Checkbox, attributes::Checkbox);
    GET_PTR();
    COMPARE(Checkbox);
    ATTRIBUTES(Checkbox, defaultCheckboxAttributes);
  };
} // namespace wind::dom::shadow
