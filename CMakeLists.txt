cmake_minimum_required(VERSION 3.10)
project(PageRank)

set(CMAKE_CXX_STANDARD 11)

add_executable(PageRank tp1.cpp Matrix.h Matrix.cpp ReadWrite.h ReadWrite.cpp MatrixOperations.h MatrixOperations.cpp VectorOperations.cpp VectorOperations.h)
