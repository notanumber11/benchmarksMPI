cmake_minimum_required(VERSION 3.6)
project(benchmarks)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)


set(SOURCE_FILES main.c config.c config.h benchmarks.c benchmarks.h)
add_executable(benchmarks ${SOURCE_FILES} config.c benchmarks.c benchmarks.h)

target_link_libraries(benchmarks m)
