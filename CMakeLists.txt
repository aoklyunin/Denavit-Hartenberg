cmake_minimum_required(VERSION 3.9)
PROJECT(Denavit-Hartenberg-visualization)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


#FIND_PACKAGE(GL REQUIRED)

#add_executable(dh_vis windows_old/main_windows.cpp src/ClaseOpenGL.cpp src/Matrix.cpp src/modelo3D.cpp src/Robot.cpp src/vector3d.cpp src/Triangle3D.cpp )


add_executable(dh_vis src/main.cpp src/ClaseOpenGL.cpp src/Matrix.cpp src/modelo3D.cpp src/Robot.cpp src/vector3d.cpp src/Triangle3D.cpp include/ClaseOpenGL.h include/vector3d.h include/modelo3D.h include/Triangle3D.h include/Robot.h include/Matrix.h)

target_link_libraries(dh_vis ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})