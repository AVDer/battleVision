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

#ifndef BATTLEVISION_RENDERINFO_H
#define BATTLEVISION_RENDERINFO_H

#include "glad/glad.h"
#include "glm/glm.hpp"

struct RenderInfo {
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indecies;
  glm::mat4 transformation;
};

struct OpenGLRenderInfo : public RenderInfo {};

typedef struct {
  GLuint count;
  GLuint primCount;
  GLuint firstIndex;
  GLuint baseVertex;
  GLuint baseInstance;
} DrawElementsIndirectCommand;

#endif  // BATTLEVISION_RENDERINFO_H
