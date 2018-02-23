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

#ifndef WINDOWSETTINGS_H_
#define WINDOWSETTINGS_H_

#include <cstdint>

namespace bvl {
  namespace gui {

    struct Gap {
      static const uint16_t small = 5;
      static const uint16_t normal = 10;

      static const uint16_t double_small = small * 2;
      static const uint16_t double_normal = normal * 2;
    };

  }
}


#endif /* WINDOWSETTINGS_H_ */
