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

#include <memory>

#include "editor/test_generator.h"
#include "gui/BattleDrawWindow.h"

int main(int /*argc*/, char** /*argv*/) {
  test_generator::generate_battle_file();
  std::unique_ptr<BattleDrawWindow> main_window{new BattleDrawWindow(
      Settings::kMainWindowWidth, Settings::kMainWindowHeight, "BattleVision 1.1.0.0")};

  return main_window->run();
}
