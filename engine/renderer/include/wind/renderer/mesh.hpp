#include "wind/utils/utils.hpp"

namespace wind {

class Mesh {
public:
  struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
  };

  Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices);
  ~Mesh();

  uint id();
  uint length();

private:
  uint VAO, VBO, EBO;
  std::vector<uint> indices;
  std::vector<Vertex> vertices;
};

} // namespace wind