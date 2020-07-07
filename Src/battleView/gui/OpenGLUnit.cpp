#include "OpenGLUnit.h"

#include "glad/glad.h"
#include <GL/gl.h>

OpenGLUnit::OpenGLUnit() {
  glGenVertexArrays(1, &gl_vao_);
  glGenBuffers(1, &gl_vbo_);
  glGenBuffers(1, &gl_ebo_);
}

void OpenGLUnit::prepare() const {
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
  glBindVertexArray(gl_vao_);
  {
    auto debug = draw_strategy_->draw_structures();

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