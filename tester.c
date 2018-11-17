#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i, j;
    char comando[100];
    FILE *outFile;

    for(i = 1; i <= 4; i++){
<<<<<<< HEAD
        outFile = fopen("somaComum.txt", "a");
        fprintf(outFile, "\n############ %d PROCESSOS ############\n", i);
        fclose(outFile);
        sprintf(comando, "mpiexec -n %d somaComum.exe", i);
=======
        outFile = fopen("somaLog.txt", "a");
        fprintf(outFile, "\n############ %d PROCESSOS ############\n", i);
        fclose(outFile);
        sprintf(comando, "mpiexec -n %d somaLog.exe", i);
>>>>>>> fccef233ee67045c1389a6e633dadc7133c3390c
        for(j = 0; j<5; j++){
            system(comando);
        }
    }

    return 0;
}
