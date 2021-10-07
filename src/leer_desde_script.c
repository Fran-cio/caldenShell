#include <stdio.h>
#include <stdlib.h>
#include "../include/linea_de_comandos.h"

void ejecutar_script(char *argumento)
{
    FILE *file= fopen(argumento,"r");
    char *temp= (char*) malloc(sizeof(char)*512);
    while (fgets(temp,512,file)!=NULL) {
        comandos(temp);
    }
    free(temp);
    return;
}

