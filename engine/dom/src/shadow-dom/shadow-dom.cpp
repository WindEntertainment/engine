#include "wind/dom/shadow-dom/shadow-dom.hpp"

namespace wind::dom::shadow {
  std::shared_ptr<Root> init(glm::ivec2 windowSize) {
    auto root = std::make_shared<Root>();
    return root;
  };

} // namespace wind::dom::shadow
