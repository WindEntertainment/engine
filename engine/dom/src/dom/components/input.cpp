#include "wind/dom/dom/components/input.hpp"

namespace wind::dom {
  Input::Input(unsigned int id, attributes::Input attributes)
      : UIElement(id), attributes(std::move(attributes)) {};
  void Input::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Input::reset() { attributes = attributes::defaultInputAttributes; };

  void Input::update() {};

} // namespace wind::dom
