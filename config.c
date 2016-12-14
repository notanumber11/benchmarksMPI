//
// Created by denis on 17/10/16.
//

#include "config.h"
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void printBytesAndTymes(){
    printf(" Bytes --- Times \n");
    int i = 0;
    for(i = 0; i < SIZE ; i++){
        printf("%d   ---   %d \n", bytes[i],times[i]);
    }
}



int getTimes(int bytes){
    int value = fmin(MESSAGES_PER_SAMPLE,OVERALL/bytes);
    int times = fmax(1,value);
    return times;
}

void initBytesAndTimes(){
    bytes[0] = 0;
    int i = 1;
    for(i = 1; i < SIZE ; i++){
        bytes[i] = pow(2,i-1);
    }

    times[0] = 1000;
    for(i = 1; i < SIZE ; i++){
        times[i] = getTimes(bytes[i]);
    }
}

double normalizedTime(){
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_rank == 0){
        double vector1[1000];
        double vector2[1000];
        double r=0;
        double result=0;
        double start = 0;
        double finish = 0;

        srand(time(NULL));
        int i = 0;
        for(i = 0; i<1000; i++){

            r = rand();
            vector1[i]= r;
            r = rand();
            vector2[i] = r;

        }
        start = MPI_Wtime();
        for(i =0;i<1000;i++){
            result =  result  + vector1[i] * vector2[i];
        }
        finish = MPI_Wtime();
        printf("Normalized time; %e ; microseconds ; accuracy ; %e ;\n", (finish-start) * pow(10,6),MPI_Wtick()* pow(10,6));
        return finish-start;
    }
    return -1;
}



