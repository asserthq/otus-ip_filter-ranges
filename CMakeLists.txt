cmake_minimum_required(VERSION 3.15)
project(otus-hw3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(range-v3 REQUIRED)

add_executable(ip_filter src/ip_filter.cpp)
# Using the global target name
target_link_libraries(ip_filter range-v3::range-v3)