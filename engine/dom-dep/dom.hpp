#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"

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

    struct attributes::Base {
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

      bool compareBase(const attributes::Base& attributes) {
        return std::tie(this->disabled) == std::tie(attributes.disabled);
      };

      virtual bool compare(const attributes::Base& attributes) = 0;

      bool operator==(const attributes::Base& element) {
        return compareBase(element) && compare(element);
      };

      // public:
      //   virtual ~attributes::Base() = default;
    };

    struct attributes::Button : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Button* attrs =
          dynamic_cast<const attributes::Button*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Button defaultButtonAttributes = {};

    struct attributes::Image : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Image* attrs =
          dynamic_cast<const attributes::Image*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Image defaultImageAttributes = {};

    struct attributes::Text : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Text* attrs =
          dynamic_cast<const attributes::Text*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Text defaultTextAttributes = {};

    struct attributes::Input : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Input* attrs =
          dynamic_cast<const attributes::Input*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Input defaultInputAttributes = {};

    struct attributes::Checkbox : public attributes::Base {
      bool tmp = {false};

      std::function<void()> onChange;

      bool compare(const attributes::Base& attributes) override {
        const attributes::Checkbox* attrs =
          dynamic_cast<const attributes::Checkbox*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Checkbox defaultCheckboxAttributes = {};

    struct attributes::Div : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Div* attrs =
          dynamic_cast<const attributes::Div*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Div defaultDivAttributes = {};

    struct attributes::Select : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Select* attrs =
          dynamic_cast<const attributes::Select*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Select defaultSelectAttributes = {};

    struct attributes::Root : public attributes::Base {
      bool tmp = {false};

      bool compare(const attributes::Base& attributes) override {
        const attributes::Root* attrs =
          dynamic_cast<const attributes::Root*>(&attributes);
        if (!attrs) {
          return false;
        }

        return std::tie(this->tmp) == std::tie(attrs->tmp);
      }
    };
    static const attributes::Root defaultRootAttributes = {};

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
      // virtual Ptr deepCopy() = 0;
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
      Root(unsigned int id, attributes::Root attributes);

      void render(wind::CommandBuffer& renderer) override;
      void update() override;
      void reset() override;
      // Ptr deepCopy() override;

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

      attributes::Root attributes = attributes::defaultRootAttributes;
    };

    class Button : public UIElement,
                   public std::enable_shared_from_this<Button> {
    public:
      GET_PTR();
      Button(unsigned int id, attributes::Button attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Button attributes = attributes::defaultButtonAttributes;
    };

    class Image : public UIElement, public std::enable_shared_from_this<Image> {
    public:
      GET_PTR();
      Image(unsigned int id, attributes::Image attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Image attributes = attributes::defaultImageAttributes;
    };

    class Text : public UIElement, public std::enable_shared_from_this<Text> {
    public:
      GET_PTR();
      Text(unsigned int id, attributes::Text attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Text attributes = attributes::defaultTextAttributes;
    };

    class Input : public UIElement, public std::enable_shared_from_this<Input> {
    public:
      GET_PTR();
      Input(unsigned int id, attributes::Input attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Input attributes = attributes::defaultInputAttributes;
    };

    class Checkbox : public UIElement,
                     public std::enable_shared_from_this<Checkbox> {
    public:
      GET_PTR();
      Checkbox(unsigned int id, attributes::Checkbox attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Checkbox attributes = attributes::defaultCheckboxAttributes;
    };

    class Div : public UIElement, public std::enable_shared_from_this<Div> {
    public:
      GET_PTR();
      Div(unsigned int id, attributes::Div attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Div attributes = attributes::defaultDivAttributes;
    };

    class Select : public UIElement,
                   public std::enable_shared_from_this<Select> {
    public:
      GET_PTR();
      Select(unsigned int id, attributes::Select attributes);
      void render(wind::CommandBuffer& renderer) override;

      void update() override;

      void reset() override;
      // Ptr deepCopy() override;

      attributes::Select attributes = attributes::defaultSelectAttributes;
    };

    std::shared_ptr<Root> init(glm::ivec2);

    template <Element T>
    std::shared_ptr<T> createElement() {
      auto element = std::make_shared<T>();

      return element;
    };
  } // namespace dom
} // namespace wind
