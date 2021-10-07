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
    flag_fork=fork();
    switch (flag_fork) {
        case -1:
            perror("ha ocurrido un error");
            exit(1);
            break;
        case 0:
            //Cantidad maxima de argumentos que la funcion va a aceptar es 3
            temp=ordenar_argumentos(comando); 
            if(ejecutor(temp)!=-1){}
            else 
            {
                printf("Comando desconocido");
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
    aux=(char*) malloc(sizeof(char)*512);
    aux=strrchr(temp[0],'/');
    aux++;

    if(execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1){}
    else 
    {
        temp[0]=strcat(temp[0],getenv("PWD"));
        if (execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1) {}
        else 
        {
            return -1;
            free(aux);
        }
    }
    free(aux);
    return 0;
}

char** ordenar_argumentos(char* comando)
{
    char **temp;
    temp=(char**)malloc(sizeof(char));
    int i=0;
    while (i!=4)
    {
        if (i!=0)
        {
            temp=(char**) realloc(temp,sizeof(char*)*(i+1));
        }
        if(comando!=NULL){
            temp[i]=comando;
        }else {
            temp[i]="\r";
        }
        comando= strtok(NULL, " ");
        i++;
    }
    return temp;
} 
