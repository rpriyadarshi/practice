cmake_minimum_required(VERSION 3.17)
project(simple_sat)

set(CMAKE_CXX_STANDARD 20)

add_executable(simple_sat src/test_driver.cpp src/satinstance.h src/solvers/watchlist.h src/solvers/recursive_sat.h src/sat.h src/solvers/sat_base.h)