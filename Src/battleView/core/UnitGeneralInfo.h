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

#ifndef CORE_UNITGENERALINFO_H_
#define CORE_UNITGENERALINFO_H_

#include <string>

#include "bvl/BVTypes.h"

using namespace bvl::core::types;

class UnitGeneralInfo {
 public:
  UnitGeneralInfo() = default;

  UnitGeneralInfo(uint32_t u_id, uint32_t o_id, uint32_t a, unit_type_t u_t, std::string&& n)
      : unit_id_(u_id), opponent_id_(o_id), amount_(a), unit_type_(u_t), name_(n) {}

  UnitGeneralInfo& set_id(uint32_t id) {
    unit_id_ = id;
    return *this;
  }

  UnitGeneralInfo& set_opponent_id(uint32_t id) {
    opponent_id_ = id;
    return *this;
  }

  UnitGeneralInfo& set_amount(uint32_t amount) {
    amount_ = amount;
    return *this;
  }

  UnitGeneralInfo& set_type(unit_type_t unit_type) {
    unit_type_ = unit_type;
    return *this;
  }

  UnitGeneralInfo& set_name(const std::string& name) {
    name_ = name;
    return *this;
  }

  UnitGeneralInfo& set_side_name(const std::string& name) {
    side_name_ = name;
    return *this;
  }

  uint32_t unit_id() const { return unit_id_; }
  uint32_t opponent_id() const { return opponent_id_; }
  uint32_t amount() const { return amount_; }
  unit_type_t unit_type() const { return unit_type_; }
  const std::string& name() const { return name_; }
  const std::string& side_name() const { return side_name_; }

 private:
  uint32_t unit_id_{0};
  uint32_t opponent_id_{0};
  uint32_t amount_{0};
  unit_type_t unit_type_;
  std::string name_;
  std::string side_name_;
};

#endif
