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

#include "BattleField.h"

#include "Logger.h"
#include "ShadersField.h"

#include "bvl/BVGlobal.h"

static const GLfloat screen_gap{0.1f};
static const GLfloat earth_width{0.1f};

enum Location : GLuint { projection = 0, view, model };

GLfloat field_vertices[] = {
    // Positions                             // Texture Coords
    // Field
    1.0f - screen_gap, 1.0f - screen_gap, 0.0f, 1.0f, 1.0f,    // Top Right          (0)
    1.0f - screen_gap, -1.0f + screen_gap, 0.0f, 1.0f, 0.0f,   // Bottom Right       (1)
    -1.0f + screen_gap, -1.0f + screen_gap, 0.0f, 0.0f, 0.0f,  // Bottom Left        (2)
    -1.0f + screen_gap, 1.0f - screen_gap, 0.0f, 0.0f, 1.0f,   // Top Left           (3)
    // Bottom
    1.0f - screen_gap, 1.0f - screen_gap, -earth_width, 1.1f, 1.1f,  // Top Right               (4)
    1.0f - screen_gap, -1.0f + screen_gap, -earth_width, 1.1f, -0.1f,    // Bottom Right (5)
    -1.0f + screen_gap, -1.0f + screen_gap, -earth_width, -0.1f, -0.1f,  // Bottom Left (6)
    -1.0f + screen_gap, 1.0f - screen_gap, -earth_width, -0.1f, 1.1f  // Top Left                (7)
};

GLuint indices[] = {
    // Field
    0, 1, 3, 1, 2, 3,
    // Right side
    0, 4, 5, 5, 1, 0,
    // Left side
    3, 7, 6, 6, 2, 3,
    // Near side
    1, 5, 6, 6, 2, 1,
    // Far side
    3, 0, 4, 4, 7, 3,
    // Back
    4, 5, 7, 5, 6, 7};

void BattleField::create(const std::string& texture_filename) {
  load_map_texture(texture_filename);

  field_vertices[0] = texture_->width();
  field_vertices[1] = texture_->height();
  field_vertices[5] = texture_->width();
  field_vertices[6] = 0;
  field_vertices[10] = 0;
  field_vertices[11] = 0;
  field_vertices[15] = 0;
  field_vertices[16] = texture_->height();

  field_vertices[20] = texture_->width();
  field_vertices[21] = texture_->height();
  field_vertices[25] = texture_->width();
  field_vertices[26] = 0;
  field_vertices[30] = 0;
  field_vertices[31] = 0;
  field_vertices[35] = 0;
  field_vertices[36] = texture_->height();

  shader_program_.init("Field", ShadersField::vertex_shader, ShadersField::fragment_shader);
  shader_program_.find_uniform_location("projection", Location::projection);
  shader_program_.find_uniform_location("view", Location::view);
  shader_program_.find_uniform_location("model", Location::model);

  glGenVertexArrays(1, &gl_field_vao_);
  glGenBuffers(1, &gl_field_vbo_);
  glGenBuffers(1, &gl_field_ebo_);

  glBindVertexArray(gl_field_vao_);
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(field_vertices), field_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

void BattleField::destroy() {
  glDeleteVertexArrays(1, &gl_field_vao_);
  glDeleteBuffers(1, &gl_field_vbo_);
  glDeleteBuffers(1, &gl_field_ebo_);
}

void BattleField::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
  shader_program_.use();

  // Pass them to the shaders
  glUniformMatrix4fv(shader_program_.get_location(Location::projection), 1, GL_FALSE,
                     glm::value_ptr(projection));
  glUniformMatrix4fv(shader_program_.get_location(Location::view), 1, GL_FALSE,
                     glm::value_ptr(view));
  glUniformMatrix4fv(shader_program_.get_location(Location::model), 1, GL_FALSE,
                     glm::value_ptr(model));

  glBindTexture(GL_TEXTURE_2D, texture_->id());
  glBindVertexArray(gl_field_vao_);
  {
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT,
                   reinterpret_cast<GLvoid*>(0 * sizeof(GLfloat)));
    glBindTexture(GL_TEXTURE_2D, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
                   reinterpret_cast<GLvoid*>(30 * sizeof(GLfloat)));
  }
  glBindVertexArray(0);
  // glBindTexture(GL_TEXTURE_2D, 0);
}

void BattleField::load_map_texture(const std::string& filename) {
  texture_ = std::make_unique<OGLTexture>(OGLTexture(TGAFile(filename)));
}
