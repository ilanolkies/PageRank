cmake_minimum_required(VERSION 3.12)
project(PageRank)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PageRank
        Matrix.cpp
        Matrix.h
        MatrixOperations.cpp
        MatrixOperations.h
        ReadWrite.cpp
        ReadWrite.h
        tp1.cpp
        VectorOperations.cpp
        VectorOperations.h Mediciones.cpp Mediciones.h)
