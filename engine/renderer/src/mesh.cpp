#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/mesh.hpp"

namespace wind {

  Mesh::Mesh(std::vector<Vertex>& meshVertices, std::vector<uint>& meshIndices)
      : vertices(meshVertices), indices(meshIndices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
      GL_ARRAY_BUFFER,
      vertices.size() * sizeof(Vertex),
      &vertices[0],
      GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
      GL_ELEMENT_ARRAY_BUFFER,
      indices.size() * sizeof(uint),
      &indices[0],
      GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)
    );

    glBindVertexArray(0);
  }

  Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  uint Mesh::id() { return VAO; }

  uint Mesh::length() { return indices.size(); }

} // namespace wind