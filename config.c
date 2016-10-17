//
// Created by denis on 17/10/16.
//

#include "config.h"


double normalizedTime(){
    double vector1[1000];
    double vector2[1000];
    double r=0;
    double result=0;
    double start = 0;
    double finish = 0;
    srand(time(NULL));
    for(int i = 0; i<1000; i++){

        r = rand();
        vector1[i]= r;
        r = rand();
        vector2[i] = r;

    }
    start = MPI_Wtime();
    for(int i =0;i<1000;i++){

        result =  result  + vector1[i] * vector2[i];

    }
    finish = MPI_Wtime();
    //Normalize time

    return finish-start;
}


void pingPong(int times, int bytes, int world_rank){
    //Ping pong example
    int PING_PONG_LIMIT = times;
    int ping_pong_count = 0;
    char *packet;
    packet = (char*)malloc(bytes);

    while (ping_pong_count < PING_PONG_LIMIT) {


        if((ping_pong_count + world_rank)%2==0){
            MPI_Send(&packet, 1, MPI_BYTE, (world_rank+1)%2, 0, MPI_COMM_WORLD);
           // printf("[ %d ] : Sending to  [ %d ] the packet [ %c ]\n", world_rank, (world_rank+1)%2, *packet);
        }

        else{
            MPI_Recv(&packet, 1, MPI_BYTE, (world_rank+1)%2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
           // printf("[ %d ] : Receiving from  [ %d ] the packet [ %c ]\n", world_rank, (world_rank+1)%2, *packet);
          //  packetSent++;
        }
        ping_pong_count ++;
    }
}

void pingPong2(int times, int bytes, int world_rank){
    //Ping pong example
    int process = 0;
    int PING_PONG_LIMIT = times;
    int ping_pong_count = 0;
    char *packet;
    packet = (char*)malloc(bytes);
    int  a = 3;
    // a = (int*)malloc(sizeof(int));

    int partner_rank = (world_rank + 1) % 2;
    while (ping_pong_count < PING_PONG_LIMIT) {
        if (world_rank == ping_pong_count % 2) {
            // Increment the ping pong count before you send it
            ping_pong_count++;
            MPI_Send(&a, 1, MPI_BYTE, partner_rank, 0,
                     MPI_COMM_WORLD);
            //   printf("%d sent and incremented ping_pong_count ""%d to %d\n", world_rank, ping_pong_count,partner_rank);
        } else {
            MPI_Recv(&a, 1, MPI_BYTE, partner_rank, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //  printf("%d received ping_pong_count %d from %d\n", world_rank, ping_pong_count, partner_rank);
        }
    }
}