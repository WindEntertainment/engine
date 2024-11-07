#pragma once
#include "wind/utils/utils.hpp"

namespace wind {

  class Mesh {
  public:
    struct Vertex {
      glm::vec3 position;
      glm::vec2 texCoord;
    };

    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
    Mesh(
      const std::vector<Vertex>&& vertices,
      const std::vector<uint>&& indices
    );
    ~Mesh();

    uint id();
    uint length();

  private:
    uint VAO, VBO, EBO;
    std::vector<uint> indices;
    std::vector<Vertex> vertices;

    void generateBuffers();
  };

} // namespace wind