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

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ManeuverFactory.h"
#include "MoveManeuver.h"
#include "OpponentInfo.h"
#include "ResizeManeuver.h"
#include "RotateManeuver.h"
#include "UnitsProcessor.h"

#include "../gui/OpenGLUnitsDrawer.h"

UnitsProcessor::UnitsProcessor() {
  ManeuverFactory::get().register_maneuver(ManeuverType::move, &MoveManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::rotate, &RotateManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::resize, &ResizeManeuver::create);
  Maneuver::setGlobalTime(start_time, stop_time);
  model_start = std::chrono::system_clock::now();
}

UnitsProcessor::~UnitsProcessor() {
  reset();
}

void UnitsProcessor::set_working_file(const std::string &new_string, bool renew) {
  if (working_file_ != new_string || !renew) {
    working_file_ = new_string;
    reset();
  }
}

void UnitsProcessor::create_units() {
  fill_units();
}

void UnitsProcessor::maneuver() {
  Maneuver::setTime(time_point_t(std::chrono::system_clock::now() - model_start));
  for (Unit &unit : units_) {
    for (auto &maneuver : maneuvers_) {
      maneuver->operator()(unit);
    }
  }
}

void UnitsProcessor::draw_units() {
  /*
  for (const Unit &u : units_) {
    u.draw();
  }
   */
  OpenGLUnitsDrawer::instance()->draw_units(units_);
}

void UnitsProcessor::reset() {
  units_.clear();
  fill_units();
}

void UnitsProcessor::fill_units() {

  boost::property_tree::ptree battle_description;
  boost::property_tree::read_json(working_file_, battle_description);

  int meta_version = battle_description.get("general.version", 0);

  // Opponents

  std::vector<OpponentInfo> opponents;
  for (boost::property_tree::ptree::value_type &opponent : battle_description.get_child("opponents")) {
    opponents.emplace_back(
        opponent.second.get<int>("id"),
        opponent.second.get<std::string>("name"),
        color_t(opponent.second.get<uint32_t>("color"))
    );
  }

  // Units

  for (boost::property_tree::ptree::value_type &unit : battle_description.get_child("units")) {
    UnitInfo unit_info = UnitInfo(
        UnitGeneralInfo(
            unit.second.get<uint32_t>("id"),
            unit.second.get<uint32_t>("side"),
            unit.second.get<uint32_t>("count"),
            static_cast<unit_type_t>(unit.second.get<int>("type", 0)),
            unit.second.get<std::string>("name")),
        UnitDrawInfo(
            point_t(unit.second.get<int>("position_x"),
                    unit.second.get<int>("position_y")),
            color_t(0),
            static_cast<shape_t>(unit.second.get<int>("shape")),
            point_t(unit.second.get<int>("size_x"),
                    unit.second.get<int>("size_y")),
            static_cast<angle_t>(unit.second.get<int>("angle")),
            unit_state_t::alive
        )
    );
    unit_info.set_color((*std::find_if(
        std::begin(opponents),
        std::end(opponents),
        [unit_info](const OpponentInfo &o) -> bool {
          return o.id() == unit_info.unit_general_info().opponent_id;
        })).color());
    units_.push_back(std::move(UnitFactory::get_unit(std::move(unit_info))));
  }

  // Maneuvers

  for (boost::property_tree::ptree::value_type &maneuver : battle_description.get_child("maneuvers")) {
    maneuver_data_t local_data;
    for (boost::property_tree::ptree::value_type &data_item : maneuver.second.get_child("data")) {
      local_data.push_back(data_item.second.data());
    }
    maneuvers_.push_back(ManeuverFactory::create(ManeuverType(maneuver.second.get<int>("type")),
                                                  maneuver.second.get<uint32_t>("unit"),
                                                  time_point_t(
                                                      std::chrono::seconds(maneuver.second.get<int>("start_time"))),
                                                  time_point_t(
                                                      std::chrono::seconds(maneuver.second.get<int>("stop_time"))),
                                                  std::move(local_data)

    ));
  }

}
