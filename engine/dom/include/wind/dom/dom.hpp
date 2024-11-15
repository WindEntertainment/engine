#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include <algorithm>
#include <typeindex>
#include <utility>

namespace wind {

  namespace shared {

    template <typename T>
    concept HasSize = requires(T t) {
      { t.position } -> std::convertible_to<glm::vec2>;
      { t.size } -> std::convertible_to<glm::vec2>;
    };

    class UIUtils {
    public:
      template <HasSize T>
      static bool isHovered(T object) {
        auto context = wind::InputSystem::context;
        return context->mouseContext.cursorX > object.position.x &&
               context->mouseContext.cursorX <
                 object.position.x + object.size.x &&
               context->mouseContext.cursorY > object.position.y &&
               context->mouseContext.cursorY <
                 object.position.y + object.size.y;
      };

      template <HasSize T>
      static bool isClicked(T object, bool isHovered) {
        auto context = wind::InputSystem::context;
        return isHovered && context->key.action == KeyAction::Released &&
               context->key.keycode == Keycode::M_ButtonLeft;
      }
    };

    struct BaseAttributes {
      bool disabled = {false};
      std::function<void()> onClick = {};
      std::function<void()> onHover = {};
      std::function<void()> onDragStart = {};
      std::function<void()> onDrag = {};
      std::function<void()> onDragEnd = {};
      std::function<void()> onFocus = {};
      glm::vec2 position = {0, 0};
      glm::vec2 size = {100, 100};
      glm::vec4 backgroundColor = {0.4f, 0.4f, 0.4f, 1.f};
      std::shared_ptr<Texture> texture = {};
      float angle = {};
      float borderRadius = {};
      float borderWidth = {};
      glm::vec4 borderColor = {};

      bool isHovered = false;

      bool compareBase(const BaseAttributes& attributes) {
        return std::tie(this->disabled) == std::tie(attributes.disabled);
      };

      virtual bool compare(const BaseAttributes& attributes) = 0;

      bool operator==(const BaseAttributes& element) {
        return compareBase(element) && compare(element);
      };

      // public:
      //   virtual ~BaseAttributes() = default;
    };

    struct ButtonAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const ButtonAttributes* attrs =
          dynamic_cast<const ButtonAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const ButtonAttributes defaultButtonAttributes = {};

    struct ImageAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const ImageAttributes* attrs =
          dynamic_cast<const ImageAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const ImageAttributes defaultImageAttributes = {};

    struct TextAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const TextAttributes* attrs =
          dynamic_cast<const TextAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const TextAttributes defaultTextAttributes = {};

    struct InputAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const InputAttributes* attrs =
          dynamic_cast<const InputAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const InputAttributes defaultInputAttributes = {};

    struct CheckboxAttributes : public BaseAttributes {
      bool tmp = {false};

      std::function<void()> onChange;

      bool compare(const BaseAttributes& attributes) override {
        const CheckboxAttributes* attrs =
          dynamic_cast<const CheckboxAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const CheckboxAttributes defaultCheckboxAttributes = {};

    struct DivAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const DivAttributes* attrs =
          dynamic_cast<const DivAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const DivAttributes defaultDivAttributes = {};

    struct SelectAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const SelectAttributes* attrs =
          dynamic_cast<const SelectAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const SelectAttributes defaultSelectAttributes = {};

    struct RootAttributes : public BaseAttributes {
      bool tmp = {false};

      bool compare(const BaseAttributes& attributes) override {
        const RootAttributes* attrs =
          dynamic_cast<const RootAttributes*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const RootAttributes defaultRootAttributes = {};

  } // namespace shared

  namespace dom {
#define GET_PTR()                                                              \
  Ptr getPtr() { return shared_from_this(); }

    using namespace shared;

    class UIElement;
    class Root;

    class UIElement {
    public:
      using Ptr = std::shared_ptr<UIElement>;

      UIElement(unsigned int id);

      // void destroy();

      // virtual void release() {};
      virtual void reset() {};
      virtual void update() = 0;
      virtual Ptr getPtr() = 0;

      void appendChild(Ptr child);

      void display(wind::CommandBuffer& renderer);

      virtual void render(wind::CommandBuffer& renderer) = 0;

      // std::weak_ptr<Root> root;

      std::vector<Ptr> children;

      const unsigned int id;

      void removeChild(unsigned int childId);

      std::shared_ptr<UIElement> parent = nullptr;

    protected:
    };

    template <typename T>
    concept Element = std::is_base_of<UIElement, T>::value;

    class Root : public UIElement, public std::enable_shared_from_this<Root> {
    public:
      GET_PTR();
      Root(unsigned int id, RootAttributes attributes);

      void render(wind::CommandBuffer& renderer) override;
      void update() override;
      void reset() override;

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

      RootAttributes attributes = defaultRootAttributes;
    };

    class Button : public UIElement,
                   public std::enable_shared_from_this<Button> {
    public:
      GET_PTR();
      Button(unsigned int id, ButtonAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      ButtonAttributes attributes = defaultButtonAttributes;
    };

    class Image : public UIElement, public std::enable_shared_from_this<Image> {
    public:
      GET_PTR();
      Image(unsigned int id, ImageAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      ImageAttributes attributes = defaultImageAttributes;
    };

    class Text : public UIElement, public std::enable_shared_from_this<Text> {
    public:
      GET_PTR();
      Text(unsigned int id, TextAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      TextAttributes attributes = defaultTextAttributes;
    };

    class Input : public UIElement, public std::enable_shared_from_this<Input> {
    public:
      GET_PTR();
      Input(unsigned int id, InputAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      InputAttributes attributes = defaultInputAttributes;
    };

    class Checkbox : public UIElement,
                     public std::enable_shared_from_this<Checkbox> {
    public:
      GET_PTR();
      Checkbox(unsigned int id, CheckboxAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      CheckboxAttributes attributes = defaultCheckboxAttributes;
    };

    class Div : public UIElement, public std::enable_shared_from_this<Div> {
    public:
      GET_PTR();
      Div(unsigned int id, DivAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      DivAttributes attributes = defaultDivAttributes;
    };

    class Select : public UIElement,
                   public std::enable_shared_from_this<Select> {
    public:
      GET_PTR();
      Select(unsigned int id, SelectAttributes attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;

      SelectAttributes attributes = defaultSelectAttributes;
    };

    std::shared_ptr<Root> init(glm::ivec2);

    template <Element T>
    std::shared_ptr<T> createElement() {
      auto element = std::make_shared<T>();

      return element;
    };
  } // namespace dom
} // namespace wind
