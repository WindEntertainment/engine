#pragma once
#include "wind/renderer/material.hpp"
#include "wind/renderer/mesh.hpp"

namespace wind {

struct Object {
  std::vector<Mesh&> meshes;
  std::vector<Material&> material;
};

} // namespace wind