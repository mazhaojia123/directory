cmake_minimum_required(VERSION 3.19)
project(directory)

set(CMAKE_CXX_STANDARD 14)

add_executable(directory main.cpp CatalogTree.cpp CatalogTree.h)