#pragma once
#include "pipe.hpp"

#ifdef WIND_PIPE_WRITE
#include <pugixml.hpp>
#endif

namespace wind {
  namespace assets {

    class ShaderPipe : public AssetPipe {
    public:
#ifdef WIND_PIPE_WRITE
      void
      compile(const fs::path &_source, const fs::path &_destination) override {
        std::ifstream input(_source, std::ios_base::in);
        std::ofstream output(_destination, std::ios_base::binary);

        if (!input.is_open()) {
          spdlog::error("Cannot open source file: {}", _source.string());
          return;
        }

        if (!output.is_open()) {
          spdlog::error(
            "Cannot open destination file: {}", _destination.string()
          );
          return;
        }

        // =====================================================//
        // Parse

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(_source.string().c_str());

        if (!result) {
          spdlog::error(
            "{} parsed with errors! {}", _source.string(), result.description()
          );
          return;
        }

        auto vtx = doc.child("vtx");
        if (!vtx) {
          spdlog::error("Cannot find vertex shader in {}", _source.string());
          return;
        }

        auto fgt = doc.child("fgt");
        if (!fgt) {
          spdlog::error("Cannot find fragment shader in {}", _source.string());
          return;
        }

        const char *vtxShader = vtx.child_value();
        const char *fgtShader = fgt.child_value();

        // =====================================================//
        // Compress file content

        const uLong vtxSize = strlen(vtxShader) + 1;

        uLongf vtxZippedSize = compressBound(vtxSize);
        char *vtxZipped = new char[vtxZippedSize];

        const uLong fgtSize = strlen(fgtShader) + 1;

        uLongf fgtZippedSize = compressBound(fgtSize);
        char *fgtZipped = new char[fgtZippedSize];

        // vtx
        {
          auto result = compress(
            reinterpret_cast<Bytef *>(vtxZipped),
            &vtxZippedSize,
            reinterpret_cast<const Bytef *>(vtxShader),
            vtxSize
          );
          if (result != Z_OK) {
            spdlog::error(
              "[shader-pipe] Cannot compress data: {}", (int)result
            );
            return;
          }
        }

        // fgt
        {
          auto result = compress(
            reinterpret_cast<Bytef *>(fgtZipped),
            &fgtZippedSize,
            reinterpret_cast<const Bytef *>(fgtShader),
            fgtSize
          );
          if (result != Z_OK) {
            spdlog::error(
              "[shader-pipe] Cannot compress data: {}", (int)result
            );
            return;
          }
        }

        // =====================================================//
        // Writing

        output.write(reinterpret_cast<char *>(&m_id), sizeof(asset_id));

        output << (uint)vtxZippedSize;
        output.write(vtxZipped, vtxZippedSize);

        output << (uint)fgtZippedSize;
        output.write(fgtZipped, fgtZippedSize);
      }
#endif

      void *load(std::ifstream &file) override { return nullptr; }

      ShaderPipe() : AssetPipe("shader"){};
    };

  } // namespace assets
} // namespace wind
