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
          diff.added.end(),
          element.tree->children.begin(),
          element.tree->children.end()
        );

        for (const auto& childVariant : element.tree->children) {
          std::visit(
            [&diff](auto child) -> void {
              if (child.tree->children.empty())
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
          if (!elem.tree->children.empty()) {
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
        if (std::is_same_v<T, V> && prevE.id == newE.id) {
          // if (prevE == newE) {
          // if (newE.id == 3) {
          //   /* code */
          //   spdlog::info("DIFF X: {}", newE.attributes.backgroundColor.x);
          // }
          spdlog::info(newE.id);
          diff.updated.push_back(newE);
          // }
        } else {
          diff.replaced.emplace_back(prevE.id, newE);
          if (!newE.tree->children.empty()) {
            addDiffChildren(newE, diff);
          }
        }

        auto prevChildren = prevE.tree->children;
        auto newChildren = newE.tree->children;

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

  // using FactoryMap = std::map<
  //   std::type_index,
  //   std::function<
  //     wind::dom::UIElement::Ptr(wind::dom::shadow::Element::Ptr element)>>;

  // FactoryMap factoryMap = {
  //   {typeid(Root),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Root> element =
  //        std::dynamic_pointer_cast<Root>(uiElement);
  //      return wind::share(wind::dom::Root(element->id,
  //      element->attributes));
  //    }},
  //   {typeid(Button),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Button> element =
  //        std::dynamic_pointer_cast<Button>(uiElement);
  //      return wind::share(wind::dom::Button(element->id,
  //      element->attributes));
  //    }},
  //   {typeid(Image),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Image> element =
  //        std::dynamic_pointer_cast<Image>(uiElement);
  //      return wind::share(wind::dom::Image(element->id,
  //      element->attributes));
  //    }},
  //   {typeid(Text),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Text> element =
  //        std::dynamic_pointer_cast<Text>(uiElement);
  //      return wind::share(wind::dom::Text(element->id,
  //      element->attributes));
  //    }},
  //   {typeid(Input),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Input> element =
  //        std::dynamic_pointer_cast<Input>(uiElement);
  //      return wind::share(wind::dom::Input(element->id,
  //      element->attributes));
  //    }},
  //   {typeid(Checkbox),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Checkbox> element =
  //        std::dynamic_pointer_cast<Checkbox>(uiElement);
  //      return wind::share(wind::dom::Checkbox(element->id,
  //      element->attributes)
  //      );
  //    }},
  //   {typeid(Div),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Div> element =
  //      std::dynamic_pointer_cast<Div>(uiElement); return
  //      wind::share(wind::dom::Div(element->id, element->attributes));
  //    }},
  //   {typeid(Select),
  //    [](wind::dom::shadow::Element::Ptr uiElement) {
  //      std::shared_ptr<Select> element =
  //        std::dynamic_pointer_cast<Select>(uiElement);
  //      return wind::share(wind::dom::Select(element->id,
  //      element->attributes));
  //    }}

  // };

  // using UpdateFactoryMap = std::map<
  //   std::type_index,
  //   std::function<void(
  //     wind::dom::shadow::Element::Ptr uiElement,
  //     wind::dom::UIElement::Ptr domElement
  //   )>>;

  // UpdateFactoryMap updateFactoryMap = {
  //   {typeid(Root),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Root> element =
  //        std::dynamic_pointer_cast<Root>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Root> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Root>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Button),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Button> element =
  //        std::dynamic_pointer_cast<Button>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Button> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Button>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Image),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Image> element =
  //        std::dynamic_pointer_cast<Image>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Image> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Image>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Text),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Text> element =
  //        std::dynamic_pointer_cast<Text>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Text> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Text>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Input),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Input> element =
  //        std::dynamic_pointer_cast<Input>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Input> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Input>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Checkbox),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Checkbox> element =
  //        std::dynamic_pointer_cast<Checkbox>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Checkbox> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Checkbox>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Div),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Div> element =
  //      std::dynamic_pointer_cast<Div>(uiElement); if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Div> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Div>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }},
  //   {typeid(Select),
  //    [](
  //      wind::dom::shadow::Element::Ptr uiElement,
  //      wind::dom::UIElement::Ptr domElement
  //    ) {
  //      std::shared_ptr<Select> element =
  //        std::dynamic_pointer_cast<Select>(uiElement);
  //      if (!element)
  //        return;
  //      std::shared_ptr<wind::dom::Select> realElement =
  //        std::dynamic_pointer_cast<wind::dom::Select>(domElement);
  //      if (!realElement)
  //        return;
  //      realElement->attributes = element->attributes;
  //    }}

  // };

  void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff) {
    // spdlog::info(
    //   "{} {} {}", diff.added.size(), diff.updated.size(), diff.removed.size()
    // );
    for (auto&& elementVariant : diff.added) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          // spdlog::info("ADDING 0");
          if (!element.tree->parent.has_value())
            return;

          // spdlog::info("ADDING 1");

          auto elementParent = dom->findElementById(
            dom,
            std::visit(
              [&dom, &diff](auto parent) -> unsigned int { return parent.id; },
              element.tree->parent.value()
            )
          );
          if (!elementParent)
            return;

          // spdlog::info("ADDING 2");

          auto domElement = wind::dom::shadow::toReal(element);
          if (!domElement)
            return;

          spdlog::info(domElement->id);

          elementParent->appendChild(domElement, elementParent);
        },
        elementVariant
      );
      // spdlog::info("a{}", element.id);
    }

    for (auto&& elementVariant : diff.removed) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          if (!element.tree->parent.has_value())
            return;

          auto elementParent = dom->findElementById(
            dom,
            std::visit(
              [&dom, &diff](auto parent) -> unsigned int { return parent.id; },
              element.tree->parent.value()
            )
          );
          if (!elementParent)
            return;

          elementParent->removeChild(element.id);
        },
        elementVariant
      );
    }

    for (auto&& elementVariant : diff.updated) {
      std::visit(
        [&dom, &diff](auto element) -> void {
          // spdlog::info("UPDATE 1");
          if (!element.tree->parent.has_value())
            return;

          auto domElement = dom->findElementById(dom, element.id);
          // spdlog::info("UPDATE 2");
          if (!domElement)
            return;

          using T = std::decay_t<decltype(element)>;

          std::shared_ptr<wind::dom::Root> realRootElement =
            std::dynamic_pointer_cast<wind::dom::Root>(domElement);
          // spdlog::info("UPDATE 3");
          if constexpr (std::is_same_v<T, Root>) {
            if (realRootElement) {
              updateReal(realRootElement, element);
              return;
            }
          }

          std::shared_ptr<wind::dom::Button> realButtonElement =
            std::dynamic_pointer_cast<wind::dom::Button>(domElement);
          // spdlog::info("UPDATE 4");
          if constexpr (std::is_same_v<T, Button>) {
            // spdlog::info("UPDATE 5");
            if (realButtonElement) {
              // spdlog::info("UPDATE 6");
              updateReal(realButtonElement, element);
              return;
            }
          }
        },
        elementVariant
      );
      // spdlog::info("UPDATING");

      // auto updateFactory = updateFactoryMap[typeid(*element)];
      // if (!updateFactory)
      //   continue;

      // updateFactory(element, domElement);
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
