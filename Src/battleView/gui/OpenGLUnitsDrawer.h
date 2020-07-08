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

#ifndef BATTLEVISION_OPENGLUNITSDRAWER_H
#define BATTLEVISION_OPENGLUNITSDRAWER_H

#include "ShaderProgram.h"
#include "ShadersUnit.h"

#include "bvl/BVTypes.h"
#include "core/Unit.h"

class OpenGLUnitsDrawer {
 public:
  OpenGLUnitsDrawer() {}

  void set_transitions(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
    projection_ = projection;
    view_ = view;
    model_ = model;
  }

  void draw_units(const std::vector<std::shared_ptr<Unit>>& units) {
    OpenGLUnit::shader().use();

    // Pass them to the shaders
    OpenGLUnit::shader().set_matrix_4fv(ShadersUnit::Uniform::projection,
                                        glm::value_ptr(projection_));
    OpenGLUnit::shader().set_matrix_4fv(ShadersUnit::Uniform::view, glm::value_ptr(view_));
    OpenGLUnit::shader().set_matrix_4fv(ShadersUnit::Uniform::model, glm::value_ptr(model_));

    for (const auto& unit : units) {
      unit->draw();
    }
  }

  static std::shared_ptr<OpenGLUnitsDrawer> instance() {
    if (!instance_) {
      instance_ = std::make_shared<OpenGLUnitsDrawer>();
    }
    return instance_;
  }

 private:
  inline static std::shared_ptr<OpenGLUnitsDrawer> instance_;

  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 model_;
};

#endif  // BATTLEVISION_OPENGLUNITSDRAWER_H
