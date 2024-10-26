#include "wind/renderer/command-buffer.hpp"
#include "wind/wind.hpp"

#include <glm/ext/matrix_transform.hpp>

using uint = unsigned int;

namespace game {

class Game : public wind::Game {
public:
  void start() override {
    //======================= create mesh //
    std::vector<wind::Mesh::Vertex> vertices = {
      {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}};
    std::vector<uint> indices = {0, 1, 3, 1, 2, 3};

    mesh = new wind::Mesh(vertices, indices);
    //====================================//

    //===================== create shader //
    // shader = new wind::Shader(R"(
    //         #version 330 core

    //         layout (location = 0) in vec3 aPos;
    //         layout (location = 1) in vec2 aTexCoords;

    //         uniform mat4 model;
    //         out vec2 TexCoord;

    //         void main() {
    //             gl_Position = vec4(aPos, 1.0);
    //             TexCoord = aTexCoords;
    //         }
    //     )",
    //   R"(
    //         #version 330 core

    //         out vec4 FragColor;
    //         in vec2 TexCoord;

    //         void main() {
    //             FragColor = vec4(1, 1, 1, 1);
    //         }
    // )");
    //====================================//

    //=================== create material //

    // material = new wind::Material(shader);

    //====================================//

    //=================== create transform //
    transform = glm::mat4(1);
    transform = glm::translate(transform, {0, 0, -5});
    //====================================//
  }

  void update() override {
    wind::CommandBuffer render;

    render.clear({0.2f, 0.2f, 0.5f, 1.f});
    // render.drawMesh(mesh, transform, material);

    render.submit();
  }

  void quit() override {
    // delete mesh;
    // delete material;
    // delete shader;
  }

private:
  wind::Mesh* mesh;
  wind::Shader* shader;
  wind::Material* material;
  glm::mat4 transform;
};

} // namespace game

int main(int argc, char** argv) {
  return wind::Engine::run(new game::Game());
}