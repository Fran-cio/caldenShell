#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/linea_de_comandos.h"

void finalizar(void);
int contador_de_back=0;

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
    char *temp;
    /*
     * utilizo esto para que cada vez que se termine un proceso, devuelva un 0
     * y en ese momento reduzca el contador_de_back, no es tan precisos pero 
     * funciona
     */
    int status;
    temp=strrchr(comando, '&');
    waitpid(-1, &status, WNOHANG); 
    if (!WIFSIGNALED(status))
    {
        contador_de_back--;
    }
    if(temp!=NULL){ //si se encontro el caracter '&', !=NULL
        if (!strcmp(temp,"&"))//Si se encontro, asegurarse que es efectivamente el ultimo caracter
        {
            if(fork()==0) //El proceso hijo entra al if
            {
                int jobID=contador_de_back+1;
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
                printf("\r[%d] %d \n",jobID,getpid()); 
                comandos(comando);
                printf("\r[%d] + %d done\n",jobID,getpid());

                exit(0);
            }
            else
            {
                /*
                 *  Trabajo del proceso padre
                 */
                /*
                 * Seteo que a la salida del programa espere a los posibles proce
                 * sos que se quedaron ejecutandose
                 */
                atexit(finalizar); 
                sleep(1);//para que no se superpongan salidas, coloco un pequeño delay
                contador_de_back++;
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
void finalizar(void)
{
    wait(0);
}
