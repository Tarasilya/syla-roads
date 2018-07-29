cmake_minimum_required(VERSION 3.11.2)
project(syla-roads)

if (APPLE)
	set(LINKER_FLAGS "-framework sfml-system -framework sfml-window -framework sfml-graphics")
else()
	set(LINKER_FLAGS "-lsfml-window -lsfml-graphics -lsfml-system")
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}" )
  
file(GLOB SOURCES "*.cpp")
 
add_executable(syla ${SOURCES})