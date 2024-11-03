#include "wind/wind.hpp"
#include "wind/asset-manager/asset-manager.hpp"
#include "wind/renderer/shader.hpp"

namespace wind {

  void Engine::addDefaultAssets() {
    AssetManager::addAsset(
      "default-sprite-shader",
      std::make_shared<wind::Shader>(
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
      )
    );
  }

} // namespace wind