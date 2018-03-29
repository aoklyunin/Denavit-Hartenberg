cmake_minimum_required(VERSION 3.9)
PROJECT(Denavit-Hartenberg-visualization CXX)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -ljsoncpp")
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

# jsoncpp
#
FIND_PACKAGE(jsoncpp REQUIRED)
# TODO: fix, add FindJsoncpp.cmake
INCLUDE_DIRECTORIES("/usr/include/jsoncpp")
SET(JSONCPP_LIBRARIES jsoncpp)

#FIND_PACKAGE(GL REQUIRED)


add_executable(dh_vis src/main.cpp src/modelo3D.cpp src/robot.cpp src/triangles.cpp include/modelo3D.h include/triangles.h include/robot.h src/camera.cpp include/camera.h include/traces.h src/traces.cpp include/formatting.h include/userTime.h src/openGL_wrapper.cpp include/openGL_wrapper.h include/json.h include/throws.h include/files.h)

TARGET_LINK_LIBRARIES(dh_vis ${CMAKE_THREAD_LIBS_INIT} ${JSONCPP_LIBRARIES})


target_link_libraries(dh_vis ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})