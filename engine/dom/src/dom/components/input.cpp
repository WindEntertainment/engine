#include "wind/dom/dom/components/input.hpp"

namespace wind::dom {
  Input::Input(unsigned int id, const attributes::Input& attributes)
      : UIElement(id),
        attributes(std::make_shared<attributes::Input>(attributes)) {};
  void Input::render(wind::CommandBuffer& renderer) {
    std::cout << "I'm RichText";
  };

  void Input::update() {};

} // namespace wind::dom
