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

#include <algorithm>

#include "OpenGLUnitsDrawer.h"
#include "RenderInfo.h"
#include "../../Logger.h"

OpenGLUnitsDrawer * OpenGLUnitsDrawer::m_instance {nullptr};

OpenGLUnitsDrawer::OpenGLUnitsDrawer() {
  m_shader.init(ShadersUnit::vertex_shader, ShadersUnit::fragment_shader);

  glGenVertexArrays(1, &gl_field_vao);
  glGenBuffers(1, &gl_field_vbo);
  glGenBuffers(1, &gl_field_ebo);
  glGenBuffers(1, &_indirect_buffer);

  glBindVertexArray(gl_field_vao);
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_unit_vertices.size() * sizeof(GLfloat), m_unit_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_unit_indices.size() * sizeof(GLuint), m_unit_indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLfloat *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLfloat *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

OpenGLUnitsDrawer::~OpenGLUnitsDrawer() {
  glDeleteVertexArrays(1, &gl_field_vao);
  glDeleteBuffers(1, &gl_field_vbo);
  glDeleteBuffers(1, &gl_field_ebo);
  glDeleteBuffers(1, &_indirect_buffer);
}

void OpenGLUnitsDrawer::prepare() {
  m_unit_draw_vector.clear();
}


void OpenGLUnitsDrawer::draw_units(const std::vector<Unit>& units) {

  //ToDo: Don't need to update data if no changes. Don't need to re-_indirect_buffer data if no changes.
  bool re_buffer {false};

  if (units.size() != _indirect_draw.size()) {
    _indirect_draw.resize(units.size());
    _transformations.resize(units.size());
  }

  if (std::any_of(std::begin(units), std::end(units), [](const Unit& u) {return u.draw_strategy()->is_modified();})) {

    m_unit_vertices.clear();
    m_unit_indices.clear();

    RenderInfo render_info;

    for (size_t i = 0; i < units.size(); ++i) {

      render_info = units.at(i).draw_strategy()->fill_draw_structures();

      _indirect_draw[i].count = static_cast<GLuint>(render_info.indecies.size());
      _indirect_draw[i].primCount = 1;
      _indirect_draw[i].firstIndex = static_cast<GLuint>(m_unit_indices.size());
      _indirect_draw[i].baseVertex = static_cast<GLuint>(m_unit_vertices.size()) / POINTS_PER_PIXEL;
      _indirect_draw[i].baseInstance = 0;

      m_unit_vertices.insert(std::end(m_unit_vertices), std::begin(render_info.vertices),
                             std::end(render_info.vertices));
      m_unit_indices.insert(std::end(m_unit_indices), std::begin(render_info.indecies), std::end(render_info.indecies));
      _transformations[i] = render_info.transformation;
    }

    re_buffer = true;
  }

  m_shader.use();

  // Get their uniform location
  GLint projection_location = glGetUniformLocation(m_shader.shader_id(), "projection");
  GLint view_location = glGetUniformLocation(m_shader.shader_id(), "view");
  GLint model_location = glGetUniformLocation(m_shader.shader_id(), "model");
  GLint rotate_location = glGetUniformLocation(m_shader.shader_id(), "rotation");

  // Pass them to the shaders
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(m_projection));
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(m_view));
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(m_model));

  if (re_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_unit_vertices.size() * sizeof(GLfloat), m_unit_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_unit_indices.size() * sizeof(GLuint), m_unit_indices.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, _indirect_buffer);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, _indirect_draw.size() * sizeof(DrawElementsIndirectCommand),
                 _indirect_draw.data(), GL_STATIC_DRAW);
                 
  }

  glBindVertexArray(gl_field_vao);
  {
    for (size_t i = 0; i < units.size(); ++i) {
      glUniformMatrix4fv(rotate_location, 1, GL_FALSE, glm::value_ptr(_transformations[i]));
      glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, (void *)(i * sizeof(DrawElementsIndirectCommand)));

      GLenum err = glGetError();
      if (err != GL_NO_ERROR) {
        Logger::warning("OpenGL: glDrawElementsIndirect error: %d", err);
      }
    }

    

  }

}