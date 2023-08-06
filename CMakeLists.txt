cmake_minimum_required(VERSION 3.15)
project(otus-hw3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(range-v3 REQUIRED)

add_executable(ip_filter src/ip_filter.h src/ip_filter.cpp)
target_link_libraries(ip_filter range-v3::range-v3)