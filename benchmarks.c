//
// Created by denis on 13/12/16.
//


#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include "benchmarks.h"
#include "config.h"

void pingPong(int times, int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++){
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);


        if(world_rank==0 && world_size!=2){
            printf("Ping pong should be executed with only 2 processes\n");
            return;
        }
        //Init content
        char *packet;
        packet = (char*)malloc(bytes);


        //Init timer
        double timeGlobal = 0;
        double time = 0;

        // Configure algorithm
        int PING_PONG_TIMES = times*2;
        int ping_pong_count = 0;


        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        while (ping_pong_count < PING_PONG_TIMES) {

            if((ping_pong_count+world_rank)%2==0){
                MPI_Send(packet, bytes, MPI_BYTE, (world_rank+1)%2, 0, MPI_COMM_WORLD);
            }

            else{
                MPI_Recv(packet, bytes, MPI_BYTE, (world_rank+1)%2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            ping_pong_count ++;
        }
        // End timer
        time = (MPI_Wtime()-time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        //timeGlobal = time;
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);

        if(world_rank == 0 && k==WARM_UP){
            double finalTime = timeGlobal/2/world_size/times*pow(10,6);
            printf(" %6d ; %6d ; ", bytes,times);
            printf(" %e ; %e; \n", finalTime, bytes/(THROUGHPUTCONSTANT*finalTime));
        }

        free(packet);
    }
}

void sendReceive(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        if (world_rank == 0 && world_size != 2) {
            printf("Send Receive should be executed with only 2 processes\n");
        }

        //Init content
        char *packetSend;
        packetSend = (char *) malloc(bytes);
        char *packetReceive;
        packetReceive = (char *) malloc(bytes);

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        //Configure algorithm
        int nmsg = 2;
        int source = (world_rank - 1);
        int destination = world_rank + 1;

        if (destination >= world_size)
            destination = 0;

        if (source < 0) {
            source = world_size - 1;
        }

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            // Make the algorithm
            MPI_Sendrecv(packetSend, bytes, MPI_BYTE, destination, 123, packetReceive, bytes, MPI_BYTE, source, 123,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && k == WARM_UP) {
            double finalTime = timeGlobal / world_size / times * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; %e; \n", finalTime, nmsg * bytes / (THROUGHPUTCONSTANT * finalTime));
        }
        free(packetReceive);
        free(packetSend);
    }
}

void broadcast(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init content
        char *packetSend;
        packetSend = (char *) malloc(bytes);

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        //Configure algorithm
        int root = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            root = i % world_size;
            MPI_Bcast(packetSend, bytes, MPI_BYTE, root, MPI_COMM_WORLD);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && k == WARM_UP) {
            double finalTime = timeGlobal / times / world_size * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; NP ; \n", finalTime);
        }
        free(packetSend);
    }
}

void scater(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init content
        char *packetSend;
        packetSend = (char *) malloc((size_t) (bytes * world_size));
        char *packetReceive;
        packetReceive = (char *) malloc((size_t) bytes);

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        //Configure algorithm
        int destination = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            destination = i % world_size;
            MPI_Scatter(packetSend, bytes, MPI_BYTE, packetReceive, bytes, MPI_BYTE, destination, MPI_COMM_WORLD);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && WARM_UP == k) {
            double finalTime = timeGlobal / times / world_size * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; NP ; \n", finalTime);
        }
        free(packetReceive);
        free(packetSend);
    }
}

void gather(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init content
        char *packetSend;
        packetSend = (char *) malloc((size_t) bytes);
        char *packetReceive;
        packetReceive = (char *) malloc((size_t) (bytes * world_size));

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        //Configure algorithm
        int destination = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            destination = i % world_size;
            MPI_Gather(packetSend, bytes, MPI_BYTE, packetReceive, bytes, MPI_BYTE, destination, MPI_COMM_WORLD);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && WARM_UP == k) {
            double finalTime = timeGlobal / world_size / times * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; NP ; \n", finalTime);
        }
    }

}

void reduce(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init content
        int count = bytes / sizeof(MPI_FLOAT);
        float *packetSend = malloc(sizeof(MPI_FLOAT) * count);
        float *packetReceive = malloc(sizeof(MPI_FLOAT) * count);
        int j = 0;
        for (j = 0; j < count; j++){
            packetSend[j] = ((float) rand() / (float) (RAND_MAX / rand()));
        }

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        //Configure algorithm
        int root = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            root = i % world_size;
            MPI_Reduce(packetSend, packetReceive, count, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && k == WARM_UP) {
            double finalTime = timeGlobal / world_size / times * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; NP ; \n", finalTime);
        }
        free(packetReceive);
        free(packetSend);
    }
}

void allToAll(int times,int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init content
        char *packetSend;
        packetSend = (char *) malloc(bytes * world_size);
        char *packetReceive;
        packetReceive = (char *) malloc(bytes * world_size);

        //Init timer
        double timeGlobal = 0;
        double time = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        time = MPI_Wtime();
        int i = 0;
        for (i = 0; i < times; i++) {
            MPI_Alltoall(packetSend, bytes, MPI_BYTE, packetReceive, bytes, MPI_BYTE, MPI_COMM_WORLD);
        }
        // End timer
        time = (MPI_Wtime() - time);
        // Comunicate time
        MPI_Reduce(&time, &timeGlobal, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && k == WARM_UP) {
            double finalTime = timeGlobal / times / world_size * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ;  NP ; \n", finalTime);
        }
        free(packetReceive);
        free(packetSend);
    }
}

void barrier(int times, int bytes){
    int k = 0;
    for(k=0; k <= WARM_UP;k++) {
        //Init MPI
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        //Init timer
        double timeGlobal = 0;

        // Syncronize process
        MPI_Barrier(MPI_COMM_WORLD);
        //Start timer
        double start = MPI_Wtime();
        int i = 0;
        for (int i = 0; i < times; i++) {
            MPI_Barrier(MPI_COMM_WORLD);
        }
        // End timer
        timeGlobal = (MPI_Wtime() - start);
        // Print results
        MPI_Barrier(MPI_COMM_WORLD);
        if (world_rank == 0 && k == WARM_UP) {
            double finalTime = timeGlobal / times * pow(10, 6);
            printf(" %6d ; %6d ; ", bytes, times);
            printf(" %e ; NP \n", finalTime);
        }
    }
}