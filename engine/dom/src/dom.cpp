#include "wind/dom/dom.hpp"
#include <random>

namespace wind {

  UIElement::UIElement() { children.reserve(3); }

  void UIElement::destroy() {
    parent = nullptr;
    for (const auto& child : children) {
      child->destroy();
    }
    reset();
    release();
  }
  void UIElement::appendChild(const Ptr& child) {
    if (child) {
      children.push_back(child);
      child->parent = this;
      child->root = root;
    }
  }

  void UIElement::display(wind::CommandBuffer& renderer) {
    update();
    render(renderer);
    for (const auto& child : children) {
      child->display(renderer);
    }
  }

  void UIElement::removeChild(Ptr child) {
    if (child) {
      auto it = std::ranges::find_if(children, [&](const Ptr& item) {
        return item == child;
      });

      if (it == children.end())
        return;

      (*it)->parent = nullptr;
      children.erase(it);
    }
  };

  Root::Root() { this->root = weak_from_this(); };

  void Root::render(wind::CommandBuffer& renderer) {};

  void Root::reset() {
    attributes = defaultRootAttributes;
    styles = defaultStyles;
  }

  void Root::update() {};

  void Button::render(wind::CommandBuffer& renderer) {
    renderer.drawRect(
      attributes.position,
      attributes.size,
      attributes.backgroundColor,
      nullptr,
      0,
      0
    );
  }

  void Button::reset() {
    // attributes = defaultButtonAttributes;
    styles = defaultStyles;
  }

  void Button::update() {
    auto context = wind::InputSystem::context;
    if (context->key.keycode == wind::Keycode::M_Move) {
      if (context->mouseContext.cursorX > 0 &&
          context->mouseContext.cursorX < 100 &&
          context->mouseContext.cursorY > 0 &&
          context->mouseContext.cursorY < 100) {
        attributes.backgroundColor = glm::vec4({1.0f, 1.f, 0.f, 1.f});
      }
    }
  };

  void Image::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm Image";
  }

  void Image::reset() {
    attributes = defaultImageAttributes;
    styles = defaultStyles;
  }

  void Image::update() {};

  void Text::render(wind::CommandBuffer& renderer) { std::cout << "I'm Text"; }

  void Text::reset() {
    attributes = defaultTextAttributes;
    styles = defaultStyles;
  }

  void Text::update() {};

  void RichText::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  }

  void RichText::reset() {
    attributes = defaultRichTextAttributes;
    styles = defaultStyles;
  }

  void RichText::update() {};

  std::shared_ptr<Root> init() {
    Button::registerPool(1);
    Image::registerPool();
    Text::registerPool();
    RichText::registerPool();

    auto root = std::make_shared<Root>();

    return root;
  }

} // namespace wind
