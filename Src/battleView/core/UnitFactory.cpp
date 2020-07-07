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

#include "UnitFactory.h"

#include "gui/CavalryOpenGLDraw.h"
#include "gui/InfantryOpenGLDraw.h"

std::shared_ptr<Unit> UnitFactory::get_unit(UnitInfo &&ui) {
  std::shared_ptr<Unit> unit = std::make_shared<OpenGLUnit>();
  unit->set_unit_info(ui);
  switch (ui.unit_general_info().unit_type()) {
    case unit_type_t::infantry:
      unit->set_draw_strategy(std::make_shared<InfantryOpenGLDraw>(InfantryOpenGLDraw()));
      break;
    case unit_type_t::cavalry:
      unit->set_draw_strategy(std::make_shared<CavalryOpenGLDraw>(CavalryOpenGLDraw()));
      break;
    default:
      break;
  }
  unit->prepare();
  return unit;
}
