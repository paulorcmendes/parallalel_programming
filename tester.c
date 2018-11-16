#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i, j;
    char comando[100];
    FILE *outFile;

    for(i = 1; i <= 4; i++){
        outFile = fopen("somaComum.txt", "a");
        fprintf(outFile, "\n############ %d PROCESSOS ############\n", i);
        fclose(outFile);
        sprintf(comando, "mpiexec -n %d somaComum.exe", i);
        for(j = 0; j<5; j++){
            system(comando);
        }
    }

    return 0;
}
