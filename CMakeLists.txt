
# You are free to modify this file

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
project(game)
find_package(X11 REQUIRED)
set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
file(GLOB SRC src/*/*.cpp src/*.cpp)
add_executable(game ${SRC})
target_link_libraries(game m X11)
