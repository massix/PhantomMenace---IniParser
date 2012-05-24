# Main CMakeLists file

cmake_minimum_required(VERSION 2.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(libPmIniParser)
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
