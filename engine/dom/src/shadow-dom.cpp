#include "wind/dom/shadow-dom.hpp"
#include <random>

namespace wind {

  namespace shadowDom {

    unsigned int UIElement::nextId = 0;

    UIElement::UIElement() : id(nextId++) { children.reserve(3); }

    void UIElement::appendChild(Ptr child) {
      if (child) {
        child->parent = this->getPtr();
        spdlog::info(
          "GETPTR: {}, parent: {}", !!this->getPtr(), !!child->parent
        );
        children.push_back(child);

        // child->root = root;
      }
    }

    void UIElement::removeChild(unsigned int childId) {
      auto it = std::ranges::find_if(children, [&](const Ptr& item) {
        return item->id == childId;
      });

      if (it == children.end())
        return;

      // (*it)->parent = nullptr;
      children.erase(it);
    };

    Root::Root() {
      spdlog::info('Root created');
      // this->root = weak_from_this();
    };

    std::shared_ptr<Root> init(glm::ivec2 windowSize) {
      auto root = std::make_shared<Root>();

      return root;
    };

    void addDiffChildren(
      std::shared_ptr<wind::shadowDom::UIElement> element,
      Diff& diff
    ) {
      diff.added.insert(
        diff.added.end(), element->children.begin(), element->children.end()
      );

      for (auto&& child : element->children) {
        if (child->children.empty())
          continue;

        addDiffChildren(child, diff);
      }
    }

    void getDiff(
      std::shared_ptr<wind::shadowDom::UIElement> prevElement,
      std::shared_ptr<wind::shadowDom::UIElement> newElement,
      Diff& diff
    ) {
      // std::shared_ptr<Diff> diff = wind::share(Diff());
      // spdlog::info(
      //   "prev: {} new: {}", !!prevElement, !!newElement
      //   // newElement->id
      //   // prevElement->id,
      //   // newElement->id
      //   // prevElement->children.size(),
      //   // newElement->children.size()
      // );

      // if (prevElement && prevElement->id == 2) {
      //   spdlog::info(
      //     "{} {} {} {}",
      //     !prevElement && newElement,
      //     prevElement && !newElement,
      //     wind::compareSharedByTypeId(prevElement, newElement),
      //     wind::compareSharedByValue(prevElement, newElement)
      //   );
      // }

      if (!prevElement && !newElement)
        return;

      if (!prevElement && newElement) {
        diff.added.push_back(newElement);
        if (!newElement->children.empty()) {
          addDiffChildren(newElement, diff);
        }
        return;
      }

      if (prevElement && !newElement) {
        spdlog::info(
          "REMOVED LIST: {} {}", prevElement->id, !!prevElement->parent
        );
        diff.removed.push_back(prevElement);
        return;
      }

      if (prevElement->id != newElement->id ||
          !wind::compareSharedByTypeId(prevElement, newElement)) {
        diff.replaced.emplace_back(prevElement->id, newElement);
        if (!newElement->children.empty()) {
          addDiffChildren(newElement, diff);
        }
      } else {
        if (prevElement && newElement) {
          std::shared_ptr<Button> element1 =
            std::dynamic_pointer_cast<Button>(prevElement);
          std::shared_ptr<Button> element2 =
            std::dynamic_pointer_cast<Button>(newElement);
          if (!!element1 && !!element2) {
            spdlog::info(
              "TRUE {}", !wind::compareSharedByValue(prevElement, newElement)
            );
          }
        }

        if (!wind::compareSharedByValue(prevElement, newElement)) {
          spdlog::info(
            "UPDATE: {}", wind::compareSharedByValue(prevElement, newElement)
          );
          diff.updated.push_back(newElement);
        }
      }

      // if () {
      //   // diff.added.push_back(newElement);
      //   // diff.removed.push_back(prevElement);

      //   return;
      // }

      // if (!wind::compareSharedByValue(prevElement, newElement)) {
      //   diff.updated.push_back(newElement);
      // }

      size_t childrenCount =
        std::max(prevElement->children.size(), newElement->children.size());

      for (size_t i = 0; i < childrenCount; ++i) {
        auto prevChild =
          i < prevElement->children.size() ? prevElement->children[i] : nullptr;
        auto newChild =
          i < newElement->children.size() ? newElement->children[i] : nullptr;

        getDiff(prevChild, newChild, diff);
      }
    };

    using FactoryMap = std::map<
      std::type_index,
      std::function<
        wind::dom::UIElement::Ptr(wind::shadowDom::UIElement::Ptr element)>>;

