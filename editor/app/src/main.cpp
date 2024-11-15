#include "wind/dom/dom.hpp"
#include "wind/dom/shadow-dom.hpp"
#include <editor/editor.hpp>
#include <editor/main.hpp>

#include "wind/asset-pipeline/asset-manager.hpp"

#include "wind/renderer/command-buffer.hpp"
#include "wind/renderer/procedural-graphics.hpp"

#include "wind/input-system/input-system.hpp"

namespace editor {
  class Editor : public wind::Game {
    std::shared_ptr<wind::shadowDom::Root> shadowRoot;
    std::shared_ptr<wind::shadowDom::Root> prevShadowRoot;
    std::shared_ptr<wind::dom::Root> root;
    // std::shared_ptr<projectManager::ProjectManager> projectManager;

    std::string vectorToString(
      const std::vector<std::shared_ptr<wind::shadowDom::UIElement>> vec
    ) {
      std::ostringstream oss;
      for (size_t i = 0; i < vec.size(); ++i) {
        oss << "vec[" << i << "].id=" << vec[i]->id;
        if (i < vec.size() - 1) { // Add a comma except after the last element.
          oss << ", ";
        }
      }
      return oss.str();
    };

    std::string
    vectorToString2(const std::vector<std::pair<
                      const unsigned int,
                      std::shared_ptr<wind::shadowDom::UIElement>>> p) {
      std::ostringstream oss;
      for (size_t i = 0; i < p.size(); ++i) {
        oss << "from: " << p[i].first << " to vec[" << i
            << "].id= " << p[i].second->id;
        if (i < p.size() - 1) { // Add a comma except after the last element.
          oss << ", ";
        }
      }
      return oss.str();
    };

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
      shadowRoot = wind::shadowDom::init(window->size());
      prevShadowRoot = std::make_shared<wind::shadowDom::Root>(*shadowRoot);

      auto button2 = wind::shadowDom::createElement<wind::shadowDom::Button>();
      button2->attributes.position = {100, 100};

      auto button = wind::shadowDom::createElement<wind::shadowDom::Button>();
      button->attributes.onClick =
        [&button, &shadowRoot = shadowRoot, button2]() mutable {
          spdlog::info("CLICK");
          if (shadowRoot->children.size() == 1) {
            shadowRoot->appendChild(button2);
            spdlog::info("AFTER CLICK, {}", !!shadowRoot->children[1]->parent);
          } else {
            shadowRoot->removeChild(button2->id);
          }
        };
      button->attributes.onHover = [button = button]() mutable {
        spdlog::info("HOVER");
        button->attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
        spdlog::info(button->attributes.backgroundColor.x);
      };

      shadowRoot->appendChild(button);

      // wind::shadowDom::Diff diff = wind::shadowDom::Diff();

      // wind::shadowDom::getDiff(prevShadowRoot, shadowRoot, diff);

      // spdlog::info(
      //   "added: {}; \n removed: {}; \n updated: {}; \n replaced: {}; \n",
      //   diff.added.size(),
      //   diff.removed.size(),
      //   diff.updated.size(),
      //   diff.replaced.size()
      // );

      // wind::shadowDom::fromDiff(root, diff);

      // shadowRoot->removeChild(text2);

      // wind::shadowDom::Diff diff = wind::shadowDom::Diff();

      // wind::shadowDom::getDiff(initialShadowRoot, shadowRoot, diff);

      // wind::shadowDom::fromDiff(root, diff);

      // spdlog::info(
      //   "added: {}; \n removed: {}; \n updated: {}; \n replaced: {}; \n",
      //   diff.added.size(),
      //   diff.removed.size(),
      //   diff.updated.size(),
      //   diff.replaced.size()
      // );
      // spdlog::info(
      //   "added: {}; \n removed: {}; \n updated: {}; \n replaced: {}; \n",
      //   vectorToString(diff.added),
      //   vectorToString(diff.removed),
      //   vectorToString(diff.updated),
      //   vectorToString2(diff.replaced)
      // );

      // projectManager = wind::share(projectManager::ProjectManager());
      // projectManager->loadProject();
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      // spdlog::info(shadowRoot->children.size());

      // auto button2 =
      // wind::shadowDom::createElement<wind::shadowDom::Button>();
      // button2->attributes.position = {100, 100};

      // auto button =
      // wind::shadowDom::createElement<wind::shadowDom::Button>();
      // button->attributes.onClick =
      //   [&button, &shadowRoot = shadowRoot, button2]() mutable {
      //     spdlog::info("CLICK");
      //     if (shadowRoot->children.size() == 1) {
      //       shadowRoot->appendChild(button2);
      //       spdlog::info("AFTER CLICK, {}",
      //       !!shadowRoot->children[1]->parent);
      //     } else {
      //       shadowRoot->removeChild(button2->id);
      //     }
      //   };
      // button->attributes.onHover = [&button]() {
      //   button->attributes.backgroundColor = {1.f, 0.f, 1.f, 1.f};
      // };

      // shadowRoot->appendChild(button);

      // auto button = wind::shadowDom::createElement<wind::shadowDom::Button>();

      // button->attributes.onClick = [&button]() {
      //   button->attributes.backgroundColor = {1.f, 1.f, 0.f, 1.f};
      // };

      // button->attributes.onHover = [&button]() {
      //   button->attributes.backgroundColor = {1.f, 0.f, 1.f, 1.f};
      // };

      // shadowRoot->appendChild(button);

      root->display(render);

      render.submit();

      wind::shadowDom::Diff diff = wind::shadowDom::Diff();

      // if (prevShadowRoot->children.size() == 2) {
      //   for (auto&& i : prevShadowRoot->children) {
      //     spdlog::info("CHILD: {}, PARENT: {}", i->id, !!i->parent);
      //   }
      // }

      wind::shadowDom::getDiff(prevShadowRoot, shadowRoot, diff);

      if (diff.added.size() > 0 || diff.removed.size() > 0 ||
          diff.updated.size() > 0 || diff.replaced.size() > 0) {
        spdlog::info(
          "added: {}; \n removed: {}; \n updated: {}; \n replaced: {}; \n",
          diff.added.size(),
          diff.removed.size(),
          diff.updated.size(),
          diff.replaced.size()
        );
      }

      wind::shadowDom::fromDiff(root, diff);

      prevShadowRoot = std::make_shared<wind::shadowDom::Root>(*shadowRoot);
    };

    void quit() override {};
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
