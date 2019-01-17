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

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <string>

namespace bvl::core {

template <typename T>
class TimePoint {
 public:
  TimePoint() = default;
  explicit TimePoint(T time)
      : time_s_(time),
        time_(boost::gregorian::date(1400, boost::date_time::Jan, 1),
              boost::posix_time::time_duration(0, 0, static_cast<int>(time))) {}
  explicit TimePoint(const std::string& time) : time_(boost::posix_time::from_iso_string(time)) {
    auto date = time_.date();
    time_s_ = date.year() * kYearSeconds + date.month() * kMonthSeconds + date.day() * kDaySeconds +
              time_.time_of_day().total_seconds();
  }

  T value() const { return time_s_; }

  std::string to_string() { return boost::posix_time::to_iso_string(time_); }

 private:
  // For now simplified...
  static const uint64_t kDaySeconds{60 * 60 * 24};
  static const uint64_t kMonthSeconds{kDaySeconds * 30};
  static const uint64_t kYearSeconds{kDaySeconds * 365};

  T time_s_{};
  boost::posix_time::ptime time_{boost::posix_time::not_a_date_time};
};

}  // namespace bvl::core

using model_time_t = bvl::core::TimePoint<double>;
using real_time_t = std::chrono::system_clock::time_point;