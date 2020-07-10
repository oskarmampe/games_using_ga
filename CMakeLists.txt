cmake_minimum_required(VERSION 3.16.0-rc1)

project("evo_games")

#include_directory("${CMAKE_CURRENT_SOURCE_DIR}")
#file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
#add_executable("${PROJECT_NAME}"  ${SRC_FILES})
add_executable("${PROJECT_NAME}" "evolutionary_games.cpp" "lattice.h" "lattice.cpp")

#install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
#install(FILES "evolutionary_games.cpp" DESTINATION src)