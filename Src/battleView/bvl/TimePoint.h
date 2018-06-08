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

#include <chrono>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <string>

namespace bvl {
namespace core {

template<typename T>
class TimePoint {
 public:
  TimePoint() = default;
  explicit TimePoint(T time) : time_s_(time) {}
  TimePoint(const std::string& time) {
    time_s_ = std::stod(time);
  }

  T value() const { return time_s_; }

  std::string to_string() { return std::to_string(time_s_); }

 private:
  T time_s_{};
};

}  // namespace core
}  // namespace bvl

using model_time_t = bvl::core::TimePoint<double_t>;
using real_time_t = std::chrono::system_clock::time_point;