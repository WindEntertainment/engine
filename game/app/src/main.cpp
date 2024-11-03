#include "wind/renderer/command-buffer.hpp"
#include "wind/wind.hpp"

#include "wind/asset-manager/asset-manager.hpp"
#include "wind/renderer/assets.hpp"

#include <glm/ext/matrix_transform.hpp>

using uint = unsigned int;

namespace game {

  class Game : public wind::Game {
  public:
    void start() override {
      wind::Engine::setFPS(144);

      wind::AssetManager::loadBundle("res/main.bundle");

      //===================== create sprite //

      auto shader =
        wind::AssetManager::getAsset<wind::Shader>("default-sprite-shader");

      auto texture =
        wind::AssetManager::getAsset<wind::Texture>("main/art/ship.png");

      auto material = std::make_shared<wind::Material>(shader, 1);

      sprite = std::make_shared<wind::Sprite>(material, texture);

      //====================================//

      //=================== create transform //
      transform = glm::mat4(1);
      //====================================//

      wind::Engine::getMainRenderContext()->setCamera(
        std::make_shared<wind::Camera>(
          glm::vec3{0, 0, 1},
          glm::vec3{0, 0, 1},
          glm::vec3{0, 1, 0},
          glm::ivec2{
            wind::Engine::getMainWindow()->size().x / 50,
            wind::Engine::getMainWindow()->size().y / 50
          }
        )
      );
    }

    void handleEvent(SDL_Event& event) override {}

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());

      render.clear({0.0f, 0.0f, 0.05f, 1.f});
      render.drawSprite(sprite, transform);

      render.submit();

      transform = glm::translate(
        transform, {0.f, -0.3f * wind::Engine::getDeltaTime(), 0.f}
      );
    }

    void quit() override {}

  private:
    glm::mat4 transform;
    std::shared_ptr<wind::Sprite> sprite;
  };

} // namespace game

int main(int argc, char** argv) { return wind::Engine::run(new game::Game()); }
