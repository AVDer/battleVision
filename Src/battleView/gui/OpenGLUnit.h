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

  void draw(int location) const override;
  void prepare() const override;

 private:
  std::vector<GLfloat> vertices_;
  std::vector<GLuint> indices_;

  GLuint gl_vbo_;
  GLuint gl_vao_;
  GLuint gl_ebo_;

  std::vector<glm::mat4> transformation_;
};

#endif