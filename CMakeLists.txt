cmake_minimum_required(VERSION 3.14)
project(nwOptixTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(nwOptixTest main.cpp Counter.cpp ServerHandler.cpp)

find_package(Boost REQUIRED COMPONENTS system program_options)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(nwOptixTest ${Boost_LIBRARIES})