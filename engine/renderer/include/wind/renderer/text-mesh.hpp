#pragma once
#include "wind/renderer/mesh.hpp"
#include "wind/renderer/texture.hpp"
#include "wind/renderer/opengl_includes.hpp"

namespace wind { 

  class Font {
    friend class TextMesh;
  public:
    struct Glyph {
      std::shared_ptr<Texture> texture;
      glm::ivec2 size;
      glm::ivec2 bearing;
      glm::ivec2 advance;
      unsigned char character;
    };

    Font(FT_Face face, int fontSize): face(face) {
      FT_Set_Pixel_Sizes(face, 0, fontSize);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
      for (unsigned char c = 0; c < 128; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          spdlog::error("Failed to load Glyph");
          continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glyphs.insert(std::make_pair(c, Glyph{
          .texture = std::shared_ptr<Texture>(new Texture(texture)),
          .size = { face->glyph->bitmap.width, face->glyph->bitmap.rows },
          .bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top },
          .advance = {face->glyph->advance.x, face->height},
          .character = c
        }));
      }
    }

    ~Font() { 
      FT_Done_Face(face);
    }
    
  private:
    std::map<char, Glyph> glyphs;
    FT_Face& face;
  };

  class TextMesh {
    friend class RenderContext;

  public:

    std::shared_ptr<Font> font = nullptr;
    int letterSpacing = 0;
    int lineSpacing = 0;
    int lineWidth = 0;

    void setText(const std::string& text) {
       if (font == nullptr) {
         spdlog::error("Font is nullptr");
         return;
       }

       glyphs.clear();

       std::string::const_iterator c;
       for (c = text.begin(); c != text.end(); ++c) {
         auto it = font->glyphs.find(*c);
         if (it != font->glyphs.end())
           glyphs.push_back(it->second);
         else {
           spdlog::warn("In font don't exsist glyph for this symbol: '{}'", *c);
           glyphs.push_back(font->glyphs[0]);
         }
       }
    }

    std::vector<Font::Glyph> glyphs;
    static FT_Library lb;
  };
} // namespace wind