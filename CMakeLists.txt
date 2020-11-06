cmake_minimum_required(VERSION 3.10)

project(woche1)

add_library(libweek1 SHARED src/libweek1.cc)
target_include_directories(libweek1 PRIVATE include)

set(SOURCE_FILES src/week1.cc)
add_executable(week1 ${SOURCE_FILES})
target_link_libraries(week1 libweek1)
target_include_directories(week1 PRIVATE include)
