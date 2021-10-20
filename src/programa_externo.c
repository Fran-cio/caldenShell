#include <signal.h>
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
     * Si no contiene '/', entonces no es una path y va a devolver NULL 
     */

    aux=strrchr(temp[0],'/');

    if(aux!=NULL){
        /*
         * Si se ejecuta, bien, sino devuelve -1
         */
        if(execv(temp[0],temp)!=-1){}
        else 
        {
            return -1;
        }
          /*-------------------QUEDA DE RECUERDO---------------------------------*/
         /** No es la implementacion mas elegante pero es la mas simple para cumplir*/
         /** lo que se requiere, ya que execl no interpreta los espacios del arreglo*/
         /** vacios como espacios vacios*/
         /***/
 

        /** filtro el nombre del programa siendo este lo que este despues de la ultima*/
        /** '/', se almacena eso y se elimina la '/'*/
        
        /*aux=strrchr(temp[0],'/');*/
        /*aux++;*/


        /*switch (i-1) {*/
            /*case 0:*/
                /*if(execl(temp[0],aux,(char *)0)!=-1){}*/
                /*else */
                /*{*/
                    /*return -1;*/
                /*}*/
                /*break;*/
            /*case 1:*/
                /*if(execl(temp[0],aux,temp[1],(char *)0)!=-1){}*/
                /*else */
                /*{*/
                    /*return -1;*/
                /*}*/
                /*break;*/
            /*case 2:*/
                /*if(execl(temp[0],aux,temp[1],temp[2],(char *)0)!=-1){}*/
                /*else */
                /*{*/
                    /*return -1;*/
                /*}*/
                /*break;*/
            /*case 3:*/
                /*if(execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1){}*/
                /*else */
                /*{*/
                    /*return -1;*/
                /*}*/
        /*}*/
    }
    else
    {
        char    nombre_programa[64],
                path[512];
        /*
         * Se agrega la barra para completar el path de la env var
         */
        strcpy(nombre_programa,"/");

        aux=strdup(getenv("PATH"));
        /*
         * copiamos solo el contenido de la env var $PATH en aux
         */
        aux=strtok(aux,":");

        /*
         * copiamos la env var parseada para que se concatene al nombre de nues
         * tro programa, y dentro del while intenta ejecutar el programa
         */
        strcpy(path,aux);
        strcat(nombre_programa, temp[0]);
        strcat(path, nombre_programa);

        while (aux!=NULL) {
            if(execv(path,temp)!=-1)//Si logra ejecutarlo retorna con 0
            {
                free(aux);
                return 0;
            }
            /*
             * Si no logra ejecutarlo vuelve a parsear el contenido y a generar
             * el nuevo path de programa
             */
            aux=strtok(NULL, ":");
            if (aux!=NULL) { //Esto esta para salvar maniobrar punteros a null
                strcpy(path ,aux);
                strcat(path, nombre_programa);
            }
        }
        free(aux);
        return -1; 
    }
    return 0;
}

char** ordenar_argumentos(char* comando)
{
    char **temp;
    temp=(char**)malloc(sizeof(char));
    int i=0;

    while (comando!=NULL)
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
        comando= strtok(NULL, " ");
        i++;
    }
    temp[i]=NULL; //Se le agrego al final para marcar el fin del  arreglo
    return temp;
} 

