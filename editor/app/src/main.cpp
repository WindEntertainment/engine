#include "wind/dom/dom/index.hpp"
#include "wind/dom/shadow-dom/index.hpp"
#include <editor/editor.hpp>
#include <editor/main.hpp>

#include "wind/asset-pipeline/asset-manager.hpp"

#include "wind/renderer/command-buffer.hpp"
#include "wind/renderer/procedural-graphics.hpp"

#include "wind/input-system/input-system.hpp"

namespace editor {
  class Editor : public wind::Game {
    std::shared_ptr<wind::dom::Root> root;
    std::shared_ptr<wind::dom::shadow::Root> shadowRoot =
      wind::dom::shadow::init();
    std::shared_ptr<wind::dom::shadow::Root> prevShadowRoot =
      std::make_shared<wind::dom::shadow::Root>(shadowRoot->id);

    bool isButtonsVisible = false;

  public:
    void start() override {
      wind::Engine::setTargetFPS(60);
      auto window = wind::Engine::getMainWindow();
      auto rendererContext = wind::Engine::getMainRenderContext();

      wind::Engine::getMainRenderContext()->setCamera(
        std::make_shared<wind::Camera>(
          glm::vec3{0, 0, 1},
          glm::vec3{0, 0, 1},
          glm::vec3{0, 1, 0},
          glm::ivec2{
            wind::Engine::getMainWindow()->size().x,
            wind::Engine::getMainWindow()->size().y
          }
        )
      );

      root = wind::dom::init(window->size());
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      wind::dom::shadow::nextId = 1;

      std::shared_ptr<wind::dom::shadow::Div> button =
        wind::dom::shadow::createElement<wind::dom::shadow::Div>();

      button->attributes.onClick = [&isButtonsVisible = isButtonsVisible,
                                    &shadowRoot = shadowRoot]() mutable {
        isButtonsVisible = shadowRoot->children.size() == 1;
      };

      auto a = wind::dom::shadow::Element(shadowRoot);
      appendChild(button, a);
      if (isButtonsVisible) {
        std::shared_ptr<wind::dom::shadow::Div> button2 =
          wind::dom::shadow::createElement<wind::dom::shadow::Div>();
        button2->attributes.position = {100, 100};

        std::shared_ptr<wind::dom::shadow::Div> button3 =
          wind::dom::shadow::createElement<wind::dom::shadow::Div>();
        button3->attributes.position = {200, 200};

        wind::dom::shadow::appendChild(button2, a);
        wind::dom::shadow::appendChild(button3, a);
      }

      wind::dom::shadow::Diff diff = wind::dom::shadow::Diff();
      wind::dom::shadow::getDiff(prevShadowRoot, shadowRoot, diff);
      wind::dom::shadow::fromDiff(root, diff);
      prevShadowRoot = shadowRoot;

      root->display(render);

      render.submit();

      shadowRoot = std::make_shared<wind::dom::shadow::Root>(shadowRoot->id);
    };

    void quit() override {
      shadowRoot->destroy();
      prevShadowRoot->destroy();
    };
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
