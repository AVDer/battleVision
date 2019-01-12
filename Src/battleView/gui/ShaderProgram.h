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

#ifndef BATTLEVISION_SHADERPROGRAM_H
#define BATTLEVISION_SHADERPROGRAM_H

#include <map>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class ShaderProgram {
 public:
  ShaderProgram() = default;
  void init(std::string&& name, const std::string& vertex_source,
            const std::string& fragment_source);
  void use();
  GLuint shader_id() const { return program_id_; }
  GLenum find_uniform_location(const std::string& name, GLuint id);
  GLint get_location(GLuint id) const { return locations_.at(id); }

 private:
  std::string name_;
  GLuint program_id_{0};
  std::map<GLuint, GLint> locations_;
};

#endif  // BATTLEVISION_SHADERPROGRAM_H
