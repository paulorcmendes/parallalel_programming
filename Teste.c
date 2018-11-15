#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0
#define SIZEVECTOR 10000

int main (int argc, char *argv[]) {
    int i, numtasks, taskid, len; char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    MPI_Get_processor_name(hostname, &len);
    printf ("Hello from task %d on %s!\n", taskid, hostname);
    if (taskid == MASTER){
        int v1[SIZEVECTOR], v2[SIZEVECTOR], v3[SIZEVECTOR];
        for(i = 0; i<SIZEVECTOR; i++){
            v1[i] = i;
            v2[i] = 2*i;
        }
        printf("Aqui comeca\n");
        printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
    }
    MPI_Finalize();
    printf("Aqui termina\n");
}
