#include <stdio.h>
#include <stdlib.h>
#include "../include/linea_de_comandos.h"

int ejecutar_script(char *argumento)
{
    FILE *file= fopen(argumento,"r"); //Abro el archivo pasado
    if(file==NULL) //Me aseguro que si es nulo, salga de la ejecucion
    {
        return 0;
    }
    else 
    {
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
        return 1;
    }
}

