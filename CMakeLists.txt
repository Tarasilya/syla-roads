cmake_minimum_required(VERSION 3.10)
project(syla-roads)

if (APPLE)
set(LINKER_FLAGS "-framework sfml-system -framework sfml-window -framework sfml-graphics -framework sfml-network")
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

file(GLOB SOURCES src/game/*.cpp src/painter/*.cpp src/utils/*.cpp src/client/*.cpp)
file(GLOB SERVER "src/network/*.cpp")

add_executable(syla ${SOURCES}) 
add_executable(ser ${SERVER}) 

target_include_directories(syla PRIVATE src)

if (UNIX AND NOT APPLE) 
target_link_libraries(syla -L/usr/local/lib)
target_link_libraries(syla -lsfml-window)
target_link_libraries(syla -lsfml-system)
target_link_libraries(syla -lsfml-graphics)
target_link_libraries(syla -lsfml-network)
target_link_libraries(ser -L/usr/local/lib)
target_link_libraries(ser -lsfml-system)
target_link_libraries(ser -lsfml-network)
endif()