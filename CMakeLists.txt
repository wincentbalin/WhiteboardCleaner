cmake_minimum_required(VERSION 3.5)

project(whiteboardcleaner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options filesystem)
include_directories(${Boost_INCLUDE_DIR})

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=1 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})

add_executable(whiteboardcleaner whiteboardcleaner.cpp)
target_link_libraries(whiteboardcleaner LINK_PUBLIC ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES})
