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

#include "Unit.h"

#include "Logger.h"

Unit::Unit(const Unit &that) : sub_units_(that.sub_units_), unit_info_(that.unit_info_) {}

Unit::Unit(Unit &&that) noexcept
    : sub_units_(std::move(that.sub_units_)), unit_info_(that.unit_info_) {}

Unit &Unit::set_unit_info(const UnitInfo &unit_info) {
  unit_info_ = unit_info;
  return *this;
}

Unit &Unit::set_draw_strategy(std::shared_ptr<DrawStrategy> &&strategy) {
  draw_strategy_ = strategy;
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
  return *this;
}

void Unit::rotate(bvl::core::types::angle_t angle) { unit_info_.rotate(angle); }

void Unit::move(coordinate_t xdiff, coordinate_t ydiff) { unit_info_.move(xdiff, ydiff); }

void Unit::set_position(coordinate_t newx, coordinate_t newy) {
  unit_info_.set_potition(newx, newy);
}

void Unit::set_angle(angle_t angle) { unit_info_.set_angle(angle); }

void Unit::set_size(coordinate_t width, coordinate_t height) { unit_info_.set_size(width, height); }

void Unit::enlarge(int16_t xdiff, int16_t ydiff) { unit_info_.enlarge(xdiff, ydiff); }

void Unit::print_info() const {
  auto draw_info = unit_info_.unit_draw_info();
  Logger::info("Unit info: %s/%s : %dx%d @ Position: %d:%d / %d",
               unit_info_.unit_general_info().name().c_str(),
               unit_info_.unit_general_info().side_name().c_str(), draw_info.size().x(),
               draw_info.size().y(), draw_info.position().x(), draw_info.position().y(),
               static_cast<int16_t>(draw_info.angle()));
}
