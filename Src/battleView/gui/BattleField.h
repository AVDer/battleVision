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

#ifndef BATTLEVISION_BATTLEFIELD_H
#define BATTLEVISION_BATTLEFIELD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLTexture.h"
#include "ShaderProgram.h"

class BattleField {
public:
  void create(const std::string& texture_filename);
  void destroy();

  void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model);

  auto texture_ratio() const { return texture_->ratio(); }
  int texture_width() const { return texture_->width(); }
  int texture_height() const { return texture_->height(); }

private:
  void load_map_texture(const std::string& filename);

  GLuint gl_field_vbo {0};
  GLuint gl_field_vao {0};
  GLuint gl_field_ebo {0};

  ShaderProgram shader_program_;
  std::unique_ptr<OGLTexture> texture_;
};


#endif //BATTLEVISION_BATTLEFIELD_H
