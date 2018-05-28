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

#ifndef CORE_IDRAWER_H_
#define CORE_IDRAWER_H_

#include "bvl/BVTypes.h"

using namespace bvl::core::types;

/*
class IDrawer {
public:
  virtual void set_color(color_t c) = 0;

  virtual void draw_rect(point_t p1, point_t p2, angle_t a) = 0;
  virtual void draw_empty_rect(point_t p1, point_t p2, angle_t a, uint16_t width
= 1) = 0; virtual void draw_line(point_t p1, point_t p2, angle_t a, uint16_t
width = 1) = 0;

  virtual ~IDrawer() { }

  bool show_dir_arrow() const {
    return m_show_dir_arrow;
  }

  void set_show_dir_arrow(bool show_dir_arrow) {
    m_show_dir_arrow = show_dir_arrow;
  }

protected:
  virtual void draw_direction_arrow(point_t position, angle_t a, uint16_t size =
10) = 0;

private:
  bool m_show_dir_arrow {false};
};
*/

#endif /* CORE_IDRAWER_H_ */
