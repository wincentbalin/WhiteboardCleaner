cmake_minimum_required(VERSION 3.5)

project(imagescaler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options filesystem)
include_directories(${Boost_INCLUDE_DIR})

add_executable(imagescaler imagescaler.cpp)
target_link_libraries(imagescaler LINK_PUBLIC ${Boost_LIBRARIES} )
