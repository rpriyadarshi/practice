cmake_minimum_required(VERSION 3.17)
project(ncurses)

set(CMAKE_CXX_STANDARD 20)

#set(NCURSES_PATH $ENV{NCURSES_PATH})
#message("NCURSES_PATH = ${NCURSES_PATH}")
#set(CURSES_USE_NCURSES TRUE)
#set(CURSES_LIBRARY NCURSES_PATH/lib)
#set(CURSES_INCLUDE_PATH NCURSES_PATH/include/ncursest)
#include_directories(${CURSES_INCLUDE_DIR})
find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})

add_executable(ncurses main.cpp)
target_link_libraries(ncurses ${CURSES_LIBRARY})
