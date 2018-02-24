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

#include "BattleDrawWindow.h"

#include <chrono>

#include "../bvl/DelayTimer.h"
#include "OpenGLUnitsDrawer.h"
#include "../../Logger.h"

ViewState view_state;
UnitAdjustInfo unit_adjust_info;

BattleDrawWindow::BattleDrawWindow(types::gui_res_t width, types::gui_res_t height, std::string&& title) :
    width_(width),
    height_(height),
    title_(title),
    texture_filename_("bm.bmp") {

  init_open_gl();
  createField(texture_filename_);
  view_state.zoom_number = 1. / std::max(battle_field_.texture_width(), battle_field_.texture_height());

  units_processor_.set_working_file("Marathon.battle");
  units_processor_.create_units();

  projection_ = glm::perspective(45.0f, (GLfloat)width_ / (GLfloat)height_, 0.1f, 100.0f);
  view_ = glm::translate(view_, glm::vec3(0, 0, -1.f));
}

BattleDrawWindow::~BattleDrawWindow() {
  glfwTerminate();
}

void BattleDrawWindow::update_size() {
  static int old_width {0}, old_height {0};
  int width, height;
  glfwGetFramebufferSize(glfw_window_, &width, &height);

  if (width != old_width || height != old_height) {

    assert(height);

    GLfloat ratio = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    old_height = height;
    old_width = width;

    Logger::debug("BattleWindow: New size: width: %d, height: %d, ratio: %f", width, height, ratio);

  }
}

void BattleDrawWindow::createField(const std::string& texture_filename) {
  battle_field_.create(texture_filename);
}

void BattleDrawWindow::draw() {
  glm::mat4 model;

  // Clear
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  update_size();

  model = glm::translate(model, glm::vec3(view_state.trans_x_number, view_state.trans_y_number, 0.f));
  model = glm::rotate(model, glm::radians(static_cast<float>(view_state.rotate_y_number)), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(static_cast<float>(view_state.rotate_x_number)), glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::scale(model, glm::vec3(view_state.zoom_number, view_state.zoom_number, 1.));
  model = glm::translate(model, glm::vec3(-1 * battle_field_.texture_width() / 2,
                                          -1 * battle_field_.texture_height() / 2,
                                          0.f));

  battle_field_.draw(projection_, view_, model);

  OpenGLUnitsDrawer::instance()->set_transitions(projection_, view_, model);
  OpenGLUnitsDrawer::instance()->prepare();
  units_processor_.maneuver();

  units_processor_.draw_units();
  if (unit_adjust_info.add_rotation) {
    units_processor_.rotate(unit_adjust_info.add_rotation);
    unit_adjust_info.add_rotation = 0;
  }
  if (unit_adjust_info.add_x || unit_adjust_info.add_y) {
    units_processor_.move(unit_adjust_info.add_x, unit_adjust_info.add_y);
    unit_adjust_info.add_x = 0;
    unit_adjust_info.add_y = 0;
  }
  if (unit_adjust_info.add_w_x || unit_adjust_info.add_w_y) {
    units_processor_.enlarge(unit_adjust_info.add_w_x, unit_adjust_info.add_w_y);
    unit_adjust_info.add_w_x = 0;
    unit_adjust_info.add_w_y = 0;
  }
  if (unit_adjust_info.to_print) {
    units_processor_.print_unit_info();
    unit_adjust_info.to_print = false;
  }
  if (unit_adjust_info.next_unit) {
    units_processor_.next_selected_unit();
    unit_adjust_info.next_unit = false;
  }
  if (unit_adjust_info.prev_unit) {
    units_processor_.prev_selected_unit();
    unit_adjust_info.prev_unit = false;
  }

}

void BattleDrawWindow::init_open_gl() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  glfw_window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (glfw_window_ == nullptr) {
    Logger::error("GLFW: Failed to create GLFW window");
    glfwTerminate();
  }
  else {
    Logger::info("GLFW: GLFW successfully initialized");
  }
  glfwMakeContextCurrent(glfw_window_);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::error("GLAD: Failed to initialize GLAD");
  } 
  else {
    Logger::info("GLAD: GLAD successfully initialized");
  }

  int width, height;
  glfwGetFramebufferSize(glfw_window_, &width, &height);

  glViewport(0, 0, width / 2, height);
  glEnable(GL_DEPTH_TEST);

  glfwSetKeyCallback(glfw_window_, key_callback);
  glfwSetScrollCallback(glfw_window_, scroll_callback);
  glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
  glfwSetCursorPosCallback(glfw_window_, cursor_position_callback);
}

