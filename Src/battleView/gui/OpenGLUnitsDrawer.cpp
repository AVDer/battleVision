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

#include "Logger.h"
#include "OpenGLUnitsDrawer.h"
#include "RenderInfo.h"

OpenGLUnitsDrawer *OpenGLUnitsDrawer::instance_{nullptr};

OpenGLUnitsDrawer::OpenGLUnitsDrawer() {
  shader_.init(ShadersUnit::vertex_shader, ShadersUnit::fragment_shader);

  glGenVertexArrays(1, &gl_field_vao_);
  glGenBuffers(1, &gl_field_vbo_);
  glGenBuffers(1, &gl_field_ebo_);
  glGenBuffers(1, &indirect_buffer_);

  glBindVertexArray(gl_field_vao_);
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo_);
    glBufferData(GL_ARRAY_BUFFER, unit_vertices_.size() * sizeof(GLfloat), unit_vertices_.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, unit_indices_.size() * sizeof(GLuint),
                 unit_indices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

OpenGLUnitsDrawer::~OpenGLUnitsDrawer() {
  glDeleteVertexArrays(1, &gl_field_vao_);
  glDeleteBuffers(1, &gl_field_vbo_);
  glDeleteBuffers(1, &gl_field_ebo_);
  glDeleteBuffers(1, &indirect_buffer_);
}

void OpenGLUnitsDrawer::prepare() { unit_draw_vector_.clear(); }

void OpenGLUnitsDrawer::draw_units(const std::vector<Unit> &units) {
  // ToDo: Don't need to update data if no changes. Don't need to re-_indirect_buffer data if no
  // changes.
  bool re_buffer{false};
  static bool init{false};

  if (units.size() != indirect_draw_.size()) {
    indirect_draw_.resize(units.size());
    transformations_.resize(units.size());
  }

  if (std::any_of(std::begin(units), std::end(units),
                  [](const Unit &u) { return u.draw_strategy()->is_modified(); })) {
    unit_vertices_.clear();
    unit_indices_.clear();

    RenderInfo render_info;

    for (size_t i = 0; i < units.size(); ++i) {
      render_info = units.at(i).draw_strategy()->fill_draw_structures();

      indirect_draw_[i].count = static_cast<GLuint>(render_info.indecies.size());
      indirect_draw_[i].primCount = 1;
      indirect_draw_[i].firstIndex = static_cast<GLuint>(unit_indices_.size());
      indirect_draw_[i].baseVertex = static_cast<GLuint>(unit_vertices_.size()) / kPointsPerPixel;
      indirect_draw_[i].baseInstance = 0;

      unit_vertices_.insert(std::end(unit_vertices_), std::begin(render_info.vertices),
                            std::end(render_info.vertices));
      unit_indices_.insert(std::end(unit_indices_), std::begin(render_info.indecies),
                           std::end(render_info.indecies));
      transformations_[i] = render_info.transformation;
    }

    re_buffer = true;
  }

  shader_.use();

  // Get their uniform location
  GLint projection_location = glGetUniformLocation(shader_.shader_id(), "projection");
  GLint view_location = glGetUniformLocation(shader_.shader_id(), "view");
  GLint model_location = glGetUniformLocation(shader_.shader_id(), "model");
  GLint rotate_location = glGetUniformLocation(shader_.shader_id(), "rotation");

  // Pass them to the shaders
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection_));
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_));
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_));
  ;

  if (re_buffer) {
    glBindVertexArray(gl_field_vao_);
    {
      glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo_);
      glBufferData(GL_ARRAY_BUFFER, unit_vertices_.size() * sizeof(GLfloat), unit_vertices_.data(),
                   GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, unit_indices_.size() * sizeof(GLuint),
                   unit_indices_.data(), GL_STATIC_DRAW);

      if (!init) {
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_buffer_);
        glBufferData(GL_DRAW_INDIRECT_BUFFER,
                     indirect_draw_.size() * sizeof(DrawElementsIndirectCommand),
                     indirect_draw_.data(), GL_STATIC_DRAW);
        init = true;
      }
    }
    glBindVertexArray(0);
  }

  glBindVertexArray(gl_field_vao_);
  {
    for (size_t i = 0; i < units.size(); ++i) {
      glUniformMatrix4fv(rotate_location, 1, GL_FALSE, glm::value_ptr(transformations_[i]));
      glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                             (void *)(i * sizeof(DrawElementsIndirectCommand)));

      GLenum err = glGetError();
      if (err != GL_NO_ERROR) {
        Logger::warning("OpenGL: glDrawElementsIndirect error: %d", err);
      }
    }
  }
}