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

#include "ManeuverFactory.h"

void ManeuverFactory::register_maneuver(ManeuverType type, ManeuverConstructor constructor) {
  maneuver_base[type] = constructor;
}

std::unique_ptr<Maneuver> ManeuverFactory::create(ManeuverType type, uint32_t unit_id,
                                                  time_point_t start_time, time_point_t stop_time,
                                                  std::vector<std::string>&& data) {
  return std::move(maneuver_base[type](unit_id, start_time, stop_time, std::move(data)));
}

std::map<ManeuverType, ManeuverFactory::ManeuverConstructor> ManeuverFactory::maneuver_base;