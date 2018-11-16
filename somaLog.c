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
    int i, j, nproc, pid, v[VET_SIZE];
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
        outFile = fopen("somaLog.txt", "a");
        tempoInicial = MPI_Wtime();
    }
    MPI_Bcast(v, VET_SIZE, MPI_INT, 0, MPI_COMM_WORLD );//mandando o vetor pros outros processos


    int my_first, my_last, qtd;

    qtd = ceil((double)VET_SIZE/nproc); //divisao arredondando para cima
    my_first = pid*qtd; //onde eu começo
    my_last = my_first+qtd; //o primeiro do próximo
    my_last = my_last > VET_SIZE ? VET_SIZE : my_last;
    //printf("Processo: %d\nMy First: %d\nMy Last: %d\n\n", pid, my_first, my_last);

    int minhaSoma = 0, somaRecebida, somaTotal;

    for(i = my_first; i<my_last; i++){
        minhaSoma+=v[i];
    }
    //printf("Soma do processo %d: %d\n\n", pid, minhaSoma);

    int profundidade = ceil(log2(nproc));
    int fator, envia;

    fator = 1;
    for(i = 1; i<=profundidade;i++){
        envia = fator*2;
        for(j = 0; j<nproc;j+=fator){
            if(j!=pid) continue;
            if(j%envia != 0){
                MPI_Send(&minhaSoma, 1, MPI_INT, j-fator, 1, MPI_COMM_WORLD);
            }else if(j+fator < nproc){
                MPI_Recv(&somaRecebida, 1, MPI_INT, j+fator, 1, MPI_COMM_WORLD, &status);
                minhaSoma+=somaRecebida;
                //printf("%d recebeu de %d Soma: %d\n", j, j+fator, minhaSoma);
            }
        }
        fator = envia;
    }
    if(pid == 0){
        tempoFinal = MPI_Wtime();
        somaTotal = minhaSoma;
        //fprintf(outFile, "\nSoma Total: %d   Tempo em milisegundos: %f    Processos: %d\n", somaTotal, (tempoFinal-tempoInicial)*1000, nproc);
        fprintf(outFile, "%f\n", (tempoFinal-tempoInicial)*1000); // tempo em milisegundos
        fclose(outFile);
    }
    MPI_Finalize();

    return 0;
}
