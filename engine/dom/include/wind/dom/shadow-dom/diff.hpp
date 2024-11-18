#pragma once
#include "shared.hpp"
#include "wind/dom/shadow-dom/components/index.hpp"
#include "wind/dom/dom/components/index.hpp"

namespace wind::dom::shadow {
  struct Diff {
    std::vector<std::shared_ptr<UIElement>> removed;
    std::vector<std::shared_ptr<UIElement>> added;
    std::vector<std::shared_ptr<UIElement>> updated;
    std::vector<std::pair<const unsigned int, std::shared_ptr<UIElement>>>
      replaced;
  };

  void addDiffChildren(
    std::shared_ptr<wind::dom::shadow::UIElement> element,
    Diff& diff
  );

  void getDiff(
    std::shared_ptr<UIElement> prevElement,
    std::shared_ptr<UIElement> newElement,
    Diff& diff
  );

  void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff);
} // namespace wind::dom::shadow
