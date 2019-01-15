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

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "ManeuverFactory.h"
#include "MoveManeuver.h"
#include "OpponentInfo.h"
#include "ResizeManeuver.h"
#include "RotateManeuver.h"
#include "UnitsProcessor.h"

#include "gui/ConsoleUnitsDrawer.h"
#include "gui/OpenGLUnitsDrawer.h"

UnitsProcessor::UnitsProcessor() {
  ManeuverFactory::get().register_maneuver(ManeuverType::move, &MoveManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::rotate, &RotateManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::resize, &ResizeManeuver::create);
  simulation_start_ = std::chrono::system_clock::now();
}

UnitsProcessor::~UnitsProcessor() { reset(); }

void UnitsProcessor::set_working_file(const std::string &new_string, bool renew) {
  if (working_file_ != new_string || !renew) {
    working_file_ = new_string;
    reset();
  }
}

void UnitsProcessor::create_units() { fill_units(); }

void UnitsProcessor::maneuver() {
  // ToDo: handle finish
  if (std::chrono::system_clock::now() - simulation_start_ > real_stop_time_ - real_start_time_)
    exit(1);

  Maneuver::setTime(
      static_cast<double_t>((std::chrono::system_clock::now() - simulation_start_).count()) /
      (real_stop_time_ - real_start_time_).count());
  for (Unit &unit : units_) {
    for (auto &maneuver : maneuvers_) {
      maneuver->operator()(unit);
    }
  }
}

void UnitsProcessor::draw_units() {
  OpenGLUnitsDrawer::instance()->draw_units(units_);
  // ConsoleUnitsDrawer::instance()->draw_units(units_);
}

void UnitsProcessor::reset() {
  units_.clear();
  fill_units();
}

void UnitsProcessor::fill_units() {
  boost::property_tree::ptree battle_description;
  boost::property_tree::read_json(working_file_, battle_description);

  int meta_version = battle_description.get("general.version", 0);

  map_file_name_ = battle_description.get("general.map", "");
  model_start_time_ = battle_description.get("general.start_time", "0");
  model_stop_time_ = battle_description.get("general.stop_time", "9");
  Maneuver::setGlobalTime(model_start_time_, model_stop_time_);

  // Opponents

  for (boost::property_tree::ptree::value_type &opponent :
       battle_description.get_child("opponents")) {
    opponents_[opponent.second.get<int>("id")] = {opponent.second.get<std::string>("name"),
                                                  color_t(opponent.second.get<uint32_t>("color"))};
  }

  // Units

  for (boost::property_tree::ptree::value_type &unit : battle_description.get_child("units")) {
    UnitGeneralInfo general_info;
    UnitDrawInfo draw_info;
    general_info.set_id(unit.second.get<uint32_t>("id"))
        .set_opponent_id(unit.second.get<uint32_t>("side"))
        .set_amount(unit.second.get<uint32_t>("count"))
        .set_type(static_cast<unit_type_t>(unit.second.get<int>("type", 0)))
        .set_name(unit.second.get<std::string>("name"));
    draw_info
        .set_position(
            point_t(unit.second.get<int>("position_x"), unit.second.get<int>("position_y")))
        .set_color(opponents_[general_info.opponent_id()].color())
        .set_shape(static_cast<shape_t>(unit.second.get<int>("shape")))
        .set_size(point_t(unit.second.get<int>("size_x"), unit.second.get<int>("size_y")))
        .set_angle(static_cast<angle_t>(unit.second.get<int>("angle")))
        .set_state(unit_state_t::alive);
    units_.push_back(
        std::move(UnitFactory::get_unit({std::move(general_info), std::move(draw_info)})));
  }

  // Maneuvers

  for (boost::property_tree::ptree::value_type &maneuver :
       battle_description.get_child("maneuvers")) {
    maneuver_data_t local_data;
    for (boost::property_tree::ptree::value_type &data_item : maneuver.second.get_child("data")) {
      local_data.push_back(data_item.second.data());
    }
    maneuvers_.push_back(ManeuverFactory::create(
        ManeuverType(maneuver.second.get<int>("type")), maneuver.second.get<uint32_t>("unit"),
        model_time_t(maneuver.second.get<std::string>("start_time")),
        model_time_t(maneuver.second.get<std::string>("stop_time")), std::move(local_data)));
  }
}
