cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE release)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_VERSION 11)


if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
  	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
  if(CMAKE_BUILD_TYPE eq debug)
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  elseif(CMAKE_BUILD_TYPE eq release)
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
)

file(GLOB SRC
	src/main.cc
	src/win.cc
	src/arko.cc
	src/ark.cc
	src/eventh.cc
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
