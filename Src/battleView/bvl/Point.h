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

#ifndef POINT_H
#define POINT_H

#include <cstdint>

namespace bvl {
  namespace core {
    namespace types {

      template<typename T>
      class Point {
      public:
        Point(const T &i_x = 0, const T &i_y = 0) : x_(i_x), y_(i_y) { }

        T x() const { return x_; }

        T y() const { return y_; }

        void set_x(T x) { x_ = x; }
        void set_y(T y) { y_ = y; }

        Point operator+=(const Point &that) {
          x_ += that.x();
          y_ += that.y();
          return *this;
        }

      private:
        T x_;
        T y_;
      };

      template<typename T>
      Point<T> operator+(const Point<T> &lhs, const Point<T> &rhs) {
        return Point<T>(lhs.x() + rhs.x(), lhs.y() + rhs.y());
      }

    }
  }
}

#endif // POINT_H
