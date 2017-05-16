### Benchmarks intel MPI
C program to test the different comunication cost between parallel program with  intel MPI

## Evaluated system
Super computer Finis Terrae II in Santiago de Compostela/Galicia/Spain

### Main characteristics
- 306 nodes Thin : 2 x Intel Haswell 2680v3, 24 cores, 128GB, 1TB HDD local
- 4 nodes with GPU : Thin node + 2 GPUs K80 por nodo
- 2 nodos with accelerator Intel Phi : Thin node + 2 Intel Phi 7120 por nodo
- 1 nodo Fat : 8 x Intel Haswell 8867v3, 128 cores, 4TB, 24 TB HDD local
- 4 nodos login : Thin node (nodos de acceso)
- Operated system Linux RedHat 6.7
- Slum queue system

### Evaluated benchmarks
- Ping pong
- Send receive
- Broadcast
- Scatter
- Gather
- AlltoAll
- Reduce
- Barrier

### Methodology
This work has been based on Intel MPI Benchmarks User Guide and Methodology Description
Document number: 320714-008EN

### More details
For furthermore information you can read the file benchmarks.pdf (Spanish)

