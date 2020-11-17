cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(CPPDatenanalyse)

find_package(Catch2 REQUIRED)

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
