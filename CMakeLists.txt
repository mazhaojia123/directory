cmake_minimum_required(VERSION 3.19)
project(directory)

set(CMAKE_CXX_STANDARD 14)

add_executable(directory main.cpp split.h CatalogTree.cpp CatalogTree.h Shell.cpp Shell.h split.cpp)