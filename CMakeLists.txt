cmake_minimum_required(VERSION 3.5)

project(imagescaler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options filesystem)
include_directories(${Boost_INCLUDE_DIR})

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})

add_executable(imagescaler imagescaler.cpp)
target_link_libraries(imagescaler LINK_PUBLIC ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES})
