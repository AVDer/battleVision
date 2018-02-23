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

#ifndef BVL_COLOR_H_
#define BVL_COLOR_H_

#include "BVGlobal.h"

struct gl_color_s {
  float r;
  float g;
  float b;
};

template<typename T = uint32_t>
class Color {
public:
  explicit Color(T i_color = 0) : color_(i_color) { };

  gl_color_s get() const {
    return gl_color_s{
        static_cast<float>((color_ >> 24) & 0xFF) / 255.f,
        static_cast<float>((color_ >> 16) & 0xFF) / 255.f,
        static_cast<float>((color_ >> 8) & 0xFF) / 255.f
    };
  }

  T raw_color() const {
    return color_;
  }

  T operator*(double scale) {
    return color_ * scale;
  }

private:
  T color_;
};

#endif /* BVL_COLOR_H_ */
