
#include <mpi.h>
#include <stdio.h>

//********************************************************************************************************************//
#include "config.h"
#include "benchmarks.h"
//********************************************************************************************************************//

#define pingPoingFlag   1
#define sendReceiveFlag 1
#define broadcastFlag   1
#define scaterFlag      1
#define gatherFlag      1
#define reduceFlag      1
#define allToAllFlag    1
#define barrierFlag     1

void pingPongMain(int world_rank, int world_size);
void printHeader();


int main (int argc, char** argv) {


    MPI_Init(&argc,&argv);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Barrier(MPI_COMM_WORLD);
    if(world_rank == 0){

        normalizedTime();
    }
    initBytesAndTimes();
    MPI_Barrier(MPI_COMM_WORLD);


    if(pingPoingFlag){
        pingPongMain(world_rank,world_size);
    }

     if(sendReceiveFlag){
        sendReceiveMain(world_rank,world_size);
    }
     if(broadcastFlag){
        broadcastMain(world_rank,world_size);
    }
     if(scaterFlag){
        ScatterMain(world_rank,world_size);
    }
     if(gatherFlag){
        gatherMain(world_rank,world_size);
    }
     if(reduceFlag){
        reduceMain(world_rank,world_size);
    }
     if(allToAllFlag){
        allToAllMain(world_rank, world_size);
    }
     if(barrierFlag){
        barrierMain(world_rank,world_size);
    }

    MPI_Finalize();
}

void pingPongMain(int world_rank,int world_size) {
    if(world_size == 2){
        if(world_rank==0){
            printf("\n\nPingPong; Nº Process; %d ;\n\n",world_size);
            printHeader();
        }
        for(int i = 0; i < SIZE ; i++){
            pingPong(times[i],bytes[i]);
        }
    }
}

void sendReceiveMain(int world_rank, int world_size){
    if(world_size == 2){
        if(world_rank==0){
            printf("\n\nSendReceive; Nº Process; %d ;\n\n",world_size);
            printHeader();
        }
        for(int i = 0; i < SIZE ; i++){
            sendReceive(times[i],bytes[i]);
        }
    }
}

void broadcastMain(int world_rank, int world_size){
    if(world_rank==0){
        printf("\n\nBroadcast; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        broadcast(times[i],bytes[i]);
    }
}

void ScatterMain(int world_rank, int world_size){
    if(world_rank==0){
        printf("\n\nScater; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        scater(times[i],bytes[i]);
    }

}

void gatherMain(int world_rank, int world_size){
    if(world_rank==0){
        printf("\n\nGather; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        gather(times[i],bytes[i]);
    }

}

void reduceMain(int world_rank, int world_size){
    if(world_rank==0){
        printf("\n\nReduce; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        reduce(times[i],bytes[i]);
    }

}

void allToAllMain(int world_rank, int world_size){
    if(world_rank==0){
        printf("\n\nAllToAll; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        allToAll(times[i],bytes[i]);
    }

}

void barrierMain(int world_rank,int world_size){
    if(world_rank==0){
        printf("\n\nBarrier; Nº Process; %d ;\n\n",world_size);
        printHeader();
    }
    for(int i = 0; i < SIZE ; i++){
        barrier(times[i],bytes[i]);
    }

}

void printHeader(){
    printf("Bytes; Times; Latency(ys); Bandwidth(MBps); \n");
}
