cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE release)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_VERSION 17)

# No need to set optimization levels as cmake will set the automatically depending
# on build type.

project(cgol)

include_directories(
  ./head/
  
)

add_executable(
  cgol

  src/main.cpp
  src/back.cpp

  head/back.hpp
  head/config.hpp
)

target_link_libraries(
	cgol
	SDL2main
	SDL2
)
