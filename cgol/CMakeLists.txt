cmake_minimum_required(VERSION 3.5.2)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_VERSION 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

project(cgol)

file(GLOB HEAD
	head/config.hh
	head/cell.hh
)

file(GLOB SRC
	src/simulation.cc
	src/cell.cc
)

include_directories(
		./head/
)

add_executable(
		cgol
		${SRC}
		${HEAD}
)

target_link_libraries(
	cgol
	SDL2main
	SDL2
)
