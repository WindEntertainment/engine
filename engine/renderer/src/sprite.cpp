#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/sprite.hpp"

namespace wind {

  Sprite::Sprite(
    std::shared_ptr<Material> material,
    std::shared_ptr<Texture> texture
  ) {
    setTexture(texture);
    setMaterial(material);

    vertices = {
      {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}
    };
    indices = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
      GL_ARRAY_BUFFER,
      vertices.size() * sizeof(Mesh::Vertex),
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
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Mesh::Vertex),
      (void*)offsetof(Mesh::Vertex, texCoord)
    );

    glBindVertexArray(0);
  }

  Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  uint Sprite::id() const { return VAO; }
  uint Sprite::length() const { return indices.size(); }

  std::shared_ptr<Material> Sprite::getMaterial() { return material; }

  std::shared_ptr<Texture> Sprite::getTexture() { return texture; }

  void Sprite::setMaterial(std::shared_ptr<Material> material) {
    this->material = material;
    if (texture)
      material->setTexture(texture);
  }

  void Sprite::setTexture(std::shared_ptr<Texture> texture) {
    this->texture = texture;
    if (material)
      material->setTexture(texture, 0);
  }

} // namespace wind