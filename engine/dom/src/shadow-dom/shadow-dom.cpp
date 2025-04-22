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

  dom::attributes::Root mergeAttributes(std::shared_ptr<Root> shadow) {
    dom::attributes::Root domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);

    // if (shadow->parent.has_value()) {
    //   std::visit(
    //     [&](const auto& parent) {
    //       auto parentAttributes = parent->attributes;
    //       if (parentAttributes.position.has_value() &&
    //           attrs.position.has_value()) {
    //         auto parentPosition = parentAttributes.position.value();
    //         auto position = attrs.position.value();
    //         attrs.position = {
    //           parentPosition.x + position.x, parentPosition.y + position.y
    //         };
    //       }
    //     },
    //     shadow->parent.value()
    //   );
    // }

    return domAttrs;
  };

  dom::attributes::Div mergeAttributes(std::shared_ptr<Div> shadow) {
    dom::attributes::Div domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);

    if (shadow->parent.has_value()) {
      std::visit(
        [&](const auto& parent) {
          // spdlog::info(
          //   "{}:{} {}:{}",
          //   attrs.position.value().x,
          //   attrs.position.value().y,
          //   parent->attributes.position.value().x,
          //   parent->attributes.position.value().y
          // );
          auto parentAttributes = parent->attributes;
          if (parentAttributes.x.has_value() &&
              parentAttributes.y.has_value() && attrs.x.has_value() &&
              attrs.y.has_value()) {
            // auto parentX = parentAttributes.x.value().value;
            // auto x = attrs.x.value().value;

            // auto parentY = parentAttributes.y.value().value;
            // auto y = attrs.y.value().value;
            // attrs.x = {parentX + x, parentY + y};
            // attrs.y = {parentX + x, parentY + y};

            // TODO: will it even work?
            auto x = attrs.x.value().value += parentAttributes.x.value().value;
            auto y = attrs.y.value().value += parentAttributes.y.value().value;
          }
        },
        shadow->parent.value()
      );
    }

    return domAttrs;
  };

  dom::attributes::Text mergeAttributes(std::shared_ptr<Text> shadow) {
    dom::attributes::Text domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);

    // if (shadow->parent.has_value()) {
    //   std::visit(
    //     [&](const auto& parent) {
    //       auto parentAttributes = parent->attributes;
    //       if (parentAttributes.position.has_value() &&
    //           attrs.position.has_value()) {
    //         auto parentPosition = parentAttributes.position.value();
    //         auto position = attrs.position.value();
    //         attrs.position = {
    //           parentPosition.x + position.x, parentPosition.y + position.y
    //         };
    //       }
    //     },
    //     shadow->parent.value()
    //   );
    // }

    return domAttrs;
  };

  dom::attributes::Input mergeAttributes(std::shared_ptr<Input> shadow) {
    dom::attributes::Input domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);
    return domAttrs;
  };

  dom::attributes::Checkbox mergeAttributes(std::shared_ptr<Checkbox> shadow) {
    dom::attributes::Checkbox domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);
    return domAttrs;
  };

  dom::attributes::Select mergeAttributes(std::shared_ptr<Select> shadow) {
    dom::attributes::Select domAttrs = {};
    auto attrs = shadow->attributes;
    auto a = attrs.asMutableTuple();
    auto b = shadow->clickAttributes.asMutableTuple();
    auto c = shadow->hoverAttributes.asMutableTuple();

    utils::replaceTuples(a, b, c);
    return domAttrs;
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
    shadow->attributes = shadow::attributes::getDefaultRootAttributes();
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
    shadow->attributes = shadow::attributes::getDefaultDivAttributes();
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
    shadow->attributes = shadow::attributes::getDefaultTextAttributes();
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
    shadow->attributes = shadow::attributes::getDefaultInputAttributes();
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
    shadow->attributes = shadow::attributes::getDefaultCheckboxAttributes();
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
    shadow->attributes = shadow::attributes::getDefaultSelectAttributes();
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

    if (!realRoot->attributes.size.has_value() ||
        !realRoot->attributes.position.has_value()) {
      return root;
    }

    auto size = realRoot->attributes.size.value();
    auto position = realRoot->attributes.position.value();

    root->attributes.x = {
      .value = position.x, .units = attributes::Units::pixel
    };
    root->attributes.y = {
      .value = position.y, .units = attributes::Units::pixel
    };
    root->attributes.width = {
      .value = size.x, .units = attributes::Units::pixel
    };
    root->attributes.height = {
      .value = size.y, .units = attributes::Units::pixel
    };

    return root;
  }
} // namespace wind::dom::shadow
