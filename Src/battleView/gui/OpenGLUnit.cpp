#include "OpenGLUnit.h"

#include "glad/glad.h"
#include <GL/gl.h>

OpenGLUnit::OpenGLUnit() {
  glGenVertexArrays(1, &gl_vao_);
  glGenBuffers(1, &gl_vbo_);
  glGenBuffers(1, &gl_ebo_);

  glBindVertexArray(gl_vao_);
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), vertices_.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), indices_.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
  }
  glBindVertexArray(0);
}

OpenGLUnit::~OpenGLUnit() {
  glDeleteVertexArrays(1, &gl_vao_);
  glDeleteBuffers(1, &gl_vbo_);
  glDeleteBuffers(1, &gl_ebo_);
}