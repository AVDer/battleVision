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

#ifndef CORE_UNITINFO_H_
#define CORE_UNITINFO_H_

#include <memory>
#include <string>

#include "bvl/BVTypes.h"

#include "OpponentInfo.h"
#include "UnitDrawInfo.h"
#include "UnitGeneralInfo.h"

using namespace bvl::core::types;

class UnitInfo {
 public:
  UnitInfo() = default;

  UnitInfo(UnitGeneralInfo&& unit_general_info, UnitDrawInfo unit_draw_info)
      : unit_general_info_(unit_general_info), unit_draw_info_(unit_draw_info) {}

  UnitInfo(const UnitInfo& unit_info) {
    unit_general_info_ = unit_info.unit_general_info();
    unit_draw_info_ = unit_info.unit_draw_info();
  }

  UnitInfo& operator=(const UnitInfo& that);

  const UnitGeneralInfo& unit_general_info() const { return unit_general_info_; }

  const UnitDrawInfo& unit_draw_info() const { return unit_draw_info_; }

  UnitInfo& set_opponent(std::shared_ptr<OpponentInfo> opponent);

  void rotate(bvl::core::types::angle_t angle);

  void move(coordinate_t x, coordinate_t y);

  void set_potition(coordinate_t x, coordinate_t y);

  void set_angle(angle_t angle);

  void set_size(coordinate_t width, coordinate_t height);

  void enlarge(coordinate_t x, coordinate_t y);

 private:
  UnitGeneralInfo unit_general_info_;
  UnitDrawInfo unit_draw_info_;
  std::shared_ptr<OpponentInfo> opponent_;
};

#endif /* CORE_UNITINFO_H_ */
