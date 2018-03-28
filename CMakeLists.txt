cmake_minimum_required(VERSION 3.9)
PROJECT(Denavit-Hartenberg-visualization)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

#
# rhreads
#
FIND_PACKAGE(Threads REQUIRED)

#
# eigen
#
FIND_PACKAGE(Eigen3 REQUIRED Core)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIRS})

#FIND_PACKAGE(GL REQUIRED)

add_executable(dh_vis src/main.cpp src/modelo3D.cpp src/Robot.cpp src/Triangle3D.cpp  include/modelo3D.h include/Triangle3D.h include/Robot.h src/Camera.cpp include/Camera.h include/traces.h src/traces.cpp include/formatting.h include/userTime.h include/userMath.h src/OpenGLWrapper.cpp include/OpenGLWrapper.h)

target_link_libraries(dh_vis ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})