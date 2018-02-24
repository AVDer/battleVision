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

#include "SOIL.h"

#include "../bvl/BVGlobal.h"
#include "ShadersField.h"
#include "../../Logger.h"

static const GLfloat screen_gap {0.1f};
static const GLfloat earth_width {0.1f};

GLfloat field_vertices[] = {
    // Positions                             // Texture Coords
    // Field
    1.0f - screen_gap,  1.0f - screen_gap,  0.0f,    1.0f, 1.0f,   // Top Right          (0)
    1.0f - screen_gap, -1.0f + screen_gap,  0.0f,    1.0f, 0.0f,   // Bottom Right       (1)
    -1.0f + screen_gap, -1.0f + screen_gap, 0.0f,    0.0f, 0.0f,   // Bottom Left        (2)
    -1.0f + screen_gap,  1.0f - screen_gap, 0.0f,    0.0f, 1.0f,   // Top Left           (3)
    // Bottom
    1.0f - screen_gap,  1.0f - screen_gap,  -earth_width,    1.1f,  1.1f,   // Top Right               (4)
    1.0f - screen_gap, -1.0f + screen_gap,  -earth_width,    1.1f,  -0.1f,  // Bottom Right            (5)
    -1.0f + screen_gap, -1.0f + screen_gap, -earth_width,    -0.1f, -0.1f,  // Bottom Left             (6)
    -1.0f + screen_gap,  1.0f - screen_gap, -earth_width,    -0.1f, 1.1f    // Top Left                (7)
};

GLuint indices[] = {
    // Field
    0, 1, 3,
    1, 2, 3,
    // Right side
    0, 4, 5,
    5, 1, 0,
    // Left side
    3, 7, 6,
    6, 2, 3,
    // Near side
    1, 5, 6,
    6, 2, 1,
    // Far side
    3, 0, 4,
    4, 7, 3,
    // Back
    4, 5, 7,
    5, 6, 7
};


BattleField::~BattleField() {
  glDeleteVertexArrays(1, &gl_field_vao);
  glDeleteBuffers(1, &gl_field_vbo);
  glDeleteBuffers(1, &gl_field_ebo);
}

void BattleField::create(const std::string& texture_filename) {
  load_map_texture(texture_filename);
  field_vertices[0] = m_texture_width;
  field_vertices[1] = m_texture_height;
  field_vertices[5] = m_texture_width;
  field_vertices[6] = 0;
  field_vertices[10] = 0;
  field_vertices[11] = 0;
  field_vertices[15] = 0;
  field_vertices[16] = m_texture_height;

  field_vertices[20] = m_texture_width;
  field_vertices[21] = m_texture_height;
  field_vertices[25] = m_texture_width;
  field_vertices[26] = 0;
  field_vertices[30] = 0;
  field_vertices[31] = 0;
  field_vertices[35] = 0;
  field_vertices[36] = m_texture_height;


  m_shader.init(ShadersField::vertex_shader, ShadersField::fragment_shader);

  glGenVertexArrays(1, &gl_field_vao);
  glGenBuffers(1, &gl_field_vbo);
  glGenBuffers(1, &gl_field_ebo);

  glBindVertexArray(gl_field_vao); {
    glBindBuffer(GL_ARRAY_BUFFER, gl_field_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(field_vertices), field_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_field_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

void BattleField::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
  static uint64_t frame_number {0};

  m_shader.use();

  // Get their uniform location
  GLint projection_location = glGetUniformLocation(m_shader.shader_id(), "projection");
  GLint view_location = glGetUniformLocation(m_shader.shader_id(), "view");
  GLint model_location = glGetUniformLocation(m_shader.shader_id(), "model");
  // Pass them to the shaders
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glBindVertexArray(gl_field_vao);
  {
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, (GLvoid *) (0 * sizeof(GLfloat)));
    glBindTexture(GL_TEXTURE_2D, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) (30 * sizeof(GLfloat)));
  }
  glBindVertexArray(0);
}

void BattleField::load_map_texture(const std::string& filename) {
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *image = SOIL_load_image(filename.c_str(), &m_texture_width, &m_texture_height, nullptr, SOIL_LOAD_RGB);
    m_texture_ratio = static_cast<double>(m_texture_width) / m_texture_height;
    if (!image) {
      Logger::warning("BattleField: Texture %s can't be found", filename.c_str());
    }
    else {
      Logger::info("BattleField: Texture %s loaded", filename.c_str());
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texture_width, m_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
}
