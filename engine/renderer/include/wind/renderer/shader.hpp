#pragma once
#include "wind/utils/utils.hpp"

namespace wind {

class Shader {
private:
  uint _id;

public:
  Shader(const char* vertex_shader_text, const char* fragment_shader_text);
  ~Shader();

  uint id();
};

} // namespace wind