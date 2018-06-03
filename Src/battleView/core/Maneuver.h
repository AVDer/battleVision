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
#include <string>
#include <vector>

#include "Logger.h"
#include "Unit.h"

using time_point_t = std::chrono::system_clock::time_point;
using maneuver_data_t = std::vector<std::string>;
using bvl::core::types::coordinate_t;

enum class ManeuverType { stop = 0, move, rotate, resize };

class Maneuver {
 public:
  Maneuver() = default;

  Maneuver(uint32_t unit_id, ManeuverType maneuver_type, time_point_t start_time,
           time_point_t stop_time, maneuver_data_t &&maneuver_data)
      : unit_id_(unit_id),
        maneuver_type_(maneuver_type),
        start_time_(start_time),
        stop_time_(stop_time),
        maneuver_data_(std::move(maneuver_data)) {}

  virtual ~Maneuver() = default;

  static void setGlobalTime(time_point_t start, time_point_t stop) {
    global_start_time = start;
    global_stop_time = stop;
  }

  static void setTime(time_point_t time) { global_time = time; }

  static time_point_t global_start_time;
  static time_point_t global_stop_time;
  static time_point_t global_time;

  virtual void operator()(Unit &unit) = 0;

  uint32_t unit_id() const { return unit_id_; }

  ManeuverType maneuver_type() const { return maneuver_type_; }

  time_point_t start_time() const { return start_time_; }

  time_point_t stop_time() const { return stop_time_; }

  maneuver_data_t data() const { return maneuver_data_; }

 protected:
  virtual size_t data_arity() = 0;

  bool data_valid() {
    if (maneuver_data_.size() != data_arity()) {
      Logger::error("Maneuver: Incorect maneuver data arity: %d != %d", maneuver_data_.size(), data_arity());
      return false;
    } else {
      return true;
    }
  }

  uint32_t unit_id_{0};
  ManeuverType maneuver_type_{ManeuverType::stop};
  time_point_t start_time_;
  time_point_t stop_time_;
  maneuver_data_t maneuver_data_;
};

#endif  // BATTLEVISION_MANEUVER_H
