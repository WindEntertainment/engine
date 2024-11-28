#include "wind/dom/dom/index.hpp"
#include "wind/dom/shadow-dom/index.hpp"
#include <wind/utils/utils.hpp>
#include "wind/wind.hpp"
#include "wind/asset-pipeline/asset-manager.hpp"

#include "wind/renderer/command-buffer.hpp"
#include "wind/renderer/procedural-graphics.hpp"

#include "wind/input-system/input-system.hpp"

namespace editor {
  using namespace wind::dom::shadow;
  namespace dom = wind::dom;

  template <typename T>
  using shared = std::shared_ptr<T>;

  class Editor : public wind::Game {
    shared<dom::Root> root;
    shared<Root> shadowRoot;
    shared<Root> prevShadowRoot;

    shared<wind::Font> font = nullptr;

    bool isButtonsVisible = false;

  public:
    void start() override {
      wind::Engine::setTargetFPS(60);

      wind::AssetManager::loadBundle("res/main.bundle");

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

      root = dom::init(window->size());
      shadowRoot = init(root);
      prevShadowRoot = std::make_shared<Root>(shadowRoot->id);

      font = wind::AssetManager::getAsset<wind::Font>(
        "main/fonts/SourGummy-VariableFont.ttf"
      );

      auto example = createElement<Div>();

      mergeAttributes2(example);
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      nextId = 1;

      shadowRoot->attributes.backgroundColor = glm::vec4{0.3f, 0.2f, 0.8f, 1.f};

      auto button = createElement<Div>();
      button->attributes.size = {100, 100};
      button->attributes.onClick = [&isButtonsVisible = isButtonsVisible,
                                    &shadowRoot = shadowRoot](auto) mutable {
        isButtonsVisible = shadowRoot->children.size() == 1;
      };
      appendChild(button, shadowRoot);

      if (isButtonsVisible) {
        auto button2 = createElement<Div>();
        button2->attributes.position = {100, 100};
        button2->attributes.size = {100, 100};

        auto button3 = createElement<Div>();
        button3->attributes.position = {200, 200};
        button3->attributes.size = {100, 100};

        auto text = createElement<Text>();
        text->attributes.value = "CHIKI BRIKI";
        text->attributes.color = glm::vec4{1.f, 0.5f, 0.1f, 1.f};
        text->attributes.font = font;

        appendChild(text, button2);
        appendChild(button2, shadowRoot);
        appendChild(button3, shadowRoot);
      }

      auto diff = Diff();
      getDiff(prevShadowRoot, shadowRoot, diff);
      fromDiff(root, diff);

      root->display(render);
      render.submit();

      destroy(prevShadowRoot);
      prevShadowRoot = shadowRoot;
      shadowRoot = std::make_shared<Root>(shadowRoot->id);
      shadowRoot->attributes.size = root->attributes.size;
      shadowRoot->attributes.position = root->attributes.position;
    };

    void quit() override {
      destroy(shadowRoot);
      destroy(prevShadowRoot);
    };
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
