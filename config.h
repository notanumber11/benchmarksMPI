//
// Created by denis on 17/10/16.
//

#ifndef BENCHMARKS_CONFIG_H
#define BENCHMARKS_CONFIG_H

#include <math.h>

#define SIZE 24
#define MESSAGES_PER_SAMPLE 1000
#define OVERALL 41943040
#define THROUGHPUTCONSTANT 1.048576
#define WARM_UP 0

int times[SIZE];
int bytes[SIZE];

double normalizedTime();
void initBytesAndTimes();

#endif //BENCHMARKS_CONFIG_H