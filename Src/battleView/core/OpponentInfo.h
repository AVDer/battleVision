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

#ifndef CORE_OPPONENTINFO_H_
#define CORE_OPPONENTINFO_H_

#include <string>

#include "bvl/BVTypes.h"

class OpponentInfo {
 public:
  OpponentInfo() = default;

  OpponentInfo(std::string&& name, bvl::core::types::color_t color) : name_(name), color_(color) {}

  std::string name() const { return name_; }

  bvl::core::types::color_t color() const { return color_; }

 private:
  std::string name_;
  bvl::core::types::color_t color_;
};

#endif /* CORE_OPPONENTINFO_H_ */
