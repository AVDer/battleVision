/******************************************************************************
This file is part of battleVision.

battleVision is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

battleVision is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with battleVision.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "ShaderProgram.h"

#include "Logger.h"

void ShaderProgram::init(std::string&& name, const std::string& vertex_source,
                         const std::string& fragment_source) {
  name_ = name;
  GLint success;
  GLchar infoLog[512];

  const GLchar* vertex_shader_code = vertex_source.c_str();
  const GLchar* fragment_shader_code = fragment_source.c_str();

  GLuint vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
    Logger::error("OpenGL: Shader %s: Vertex compilation failed: %s", name_.c_str(), infoLog);
  }

  GLuint fragment_shader{glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    Logger::error("OpenGL: Shader %s: Fragment compilation failed: %s", name_.c_str(), infoLog);
  }

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader);
  glAttachShader(program_id_, fragment_shader);
  glLinkProgram(program_id_);

  glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program_id_, 512, nullptr, infoLog);
    Logger::error("OpenGL: Shader %s: Program compilation failed: %s", name_.c_str(), infoLog);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  Logger::debug("OpenGL: Shader %s: Created", name_.c_str());
}

void ShaderProgram::use() { glUseProgram(program_id_); }

GLenum ShaderProgram::find_uniform_location(const std::string& name, GLuint id) {
  GLint location = glGetUniformLocation(program_id_, name.c_str());
  if (GLenum err = glGetError(); err != GL_NO_ERROR) {
    Logger::error("OpenGL: Location for %s can't be found: %d", name.c_str(), err);
    return err;
  }
  Logger::debug("OpenGL: Shader %s: Found location %d for \"%s\"", name_.c_str(), location,
                name.c_str());
  locations_[id] = location;
  return GL_NO_ERROR;
}
