//
// Created by denis on 13/12/16.
//

#ifndef BENCHMARKS_BENCHMARKS_H
#define BENCHMARKS_BENCHMARKS_H

void pingPong(int times, int bytes);

void sendReceive(int times, int bytes);

void broadcast(int times, int bytes);

void scater(int times, int bytes);

void gather(int times, int bytes);

void reduce(int times, int bytes);

void allToAll(int times, int bytes);

void barrier(int times, int bytes);

#endif //BENCHMARKS_BENCHMARKS_H

