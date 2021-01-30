cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(Traffic LANGUAGES CXX CUDA)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# traffic
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_packages/")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

set(CMAKE_BUILD_TYPE Debug)

set(TRAFFIC_SOURCES
        src/road.cc
        src/car.cu
        src/traffic.cc
        src/SDL_Manager.cc
)
add_executable(traffic ${TRAFFIC_SOURCES})
target_link_libraries(traffic PRIVATE
    Eigen3::Eigen ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
target_include_directories(traffic PRIVATE
    ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_include_directories(traffic PUBLIC include)

target_compile_options(traffic PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-G>)

