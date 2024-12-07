#include "wind/dom/dom/dom.hpp"

namespace wind::dom {
  std::shared_ptr<Root> init(glm::ivec2 windowSize) {
    auto root = std::make_shared<Root>(1, attributes::Root());
    root->attributes.size = {windowSize.x, windowSize.y};
    root->attributes.position = {0, 0};
    return root;
  };
} // namespace wind::dom
