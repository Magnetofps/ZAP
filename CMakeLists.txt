cmake_minimum_required(VERSION 3.9)

project(zap VERSION 1.1)

#No Warnings
add_definitions(-w)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Add the source files for ImGui
add_library(imgui STATIC
  imgui/imgui.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_impl_opengl3.cpp
  imgui/imgui_impl_glfw.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_freetype.cpp
        Overlay/IconsFontAwesome5.h
)

# Set the include directories for ImGui
target_include_directories(imgui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Find packages
find_package (X11 REQUIRED)
find_package (Freetype REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIRS})

# Add additional libs
link_directories(/usr/local/lib)

# Add the executable target
add_executable(zap main.cpp)

# Link the executable against the ImGui library, GLFW/OpenGL libraries and X11 libraries
target_link_libraries(zap
  imgui
  glfw3
  GL
  X11
  Xinerama
  Xi
  udev
  ${X11_LIBRARIES}
  ${X11_XTest_LIB}
  ${FREETYPE_LIBRARIES}
)

# Set the include directories for the executable
target_include_directories(zap PUBLIC
  /usr/local/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Utils
  ${CMAKE_CURRENT_SOURCE_DIR}/Core
  ${CMAKE_CURRENT_SOURCE_DIR}/Math
  ${CMAKE_CURRENT_SOURCE_DIR}/Features
  ${CMAKE_CURRENT_SOURCE_DIR}/Overlay
)

# Create a folder for Configs
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Configs)

# Copy run.sh to build folder
file(COPY ${CMAKE_SOURCE_DIR}/run.sh DESTINATION ${CMAKE_BINARY_DIR})
