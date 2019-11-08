cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE release)
	message("Building for release")
	
else()
  message("Building for debug")
	
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_STANDARD 17)

# No need to set optimization levels as cmake will set the automatically depending
# on build type.

project(snake)

include_directories(
  ./head/  
)

add_executable(
  snake

  src/main.cpp
)

target_link_libraries(
	snake
	SDL2main
	SDL2

    SDL2_gpu
)