int BattleDrawWindow::run() {
  static uint32_t fps {0};
  static DelayTimer<uint16_t> fps_counter(1000);
  static DelayTimer<uint16_t> frame_update_counter(10);
  
  while (!glfwWindowShouldClose(glfw_window_)) {
    if (!to_refresh_) continue;
    if (!frame_update_counter.elapsed()) continue;

    if (fps_counter.elapsed()) {
      Logger::trace("FPS: %d", fps);
      fps = 0;
    }
    ++fps;

    glfwPollEvents();

    draw();

    glfwSwapBuffers(glfw_window_);


    // m_to_refresh = false;
  }
  
  return 0;
}

void key_callback(GLFWwindow *window, int key, int /*scancode*/, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_J && action == GLFW_PRESS) {
    unit_adjust_info.add_rotation += 1;
  }
  if (key == GLFW_KEY_K && action == GLFW_PRESS) {
    unit_adjust_info.add_rotation -= 1;
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    unit_adjust_info.add_x -= (mode & GLFW_MOD_SHIFT) ? 10 : 1;
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    unit_adjust_info.add_x += (mode & GLFW_MOD_SHIFT) ? 10 : 1;
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    unit_adjust_info.add_y += (mode & GLFW_MOD_SHIFT) ? 10 : 1;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    unit_adjust_info.add_y -= (mode & GLFW_MOD_SHIFT) ? 10 : 1;
  }
  if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    unit_adjust_info.add_w_x += 1;
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    unit_adjust_info.add_w_x -= 1;
  }
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    unit_adjust_info.add_w_y += 1;
  }
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    unit_adjust_info.add_w_y -= 1;
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    unit_adjust_info.to_print = true;
  }

  if (key == GLFW_KEY_N && action == GLFW_PRESS) {
    unit_adjust_info.next_unit = true;
  }
  if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    unit_adjust_info.prev_unit = true;
  }
}

void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
  view_state.zoom_number *= (1. + yoffset / 10);
}

void mouse_button_callback(GLFWwindow* /*window*/, int button, int action, int /*mods*/) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      view_state.drag_started = true;
      view_state.drag_start_x = -1;
      view_state.drag_start_y = -1;
    }
    else {
      view_state.drag_started = false;
      view_state.init_trans_x = view_state.trans_x_number;
      view_state.init_trans_y = view_state.trans_y_number;
    }
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    if (action == GLFW_PRESS) {
      view_state.rotate_started = true;
      view_state.rotate_start_x = 0;
      view_state.rotate_start_y = 0;
    }
    else {
      view_state.rotate_started = false;
      view_state.init_rotate_x = view_state.rotate_x_number;
      view_state.init_rotate_y = view_state.rotate_y_number;
    }
  }
}

void cursor_position_callback(GLFWwindow* /*window*/, double xpos, double ypos) {
  if (view_state.drag_started) {
    if (view_state.drag_start_x < 0) {
      view_state.drag_start_x = xpos;
      view_state.drag_start_y = ypos;
    }
    else {
      view_state.trans_x_number = (xpos - view_state.drag_start_x) / Settings::main_window_width + view_state.init_trans_x;
      view_state.trans_y_number = (view_state.drag_start_y - ypos) / Settings::main_window_height + view_state.init_trans_y;
    }
  }
  if (view_state.rotate_started) {
    if (view_state.rotate_start_x == 0) {
      view_state.rotate_start_x = xpos;
      view_state.rotate_start_y = ypos;
    }
    else {
      view_state.rotate_x_number = 100. * (xpos - view_state.rotate_start_x) / Settings::main_window_width + view_state.init_rotate_x;
      view_state.rotate_y_number = 100. * (ypos - view_state.rotate_start_y) / Settings::main_window_height + view_state.init_rotate_y;
    }
  }
}
