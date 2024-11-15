#pragma once
#include <wind/utils/utils.hpp>
#include <wind/dom/dom.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include <algorithm>
#include <typeindex>
#include <utility>

namespace wind {

  namespace shadowDom {

#define COMPARE(className)                                                     \
  bool operator==(UIElement& elementReference) override {                      \
    className* element = dynamic_cast<className*>(&elementReference);          \
    if (!element)                                                              \
      return false;                                                            \
    return attributes == element->attributes;                                  \
  }

#define GET_PTR()                                                              \
  Ptr getPtr() { return shared_from_this(); }

    using namespace wind;
    using namespace shared;

    class UIElement {
    public:
      using Ptr = std::shared_ptr<UIElement>;

      UIElement();

      // bool operator==(std::shared_ptr<UIElement> element) {
      //   // TODO: test
      //   return this->attributes == element->attributes;
      // };

      virtual bool operator==(UIElement& other) = 0;

      void appendChild(Ptr child);

      virtual Ptr getPtr() = 0;

      std::vector<Ptr> children;

      void removeChild(unsigned int childId);

      const unsigned int id;
      static unsigned int nextId;

      std::shared_ptr<UIElement> parent = nullptr;

    protected:
    };

    struct Diff {
      std::vector<UIElement::Ptr> removed;
      std::vector<UIElement::Ptr> added;
      std::vector<UIElement::Ptr> updated;
      std::vector<std::pair<const unsigned int, UIElement::Ptr>> replaced;
    };

    void addDiffChildren(
      std::shared_ptr<wind::shadowDom::UIElement> element,
      Diff& diff
    );

    void getDiff(
      std::shared_ptr<UIElement> prevElement,
      std::shared_ptr<UIElement> newElement,
      Diff& diff
    );

    void fromDiff(std::shared_ptr<wind::dom::Root> dom, Diff& diff);

    template <typename T>
    concept Element = std::is_base_of<UIElement, T>::value;

    class Root : public UIElement, public std::enable_shared_from_this<Root> {
    public:
      Root();
      GET_PTR();
      COMPARE(Root);
      RootAttributes attributes = defaultRootAttributes;
    };

    class Button : public UIElement,
                   public std::enable_shared_from_this<Button> {
    public:
      GET_PTR();
      COMPARE(Button);
      ButtonAttributes attributes = defaultButtonAttributes;
    };

    class Image : public UIElement, public std::enable_shared_from_this<Image> {
    public:
      GET_PTR();
      COMPARE(Image);
      ImageAttributes attributes = defaultImageAttributes;
    };

    class Text : public UIElement, public std::enable_shared_from_this<Text> {
    public:
      GET_PTR();
      COMPARE(Text);
      TextAttributes attributes = defaultTextAttributes;
    };

    class Input : public UIElement, public std::enable_shared_from_this<Input> {
    public:
      GET_PTR();
      COMPARE(Input);
      InputAttributes attributes = defaultInputAttributes;
    };

    class Checkbox : public UIElement,
                     public std::enable_shared_from_this<Checkbox> {
    public:
      GET_PTR();
      COMPARE(Checkbox);
      CheckboxAttributes attributes = defaultCheckboxAttributes;
    };

    class Div : public UIElement, public std::enable_shared_from_this<Div> {
    public:
      GET_PTR();
      COMPARE(Div);
      DivAttributes attributes = defaultDivAttributes;
    };

    class Select : public UIElement,
                   public std::enable_shared_from_this<Select> {
    public:
      GET_PTR();
      COMPARE(Select);
      SelectAttributes attributes = defaultSelectAttributes;
    };

    template <Element T>
    std::shared_ptr<T> createElement() {
      auto element = std::make_shared<T>();

      return element;
    };
    std::shared_ptr<Root> init(glm::ivec2);
  } // namespace shadowDom

} // namespace wind
