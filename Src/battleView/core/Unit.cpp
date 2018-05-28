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

Unit::Unit(DrawStrategy *str) :
  draw_strategy_(str) {
}

Unit::Unit(const UnitInfo &unit_info) :
  unit_info_(unit_info),
  draw_strategy_(nullptr) {
}

Unit::Unit(const Unit &that) :
  sub_units_(that.sub_units_),
  unit_info_(that.unit_info_),
  draw_strategy_(that.draw_strategy_) {
}

Unit::Unit(Unit &&that) noexcept :
  sub_units_(std::move(that.sub_units_)),
  unit_info_(that.unit_info_),
  draw_strategy_(std::move(that.draw_strategy_)) {
}

Unit Unit::set_unit_info(const UnitInfo &unit_info) {
  unit_info_ = unit_info;
  return *this;
}

void Unit::draw() const {
  /*
  assert(draw_strategy_ != nullptr);
  if (is_selected_)
    draw_strategy_->draw(unit_info_.unit_draw_info().modify_color(2.));
  else
    draw_strategy_->draw(unit_info_.unit_draw_info());
    */
}

Unit Unit::set_draw_strategy(std::shared_ptr<DrawStrategy>&& strategy) {
  draw_strategy_ = strategy;
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
  return (*this);
}

void Unit::rotate(bvl::core::types::angle_t angle) {
  unit_info_.rotate(angle);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::move(coordinate_t xdiff, coordinate_t ydiff) {
  unit_info_.move(xdiff, ydiff);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::set_position(coordinate_t newx, coordinate_t newy) {
  unit_info_.set_potition(newx, newy);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::set_angle(angle_t angle) {
  unit_info_.set_angle(angle);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::set_size(coordinate_t width, coordinate_t height) {
  unit_info_.set_size(width, height);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::enlarge(int16_t xdiff, int16_t ydiff) {
  unit_info_.enlarge(xdiff, ydiff);
  draw_strategy_->update_draw_info(unit_info_.unit_draw_info());
}

void Unit::print_info() {
  Logger::info("Unit info: %dx%d @ Position: %d:%d / %d", unit_info_.unit_draw_info().size.x(), unit_info_.unit_draw_info().size.y(),
            unit_info_.unit_draw_info().position.x(), unit_info_.unit_draw_info().position.y(), unit_info_.unit_draw_info().angle);
}
