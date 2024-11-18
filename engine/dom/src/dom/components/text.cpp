#include "wind/dom/dom/components/text.hpp"

namespace wind::dom {
  Text::Text(unsigned int id, const attributes::Text& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Text>(attributes)) {};

  void Text::render(wind::CommandBuffer& renderer) { std::cout << "I'm Text"; };

  void Text::update() {};
} // namespace wind::dom
