#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/linea_de_comandos.h"

int segundo_plano(char *comando)
{
    /*
     *  Este comando tiene la funcion quitar el caracter '\n' ya que dificulta
     *  el uso de los comandos ingresados
     */
    comando[strcspn(comando, "\n")] = '\000';
    /*
     *  Con la variable temp me aseguro que el ultimo valor sea '&' indicando
     *  que el comando que lo precede debe ejecutarse en 2do plano.
     */
    char *temp=(char*) malloc(sizeof(char)*6);
    temp=strrchr(comando, '&');

    if(temp!=NULL){ //si se encontro el caracter '&', !=NULL
        if (!strcmp(temp,"&"))//Si se encontro, asegurarse que es efectivamente el ultimo caracter
        {
            if(fork()==0) //El proceso hijo entra al if
            {
                /*
                 *  Trabajo del proceso hijo 
                 */
                comando[strcspn(comando, "&")] = '\000'; //Elimino el caracter '&'
                /*
                 *  imprimo el pid, lamentablente desconozco como obtener el job id
                 *  asi que imprimo 1.
                 *  El comando es enviado a la funcion comando que hace el trabajo
                 *  encomendado y cuando termina imprime que termino y sale.
                 */
                printf("[%d] %d \n",1,getpid()); 
                comandos(comando);
                printf("[%d] + %d done\n",1,getpid());

                exit(0);
            }
            else
            {
                /*
                 *  Trabajo del proceso padre
                 */
                wait(0);
                /*
                 *  Al devolver 1, inico que el comando ya fue ejecutado por el
                 *  proceso hijo
                 */
                return 1;
            }
        }
    }
    return 0;
}
