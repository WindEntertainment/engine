#include "wind/dom/dom/components/div.hpp"

namespace wind::dom {
  Div::Div(unsigned int id, attributes::Div attributes)
      : UIElement(id), attributes(std::move(attributes)) {};
  void Div::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Div::reset() { attributes = attributes::defaultDivAttributes; };

  void Div::update() {};
} // namespace wind::dom
