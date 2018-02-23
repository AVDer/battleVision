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

#ifndef CORE_DRAWSTRATEGY_H_
#define CORE_DRAWSTRATEGY_H_

#include <memory>
#include "IDrawer.h"
#include "UnitInfo.h"

#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>

#include "../gui/RenderInfo.h"

class DrawStrategy {
public:
  DrawStrategy() = default;
  virtual ~DrawStrategy() = default;

  virtual void update_draw_info(const UnitDrawInfo &udi) = 0;
  //virtual void fill_draw_structures(std::vector<GLfloat> & vertices, std::vector<GLuint> & indecies, glm::mat4 & transformation) = 0;
  virtual RenderInfo fill_draw_structures() = 0;

  bool is_modified() const {return is_modified_;}

protected:
  bool is_modified_ {false};
};

#endif /* CORE_DRAWSTRATEGY_H_ */
