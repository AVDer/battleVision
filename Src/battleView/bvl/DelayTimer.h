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

#ifndef BATTLEVISION_DELAYTIMER_H
#define BATTLEVISION_DELAYTIMER_H

#include <chrono>

template <typename Duration>
class DelayTimer {

public:
  explicit DelayTimer(Duration duration):
  duration_(duration) {
  }

  bool elapsed() {
    auto time_current = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(time_current - time_stamp_).count() > duration_) {
      time_stamp_ = time_current;
      return true;
    }
    return false;
  }

private:
  Duration duration_;
  std::chrono::steady_clock::time_point time_stamp_ {std::chrono::steady_clock::now()};

};


#endif //BATTLEVISION_DELAYTIMER_H
