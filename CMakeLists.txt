cmake_minimum_required(VERSION 3.14)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled3 main.cpp Counter.cpp ServerHandler.cpp)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS system program_options)

include_directories(${Boost_INCLUDE_DIR})
# Note: a target should be already defined using 'add_executable' or 'add_library'
target_link_libraries(untitled3 ${Boost_LIBRARIES})