#pragma once
#include "wind/utils/utils.hpp"
#include "wind/renderer/material.hpp"
#include "wind/renderer/texture.hpp"
#include "wind/renderer/mesh.hpp"

namespace wind {

  class Sprite {
  public:
    Sprite(std::shared_ptr<Material>, std::shared_ptr<Texture>);
    ~Sprite();

    [[nodiscard]] uint id() const;
    [[nodiscard]] uint length() const;

    std::shared_ptr<Material> getMaterial();
    std::shared_ptr<Texture> getTexture();

    void setMaterial(std::shared_ptr<Material>);
    void setTexture(std::shared_ptr<Texture>);

  private:
    uint VAO, VBO, EBO;
    std::vector<uint> indices;
    std::vector<Mesh::Vertex> vertices;

    std::shared_ptr<Material> material;
    std::shared_ptr<Texture> texture;
  };

} // namespace wind