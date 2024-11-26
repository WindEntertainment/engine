#pragma once
#include "shared.hpp"
#include "wind/dom/shadow-dom/components/index.hpp"
#include "wind/dom/dom/components/index.hpp"
#include "wind/dom/shadow-dom/shadow-dom.hpp"

namespace wind::dom::shadow {
  struct Diff {
    std::vector<Element> removed;
    std::vector<Element> added;
    std::vector<Element> updated;
    std::vector<std::pair<const unsigned int, Element>> replaced;
  };

  void addDiffChildren(const Element& element, Diff& diff);

  void getDiff(
    std::optional<Element> prevElement,
    std::optional<Element> newElement,
    Diff& diff
  );

  void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff);
} // namespace wind::dom::shadow
