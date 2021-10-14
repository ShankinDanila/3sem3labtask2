cmake_minimum_required(VERSION 3.20)
project(Dialog)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(Dialog main.cpp Dialog.cpp Dialog.h)

include(FindPkgConfig)
find_package(Library REQUIRED)
include_directories(${CLASS_INCLUDE_DIR})
target_link_libraries(Dialog ${CLASS_LIBRARY11})