    FactoryMap factoryMap = {
      {typeid(Root),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Root> element =
           std::dynamic_pointer_cast<Root>(uiElement);
         return wind::share(wind::dom::Root(element->id, element->attributes));
       }},
      {typeid(Button),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Button> element =
           std::dynamic_pointer_cast<Button>(uiElement);
         return wind::share(wind::dom::Button(element->id, element->attributes)
         );
       }},
      {typeid(Image),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Image> element =
           std::dynamic_pointer_cast<Image>(uiElement);
         return wind::share(wind::dom::Image(element->id, element->attributes));
       }},
      {typeid(Text),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Text> element =
           std::dynamic_pointer_cast<Text>(uiElement);
         return wind::share(wind::dom::Text(element->id, element->attributes));
       }},
      {typeid(Input),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Input> element =
           std::dynamic_pointer_cast<Input>(uiElement);
         return wind::share(wind::dom::Input(element->id, element->attributes));
       }},
      {typeid(Checkbox),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Checkbox> element =
           std::dynamic_pointer_cast<Checkbox>(uiElement);
         return wind::share(
           wind::dom::Checkbox(element->id, element->attributes)
         );
       }},
      {typeid(Div),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Div> element =
           std::dynamic_pointer_cast<Div>(uiElement);
         return wind::share(wind::dom::Div(element->id, element->attributes));
       }},
      {typeid(Select),
       [](wind::shadowDom::UIElement::Ptr uiElement) {
         std::shared_ptr<Select> element =
           std::dynamic_pointer_cast<Select>(uiElement);
         return wind::share(wind::dom::Select(element->id, element->attributes)
         );
       }}

    };

    using UpdateFactoryMap = std::map<
      std::type_index,
      std::function<void(
        wind::shadowDom::UIElement::Ptr uiElement,
        wind::dom::UIElement::Ptr domElement
      )>>;

    UpdateFactoryMap updateFactoryMap = {
      {typeid(Root),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Root> element =
           std::dynamic_pointer_cast<Root>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Root> realElement =
           std::dynamic_pointer_cast<wind::dom::Root>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Button),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Button> element =
           std::dynamic_pointer_cast<Button>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Button> realElement =
           std::dynamic_pointer_cast<wind::dom::Button>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Image),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Image> element =
           std::dynamic_pointer_cast<Image>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Image> realElement =
           std::dynamic_pointer_cast<wind::dom::Image>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Text),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Text> element =
           std::dynamic_pointer_cast<Text>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Text> realElement =
           std::dynamic_pointer_cast<wind::dom::Text>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Input),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Input> element =
           std::dynamic_pointer_cast<Input>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Input> realElement =
           std::dynamic_pointer_cast<wind::dom::Input>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Checkbox),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Checkbox> element =
           std::dynamic_pointer_cast<Checkbox>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Checkbox> realElement =
           std::dynamic_pointer_cast<wind::dom::Checkbox>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Div),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Div> element =
           std::dynamic_pointer_cast<Div>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Div> realElement =
           std::dynamic_pointer_cast<wind::dom::Div>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }},
      {typeid(Select),
       [](
         wind::shadowDom::UIElement::Ptr uiElement,
         wind::dom::UIElement::Ptr domElement
       ) {
         std::shared_ptr<Select> element =
           std::dynamic_pointer_cast<Select>(uiElement);
         if (!element)
           return;
         std::shared_ptr<wind::dom::Select> realElement =
           std::dynamic_pointer_cast<wind::dom::Select>(domElement);
         if (!realElement)
           return;
         realElement->attributes = element->attributes;
       }}

    };

    void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff) {
      for (auto&& element : diff.added) {
        if (!element->parent)
          continue;

        auto elementParent = dom->findElementById(dom, element->parent->id);
        if (!elementParent)
          continue;

        auto factory = factoryMap[typeid(*element)];
        if (!factory)
          continue;

        wind::dom::UIElement::Ptr domElement = factory(element);
        spdlog::info("APPENDED");
        elementParent->appendChild(domElement);
      }

      for (auto&& element : diff.removed) {
        spdlog::info("DELETING {}", !!element->parent);

        if (!element->parent)
          continue;

        spdlog::info(element->id);

        auto elementParent = dom->findElementById(dom, element->parent->id);
        if (!elementParent)
          continue;

        elementParent->removeChild(element->id);
      }

      for (auto&& element : diff.updated) {
        if (!element->parent)
          continue;

        auto domElement = dom->findElementById(dom, element->id);

        if (!domElement)
          continue;

        auto updateFactory = updateFactoryMap[typeid(*element)];
        if (!updateFactory)
          continue;

        updateFactory(element, domElement);
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

  } // namespace shadowDom
} // namespace wind
