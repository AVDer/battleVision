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

#include "ShaderProgram.h"
#include "ShadersUnit.h"
#include "RenderInfo.h"

#include "core/Unit.h"
#include "bvl/BVTypes.h"

struct UnitDrawData {
  UnitDrawData(GLuint v, GLsizei p, glm::mat4 t) :
      vao_index(v),
      points_number(p),
      transformation(t) {}
  GLuint vao_index;
  GLsizei points_number;
  glm::mat4 transformation;
};

class OpenGLUnitsDrawer {

public:

  static OpenGLUnitsDrawer * instance() {
    if (!m_instance) {
      m_instance = new OpenGLUnitsDrawer;
    }
    return m_instance;
  }

  ~OpenGLUnitsDrawer();

  void prepare();

  void draw_units(const std::vector<Unit>& units);

  void set_transitions(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
    m_projection = projection;
    m_view = view;
    m_model = model;
  }

private:

  const static uint16_t POINTS_PER_PIXEL = 6;
  const static uint16_t MAX_UNITS_NUMBER = 20;

  using unit_draw_data = UnitDrawData;
  OpenGLUnitsDrawer();
  static OpenGLUnitsDrawer * m_instance;
  std::vector<unit_draw_data> m_unit_draw_vector;

  glm::mat4 m_projection;
  glm::mat4 m_view;
  glm::mat4 m_model;

  ShaderProgram m_shader;

  std::vector<GLfloat> m_unit_vertices;
  std::vector<GLuint> m_unit_indices;

  GLuint gl_field_vbo;
  GLuint gl_field_vao;
  GLuint gl_field_ebo;
  GLuint _indirect_buffer;

  std::vector<DrawElementsIndirectCommand> _indirect_draw;
  std::vector<glm::mat4> _transformations;
};


#endif //BATTLEVISION_OPENGLUNITSDRAWER_H
