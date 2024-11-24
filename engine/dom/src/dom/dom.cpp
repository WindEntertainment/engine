#include "wind/dom/dom/dom.hpp"

namespace wind::dom {
  std::shared_ptr<Root> init(glm::ivec2 windowSize) {
    auto root = std::make_shared<Root>(1, attributes::Root());
    return root;
  };
} // namespace wind::dom
