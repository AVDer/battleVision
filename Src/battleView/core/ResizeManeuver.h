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

#ifndef BATTLEVISION_RESIZEMANEUVER_H
#define BATTLEVISION_RESIZEMANEUVER_H

#include "Maneuver.h"

class ResizeManeuver : public Maneuver {
 public:
  ResizeManeuver(uint32_t unit_id, model_time_t start_time, model_time_t stop_time,
                 maneuver_data_t &&data)
      : Maneuver(unit_id, ManeuverType::resize, start_time, stop_time, std::move(data)) {
    if (data_valid()) {
      start_width_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(0)));
      start_height_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(1)));
      stop_width_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(2)));
      stop_height_ = static_cast<coordinate_t>(std::stoi(maneuver_data_.at(3)));
    }
  }

  static std::unique_ptr<Maneuver> create(uint32_t unit_id, const model_time_t &start_time,
                                          const model_time_t &stop_time, maneuver_data_t &&data) {
    return std::make_unique<ResizeManeuver>(
        ResizeManeuver(unit_id, start_time, stop_time, std::move(data)));
  }

  void operator()(std::shared_ptr<Unit> unit) override {
    if (unit->id() != unit_id_) return;
    if (global_time_.value() < start_time_.value()) {
      unit->set_size(start_width_, start_height_);
    } else if (global_time_.value() >= stop_time_.value()) {
      unit->set_size(stop_width_, stop_height_);
    } else {
      unit->set_size(static_cast<coordinate_t>((global_time_.value() - start_time_.value()) /
                                                   (stop_time_.value() - start_time_.value()) *
                                                   (stop_width_ - start_width_) +
                                               start_width_),
                     static_cast<coordinate_t>((global_time_.value() - start_time_.value()) /
                                                   (stop_time_.value() - start_time_.value()) *
                                                   (stop_height_ - start_height_) +
                                               start_height_));
    }
  }

 private:
  size_t data_arity() override { return 4; }

  coordinate_t start_width_ = 0;
  coordinate_t stop_width_ = 0;
  coordinate_t start_height_ = 0;
  coordinate_t stop_height_ = 0;
};

#endif  // BATTLEVISION_RESIZEMANEUVER_H
