cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE release)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_VERSION 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${SET_CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")

project(cgol)

file(GLOB HEAD
	head/config.hh
	head/cell.hh
	head/argh.hh
)

file(GLOB SRC
	src/simulation.cc
	src/cell.cc
	src/argh.cc
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
