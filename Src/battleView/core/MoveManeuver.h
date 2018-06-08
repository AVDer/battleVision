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

#ifndef BATTLEVISION_MOVEMANEUVER_H
#define BATTLEVISION_MOVEMANEUVER_H

#include "Maneuver.h"

class MoveManeuver : public Maneuver {
 public:
  MoveManeuver(uint32_t unit_id, model_time_t start_time, model_time_t stop_time,
               maneuver_data_t &&data)
      : Maneuver(unit_id, ManeuverType::move, start_time, stop_time, std::move(data)) {
    if (data_valid()) {
      start_x_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(0)));
      start_y_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(1)));
      stop_x_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(2)));
      stop_y_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(3)));
    }
  }

  static std::unique_ptr<Maneuver> create(uint32_t unit_id, model_time_t start_time,
                                          model_time_t stop_time, maneuver_data_t &&data) {
    return std::make_unique<MoveManeuver>(
        MoveManeuver(unit_id, start_time, stop_time, std::move(data)));
  }

  void operator()(Unit &unit) override {
    if (unit.id() != unit_id_) return;
    if (global_time_.value() < start_time_.value()) {
      unit.set_position(start_x_, start_y_);
    } else if (global_time_.value() >= stop_time_.value()) {
      unit.set_position(stop_x_, stop_y_);
    } else {
      unit.set_position(static_cast<coordinate_t>((global_time_.value() - start_time_.value()) /
                                                      (stop_time_.value() - start_time_.value()) *
                                                      (stop_x_ - start_x_) +
                                                  start_x_),
                        static_cast<coordinate_t>((global_time_.value() - start_time_.value()) /
                                                      (stop_time_.value() - start_time_.value()) *
                                                      (stop_y_ - start_y_) +
                                                  start_y_));
    }
  }

 private:
  size_t data_arity() override { return 4; }

  coordinate_t start_x_ = 0;
  coordinate_t stop_x_ = 0;
  coordinate_t start_y_ = 0;
  coordinate_t stop_y_ = 0;
};

#endif  //#define BATTLEVISION_MOVEMANEUVER_H