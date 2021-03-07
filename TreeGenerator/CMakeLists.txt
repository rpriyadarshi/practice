cmake_minimum_required(VERSION 3.17)
project(TreeGenerator)

set(CMAKE_CXX_STANDARD 20)

add_executable(TreeGenerator main.cpp rackoner.h rackoner.cpp schema.h schema.cpp generator.h generator.cpp)