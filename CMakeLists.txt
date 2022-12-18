cmake_minimum_required(VERSION 3.23.2)
project(Ass2)

#set(GCC_COVERAGE_COMPILE_FLAGS "−Wall −ansi −Wpedantic −Wextra")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
# -Weffc++ -pedantic -fPIE -std=c++17
SET(CMAKE_CXX_FLAGS -Wall)
SET(CMAKE_CXX_FLAGS -Wextra)
SET(CMAKE_CXX_FLAGS -Weffc++)
SET(CMAKE_CXX_FLAGS -Wsign-compare)
SET(CMAKE_CXX_FLAGS -Wfatal-errors)
#SET(CMAKE_CXX_FLAGS -std=c++17)
set(CMAKE_CXX_STANDARD 17)

add_executable(Ass2 main.cpp map.h map_rb.h map_pt.h)
