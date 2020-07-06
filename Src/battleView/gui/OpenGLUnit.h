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

#ifndef BATTLEVISION_OPENGLUNIT_H
#define BATTLEVISION_OPENGLUNIT_H

#include "../core/Unit.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class OpenGLUnit : public Unit {
 public:
  OpenGLUnit();

  ~OpenGLUnit();

  void draw() const override{

  };

  // OpenGLUnitsDrawer::instance()->set_transitions(projection_, view_, model);

  void set_transitions(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
    projection_ = projection;
    view_ = view;
    model_ = model;
  }

 private:
  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 model_;

  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;

  GLuint gl_vbo_;
  GLuint gl_vao_;
  GLuint gl_ebo_;

  std::vector<glm::mat4> transformations_;
};

#endif