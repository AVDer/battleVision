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

#ifndef CORE_UNITSPROCESSOR_H_
#define CORE_UNITSPROCESSOR_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Maneuver.h"
#include "Unit.h"
#include "UnitFactory.h"

class UnitsProcessor {
 public:
  UnitsProcessor();

  ~UnitsProcessor();

  void set_working_file(const std::string &, bool renew = false);

  auto map_file_name() const { return map_file_name_; }

  void create_units();

  void maneuver();

  void draw_units();

  void reset();

  void rotate(bvl::core::types::angle_t angle) { units_[selected_unit_].rotate(angle); }

  void move(int16_t xdiff, int16_t ydiff) { units_[selected_unit_].move(xdiff, ydiff); }

  void enlarge(int16_t xdsize, int16_t ydsize) { units_[selected_unit_].enlarge(xdsize, ydsize); }

  void print_unit_info() { units_[selected_unit_].print_info(); }

  void next_selected_unit() {
    units_.at(selected_unit_).set_selected(false);
    if (++selected_unit_ >= units_.size()) selected_unit_ = 0;
    units_.at(selected_unit_).set_selected(true);
  }

  void prev_selected_unit() {
    units_.at(selected_unit_).set_selected(false);
    if (selected_unit_ == 0) {
      selected_unit_ = units_.size() - 1;
    } else {
      --selected_unit_;
    }
    units_.at(selected_unit_).set_selected(true);
  }

 private:
  const real_time_t real_start_time_{std::chrono::seconds(0)};
  const real_time_t real_stop_time_{std::chrono::seconds(5)};
  real_time_t simulation_start_;

  model_time_t model_start_time_;
  model_time_t model_stop_time_;

  std::string working_file_;
  std::string map_file_name_;
  std::vector<Unit> units_;
  std::unordered_map<uint32_t, std::shared_ptr<OpponentInfo>> opponents_;
  std::vector<std::unique_ptr<Maneuver>> maneuvers_;

  void fill_units();

  std::size_t selected_unit_{0};
};

#endif /* CORE_UNITSPROCESSOR_H_ */
