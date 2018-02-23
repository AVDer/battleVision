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

#ifndef GUI_INFANTRYOPENGLDRAW_H
#define GUI_INFANTRYOPENGLDRAW_H

#include "OpenGLDrawStrategy.h"

class InfantryOpenGLDraw : public OpenGLDrawStrategy {
public:
  InfantryOpenGLDraw() = default;

  void fill_vertex(const UnitDrawInfo &udi) override {
    m_unit_vertices = {
        // top
        1.f, 1.f, unit_height,
        _color.r, _color.g, _color.b,
        1.f, 0.f, unit_height,
        _color.r, _color.g, _color.b,
        0.f, 0.f, unit_height,
        _color.r, _color.g, _color.b,
        0.f, 1.f, unit_height,
        _color.r, _color.g, _color.b,

        // bottom
        1.f, 1.f, 0.f,
        _color.r, _color.g, _color.b,
        1.f, 0.f, 0.f,
        _color.r, _color.g, _color.b,
        0.f, 0.f, 0.f,
        _color.r, _color.g, _color.b,
        0.f, 1.f, 0.f,
        _color.r, _color.g, _color.b,
    };

    m_unit_indices = {
        // top
        0, 1, 3,
        1, 2, 3,
        // right side
        0, 4, 5,
        5, 1, 0,
        // left side
        3, 7, 6,
        6, 2, 3,
        // near side
        1, 5, 6,
        6, 2, 1,
        // bar side
        3, 0, 4,
        4, 7, 3,
        // bottom
        // 4, 5, 7,
        // 5, 6, 7
    };

  }

};

#endif /* CORE_FILLDRAW_H_ */
