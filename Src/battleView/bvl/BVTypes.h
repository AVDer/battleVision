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

#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <cstdint>
#include <utility>

#include "BVGlobal.h"
#include "Color.h"
#include "Point.h"

namespace bvl::core::types {

template <typename Enumeration>
auto as_integer(Enumeration const value) {
  return static_cast<typename std::underlying_type_t<Enumeration>>(value);
}

enum class unit_type_t { undefined, infantry, cavalry, archery };

enum class shape_t { undefined = 0, rectangle = 1, triangle };

enum class unit_state_t { undefined = 0, alive = 1, active, killed };

using coordinate_t = int16_t;
using point_t = Point<coordinate_t>;
using rect_size_t = Point<coordinate_t>;
using angle_t = double;
using color_t = Color<uint32_t>;

using proportion_t = std::pair<uint8_t, uint8_t>;

}

#endif  // TYPES_H
