cmake_minimum_required(VERSION 3.28)
project(RationalModule VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(rational)

target_sources(rational
        PUBLIC
        FILE_SET CXX_MODULES
        TYPE CXX_MODULES
        FILES
        modules/rational.cppm
)
target_sources(rational
        PRIVATE
        modules/rational-impl.cpp
)

add_executable(rational_program main.cpp)
target_link_libraries(rational_program PRIVATE rational)
