#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"

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

#define DEEP_COPY(className, attributesName)                                   \
  Ptr deepCopy() override {                                                    \
    auto element = wind::share(className(this->id));                           \
    element->attributes = attributesName(this->attributes);                    \
    for (auto&& child : this->children) {                                      \
      element->appendChild(child->deepCopy());                                 \
    };                                                                         \
    return element;                                                            \
  };

    using namespace wind;
    using namespace shared;

    class UIElement {
    public:
      using Ptr = std::shared_ptr<UIElement>;

      UIElement();
      UIElement(unsigned int id);

      // bool operator==(std::shared_ptr<UIElement> element) {
      //   // TODO: test
      //   return this->attributes == element->attributes;
      // };

      virtual bool operator==(UIElement& other) = 0;

      void appendChild(Ptr child);
      virtual Ptr deepCopy() = 0;
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
      std::shared_ptr<wind::dom::shadow::UIElement> element,
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
      Root(const unsigned int id);
      UIElement::Ptr
      findElementById(const UIElement::Ptr& root, const unsigned int& id) {
        if (!root)
          return nullptr;

        if (root->id == id)
          return root;

        for (const auto& child : root->children) {
          auto result = findElementById(child, id);
          if (result)
            return result;
        }

        return nullptr;
      }

      DEEP_COPY(Root, attributes::Root);
      // Ptr deepCopy() override {
      //   auto element = wind::share(Root(this->id));
      //   element->attributes = attributes::Root(this->attributes);
      //   for (auto&& child : this->children) {
      //     element->appendChild(child->deepCopy());
      //   }
      // };
      GET_PTR();
      COMPARE(Root);
      attributes::Root attributes = attributes::defaultRootAttributes;
    };

    class Button : public UIElement,
                   public std::enable_shared_from_this<Button> {
    public:
      Button();
      Button(const unsigned int id);
      DEEP_COPY(Button, attributes::Button);
      GET_PTR();
      COMPARE(Button);
      attributes::Button attributes = attributes::defaultButtonAttributes;
    };

    class Image : public UIElement, public std::enable_shared_from_this<Image> {
    public:
      Image();
      Image(const unsigned int id);
      DEEP_COPY(Image, attributes::Image);
      GET_PTR();
      COMPARE(Image);
      attributes::Image attributes = attributes::defaultImageAttributes;
    };

    class Text : public UIElement, public std::enable_shared_from_this<Text> {
    public:
      Text();
      Text(const unsigned int id);
      DEEP_COPY(Text, attributes::Text);
      GET_PTR();
      COMPARE(Text);
      attributes::Text attributes = attributes::defaultTextAttributes;
    };

    class Input : public UIElement, public std::enable_shared_from_this<Input> {
    public:
      Input();
      Input(const unsigned int id);
      DEEP_COPY(Input, attributes::Input);
      GET_PTR();
      COMPARE(Input);
      attributes::Input attributes = attributes::defaultInputAttributes;
    };

    class Checkbox : public UIElement,
                     public std::enable_shared_from_this<Checkbox> {
    public:
      Checkbox();
      Checkbox(const unsigned int id);
      DEEP_COPY(Checkbox, attributes::Checkbox);
      GET_PTR();
      COMPARE(Checkbox);
      attributes::Checkbox attributes = attributes::defaultCheckboxAttributes;
    };

    class Div : public UIElement, public std::enable_shared_from_this<Div> {
    public:
      Div();
      Div(const unsigned int id);
      DEEP_COPY(Div, attributes::Div);
      GET_PTR();
      COMPARE(Div);
      attributes::Div attributes = attributes::defaultDivAttributes;
    };

    class Select : public UIElement,
                   public std::enable_shared_from_this<Select> {
    public:
      Select();
      Select(const unsigned int id);
      DEEP_COPY(Select, attributes::Select);
      GET_PTR();
      COMPARE(Select);
      attributes::Select attributes = attributes::defaultSelectAttributes;
    };

    template <Element T>
    std::shared_ptr<T> createElement() {
      auto element = std::make_shared<T>();

      return element;
    };
    std::shared_ptr<Root> init(glm::ivec2);
  } // namespace shadowDom

} // namespace wind
