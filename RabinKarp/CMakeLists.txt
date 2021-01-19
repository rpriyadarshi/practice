cmake_minimum_required(VERSION 3.17)
project(RabinKarp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(RabinKarp main.cpp)