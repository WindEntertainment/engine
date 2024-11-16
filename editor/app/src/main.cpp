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
    std::shared_ptr<wind::dom::shadow::Root> shadowRoot;
    std::shared_ptr<wind::dom::shadow::Root> prevShadowRoot;
    std::shared_ptr<wind::dom::Root> root;
    // std::shared_ptr<projectManager::ProjectManager> projectManager;

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
      shadowRoot = wind::dom::shadow::init(window->size());
      auto prevShadowRoot2 = shadowRoot->deepCopy();
      std::shared_ptr<wind::dom::shadow::Root> qwe =
        std::dynamic_pointer_cast<wind::dom::shadow::Root>(prevShadowRoot2);
      if (qwe) {
        prevShadowRoot = qwe;
      }

      auto button2 =
        wind::dom::shadow::createElement<wind::dom::shadow::Button>();
      button2->attributes.position = {100, 100};

      auto button =
        wind::dom::shadow::createElement<wind::dom::shadow::Button>();
      button->attributes.onClick =
        [&button, &shadowRoot = shadowRoot, button2]() mutable {
          spdlog::info(shadowRoot->children.size());
          if (shadowRoot->children.size() == 1) {
            shadowRoot->appendChild(button2);
          } else {
            shadowRoot->removeChild(button2->id);
          }
        };
      button->attributes.onHover = [button = button]() mutable {
        button->attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
      };

      shadowRoot->appendChild(button);
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      root->display(render);

      render.submit();

      wind::dom::shadow::Diff diff = wind::dom::shadow::Diff();

      wind::dom::shadow::getDiff(prevShadowRoot, shadowRoot, diff);

      wind::dom::shadow::fromDiff(root, diff);

      auto prevShadowRoot2 = shadowRoot->deepCopy();
      std::shared_ptr<wind::dom::shadow::Root> qwe =
        std::dynamic_pointer_cast<wind::dom::shadow::Root>(prevShadowRoot2);
      if (qwe) {
        prevShadowRoot = qwe;
      }
    };

    void quit() override {};
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
