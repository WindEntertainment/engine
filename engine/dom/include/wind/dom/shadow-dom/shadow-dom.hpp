#pragma once
#include "shared.hpp"
#include "wind/dom/shadow-dom/components/index.hpp"

namespace wind::dom::shadow {
  std::shared_ptr<Root> init(glm::ivec2);

  template <typename T>
  concept Element = std::is_base_of<UIElement, T>::value;

  template <Element T>
  std::shared_ptr<T> createElement() {
    auto element = std::make_shared<T>();

    return element;
  };
} // namespace wind::dom::shadow
