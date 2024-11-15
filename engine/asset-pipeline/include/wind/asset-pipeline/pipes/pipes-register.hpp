#pragma once
#include "pipe.hpp"

#include "default-pipe.hpp"
#include "img-pipe.hpp"
#include "shader-pipe.hpp"

namespace wind {
  namespace assets {

    class PipeRegister {
    private:
      static std::vector<AssetPipe*> pipes;

    public:
      static AssetPipe* getPipe(asset_id id) {
        for (auto pipe : pipes) {
          if (id == pipe->id())
            return pipe;
        }

        return nullptr;
      }

      static void regPipe(AssetPipe* _pipe) {
        pipes.push_back(_pipe);
        spdlog::debug("PipeRegister: registered new pipe: {}", _pipe->id());
      }
    };

  } // namespace assets
} // namespace wind
