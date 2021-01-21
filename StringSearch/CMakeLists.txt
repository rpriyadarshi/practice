cmake_minimum_required(VERSION 3.17)
project(StringSearch)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(StringSearch main.cpp rabinkarp.h bruteforce.h bruteforcebackup.h solution.h repsubstr.h knuthmorrispratt.h search.h)