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

#ifndef BATTLEDRAWWINDOW_H_
#define BATTLEDRAWWINDOW_H_

#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../bvl/BVGUITypes.h"
#include "../bvl/WindowSettings.h"

#include "../core/DrawStrategy.h"
#include "../core/UnitsProcessor.h"

#include "BattleField.h"

using namespace bvl::gui;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

struct ViewState {
  double zoom_number {1};
  double trans_y_number {0};
  double trans_x_number {0};
  double rotate_y_number {0};
  double rotate_x_number {0};

  bool drag_started {false};
  double drag_start_x {0};
  double drag_start_y {0};
  double init_trans_x {0};
  double init_trans_y {0};

  bool rotate_started {false};
  double rotate_start_x {0};
  double rotate_start_y {0};
  double init_rotate_x {rotate_x_number};
  double init_rotate_y {rotate_y_number};
};

struct UnitAdjustInfo {
  bvl::core::types::angle_t add_rotation {0};
  uint16_t add_x {0};
  uint16_t add_y {0};
  uint16_t add_w_x {0};
  uint16_t add_w_y {0};
  bool to_print {false};
  bool next_unit {false};
  bool prev_unit {false};
};

class BattleDrawWindow {
public:
  BattleDrawWindow(types::gui_res_t width, types::gui_res_t height, std::string&& title = "");

  virtual ~BattleDrawWindow();

  void init_open_gl();

  int run();

  void createField(const std::string& texture_filename);

  void update_size();

  void draw();

private:
  static constexpr float gl_field_size {1000.f};
  GLFWwindow* glfw_window_ {nullptr};
  BattleField battle_field_;

  types::gui_res_t width_;
  types::gui_res_t height_;
  std::string title_;
  bool to_refresh_ {true};

  UnitsProcessor units_processor_;

  std::string texture_filename_;

  glm::mat4 projection_;
  glm::mat4 view_;
};

#endif /* BATTLEDRAWWINDOW_H_ */
