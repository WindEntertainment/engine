#include "wind/dom/shadow-dom/diff.hpp"
#include <random>
#include <utility>
#include <algorithm>
#include <typeindex>

namespace wind::dom::shadow {
  void addDiffChildren(const Element& elementVariant, Diff& diff) {
    std::visit(
      [&diff](auto element) -> void {
        diff.added.insert(
          diff.added.end(), element->children.begin(), element->children.end()
        );

        for (const auto& childVariant : element->children) {
          std::visit(
            [&diff](auto child) -> void {
              if (child->children.empty())
                return;
              addDiffChildren(child, diff);
            },
            childVariant
          );
        }
      },
      elementVariant
    );
  }

  void getDiff(
    std::optional<Element> prevElement,
    std::optional<Element> newElement,
    Diff& diff
  ) {
    if (!prevElement.has_value() && !newElement.has_value())
      return;

    if (!prevElement.has_value() && newElement.has_value()) {
      std::visit(
        [&diff](auto& elem) -> void {
          diff.added.push_back(elem);
          if (!elem->children.empty()) {
            addDiffChildren(elem, diff);
          }
        },
        newElement.value()
      );

      return;
    }

    if (prevElement.has_value() && !newElement.has_value()) {
      diff.removed.push_back(prevElement.value());
      return;
    }

    std::visit(
      [&diff](auto& prevE, auto& newE) -> void {
        using T = std::decay_t<decltype(prevE)>;
        using V = std::decay_t<decltype(newE)>;
        if (std::is_same_v<T, V> && prevE->id == newE->id) {
          // if (prevE == newE) {
          // if (newE->id == 3) {
          //   /* code */
          //   spdlog::info("DIFF X: {}", newE.attributes.backgroundColor.x);
          // }
          // spdlog::info(newE->id);
          diff.updated.push_back(newE);
          // }
        } else {
          diff.replaced.emplace_back(prevE->id, newE);
          if (!newE->children.empty()) {
            addDiffChildren(newE, diff);
          }
        }

        auto prevChildren = prevE->children;
        auto newChildren = newE->children;

        size_t childrenCount =
          std::max(prevChildren.size(), newChildren.size());

        for (size_t i = 0; i < childrenCount; ++i) {
          getDiff(
            i < prevChildren.size() ? std::optional(prevChildren[i])
                                    : std::nullopt,
            i < newChildren.size() ? std::optional(newChildren[i])
                                   : std::nullopt,
            diff
          );
        }
      },
      prevElement.value(),
      newElement.value()
    );
  };

  void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff) {
    for (auto&& elementVariant : diff.added) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          if (!element->parent.has_value())
            return;

          auto elementParent = dom->findElementById(
            dom,
            std::visit(
              [&dom, &diff](auto parent) -> unsigned int { return parent->id; },
              element->parent.value()
            )
          );
          if (!elementParent)
            return;

          auto domElement = wind::dom::shadow::toReal(element);
          if (!domElement)
            return;

          elementParent->appendChild(domElement, elementParent);
        },
        elementVariant
      );
    }

    for (auto&& elementVariant : diff.removed) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          if (!element->parent.has_value())
            return;

          auto elementParent = dom->findElementById(
            dom,
            std::visit(
              [&dom, &diff](auto parent) -> unsigned int { return parent->id; },
              element->parent.value()
            )
          );
          if (!elementParent)
            return;

          elementParent->removeChild(element->id);
        },
        elementVariant
      );
    }

    for (auto&& elementVariant : diff.updated) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          if (!element->parent)
            return;

          auto domElement = dom->findElementById(dom, element->id);
          if (!domElement)
            return;

          using T = std::decay_t<decltype(element)>;

          std::shared_ptr<wind::dom::Root> realRootElement =
            std::dynamic_pointer_cast<wind::dom::Root>(domElement);
          if constexpr (std::is_same_v<T, Root>) {
            if (realRootElement) {
              updateReal(realRootElement, element);
              return;
            }
          }

          std::shared_ptr<wind::dom::Div> realButtonElement =
            std::dynamic_pointer_cast<wind::dom::Div>(domElement);
          if constexpr (std::is_same_v<T, Div>) {
            if (realButtonElement) {
              updateReal(realButtonElement, element);
              return;
            }
          }
        },
        elementVariant
      );
    }

    // for (auto&& replace : diff.replaced) {
    //   auto replacedElement = dom->findElementById(dom, replace.first);

    // int index = std::distance(
    //   replacedElement->parent->children.begin(), replacedElement
    // );

    // replacedElement->parent->children[index] = replace.second;

    // auto it = std::ranges::find_if(
    //   replacedElement->parent->children,
    //   [searchId = replace.first](wind::dom::UIElement::Ptr element) {
    //     return element->id == searchId;
    //   }
    // );

    // if (it == replacedElement->parent->children.end())
    //   continue;

    // replacedElement->parent->children.
    // }
  };

} // namespace wind::dom::shadow
