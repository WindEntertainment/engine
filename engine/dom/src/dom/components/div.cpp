#include "wind/dom/dom/components/div.hpp"

namespace wind::dom {
  Div::Div(unsigned int id, const attributes::Div& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Div>(attributes)) {};
  void Div::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Div::update() {};
} // namespace wind::dom
