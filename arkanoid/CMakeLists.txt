cmake_minimum_required(VERSION 3.5.2)

if(NOT CMAKE_BUILD_TYPE)
	message("Building for release")
	set(CMAKE_BUILD_TYPE RELEASE)
	
else()
	message("Building for debug")	
  endif()
  
# TODO make this compiler independent.

# have to force -std=c++17 because cmake won't input it for some reason.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -std=c++17")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g3 -O0 -Wno-unknown-params -Wno-format")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")


project(ark)

include_directories(
  ./head/
  )

link_directories(
  )

add_executable(
  ark
  
  src/main.cpp

  head/paddle.hpp
  )

# Windows configuration
if(WIN32)

  message("Setting up for windows")
  # TODO test

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")

  target_link_libraries(
    ark

    mapgame
    )

# Linux (X11) Configuration
  elseif(UNIX)

	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/lib64/")

target_link_libraries(
  ark
  SDL2main
  SDL2
  )

else()
  
  message(FATAL_ERROR "This platform is not supported.")

endif()
