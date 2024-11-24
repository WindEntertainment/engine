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
    // wind::dom::shadow::Element shadowRoot =
    //   wind::dom::shadow::Element(wind::dom::shadow::Root());
    // wind::dom::shadow::Element prevShadowRoot =
    //   wind::dom::shadow::Element(wind::dom::shadow::Root());
    std::shared_ptr<wind::dom::Root> root;
    wind::dom::shadow::Root shadowRoot = wind::dom::shadow::Root();
    wind::dom::shadow::Root prevShadowRoot = shadowRoot;
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
      prevShadowRoot.tree = std::make_shared<wind::dom::shadow::Tree>();

      // shadowRoot = wind::dom::shadow::init(window->size());
      // prevShadowRoot = shadowRoot.deepCopy();
      // std::shared_ptr<wind::dom::shadow::Root> qwe =
      //   std::dynamic_pointer_cast<wind::dom::shadow::Root>(prevShadowRoot2);
      // if (prevShadowRoot2.) {
      //   prevShadowRoot = prevShadowRoot2;
      // }

      // wind::dom::shadow::Button button2 = wind::dom::shadow::Button();
      // // wind::dom::shadow::createElement<wind::dom::shadow::Button>();
      // // auto a = button2.getAttributes<wind::dom::attributes::Button>();
      // // if (a.has_value()) {
      // button2.attributes.position = {100, 100};
      // // }

      // std::visit(
      //   [](const wind::dom::shadow::ElementVariants& button) -> void {
      //     if constexpr (!std::is_same_v<
      //                     std::decay_t<decltype(button)>,
      //                     std::monostate>) {
      //       // Only call log if the type is not std::monostate
      //       button.
      //     };
      //     // using T = std::decay_t<decltype(button)>;
      //     // if constexpr (!std::is_same_v<T, std::monostate>) {
      //     //   button.attributes.position = {100, 100};
      //     // };
      //     // if constexpr (!std::is_same_v<T, std::monostate>) {
      //     //   return;
      //     // } else {
      //     //   button.
      //     // };
      //   },
      //   button2.item
      // );
      // button2->attributes->position = {100, 100};

      // wind::dom::shadow::Button button = wind::dom::shadow::Button();
      // // wind::dom::shadow::createElement<wind::dom::shadow::Button>();
      // spdlog::info(
      //   "{} {} {} {}", shadowRoot.id, prevShadowRoot.id, root->id, button.id
      // );

      // button.attributes.onClick =
      //   [&button, &shadowRoot = shadowRoot, &button2]() mutable {
      //     auto a = wind::dom::shadow::Element(shadowRoot);
      //     // spdlog::info(shadowRoot.children.size());
      //     if (shadowRoot.tree->children.size() == 1) {
      //       spdlog::info(button2.id);
      //       // wind::dom::shadow::appendChild(button2, a);
      //     } else {
      //       // wind::dom::shadow::removeChild(button2.id, a);
      //     }
      //   };
      // button.attributes.onHover = [button, &shadowRoot = shadowRoot]()
      // mutable {
      //   spdlog::info("HOVER");
      //   // button.attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
      //   // using T = std::decay_t<decltype(shadowRoot.tree->children[0])>;
      //   // if (std::is_same_v<T, wind::dom::shadow::Button>) {
      //   //   ;
      //   // };
      // std::visit(
      //   [](auto& elem) -> void {
      //     elem.attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
      //     // elem
      //     // spdlog::info(
      //     //   "{} {} {} {}",
      //     //   elem.id,
      //     //   elem.attributes.backgroundColor.x,
      //     //   elem.attributes.backgroundColor.y,
      //     //   elem.attributes.backgroundColor.z
      //     // );
      //   },
      //   shadowRoot.tree->children[0]
      // );
      //   spdlog::info(
      //     "{} {} {} {}",
      //     button.id,
      //     button.attributes.backgroundColor.x,
      //     button.attributes.backgroundColor.y,
      //     button.attributes.backgroundColor.z
      //   );
      // };

      // wind::dom::shadow::UIElement::InnerElementPtr element123 =
      //   std::make_shared<wind::dom::shadow::UIElement<
      //     wind::dom::shadow::Button,
      //     wind::dom::Button,
      //     wind::dom::attributes::Button>>(button);
      // appendChild(button, a);

      // auto a = wind::dom::shadow::Element(shadowRoot);
      // appendChild(button, a);
      // spdlog::info(shadowRoot.tree->children.size());
      // spdlog::info(prevShadowRoot.tree->children.size());

      // wind::dom::shadow::Diff diff = wind::dom::shadow::Diff();
      // wind::dom::shadow::getDiff(prevShadowRoot, shadowRoot, diff);

      // wind::dom::shadow::fromDiff(root, diff);
      // prevShadowRoot = shadowRoot;
    };

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    };

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());
      render.clear({0.0f, 0.0f, 0.05f, 1.f});

      wind::dom::shadow::nextId = 2;
      shadowRoot.tree = std::make_shared<wind::dom::shadow::Tree>();

      spdlog::info(wind::dom::shadow::nextId);
      wind::dom::shadow::Button button =
        wind::dom::shadow::Button(wind::dom::shadow::nextId++);
      button.attributes.onHover =
        [&button, &shadowRoot = shadowRoot, &root = root]() mutable {
          spdlog::info(!!root->findElementById(root, 2));
          std::shared_ptr<wind::dom::Button> attrs =
            std::dynamic_pointer_cast<wind::dom::Button>(
              root->findElementById(root, 2)
            );

          spdlog::info(!!attrs);

          attrs->attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
          spdlog::info("HOVER");
          std::visit(
            [](auto& elem) -> void {
              elem.attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
              // elem
              spdlog::info(
                "{} {} {} {}",
                elem.id,
                elem.attributes.backgroundColor.x,
                elem.attributes.backgroundColor.y,
                elem.attributes.backgroundColor.z
              );
            },
            shadowRoot.tree->children[0]
          );
          // button.attributes.backgroundColor = glm::vec4{1.f, 0.f, 1.f, 1.f};
        };

      spdlog::info(button.id);

      auto a = wind::dom::shadow::Element(shadowRoot);
      appendChild(button, a);

      wind::dom::shadow::Diff diff = wind::dom::shadow::Diff();
      wind::dom::shadow::getDiff(prevShadowRoot, shadowRoot, diff);
      spdlog::info(
        "{} {} {}", diff.added.size(), diff.updated.size(), diff.removed.size()
      );

      std::visit(
        [](auto& elem) -> void {
          spdlog::info(elem.attributes.backgroundColor.x);
        },
        diff.updated[0]
      );

      wind::dom::shadow::fromDiff(root, diff);
      prevShadowRoot = shadowRoot;
      // shadowRoot.tree = std::make_shared<wind::dom::shadow::Tree>();

      root->display(render);

      render.submit();

      // shadowRoot =

      // std::shared_ptr<wind::dom::shadow::Root> qwe =
      //   std::dynamic_pointer_cast<wind::dom::shadow::Root>(prevShadowRoot2);
      // if (prevShadowRoot2) {
      //   prevShadowRoot = prevShadowRoot2;
      // }
    };

    void quit() override {};
  };
} // namespace editor

int main(int argc, char** argv) {
  return wind::Engine::run(new editor::Editor());
}
