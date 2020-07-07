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

#include <glad/glad.h>
#include <GL/gl.h>
#include <vector>

#include "RenderInfo.h"
#include "ShaderProgram.h"
#include "ShadersUnit.h"

#include "bvl/BVTypes.h"
#include "core/Unit.h"

class OpenGLUnitsDrawer {
 public:
  enum Location : GLuint { projection = 0, view, model, rotation };

  OpenGLUnitsDrawer() {
    shader_.init("UnitDrawer", ShadersUnit::vertex_shader, ShadersUnit::fragment_shader);
    shader_.find_uniform_location("projection", Location::projection);
    shader_.find_uniform_location("view", Location::view);
    shader_.find_uniform_location("model", Location::model);
    shader_.find_uniform_location("rotation", Location::rotation);
  }

  void set_transitions(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) {
    projection_ = projection;
    view_ = view;
    model_ = model;
  }

  void draw_units(const std::vector<std::shared_ptr<Unit>>& units) {
    shader_.use();

    // Pass them to the shaders
    glUniformMatrix4fv(shader_.get_location(Location::projection), 1, GL_FALSE,
                       glm::value_ptr(projection_));
    glUniformMatrix4fv(shader_.get_location(Location::view), 1, GL_FALSE, glm::value_ptr(view_));
    glUniformMatrix4fv(shader_.get_location(Location::model), 1, GL_FALSE, glm::value_ptr(model_));

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
  ShaderProgram shader_;

  glm::mat4 projection_;
  glm::mat4 view_;
  glm::mat4 model_;
};

#endif  // BATTLEVISION_OPENGLUNITSDRAWER_H
