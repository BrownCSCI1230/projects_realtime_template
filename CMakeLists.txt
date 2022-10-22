cmake_minimum_required(VERSION 3.16)
# Sets project name
project(projects_realtime LANGUAGES CXX C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Sets C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specifies required Qt components
find_package(Qt6 COMPONENTS Core          REQUIRED)
find_package(Qt6 COMPONENTS Gui           REQUIRED)
find_package(Qt6 COMPONENTS OpenGL        REQUIRED)
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Gui           REQUIRED)
find_package(Qt6 COMPONENTS Xml           REQUIRED)

# Specifies .cpp and .h files to be passed to the compiler
add_executable(${PROJECT_NAME}
main.cpp 
realtime.h realtime.cpp
mainwindow.h mainwindow.cpp 
settings.cpp


utils/SceneData.h
utils/ScenefileReader.h utils/ScenefileReader.cpp
utils/SceneParser.h utils/SceneParser.cpp
utils/shaderloader.h
settings.h

Resources/Shaders/default.frag
Resources/Shaders/default.vert
)

# GLEW: this creates its library and allows you to `#include "GL/glew.h"`
add_library(StaticGLEW STATIC glew/src/glew.c)
include_directories(${PROJECT_NAME} PRIVATE glew/include)
add_subdirectory(glm)

# Specifies libraries to be linked (Qt components, glew, etc)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt::Core
  Qt::Gui
  Qt::OpenGL
  Qt::OpenGLWidgets
  Qt::Gui
  Qt::Xml
  StaticGLEW
  glm
)

# GLEW: this provides support for Windows (including 64-bit)
if (WIN32)
  add_compile_definitions(GLEW_STATIC)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    glu32
  )
endif()

# Set this flag to silence warnings on Windows
if (MSVC OR MSYS OR MINGW)
  set(CMAKE_CXX_FLAGS "-Wno-volatile")
endif()
# Set this flag to silence warnings on MacOS
if (APPLE)
  set(CMAKE_CXX_FLAGS "-Wno-deprecated-volatile")
endif()
