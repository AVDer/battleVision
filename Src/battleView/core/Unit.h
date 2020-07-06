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

#ifndef CORE_UNIT_H_
#define CORE_UNIT_H_

#include <vector>

#include "DrawStrategy.h"
#include "OpponentInfo.h"
#include "UnitInfo.h"

class Unit {
 public:
  Unit() = default;
  Unit(const Unit& that);
  Unit(Unit&& that) noexcept;

  Unit& operator=(const Unit& that) = delete;

  virtual void draw() const {};
  Unit& set_unit_info(const UnitInfo& unit_info);
  Unit& set_draw_strategy(std::shared_ptr<DrawStrategy>&& strategy);

  void rotate(bvl::core::types::angle_t angle);
  void move(coordinate_t xdiff, coordinate_t ydiff);
  void set_position(coordinate_t newx, coordinate_t newy);
  void set_angle(angle_t angle);
  void set_size(coordinate_t width, coordinate_t height);
  void enlarge(int16_t xdiff, int16_t ydiff);
  void print_info() const;

  void set_opponent(std::shared_ptr<OpponentInfo> opponent) { unit_info_.set_opponent(opponent); }

  void set_active(bool active) { is_active_ = active; }

  void set_selected(bool selected) { is_selected_ = selected; }

  auto draw_strategy() const { return draw_strategy_; }
  auto id() const { return unit_info_.unit_general_info().unit_id(); }

 private:
  std::vector<Unit> sub_units_;
  UnitInfo unit_info_;
  std::shared_ptr<DrawStrategy> draw_strategy_;
  bool is_active_{false};
  bool is_selected_{false};
};

#endif /* CORE_UNIT_H_ */
