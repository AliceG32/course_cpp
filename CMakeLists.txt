cmake_minimum_required(VERSION 3.14)
project(HybridSortTest)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(hybrid_sort_test main.cpp)

target_link_libraries(hybrid_sort_test GTest::gtest GTest::gtest_main)