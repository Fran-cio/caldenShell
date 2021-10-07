#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/linea_de_comandos.h"

int segundo_plano(char *comando)
{
    char *temp=(char*) malloc(sizeof(char)*6);
    temp=strrchr(comando, '&');
    if(temp!=NULL){
        if (!strcmp(temp,"&")){
            if(fork()==0){
                comando[strcspn(comando, "&")] = '\000';
                printf("[%d] %d \n",1,getpid());
                comandos(comando);
                printf("[%d] + %d done\n",1,getpid());
                exit(0);
            }else {
                wait(0);
                return 1;
            }
        }
    }
    return 0;
}
