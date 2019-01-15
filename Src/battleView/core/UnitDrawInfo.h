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

#ifndef CORE_UNITDRAWINFO_H_
#define CORE_UNITDRAWINFO_H_

#include <string>

#include "bvl/BVTypes.h"

using namespace bvl::core::types;

class UnitDrawInfo {
 public:
  UnitDrawInfo() = default;

  UnitDrawInfo(point_t pos, color_t c, shape_t sh, rect_size_t s, angle_t a, unit_state_t us)
      : position_(pos), color_(c), shape_(sh), size_(s), angle_(a), state_(us) {}

  UnitDrawInfo& modify_color(double factor) { return set_color(color_t(color_ * factor)); }

  UnitDrawInfo& set_position(point_t position) {
    position_ = position;
    return *this;
  }

  UnitDrawInfo& set_color(color_t color) {
    color_ = color;
    return *this;
  }

  UnitDrawInfo& set_shape(shape_t shape) {
    shape_ = shape;
    return *this;
  }

  UnitDrawInfo& set_size(rect_size_t size) {
    size_ = size;
    return *this;
  }

  UnitDrawInfo& set_angle(angle_t angle) {
    angle_ = angle;
    return *this;
  }

  UnitDrawInfo& set_state(unit_state_t state) {
    state_ = state;
    return *this;
  }

  point_t position() const { return position_; }
  color_t color() const { return color_; }
  shape_t shape() const { return shape_; }
  rect_size_t size() const { return size_; }
  angle_t angle() const { return angle_; }
  unit_state_t state() const { return state_; }

 private:
  point_t position_;
  color_t color_;
  shape_t shape_{shape_t::undefined};
  rect_size_t size_;
  angle_t angle_{0};
  unit_state_t state_{unit_state_t::undefined};
};

#endif
