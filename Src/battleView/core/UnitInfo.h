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

#ifndef CORE_UNITINFO_H_
#define CORE_UNITINFO_H_

#include <string>

#include "bvl/BVTypes.h"

using namespace bvl::core::types;

struct UnitGeneralInfo {
  UnitGeneralInfo() = default;

  UnitGeneralInfo(uint32_t u_id, uint32_t o_id, uint32_t a, unit_type_t u_t, std::string&& n) :
    unit_id(u_id),
    opponent_id(o_id),
    amount(a),
    unit_type(u_t),
    name(n) { }

  uint32_t unit_id {0};
  uint32_t opponent_id {0};
  uint32_t amount {0};
  unit_type_t unit_type;
  std::string name;
};

struct UnitDrawInfo {
  UnitDrawInfo() = default;

  UnitDrawInfo(point_t pos, color_t c, shape_t sh, rect_size_t s, angle_t a, unit_state_t us) :
    position(pos),
    color(c),
    shape(sh),
    size(s),
    angle(a),
    state(us) { }

  UnitDrawInfo modify_color(double factor) {
    UnitDrawInfo modified_info = *this;
    modified_info.color = color_t(modified_info.color * factor);
    return modified_info;
  }

  point_t position;
  color_t color;
  shape_t shape {shape_t::undefined};
  rect_size_t size;
  angle_t angle {0};
  unit_state_t state {unit_state_t::undefined};
};

class UnitInfo {
public:
  UnitInfo() = default;

  UnitInfo(UnitGeneralInfo&& unit_general_info, UnitDrawInfo unit_draw_info) :
    unit_general_info_(unit_general_info),
    unit_draw_info_(unit_draw_info) {
  }

  UnitInfo(const UnitInfo &unit_info) {
    unit_general_info_ = unit_info.unit_general_info();
    unit_draw_info_ = unit_info.unit_draw_info();
  }

  UnitGeneralInfo unit_general_info() const {
    return unit_general_info_;
  }

  UnitDrawInfo unit_draw_info() const {
    return unit_draw_info_;
  }

  void set_color(color_t color) {
    unit_draw_info_.color = color;
  }

  void rotate(bvl::core::types::angle_t angle) {
    unit_draw_info_.angle += angle;
  }

  void move(coordinate_t x, coordinate_t y) {
    unit_draw_info_.position += bvl::core::types::point_t(x, y);
  }

  void set_potition(coordinate_t x, coordinate_t y) {
    point_t new_position {unit_draw_info_.position};
    if (x > 0) new_position.set_x(x);
    if (y > 0) new_position.set_y(y);
    unit_draw_info_.position = new_position;
  }

  void set_angle(angle_t angle) {
    unit_draw_info_.angle = angle;
  }

  void set_size(coordinate_t width, coordinate_t height) {
    point_t new_size {unit_draw_info_.size};
    if (width > 0) new_size.set_x(width);
    if (height > 0) new_size.set_y(height);
    unit_draw_info_.size = new_size;
  }

  void enlarge(coordinate_t x, coordinate_t y) {
    unit_draw_info_.size += bvl::core::types::point_t(x, y);
  }

private:
  UnitGeneralInfo unit_general_info_;
  UnitDrawInfo unit_draw_info_;
};

#endif /* CORE_UNITINFO_H_ */
