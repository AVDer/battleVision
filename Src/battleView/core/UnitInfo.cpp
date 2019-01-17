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

#include "UnitInfo.h"

UnitInfo& UnitInfo::operator=(const UnitInfo& that) {
  this->unit_general_info_ = that.unit_general_info();
  this->unit_draw_info_ = that.unit_draw_info();
  return *this;
}

UnitInfo& UnitInfo::set_opponent(std::shared_ptr<OpponentInfo> opponent) {
  opponent_ = opponent;
  unit_general_info_.set_side_name(opponent->name());
  unit_draw_info_.set_color(opponent->color());
  return *this;
}

// Tranformations

void UnitInfo::rotate(bvl::core::types::angle_t dangle) {
  unit_draw_info_.set_angle(unit_draw_info_.angle() + dangle);
}

void UnitInfo::move(coordinate_t dx, coordinate_t dy) {
  unit_draw_info_.set_position(unit_draw_info_.position() + bvl::core::types::point_t(dx, dy));
}

void UnitInfo::set_potition(coordinate_t x, coordinate_t y) {
  point_t new_position{unit_draw_info_.position()};
  if (x > 0) new_position.set_x(x);
  if (y > 0) new_position.set_y(y);
  unit_draw_info_.set_position(new_position);
}

void UnitInfo::set_angle(angle_t angle) { unit_draw_info_.set_angle(angle); }

void UnitInfo::set_size(coordinate_t width, coordinate_t height) {
  point_t new_size{unit_draw_info_.size()};
  if (width > 0) new_size.set_x(width);
  if (height > 0) new_size.set_y(height);
  unit_draw_info_.set_size(new_size);
}

void UnitInfo::enlarge(coordinate_t dx, coordinate_t dy) {
  unit_draw_info_.set_size(unit_draw_info_.size() + bvl::core::types::point_t(dx, dy));
}