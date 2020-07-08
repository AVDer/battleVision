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

#ifndef BATTLEVISION_SHADERSUNIT_H
#define BATTLEVISION_SHADERSUNIT_H

#include <GL/gl.h>

namespace ShadersUnit {

enum Uniform : GLuint { projection = 0, view, model, transform };

constexpr GLchar *vertex_shader = (GLchar *)R"(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_color;

out vec3 f_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 transform;

void main() {
  gl_Position = projection * view * model * transform * vec4(position, 1.0f);
  f_color = in_color;
}
)";

constexpr GLchar *fragment_shader = (GLchar *)R"(
#version 330 core

in vec3 f_color;

out vec4 color;

void main() {
  color = vec4(f_color, 1.0f);
}
)";

};  // namespace ShadersUnit

#endif  // BATTLEVISION_SHADERSUNIT_H
