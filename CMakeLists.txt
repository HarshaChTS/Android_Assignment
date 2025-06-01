cmake_minimum_required(VERSION 3.10)
project(CS312-Particles)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
  find_package(OpenGL REQUIRED)
  find_library(GLEW NAMES glew32s PATHS external/lib/x64)
  find_library(GLFW NAMES glfw3 PATHS external/lib)

  set(INCLUDE_DIRS external/include)
  set(LIBRARY_DIRS lib external/lib)

  set(CMAKE_CXX_FLAGS 
      "/wd4018 /wd4244 /wd4305 
      /D_CRT_SECURE_NO_WARNINGS 
      /D_CRT_NONSTDC_NO_DEPRECATE 
      /D NOMINMAX /DGLEW_STATIC /EHsc")

  set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:\"MSVCRT\" /NODEFAULTLIB:\"LIBCMT\"")
  set(CORE ${GLEW} ${GLFW} opengl32.lib)

elseif (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -Wno-reorder-ctor -Wno-unused-variable -g -stdlib=libc++ -std=c++14")
  
  find_library(GL_LIB OpenGL)
  find_library(GLFW glfw)

  set(INCLUDE_DIRS /System/Library/Frameworks external/include /usr/local/include)
  set(CORE ${GLFW} ${GL_LIB})
  add_definitions(-DAPPLE)

elseif (UNIX)
  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11 -Wno-comment")

  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  find_library(GLFW glfw)

  set(INCLUDE_DIRS external/include)
  set(LIBRARY_DIRS external/lib /usr/X11R6/lib /usr/local/lib lib)

  set(CORE ${GLEW_LIBRARIES} ${GLFW} ${OPENGL_LIBRARIES} GL GLU X11)
  add_definitions(-DUNIX)
endif()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})

set(RENDER_SOURCES 
    src/AGL.h
    src/AGLM.h
    src/AGLM.cpp
    src/image.h
    src/image.cpp
    src/renderer.h
    src/renderer.cpp
)

set(PSYS_SOURCES 
    src/myparticlesystem.h
    src/myparticlesystem.cpp
    src/particlesystem.h
    src/particlesystem.cpp
)

set(SHADERS
    shaders/billboard.fs
    shaders/billboard.vs
)

add_executable(demo src/main-demo.cpp ${PSYS_SOURCES} ${RENDER_SOURCES} ${SHADERS})
target_link_libraries(demo ${CORE})
