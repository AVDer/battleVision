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

#ifndef BATTLEVISION_SHADERSFIELD_H
#define BATTLEVISION_SHADERSFIELD_H

#include <GL/gl.h>

namespace ShadersField {

constexpr GLchar *vertex_shader = (GLchar *)R"(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 f_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  f_tex_coord = texCoord;
}
)";

constexpr GLchar *fragment_shader = (GLchar *)R"(
#version 330 core

out vec4 color;

in vec2 f_tex_coord;

uniform sampler2D in_texture;

void main() {
  color = texture(in_texture, f_tex_coord);
}
)";

};  // namespace ShadersField

#endif  // BATTLEVISION_SHADERSFIELD_H
