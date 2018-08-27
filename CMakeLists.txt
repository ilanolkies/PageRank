cmake_minimum_required(VERSION 3.10)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

add_executable(PageRank tp1.cpp MatrizRala.h MatrizRala.cpp ReadWrite.cpp ReadWrite.h)
