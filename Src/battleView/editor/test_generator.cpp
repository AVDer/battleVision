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

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "bvl/BVTypes.h"
#include "core/ManeuverFactory.h"
#include "core/MoveManeuver.h"
#include "core/OpponentInfo.h"
#include "core/ResizeManeuver.h"
#include "core/RotateManeuver.h"

namespace test_generator {

int generate_battle_file() {
  boost::property_tree::ptree battle_description_tree;
  battle_description_tree.put("general.version", 2);
  battle_description_tree.put("general.map", "bm.tga");
  battle_description_tree.put("general.start_time", "0");
  battle_description_tree.put("general.stop_time", "9");

  // Opponents

  std::map<uint32_t, OpponentInfo> opponents;
  opponents[1] = {"Greece", bvl::core::types::color_t(0x00007000)};
  opponents[2] = {"Persia", bvl::core::types::color_t(0x70000000)};

  boost::property_tree::ptree opponents_tree;
  for (const auto& [id, o] : opponents) {
    boost::property_tree::ptree opponent_node;
    opponent_node.put("id", id);
    opponent_node.put("name", o.name());
    opponent_node.put("color", o.color().raw_color());
    opponents_tree.push_back(std::make_pair("", opponent_node));
  }
  battle_description_tree.add_child("opponents", opponents_tree);

  // Units

  std::vector<UnitInfo> units_info;
  units_info.push_back(UnitInfo(
      UnitGeneralInfo(1, 1, 4000, unit_type_t::infantry, "Fila (Miltiad)"),
      UnitDrawInfo({280, 601}, color_t(0), shape_t::rectangle, {220, 18}, 226, unit_state_t(1))));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(2, 1, 4000, unit_type_t::infantry, "Platea"),
               {{110, 427}, color_t(0), shape_t::rectangle, {110, 34}, 226, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(3, 1, 4000, unit_type_t::infantry, "Athens (Kallimah)"),
               {{461, 762}, color_t(0), shape_t::rectangle, {110, 34}, 226, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(4, 2, 100, unit_type_t::infantry, "1st infantry line"),
               {{537, 392}, color_t(0), shape_t::rectangle, {314, 12}, 44, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(5, 2, 100, unit_type_t::infantry, "2nd infantry line"),
               {{580, 374}, color_t(0), shape_t::rectangle, {362, 25}, 44, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(6, 2, 100, unit_type_t::infantry, "3rd infantry line"),
               {{615, 344}, color_t(0), shape_t::rectangle, {362, 25}, 44, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(7, 2, 500, unit_type_t::cavalry, "Right cavalry wing"),
               {{681, 534}, color_t(0), shape_t::rectangle, {66, 18}, 44, unit_state_t::alive}));
  units_info.push_back(
      UnitInfo(UnitGeneralInfo(8, 2, 500, unit_type_t::cavalry, "Left cavalry wing"),
               {{383, 239}, color_t(0), shape_t::rectangle, {66, 18}, 44, unit_state_t::alive}));

  boost::property_tree::ptree units_tree;
  for (const UnitInfo& ui : units_info) {
    boost::property_tree::ptree unit_node;

    auto general_info = ui.unit_general_info();
    auto draw_info = ui.unit_draw_info();
    unit_node.put("id", general_info.unit_id());
    unit_node.put("side", general_info.opponent_id());
    unit_node.put("name", general_info.name());
    unit_node.put("count", general_info.amount());
    unit_node.put("type", as_integer(general_info.unit_type()));
    unit_node.put("position_x", draw_info.position().x());
    unit_node.put("position_y", draw_info.position().y());
    unit_node.put("shape", static_cast<std::underlying_type_t<shape_t>>(draw_info.shape()));
    unit_node.put("size_x", draw_info.size().x());
    unit_node.put("size_y", draw_info.size().y());
    unit_node.put("angle", draw_info.angle());
    units_tree.push_back(std::make_pair("", unit_node));
  }
  battle_description_tree.add_child("units", units_tree);

  // Maneuvers

  std::vector<std::unique_ptr<Maneuver>> maneuvers;

  ManeuverFactory::get().register_maneuver(ManeuverType::move, &MoveManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::rotate, &RotateManeuver::create);
  ManeuverFactory::get().register_maneuver(ManeuverType::resize, &ResizeManeuver::create);
  maneuvers.push_back(std::move(ManeuverFactory::create(
      ManeuverType::move, 1, model_time_t(1), model_time_t(9), {"280", "601", "340", "548"})));
  maneuvers.push_back(ManeuverFactory::create(ManeuverType::rotate, 1, model_time_t(1),
                                              model_time_t(9), {"226", "224"}));
  maneuvers.push_back(ManeuverFactory::create(ManeuverType::resize, 1, model_time_t(1),
                                              model_time_t(9), {"220", "18", "235", "12"}));

  boost::property_tree::ptree menauvers_tree;
  for (const auto& maneuver : maneuvers) {
    boost::property_tree::ptree maneuver_node;

    maneuver_node.put("unit", maneuver->unit_id());
    maneuver_node.put("type",
                      static_cast<std::underlying_type_t<ManeuverType>>(maneuver->maneuver_type()));
    maneuver_node.put("start_time", maneuver->start_time().to_string());
    maneuver_node.put("stop_time", maneuver->stop_time().to_string());

    boost::property_tree::ptree maneuver_data;
    for (const auto& md : maneuver->data()) {
      boost::property_tree::ptree maneuver_item;
      maneuver_item.put("", md);
      maneuver_data.push_back(std::make_pair("", maneuver_item));
    }
    maneuver_node.push_back(std::make_pair("data", maneuver_data));
    menauvers_tree.push_back(std::make_pair("", maneuver_node));
  }
  battle_description_tree.add_child("maneuvers", menauvers_tree);

  boost::property_tree::write_json("Marathon.battle", battle_description_tree);
  return 0;
}

}  // namespace test_generator
