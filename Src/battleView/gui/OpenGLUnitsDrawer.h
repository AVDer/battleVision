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

#ifndef BATTLEVISION_OPENGLUNITSDRAWER_H
#define BATTLEVISION_OPENGLUNITSDRAWER_H

#include <glad/glad.h>
#include <GL/gl.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "RenderInfo.h"
#include "ShaderProgram.h"
#include "ShadersUnit.h"

#include "bvl/BVTypes.h"
#include "core/Unit.h"

struct UnitDrawData {
  UnitDrawData(GLuint v, GLsizei p, glm::mat4 t)
      : vao_index(v), points_number(p), transformation(t) {}
  GLuint vao_index;
  GLsizei points_number;
  glm::mat4 transformation;
};

class OpenGLUnitsDrawer {
  using unit_draw_data_t = UnitDrawData;

 public:
  static OpenGLUnitsDrawer* instance() {
    if (!instance_) {
      instance_ = new OpenGLUnitsDrawer;
    }
    return instance_;
  }

  ~OpenGLUnitsDrawer();

  void prepare();

  void draw_units(const std::vector<Unit>& units);

  void set_transitions(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
    projection_ = projection;
    view_ = view;
    model_ = model;
  }

 private:
  const static uint16_t kPointsPerPixel{6};
  const static uint16_t kMaxUnitsNumber{20};

  OpenGLUnitsDrawer();

  static OpenGLUnitsDrawer* instance_;
  std::vector<unit_draw_data_t> unit_draw_vector_;

  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 model_;

  ShaderProgram shader_;

  std::vector<GLfloat> unit_vertices_;
  std::vector<GLuint> unit_indices_;

  GLuint gl_units_vbo_;
  GLuint gl_units_vao_;
  GLuint gl_units_ebo_;
  GLuint indirect_buffer_;

  std::vector<DrawElementsIndirectCommand> indirect_draw_;
  std::vector<glm::mat4> transformations_;
};

#endif  // BATTLEVISION_OPENGLUNITSDRAWER_H
