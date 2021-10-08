#include <stdio.h>
#include <stdlib.h>
#include "../include/linea_de_comandos.h"

void ejecutar_script(char *argumento)
{
    FILE *file= fopen(argumento,"r"); //Abro el archivo pasado
    char *temp= (char*) malloc(sizeof(char)*512); //genero una variable donde guardar las lineas de comandos

    while (fgets(temp,512,file)!=NULL) {
        /*
         *  Los comandos extraidos del archivo linea a linea son directamente
         *  pasados a la funcion encargada de ejecutar los comandos aceptados
         */
        comandos(temp);
    }

    fclose(file);
    free(temp);
    return;
}

