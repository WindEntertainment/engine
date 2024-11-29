#include "wind/dom/shadow-dom/shadow-dom.hpp"

namespace wind::dom::shadow {

  void appendChild(std::shared_ptr<Div> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void appendChild(std::shared_ptr<Root> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void appendChild(std::shared_ptr<Text> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void appendChild(std::shared_ptr<Input> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void appendChild(std::shared_ptr<Checkbox> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void appendChild(std::shared_ptr<Select> child, const Element& parent) {
    child->parent = std::optional(parent);
    std::visit(
      [&child](auto& element) { element->children.push_back(child); }, parent
    );
  };

  void removeChild(unsigned int childId, const Element& parent) {
    std::visit(
      [&childId](const auto& element) {
        auto it = std::ranges::find_if(
          element->children,
          [&](const Element& childVariant) {
            return std::visit(
              [&childId](const auto& child) { return child->id == childId; },
              childVariant
            );
          }
        );

        if (it == element->children.end())
          return;

        // (*it)->parent = nullptr;
        element->children.erase(it);
      },
      parent
    );
  };

  attributes::Root mergeAttributes(std::shared_ptr<Root> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);

    if (shadow->parent.has_value()) {
      std::visit(
        [&](const auto& parent) {
          auto parentAttributes = parent->attributes;
          if (parentAttributes.position.has_value() &&
              attrs.position.has_value()) {
            auto parentPosition = parentAttributes.position.value();
            auto position = attrs.position.value();
            attrs.position = {
              parentPosition.x + position.x, parentPosition.y + position.y
            };
          }
        },
        shadow->parent.value()
      );
    }

    return attrs;
  };

  attributes::Div mergeAttributes(std::shared_ptr<Div> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);

    if (shadow->parent.has_value()) {
      std::visit(
        [&](const auto& parent) {
          spdlog::info(
            "{}:{} {}:{}",
            attrs.position.value().x,
            attrs.position.value().y,
            parent->attributes.position.value().x,
            parent->attributes.position.value().y
          );
          auto parentAttributes = parent->attributes;
          if (parentAttributes.position.has_value() &&
              attrs.position.has_value()) {
            auto parentPosition = parentAttributes.position.value();
            auto position = attrs.position.value();
            attrs.position = {
              parentPosition.x + position.x, parentPosition.y + position.y
            };
          }
        },
        shadow->parent.value()
      );
    }

    return attrs;
  };

  attributes::Text mergeAttributes(std::shared_ptr<Text> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);

    if (shadow->parent.has_value()) {
      std::visit(
        [&](const auto& parent) {
          auto parentAttributes = parent->attributes;
          if (parentAttributes.position.has_value() &&
              attrs.position.has_value()) {
            auto parentPosition = parentAttributes.position.value();
            auto position = attrs.position.value();
            attrs.position = {
              parentPosition.x + position.x, parentPosition.y + position.y
            };
          }
        },
        shadow->parent.value()
      );
    }

    return attrs;
  };

  attributes::Input mergeAttributes(std::shared_ptr<Input> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);
    return attrs;
  };

  attributes::Checkbox mergeAttributes(std::shared_ptr<Checkbox> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);
    return attrs;
  };

  attributes::Select mergeAttributes(std::shared_ptr<Select> shadow) {
    auto attrs = shadow->attributes;
    auto attrsTuple = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(attrsTuple, b, c);
    return attrs;
  };

  std::shared_ptr<dom::Root> toReal(std::shared_ptr<Root> shadow) {
    return wind::share(dom::Root(shadow->id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Div> toReal(std::shared_ptr<Div> shadow) {
    return wind::share(dom::Div(shadow->id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Text> toReal(std::shared_ptr<Text> shadow) {
    return wind::share(dom::Text(shadow->id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Input> toReal(std::shared_ptr<Input> shadow) {
    return wind::share(dom::Input(shadow->id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Checkbox> toReal(std::shared_ptr<Checkbox> shadow) {
    return wind::share(dom::Checkbox(shadow->id, mergeAttributes(shadow)));
  };

  std::shared_ptr<dom::Select> toReal(std::shared_ptr<Select> shadow) {
    return wind::share(dom::Select(shadow->id, mergeAttributes(shadow)));
  };

  void destroy(std::shared_ptr<Root> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultRootAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    // PoolManager::releaseFromPool(shadow);
  };

  void destroy(std::shared_ptr<Div> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultDivAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    PoolManager::releaseFromPool(shadow);
  };

  void destroy(std::shared_ptr<Text> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultTextAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    PoolManager::releaseFromPool(shadow);
  };

  void destroy(std::shared_ptr<Input> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultInputAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    PoolManager::releaseFromPool(shadow);
  };

  void destroy(std::shared_ptr<Checkbox> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultCheckboxAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    PoolManager::releaseFromPool(shadow);
  };

  void destroy(std::shared_ptr<Select> shadow) {
    shadow->id = 0;
    shadow->parent = std::nullopt;
    for (const auto& child : shadow->children) {
      std::visit([](auto c) { destroy(c); }, child);
    }
    shadow->children.clear();
    shadow->children.reserve(3);
    shadow->attributes = attributes::getDefaultSelectAttributes();
    shadow->clickAttributes = {};
    shadow->hoverAttributes = {};
    PoolManager::releaseFromPool(shadow);
  };

  void
  updateReal(std::shared_ptr<dom::Root> real, std::shared_ptr<Root> shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  void updateReal(std::shared_ptr<dom::Div> real, std::shared_ptr<Div> shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  void
  updateReal(std::shared_ptr<dom::Text> real, std::shared_ptr<Text> shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  void
  updateReal(std::shared_ptr<dom::Input> real, std::shared_ptr<Input> shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  void updateReal(
    std::shared_ptr<dom::Checkbox> real,
    std::shared_ptr<Checkbox> shadow
  ) {
    real->attributes = mergeAttributes(shadow);
  };

  void
  updateReal(std::shared_ptr<dom::Select> real, std::shared_ptr<Select> shadow) {
    real->attributes = mergeAttributes(shadow);
  };

  std::shared_ptr<Root> init(std::shared_ptr<wind::dom::Root> realRoot) {
    PoolManager::registerPool<Div>(150);
    PoolManager::registerPool<Text>(100);
    PoolManager::registerPool<Input>(20);
    PoolManager::registerPool<Checkbox>(20);
    PoolManager::registerPool<Select>(20);

    auto root = std::make_shared<Root>(1);
    root->attributes.size = realRoot->attributes.size;
    root->attributes.position = realRoot->attributes.position;

    return root;
  }
} // namespace wind::dom::shadow
