#include "wind/wind.hpp"
#include "wind/asset-pipeline/asset-manager.hpp"
#include "wind/renderer/shader.hpp"
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/material.hpp"

#include <glm/gtc/constants.hpp>

namespace wind {

  void Engine::addDefaultAssets() {
    AssetManager::addAsset(
      "default-sprite-shader",
      std::make_shared<wind::Shader>(
        R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            uniform mat4 uModel;
            uniform mat4 uView;
            uniform mat4 uProjection;

            out vec2 TexCoord;

            void main() {
                gl_Position = uView * uProjection * uModel * vec4(aPos, 1.0);
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
      )
    );

    AssetManager::addAsset(
      "default-ui-shader",
      std::make_shared<wind::Shader>(
        R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            uniform mat4 uModel;
            uniform mat4 uProjection;

            out vec2 texCoord;

            void main() {
                gl_Position = uProjection * uModel * vec4(aPos, 1.0);
                texCoord = aTexCoords;
            }
        )",
        R"(
            #version 330 core

            out vec4 FragColor;
            in vec2 texCoord;
            in vec4 color;

            uniform sampler2D tex0;

            uniform float uBorderRadius;
            uniform vec4 uColor;
            uniform vec2 uSize;

            void main() {
              vec2 pos = texCoord * uSize;
              vec2 halfSize = uSize * 0.5;
              vec2 cornerDist = abs(pos - halfSize) - (halfSize - uBorderRadius);

              float outside = max(cornerDist.x, cornerDist.y);
              if (outside > 0.0) {
                float cornerDistSq = dot(max(cornerDist, 0.0), max(cornerDist, 0.0));
                if (cornerDistSq > uBorderRadius * uBorderRadius) {
                   discard;
                }
              }

              FragColor = texture(tex0, texCoord) * uColor;
            }
    )"
      )
    );

    AssetManager::addAsset(
      "default-text-shader",
      std::make_shared<wind::Shader>(
        R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            uniform mat4 uModel;
            uniform mat4 uProjection;
            uniform vec4 uColor;

            out vec2 texCoord;
            out vec4 color;

            void main() {
                gl_Position = uProjection * uModel * vec4(aPos, 1.0);
                texCoord = aTexCoords;
                color = uColor;
            }
        )",
        R"(
            #version 330 core

            out vec4 FragColor;
            in vec2 texCoord;
            in vec4 color;

            uniform sampler2D tex0;

            void main() {
              vec4 text = texture(tex0, texCoord);
              FragColor = vec4(text.r, text.r, text.r, text.r) * color;
            }
    )"
      )
    );

    AssetManager::addAsset(
      "default-rect-mesh",
      std::shared_ptr<Mesh>(new Mesh(
        std::vector<Mesh::Vertex>{
          {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
          {{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}},
          {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}},
          {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}}
        },
        std::vector<uint>{1, 2, 3, 0, 1, 3}
      ))
    );

    AssetManager::addAsset(
      "default-ui-material",
      std::make_shared<wind::Material>(
        AssetManager::getAsset<wind::Shader>("default-ui-shader"), 1
      )
    );

     AssetManager::addAsset(
      "default-text-material",
      std::make_shared<wind::Material>(
        AssetManager::getAsset<wind::Shader>("default-text-shader"), 1
      )
    );

    static void* whiteRect = new unsigned char[4]{255, 255, 255, 255};

    AssetManager::addAsset(
      "default-white-texture",
      std::shared_ptr<wind::Texture>(new Texture(whiteRect, {1, 1}))
    );
  }

} // namespace wind
