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

#ifndef BATTLEVISION_CONSOLEUNITSDRAWER_H
#define BATTLEVISION_CONSOLEUNITSDRAWER_H

#include <vector>

#include "bvl/BVTypes.h"
#include "core/Unit.h"

class ConsoleUnitsDrawer {
 public:
  static ConsoleUnitsDrawer* instance() {
    if (!instance_) {
      instance_ = new ConsoleUnitsDrawer;
    }
    return instance_;
  }

  ~ConsoleUnitsDrawer() {
    if (instance_) delete instance_;
  };

  void draw_units(const std::vector<Unit>& units);

 private:
  ConsoleUnitsDrawer();

  static ConsoleUnitsDrawer* instance_;
};

#endif  // BATTLEVISION_CONSOLEUNITSDRAWER_H