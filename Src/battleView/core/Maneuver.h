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

#ifndef BATTLEVISION_MANEUVER_H
#define BATTLEVISION_MANEUVER_H

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Logger.h"
#include "Unit.h"
#include "bvl/TimePoint.h"

using maneuver_data_t = std::vector<std::string>;
using bvl::core::types::coordinate_t;

enum class ManeuverType { stop = 0, move, rotate, resize };

class Maneuver {
 public:
  Maneuver() = default;

  Maneuver(uint32_t unit_id, ManeuverType maneuver_type, model_time_t start_time,
           model_time_t stop_time, maneuver_data_t&& maneuver_data)
      : unit_id_(unit_id),
        maneuver_type_(maneuver_type),
        start_time_(start_time),
        stop_time_(stop_time),
        maneuver_data_(std::move(maneuver_data)) {}

  virtual ~Maneuver() = default;

  static void setGlobalTime(const model_time_t& start, const model_time_t& stop) {
    global_start_time_ = start;
    global_stop_time_ = stop;
  }

  static void setTime(const model_time_t& time) { global_time_ = time; }

  static void setTime(double_t position) {
    global_time_ =
        model_time_t(position * (global_stop_time_.value() - global_start_time_.value()) +
                     global_start_time_.value());
  }

  static model_time_t global_start_time_;
  static model_time_t global_stop_time_;
  static model_time_t global_time_;

  virtual void operator()(std::shared_ptr<Unit> unit) = 0;

  uint32_t unit_id() const { return unit_id_; }

  ManeuverType maneuver_type() const { return maneuver_type_; }

  model_time_t start_time() const { return start_time_; }

  model_time_t stop_time() const { return stop_time_; }

  maneuver_data_t data() const { return maneuver_data_; }

 protected:
  virtual size_t data_arity() = 0;

  bool data_valid() {
    if (maneuver_data_.size() != data_arity()) {
      Logger::error("Maneuver: Incorect maneuver data arity: %d != %d", maneuver_data_.size(),
                    data_arity());
      return false;
    } else {
      return true;
    }
  }

  uint32_t unit_id_{0};
  ManeuverType maneuver_type_{ManeuverType::stop};
  model_time_t start_time_;
  model_time_t stop_time_;
  maneuver_data_t maneuver_data_;
};

#endif  // BATTLEVISION_MANEUVER_H
