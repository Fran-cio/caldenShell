#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char** ordenar_argumentos(char* comando);
int ejecutor(char**);

void programa_externo(char *comando)
{
    char **temp;
    int flag_fork=0;
    /*
     * Hago un fork y asigno el flag_fork a lo que devuelva la funcion, si es
     * -1 es porque algo salio mal. Si es 0, se trata del proceso hijo y si no es
     *  asi, se trata del padre
     */
    flag_fork=fork();
    switch (flag_fork) {
        case -1:
            perror("ha ocurrido un error");
            exit(1);
            break;
        case 0:
            /*
             *  La funcion ordenar_argumentos, devuelve el programa y los argumentos
             *  almacenados en un arreglo de strings
             */
            temp=ordenar_argumentos(comando); 

            /*
             *  ejecutor() recibe este arreglo y los parcea para manejarlos de la
             *  manera correcta, si puede hacerlo, devuelve -1, sino da un mensaje
             */
            if(ejecutor(temp)!=-1){}
            else 
            {
                printf("Comando desconocido, ingrese help para conocerlos comandos"
                        " disponibles");
                exit(0);
            }
            break;
        default:
            wait(0);
            printf("\n");
            break;

    }
}

int ejecutor(char **temp)
{
    char *aux;
    /*
     * filtro el nombre del programa siendo este lo que este despues de la ultima
     * '/', se almacena eso y se elimina la '/'
     */
    aux=strrchr(temp[0],'/');
    aux++;

    /*
     * Si se ejecuta, bien, sino devuelve -1
     */
    if(execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1){}
    else 
    {
        return -1;
    }
    free(aux);
    return 0;
}

char** ordenar_argumentos(char* comando)
{
    //Cantidad maxima de argumentos que la funcion va a aceptar es 3
    char **temp;
    temp=(char**)malloc(sizeof(char));
    int i=0;
    /*
     * Inicialemente se implemento este formato de arreglo dinamico porque se penso
     * para un programa que ingrese n cantidad de argumentos para el programa
     * esto finalmente por la limitacion de usar execl, limite la cantidad de 
     * argumentos almacenados a 3
     */
    while (i!=4)
    {
        /*
         * Este realloc va generando alocacion de memoria en base a medida que
         * agregamos palabras
         */
        if (i!=0)
        {   
            void *memleek_saver = (char**) realloc(temp,sizeof(char*)*(i+1));
            if (NULL == memleek_saver)
            {
                perror("\0");
            }
            else
            {
                temp = memleek_saver;
            }
        }
        if(comando!=NULL)
        {
            temp[i]=comando; //Si tengo comando, lo guardo en el arreglo
        }
        else
        {
            temp[i]="\r";   //Si no tengo, ya lo relleno con \r 
            /*
             * Esto se hace de esta manera porque execl no toma en cuenta este
             * argumento
             */
        }
        comando= strtok(NULL, " ");
        i++;
    }
    return temp;
} 

