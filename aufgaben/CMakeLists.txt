cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(CPPDatenanalyse)

find_package(Catch2 REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include(CTest)
include(Catch)

# Playground
add_executable(playground playground.cc)

# Week 1
add_library(libweek1 week1/libweek1.cc)
add_executable(week1 week1/week1.cc)
target_link_libraries(week1 libweek1)
target_compile_options(week1 PRIVATE -Wall -Wextra -pedantic -Werror)

# Week 2
add_library(libweek2 week2/libweek2.cc)

add_executable(week2tests week2/week2tests.cc)
catch_discover_tests(week2tests)
target_link_libraries(week2tests libweek2)
target_link_libraries(week2tests Catch2::Catch2)

# Week 3
add_library(libweek3 week3/libweek3.cc)
target_include_directories(libweek3 PUBLIC include)

add_executable(week3tests week3/week3tests.cc)
catch_discover_tests(week3tests)
target_include_directories(week3tests PUBLIC include)
target_link_libraries(week3tests libweek3)
target_link_libraries(week3tests Catch2::Catch2)
