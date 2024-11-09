#include "bindings/imgui_impl_opengl3.h"
#include "bindings/imgui_impl_sdl2.h"
#include "wind/dom/dom.hpp"
#include "wind/input-system/input-system.hpp"
#include "wind/renderer/command-buffer.hpp"

#include <editor/editor.hpp>
#include <editor/main.hpp>

namespace editor {
  class Editor : public wind::Game {
    std::shared_ptr<wind::Root> root;
    std::shared_ptr<projectManager::ProjectManager> projectManager;

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

      root = wind::init();

      projectManager = wind::share(projectManager::ProjectManager());
      projectManager->loadProject();
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      auto button = wind::createElement<wind::Button>();

      root->appendChild(button);

      root->display(render);

      render.submit();
    };

    void quit() override { root->destroy(); };
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
