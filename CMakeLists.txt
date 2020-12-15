cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(CPPDatenanalyse)

find_package(Catch2 REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include(CTest)
include(Catch)

# Playground
add_executable(playground src/playground.cc)

# Week 1
add_library(libweek1 src/libweek1.cc)
target_include_directories(libweek1 PUBLIC include)
add_executable(week1 src/week1.cc)
target_link_libraries(week1 libweek1)
target_include_directories(week1 PRIVATE include)
target_compile_options(week1 PRIVATE -Wall -Wextra -pedantic -Werror)

# Week 2
add_library(libweek2 src/libweek2.cc)
target_include_directories(libweek2 PUBLIC include)

add_executable(week2tests src/week2tests.cc)
catch_discover_tests(week2tests)
target_include_directories(week2tests PUBLIC include)
target_link_libraries(week2tests libweek2)
target_link_libraries(week2tests Catch2::Catch2)

# Week 3
add_library(libweek3 src/libweek3.cc)
target_include_directories(libweek3 PUBLIC include)

add_executable(week3tests src/week3tests.cc)
catch_discover_tests(week3tests)
target_include_directories(week3tests PUBLIC include)
target_link_libraries(week3tests libweek3)
target_link_libraries(week3tests Catch2::Catch2)

# traffic
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_packages/")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

set(CMAKE_BUILD_TYPE Debug)

set(TRAFFIC_SOURCES
        src/traffic/traffic.cc
        src/traffic/car.cc
        src/traffic/road.cc
        src/traffic/pool.cc
        src/traffic/intersection.cc
)
add_executable(traffic ${TRAFFIC_SOURCES})
target_link_libraries(traffic PRIVATE
    Eigen3::Eigen ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
target_include_directories(traffic PRIVATE
    ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_include_directories(traffic PUBLIC include)

