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

#ifndef BATTLEVISION_MANEUVERFACTORY_H
#define BATTLEVISION_MANEUVERFACTORY_H

#include <map>

#include "Maneuver.h"

class ManeuverFactory {
 public:
  static std::unique_ptr<Maneuver> create(ManeuverType type, uint32_t unit_id,
                                          time_point_t start_time, time_point_t stop_time,
                                          std::vector<std::string> &&data);

  static ManeuverFactory &get() {
    static ManeuverFactory instance;
    return instance;
  }

  using ManeuverConstructor = std::unique_ptr<Maneuver> (*)(uint32_t, time_point_t, time_point_t,
                                                            std::vector<std::string> &&);

  void register_maneuver(ManeuverType type, ManeuverConstructor constructor);

 private:
  ManeuverFactory() = default;

  static std::map<ManeuverType, ManeuverConstructor> maneuver_base_;
};

#endif  // BATTLEVISION_MANEUVERFACTORY_H
