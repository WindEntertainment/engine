#include "wind/wind.hpp"

#include "wind/asset-pipeline/asset-manager.hpp"

#include "wind/renderer/command-buffer.hpp"
#include "wind/renderer/procedural-graphics.hpp"

#include "wind/input-system/input-system.hpp"

#include "wind/language/language.hpp"

#include <glm/ext/matrix_transform.hpp>

using uint = unsigned int;

namespace game {

  class Game : public wind::Game {
  public:
    void start() override {
      wind::Engine::setTargetFPS(144);

      wind::AssetManager::loadBundle("res/main.bundle");

      //===================== load texture //

      animeTexture =
        wind::AssetManager::getAsset<wind::Texture>("main/art/anime.png");

      stoneTexture =
        wind::AssetManager::getAsset<wind::Texture>("main/art/stone.png");

      //===================== create sprite //

      auto shader =
        wind::AssetManager::getAsset<wind::Shader>("default-sprite-shader");

      auto material = std::make_shared<wind::Material>(shader, 1);

      auto spriteTexture =
        wind::AssetManager::getAsset<wind::Texture>("main/art/ship.png");

      sprite = std::make_shared<wind::Sprite>(material, spriteTexture);

      transform = glm::mat4(1);
      transform = glm::translate(transform, {-350.f, -200.f, 0});
      transform = glm::rotate(transform, glm::radians(-90.f), {0.f, 0.f, 1.f});
      transform = glm::scale(transform, {100, 100, 1});

      //============== create texts meshes //

      fontHostGrotesk =
        wind::AssetManager::getAsset<wind::Font>("main/fonts/OpenSans-Bold.ttf"
        );
      fontSourGummy = wind::AssetManager::getAsset<wind::Font>(
        "main/fonts/SourGummy-VariableFont.ttf"
      );

      textSample = std::make_shared<wind::TextMesh>();
      textSample->font = fontSourGummy;
      textSample->letterSpacing = 0;
      textSample->lineSpacing = 12;
      textSample->lineWidth = 250;
      textSample->setText("Hello, World! Tell me something about this "
                          "application\nThis is new line");

      textFPS = std::make_shared<wind::TextMesh>();
      textFPS->font = fontSourGummy;
      textFPS->letterSpacing = 0;

      //=================== create camera //

      wind::Engine::getMainRenderContext()->setCamera(
        std::make_shared<wind::Camera>(
          glm::vec3{0, 0, -1},
          glm::vec3{0, 0, -1},
          glm::vec3{0, 1, 0},
          glm::ivec2{
            wind::Engine::getMainWindow()->size().x,
            wind::Engine::getMainWindow()->size().y
          }
        )
      );

      wind::InputSystem::addTrigger(
        "player-move-up",
        wind::Key{
          .keycode = wind::Keycode::K_S, .action = wind::KeyAction::Pressed
        },
        new std::function([&velocity=velocity, speed=speed](std::shared_ptr<wind::InputSystemContext> ctx) {
          velocity = -speed;
        })
      );
      wind::InputSystem::addTrigger(
        "player-move-down",
        wind::Key{
          .keycode = wind::Keycode::K_W, .action = wind::KeyAction::Pressed
        },
        new std::function([&velocity = velocity, speed = speed](std::shared_ptr<wind::InputSystemContext> ctx) { 
            velocity = speed;
        })
      );
      wind::InputSystem::addTrigger(
        "player-move-left",
        wind::Key{
          .keycode = wind::Keycode::K_A, .action = wind::KeyAction::Pressed
        },
        new std::function([&angularVelocity = angularVelocity, speed = speed](std::shared_ptr<wind::InputSystemContext> ctx) {
          angularVelocity = speed;
         })
      );
      wind::InputSystem::addTrigger(
        "player-move-right",
        wind::Key{
          .keycode = wind::Keycode::K_D, .action = wind::KeyAction::Pressed
        },
        new std::function([&angularVelocity = angularVelocity, speed = speed](std::shared_ptr<wind::InputSystemContext> ctx) {
          angularVelocity = -speed;
        })
      );
    }

    void handleEvent(SDL_Event& event) override {
      wind::InputSystem::handleEvent(event);
    }

    void update() override {
      wind::CommandBuffer render(wind::Engine::getMainRenderContext());

      static const auto circle = wind::ProceduralGraphics::genCircle(8);

      textFPS->setText(fmt::format("fps: {}", wind::Engine::getFPS()));

      render.clear({0.4f, 0.4f, 0.4f, 1.f});
      render.drawSprite(sprite, transform);

      render.drawCircle(
        circle, {200, 175.f}, 100, {1.f, 1.f, 1.f, 1.f}, animeTexture
      );

      render.drawText(
        textSample, {-150.f, 250.f}, {0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}
      );
      render.drawText(
        textFPS, {-390.f, 270.f}, {1.f, 1.f}, {1.f, 1.f, 1.f, 1.f}
      );

      render.drawText(
        fontHostGrotesk,
        "radius: 1.0",
        {-330.f, 180.f},
        {0.4f, 0.4f},
        {1.f, 1.f, 1.f, 1.f}
      );

      render.drawRect(
        {-300.f, 105.f},
        {100.f, 100.f},
        {1.f, 1.0f, 1.0f, 1.f},
        stoneTexture,
        0,
        1.f,
        0.04f,
        {0.8f, 0.8f, 0.8f, 1.f}
      );

      render.drawRect(
        {-100.f, 105.f},
        {200.f, 100.f},
        {0.0f, 0.0f, 0.0f, 0.f},
        nullptr,
        0,
        0.05f,
        0.025f,
        {0.1f, 0.1f, 0.1f, 1.f}
      );

      for (int i = 0; i < 10; ++i) {
        render.drawText(
          fontHostGrotesk,
          fmt::format("radius: {:.1f}", i / 10.f),
          {-375.f + i * 75.f, 0.f},
          {0.4f, 0.4f},
          {1.f, 1.f, 1.f, 1.f}
        );

        render.drawRect(
          {-340.f + i * 75.f, -50.f},
          {50.f, 50.f},
          {0.8f, 0.2f, 0.2f, 1.f},
          nullptr,
          0,
          i / 10.f,
          0.04f,
          {0, 0, 0, 1}
        );
      }

      render.submit();

      transform = glm::translate(
        transform,
        {0, velocity * wind::Engine::getDeltaTime(), 0.f}
      );
      transform = glm::rotate(
        transform, angularVelocity * wind::Engine::getDeltaTime(), {0, 0, 1}
      );
      
      auto pos = transform * glm::vec4{0, 0, 0, 1};
      if (pos.x >= 400) {
        transform = glm::mat4(1);
        transform = glm::translate(transform, {-400.f, -200.f, 0});
        transform =
          glm::rotate(transform, glm::radians(-90.f), {0.f, 0.f, 1.f});
        transform = glm::scale(transform, {100, 100, 1});
      }
    }

    void quit() override {}

  private:
    std::shared_ptr<wind::Sprite> sprite;
    glm::mat4 transform;

    float velocity;
    float angularVelocity;
    const float speed = 0.5f;

    std::shared_ptr<wind::Texture> animeTexture;
    std::shared_ptr<wind::Texture> stoneTexture;

    std::shared_ptr<wind::TextMesh> textSample;
    std::shared_ptr<wind::TextMesh> textFPS;

    std::shared_ptr<wind::Font> fontSourGummy;
    std::shared_ptr<wind::Font> fontHostGrotesk;
  };

} // namespace game

int main(int argc, char** argv) { return wind::Engine::run(new game::Game()); }
