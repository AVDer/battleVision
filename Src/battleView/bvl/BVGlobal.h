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

#ifndef BVL_BVGLOBAL_H_
#define BVL_BVGLOBAL_H_

#include <cstdint>

#include "BVGUITypes.h"
#include "BVTypes.h"

struct Settings {
  static const bool show_fps{false};
  static const uint16_t debug_level = 7;

  static const bvl::gui::types::gui_res_t main_window_width = 1000;
  static const bvl::gui::types::gui_res_t main_window_height = 600;
};

enum class gui_lib : uint8_t { opengl };

#endif /* BVL_BVGLOBAL_H_ */
