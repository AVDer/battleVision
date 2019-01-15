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

#include "UnitDrawInfo.h"
#include "UnitGeneralInfo.h"

using namespace bvl::core::types;

class UnitInfo {
 public:
  UnitInfo() = default;

  UnitInfo(UnitGeneralInfo&& unit_general_info, UnitDrawInfo unit_draw_info)
      : unit_general_info_(unit_general_info), unit_draw_info_(unit_draw_info) {}

  UnitInfo(const UnitInfo& unit_info) {
    unit_general_info_ = unit_info.unit_general_info();
    unit_draw_info_ = unit_info.unit_draw_info();
  }

  UnitInfo& operator=(const UnitInfo& that);

  const UnitGeneralInfo& unit_general_info() const { return unit_general_info_; }

  const UnitDrawInfo& unit_draw_info() const { return unit_draw_info_; }

  void set_color(const color_t& color) { unit_draw_info_.set_color(color); }

  void rotate(bvl::core::types::angle_t angle) {
    unit_draw_info_.set_angle(unit_draw_info_.angle() + angle);
  }

  void move(coordinate_t x, coordinate_t y) {
    unit_draw_info_.set_position(unit_draw_info_.position() + bvl::core::types::point_t(x, y));
  }

  void set_potition(coordinate_t x, coordinate_t y) {
    point_t new_position{unit_draw_info_.position()};
    if (x > 0) new_position.set_x(x);
    if (y > 0) new_position.set_y(y);
    unit_draw_info_.set_position(new_position);
  }

  void set_angle(angle_t angle) { unit_draw_info_.set_angle(angle); }

  void set_size(coordinate_t width, coordinate_t height) {
    point_t new_size{unit_draw_info_.size()};
    if (width > 0) new_size.set_x(width);
    if (height > 0) new_size.set_y(height);
    unit_draw_info_.set_size(new_size);
  }

  void enlarge(coordinate_t x, coordinate_t y) {
    unit_draw_info_.set_size(unit_draw_info_.size() + bvl::core::types::point_t(x, y));
  }

 private:
  UnitGeneralInfo unit_general_info_;
  UnitDrawInfo unit_draw_info_;
};

#endif /* CORE_UNITINFO_H_ */
