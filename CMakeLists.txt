cmake_minimum_required(VERSION 3.17)
project(battleVision LANGUAGES C CXX)

include("environment.inc")

message(STATUS "Using CMake: ${CMAKE_VERSION}")
message(STATUS "Found C compiler is: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "Found C++ compiler is: ${CMAKE_CXX_COMPILER_VERSION}")

# ---------- 3rd party libraries setup ----------

message(STATUS ${BOOST_ROOT})
set(GLFW_LIBRARIES glfw3)

# ---------- Required packages ----------

find_package(Boost 1.55.0 REQUIRED COMPONENTS date_time)
find_package(OpenGL REQUIRED)

# ---------- Include directories ----------

include_directories(Src)
include_directories(Src/battleView)
include_directories(Src/battleView/gui/glad/include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

# ---------- Source files ----------

set(SOURCE_FILES
    Src/battleView/bvl/BVGlobal.h
    Src/battleView/bvl/BVGUITypes.h
    Src/battleView/bvl/BVTypes.h
    Src/battleView/bvl/Color.h
    Src/battleView/bvl/Point.h
    Src/battleView/bvl/WindowSettings.h
    Src/battleView/core/DrawStrategy.cpp
    Src/battleView/core/DrawStrategy.h
    Src/battleView/gui/InfantryOpenGLDraw.h
    Src/battleView/core/IDrawer.h
    Src/battleView/core/OpponentInfo.h
    Src/battleView/core/Unit.cpp
    Src/battleView/core/Unit.h
    Src/battleView/core/UnitFactory.cpp
    Src/battleView/core/UnitFactory.h
    Src/battleView/core/UnitInfo.cpp
    Src/battleView/core/UnitInfo.h
    Src/battleView/core/UnitsProcessor.cpp
    Src/battleView/core/UnitsProcessor.h
    Src/battleView/editor/test_generator.cpp
    Src/battleView/editor/test_generator.h
    Src/battleView/gui/BattleDrawWindow.cpp
    Src/battleView/gui/BattleDrawWindow.h
    Src/battleView/gui/MainWindow.cpp
    Src/battleView/gui/MainWindow.h
    Src/battleView/gui/SettingsWindow.cpp
    Src/battleView/gui/SettingsWindow.h
    Src/battleView/main.cpp
    Src/battleView/gui/CavalryOpenGLDraw.h
    Src/battleView/gui/ShadersField.h
    Src/battleView/gui/BattleField.cpp
    Src/battleView/gui/BattleField.h
    Src/battleView/gui/ShaderProgram.cpp
    Src/battleView/gui/ShaderProgram.h
    Src/battleView/gui/OpenGLTexture.h
    Src/battleView/bvl/DelayTimer.h
    Src/battleView/gui/ShadersUnit.h
    Src/battleView/gui/OpenGLUnitsDrawer.cpp
    Src/battleView/gui/OpenGLUnitsDrawer.h
    Src/battleView/gui/OpenGLUnit.cpp
    Src/battleView/gui/OpenGLUnit.h
    Src/battleView/gui/ConsoleUnitsDrawer.cpp
    Src/battleView/gui/RenderInfo.h
    Src/battleView/gui/OpenGLDrawStrategy.h
    Src/battleView/gui/glad/src/glad.c
    Src/battleView/core/Maneuver.cpp
    Src/battleView/core/Maneuver.h
    Src/battleView/core/MoveManeuver.h
    Src/battleView/core/RotateManeuver.h
    Src/battleView/core/ManeuverFactory.cpp
    Src/battleView/core/ManeuverFactory.h
    Src/battleView/core/ResizeManeuver.h
    Src/Logger.h
    Src/Logger.cpp
    Src/FileTGA.h
        )

# ---------- Link directories ----------

link_directories(${ZLIB_LIBRARY_PATH})
link_directories(${GLFW_LIBRARY_PATH})
link_directories(${Boost_LIBRARY_DIRS})

# ---------- Program executable ----------

add_executable(battleVision ${SOURCE_FILES})

# ---------- Compile options ----------

set(CMAKE_VERBOSE_MAKEFILE ON)
target_compile_options(battleVision PUBLIC -Wall -Wextra)
set_target_properties(battleVision PROPERTIES CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

# ---------- Additional libraries ----------

if(MINGW)
    set(ADDITIONAL_LIBRARIES z)
else(MINGW)
    find_library(M_LIB m)
    set(ADDITIONAL_LIBRARIES dl)
endif(MINGW)

set(GRAPHICAL_LIBRARIES)

set(WM_FOUND OFF)
find_package(X11)
if (X11_FOUND)
    set(WINDOW_MANAGER_LIBRARIES X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread)
    set(WM_FOUND ON)
    message(STATUS "X11 will be used as a window system")
endif (X11_FOUND)
if (MINGW)
    set(WM_FOUND ON)
    message(STATUS "Windows will be used as a window system")
endif (MINGW)


if (NOT WM_FOUND)
    message(FATAL_ERROR "No window manager found")
endif ()

# ---------- Libraries linking ----------

target_link_libraries(battleVision ${GRAPHICAL_LIBRARIES})
target_link_libraries(battleVision ${PLATFORM_DEPENDENT_LIBS})
target_link_libraries(battleVision ${Boost_LIBRARIES})

target_link_libraries(battleVision ${GLFW_LIBRARIES})
target_link_libraries(battleVision ${OPENGL_gl_LIBRARY})

target_link_libraries(battleVision ${ADDITIONAL_LIBRARIES})
target_link_libraries(battleVision ${WINDOW_MANAGER_LIBRARIES})
