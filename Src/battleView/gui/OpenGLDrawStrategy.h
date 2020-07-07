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

#ifndef BATTLEVISION_OPENGLDRAWSTRATEGY_H
#define BATTLEVISION_OPENGLDRAWSTRATEGY_H

#include <vector>

#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "RenderInfo.h"
#include "core/DrawStrategy.h"

class OpenGLDrawStrategy : public DrawStrategy {
 public:
  OpenGLDrawStrategy() = default;

  void update_draw_info(const UnitDrawInfo &udi) override {
    // is_modified_ = true;
    auto c = udi.color().get();
    color_.r = c.r;
    color_.g = c.g;
    color_.b = c.b;

    transformation_ =
        glm::translate(glm::mat4(1.0), glm::vec3(udi.position().x(), udi.position().y(), 0.f));
    transformation_ = glm::rotate(transformation_, glm::radians(static_cast<float>(udi.angle())),
                                  glm::vec3(0.0f, 0.0f, 1.0f));
    transformation_ =
        glm::translate(transformation_, glm::vec3(-udi.size().x() / 2, -udi.size().y() / 2, 0.f));
    transformation_ = glm::scale(transformation_, glm::vec3(udi.size().x(), udi.size().y(), 1.f));

    fill_vertex(udi);
  }

  RenderInfo draw_structures() override {
    // is_modified_ = false;
    return {unit_vertices_, unit_indices_, transformation_};
  }

 protected:
  virtual void fill_vertex(const UnitDrawInfo &udi) = 0;

  static constexpr GLfloat kUnitHeight{0.05};

  std::vector<GLfloat> unit_vertices_;
  std::vector<GLuint> unit_indices_;
  glm::mat4 transformation_;
  glm::vec3 color_;
};

#endif  // BATTLEVISION_OPENGLDRAWSTRATEGY_H
