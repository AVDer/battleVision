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

#include <iostream>

void ShaderProgram::init(const std::string& vertex_source, const std::string& fragment_source) {
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
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  GLuint fragment_shader { glCreateShader(GL_FRAGMENT_SHADER) };
  glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader);
  glAttachShader(program_id_, fragment_shader);
  glLinkProgram(program_id_);

  glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(program_id_, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FIELD::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void ShaderProgram::use() {
  glUseProgram(program_id_);
}
