cmake_minimum_required(VERSION 3.6)
project(benchmarks)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)


set(SOURCE_FILES main.c config.c config.h)
add_executable(benchmarks ${SOURCE_FILES} config.c)