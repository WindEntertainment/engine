#include "wind/dom/dom/components/select.hpp"

namespace wind::dom {
  Select::Select(unsigned int id, const attributes::Select& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Select>(attributes)) {};
  void Select::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Select::update() {};
} // namespace wind::dom
