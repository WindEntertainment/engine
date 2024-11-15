#include "wind/renderer/opengl_includes.hpp"

#include "wind/renderer/shader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace wind {

Shader::Shader(const char* _vsh, const char* _fsh) {
  int success;
  char msg[512];

  // Vertex
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &_vsh, NULL);
  glCompileShader(vs);

  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, 512, NULL, msg);
    spdlog::error("Failed compile vertex shader: {}", msg);
    return;
  }

  // Fragment
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &_fsh, NULL);
  glCompileShader(fs);

  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs, 512, NULL, msg);
    spdlog::error("Failed compile fragment shader: {}", msg);
    return;
  }

  // Program
  _id = glCreateProgram();
  glAttachShader(_id, vs);
  glAttachShader(_id, fs);
  glLinkProgram(_id);

  glGetShaderiv(_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(_id, 512, NULL, msg);
    spdlog::error("Failed link shader: {}", msg);
    return;
  }

  glDeleteShader(vs);
  glDeleteShader(fs);
}

Shader::~Shader() {
  glDeleteProgram(_id);
}

uint Shader::id() {
  return _id;
}

} // namespace wind
