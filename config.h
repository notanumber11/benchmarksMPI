//
// Created by denis on 17/10/16.
//

#ifndef BENCHMARKS_CONFIG_H
#define BENCHMARKS_CONFIG_H
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double normalizedTime();

void pingPong(int times, int bytes, int world_rank);

#endif //BENCHMARKS_CONFIG_H
