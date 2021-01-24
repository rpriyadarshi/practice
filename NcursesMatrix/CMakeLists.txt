cmake_minimum_required(VERSION 3.17)
project(NcursesMatrix)

set(CMAKE_CXX_STANDARD 20)
find_package(Curses REQUIRED)

add_executable(NcursesMatrix main.cpp)
target_link_libraries(NcursesMatrix ${CURSES_LIBRARY})
