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

#include "ConsoleUnitsDrawer.h"
#include "Logger.h"

ConsoleUnitsDrawer *ConsoleUnitsDrawer::instance_{nullptr};

enum Location : GLuint { projection = 0, view, model, rotation };

ConsoleUnitsDrawer::ConsoleUnitsDrawer() {}

void ConsoleUnitsDrawer::draw_units(const std::vector<std::shared_ptr<Unit>> &units) {
  for (const auto &unit : units) {
    unit->print_info();
  }
}