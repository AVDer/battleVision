#include "OpenGLUnit.h"

#include "glad/glad.h"
#include <GL/gl.h>

OpenGLUnit::OpenGLUnit() {
  glGenVertexArrays(1, &gl_vao_);
  glGenBuffers(1, &gl_vbo_);
  glGenBuffers(1, &gl_ebo_);
}

void OpenGLUnit::prepare() {
  shader_.init("UnitDrawer", ShadersUnit::vertex_shader, ShadersUnit::fragment_shader);
  shader_.find_uniform_location("projection", ShadersUnit::Uniform::projection);
  shader_.find_uniform_location("view", ShadersUnit::Uniform::view);
  shader_.find_uniform_location("model", ShadersUnit::Uniform::model);
  shader_.find_uniform_location("transform", ShadersUnit::Uniform::transform);

  glBindVertexArray(gl_vao_);
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 draw_strategy_->draw_structures().vertices.size() * sizeof(GLfloat),
                 draw_strategy_->draw_structures().vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 draw_strategy_->draw_structures().indecies.size() * sizeof(GLuint),
                 draw_strategy_->draw_structures().indecies.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

void OpenGLUnit::draw() const {
  draw_strategy_->update_draw_info(this->unit_info_.unit_draw_info());
  shader_.set_matrix_4fv(
      ShadersUnit::Uniform::transform,
      const_cast<GLfloat *>(glm::value_ptr(draw_strategy_->draw_structures().transformation)));

  glBindVertexArray(gl_vao_);
  {
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT,
                   reinterpret_cast<GLvoid *>(0 * sizeof(GLfloat)));
  }
  glBindVertexArray(0);
}

OpenGLUnit::~OpenGLUnit() {
  glDeleteVertexArrays(1, &gl_vao_);
  glDeleteBuffers(1, &gl_vbo_);
  glDeleteBuffers(1, &gl_ebo_);
}