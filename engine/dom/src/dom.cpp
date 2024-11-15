#include "wind/dom/dom.hpp"
#include <random>
#include <utility>

namespace wind {
  namespace dom {

    UIElement::UIElement(unsigned int id) : id(id) { children.reserve(3); }

    // void UIElement::destroy() {
    //   parent = nullptr;
    //   for (const auto& child : children) {
    //     child->destroy();
    //   }
    //   reset();
    //   release();
    // }

    void UIElement::appendChild(Ptr child) {
      if (child) {
        children.push_back(child);
        // child->parent = this;
        // child->root = root;
      }
    }

    void UIElement::display(wind::CommandBuffer& renderer) {
      update();
      render(renderer);
      for (const auto& child : children) {
        child->display(renderer);
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

    Root::Root(unsigned int id, RootAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {
            // this->root = weak_from_this();
          };

    Button::Button(unsigned int id, ButtonAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Image::Image(unsigned int id, ImageAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Text::Text(unsigned int id, TextAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Input::Input(unsigned int id, InputAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Checkbox::Checkbox(unsigned int id, CheckboxAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Div::Div(unsigned int id, DivAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};
    Select::Select(unsigned int id, SelectAttributes attributes)
        : UIElement(id), attributes(std::move(attributes)) {};

    void Root::render(wind::CommandBuffer& renderer) {};

    void Root::reset() { attributes = defaultRootAttributes; }

    void Root::update() {};

    void Button::render(wind::CommandBuffer& renderer) {
      renderer.drawRect(
        attributes.position,
        attributes.size,
        attributes.backgroundColor,
        attributes.texture,
        attributes.angle,
        attributes.borderRadius,
        attributes.borderWidth,
        attributes.borderColor
      );
    };

    void Button::reset() { attributes = defaultButtonAttributes; };

    void Button::update() {
      auto context = wind::InputSystem::context;
      auto isHovered = UIUtils::isHovered(attributes);
      auto isClicked = UIUtils::isClicked(attributes, isHovered);

      if (!isHovered && attributes.isHovered) {
        attributes.isHovered = false;
      }

      if (isHovered && !attributes.isHovered) {
        attributes.isHovered = true;
        if (attributes.onHover) {
          attributes.onHover();
        }
      }

      if (isClicked && attributes.onClick) {
        attributes.onClick();
      }
    };

    void Image::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm Image";
    };

    void Image::reset() { attributes = defaultImageAttributes; };

    void Image::update() {};

    void Text::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm Text";
    };

    void Text::reset() { attributes = defaultTextAttributes; };

    void Text::update() {};

    void Input::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm RichText";
    };

    void Input::reset() { attributes = defaultInputAttributes; };

    void Input::update() {};

    void Div::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm RichText";
    };

    void Div::reset() { attributes = defaultDivAttributes; };

    void Div::update() {};

    void Select::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm RichText";
    };

    void Select::reset() { attributes = defaultSelectAttributes; };

    void Select::update() {};

    void Checkbox::render(wind::CommandBuffer& renderer) {
      std::cout << "I'm RichText";
    };

    void Checkbox::reset() { attributes = defaultCheckboxAttributes; };

    void Checkbox::update() {};

    std::shared_ptr<Root> init(glm::ivec2 windowSize) {
      auto root = std::make_shared<Root>(0, RootAttributes());

      return root;
    };
  } // namespace dom

} // namespace wind
