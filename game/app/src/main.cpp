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
      wind::AssetManager::loadBundle("res/main.bundle");

      //======================= create mesh //
      std::vector<wind::Mesh::Vertex> vertices = {
        {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}
      };
      std::vector<uint> indices = {0, 1, 3, 1, 2, 3};

      mesh = new wind::Mesh(vertices, indices);
      //====================================//

      //===================== create shader //
      shader = new wind::Shader(
        R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            out vec2 TexCoord;

            void main() {
                gl_Position = view * projection * model * vec4(aPos, 1.0);
                TexCoord = aTexCoords;
            }
        )",
        R"(
            #version 330 core

            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D tex0;

            void main() {
                FragColor = texture(tex0, TexCoord);
            }
    )"
      );
      //====================================//

      //=================== create material //

      texture =
        wind::AssetManager::getAsset<wind::Texture>("main/art/ship.png");

      material = new wind::Material(shader);
      material->setTexture(texture);

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
      render.drawMesh(mesh, transform, material);

      render.submit();

      transform = glm::translate(
        transform, {0.f, -0.3f * wind::Engine::getDeltaTime(), 0.f}
      );
    }

    void quit() override {
      delete mesh;
      delete material;
      delete shader;
    }

  private:
    wind::Texture* texture;
    wind::Mesh* mesh;
    wind::Shader* shader;
    wind::Material* material;
    glm::mat4 transform;
  };

} // namespace game

int main(int argc, char** argv) { return wind::Engine::run(new game::Game()); }
