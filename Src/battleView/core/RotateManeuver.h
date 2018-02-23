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

#ifndef BATTLEVISION_ROTATEMANEUVER_H
#define BATTLEVISION_ROTATEMANEUVER_H

#include "Maneuver.h"

class RotateManeuver : public Maneuver {

public:

  RotateManeuver(uint32_t unit_id,
                 time_point_t start_time,
                 time_point_t stop_time,
                 maneuver_data_t &&data)
      : Maneuver(unit_id, ManeuverType::rotate, start_time, stop_time, std::move(data)) {
    if (data_valid()) {
      start_angle_ = static_cast<coordinate_t >(std::stoi(maneuver_data_.at(0)));
      stop_angle_ = static_cast<coordinate_t >(std::stoi(maneuver_data_.at(1)));
    }
  }

  static std::unique_ptr<Maneuver> create(uint32_t unit_id,
                          time_point_t start_time,
                          time_point_t stop_time,
                          std::vector<std::string> &&data) {
    return std::make_unique<RotateManeuver>(RotateManeuver(unit_id, start_time, stop_time, std::move(data)));
  }

  void operator()(Unit &unit) override {
    if (unit.id() != unit_id_) return;
    if (global_time < start_time_) {
      unit.set_angle(start_angle_);
    } else if (global_time >= stop_time_) {
      unit.set_angle(stop_angle_);
    } else {
      unit.set_angle(
          static_cast<coordinate_t>(
              static_cast<double>((global_time - start_time_).count()) / (stop_time_ - start_time_).count() *
              (stop_angle_ - start_angle_) + start_angle_)
      );
    }
  }

private:

  size_t data_arity() override {
    return 2;
  }

  angle_t start_angle_;
  angle_t stop_angle_;
};


#endif //BATTLEVISION_ROTATEMANEUVER_H
