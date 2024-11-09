#pragma once
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/texture.hpp"
#include "wind/renderer/assets.hpp"

#include <glm/gtc/constants.hpp>
#include <memory>

namespace wind {

  class CircleMesh : public Mesh {
  public:
    CircleMesh(
      const std::vector<Vertex>& vertices,
      const std::vector<uint>& indices
    )
        : Mesh(vertices, indices) {}
  };

  class ProceduralGraphics {
  public:
    static std::shared_ptr<CircleMesh> genCircle(const int numSegments) {
      std::vector<Mesh::Vertex> vertices;
      std::vector<unsigned int> indices;

      const float segmentAngle = 2.f * glm::pi<float>() / numSegments;

      vertices.emplace_back(Mesh::Vertex{{0, 0, 0}, {0.5f, 0.5f}});

      for (int i = 0; i < numSegments; ++i) {
        float angle = i * segmentAngle;
        float c = cosf(angle), s = sinf(angle);

        vertices.emplace_back(
          Mesh::Vertex{{c, s, 0.f}, {0.5f + 0.5f * c, 0.5f + 0.5f * s}}
        );
      }

      for (int i = 1; i <= numSegments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back((i % numSegments) + 1);
      }

      return std::shared_ptr<CircleMesh>(new CircleMesh(vertices, indices));
    }
  };

} // namespace wind