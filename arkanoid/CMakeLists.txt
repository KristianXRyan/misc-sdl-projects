cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_VERSION 11)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
  	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
else()
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
  if(CMAKE_BUILD_TYPE MATCHES Debug)
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
  endif()
endif()

project(arkanoid)

file(GLOB HEAD
	head/config.hh
	head/win.hh
	head/arko.hh
	head/ark.hh
	head/eventh.hh
	head/state/state.hh
	head/state/statem.hh
	head/state/gstate.hh
	head/state/mstate.hh
	head/garko.hh
	head/marko.hh
)

file(GLOB SRC
	src/main.cc
	src/win.cc
	src/arko.cc
	src/ark.cc
	src/eventh.cc
	src/state/state.cc
	src/state/statem.cc
	src/state/gstate.cc
	src/state/mstate.cc
	src/garko.cc
	src/marko.cc
)

include_directories(
	./head/
)

add_executable(
	arkanoid
	${SRC}
	${HEAD}
)

target_link_libraries(
	arkanoid
	SDL2main
	SDL2
	SDL2_ttf
	SDL2_image
)
