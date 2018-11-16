# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
/*
Trabalho de computação paralela
Aluno: Paulo Renato
Professor: ACMO
*/
# define VET_SIZE 100000
int main(int argc, char *argv[]){
    int i, nproc, pid, v[VET_SIZE];
    double tempoInicial;
    double tempoFinal;
    FILE *outFile;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    //iniciando o vetor
    if(pid == 0){
        for(i = 0; i<VET_SIZE; i++){
            v[i] = 1;
        }
        outFile = fopen("somaComum.txt", "a");
    }
    MPI_Bcast(v, VET_SIZE, MPI_INT, 0, MPI_COMM_WORLD );//mandando o vetor pros outros processos
    if(pid == 0){
        tempoInicial = MPI_Wtime();
    }


    int my_first, my_last, qtd;

    qtd = ceil((double)VET_SIZE/nproc); //divisao arredondando para cima
    my_first = pid*qtd; //onde eu começo
    my_last = my_first+qtd; //o primeiro do próximo
    my_last = my_last > VET_SIZE ? VET_SIZE : my_last;
    //printf("Processo: %d\nMy First: %d\nMy Last: %d\n\n", pid, my_first, my_last);

    int minhaSoma = 0, somaTotal, somaRecebida;

    for(i = my_first; i<my_last; i++){
        minhaSoma+=v[i];
    }
    //printf("Soma do processo %d: %d\n\n", pid, minhaSoma);

    if(pid != 0){
        MPI_Send(&minhaSoma, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }else{
        somaTotal = minhaSoma;
        for(i = 1; i<nproc; i++){
            MPI_Recv(&somaRecebida, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            somaTotal += somaRecebida;
        }
        tempoFinal = MPI_Wtime();
        //printf("\n\nSoma Total: %d\nTempo em milisegundos: %f", somaTotal, (tempoFinal-tempoInicial)*1000);
        fprintf(outFile, "%f\n", (tempoFinal-tempoInicial)*1000);
        fclose(outFile);
    }

    MPI_Finalize();

    return 0;
}
