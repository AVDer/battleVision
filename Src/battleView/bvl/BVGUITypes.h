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

#ifndef BVGUITYPES_H_
#define BVGUITYPES_H_

#include <cstdint>

namespace bvl::gui::types {

using gui_res_t = uint16_t;

}

namespace bvl::gui {

template <class T>
types::gui_res_t toGuiRes(T t) {
  return static_cast<types::gui_res_t>(t);
}

}

#endif /* BVGUITYPES_H_ */
