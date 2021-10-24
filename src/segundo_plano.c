#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include "../include/linea_de_comandos.h"

void look_the_flowers_Lizzie(int);
void finalizar(void);
int *punt_cont;

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
    temp=strrchr(comando, '&');
    if(temp!=NULL){ //si se encontro el caracter '&', !=NULL
        if (!strcmp(temp,"&"))//Si se encontro, asegurarse que es efectivamente el ultimo caracter
        {
            /*
             * Asigno el puntero a una direccion de memoria compartida para que ambos pro
             * cesos tengan accesos a el. Notar que no estoy teniendo en cuenta posibles
             * peligros de concurrencia
             */
            if(punt_cont==NULL)
            {
                punt_cont= (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            }

            if(fork()==0) //El proceso hijo entra al if
            {
                int jobID=*punt_cont+1;
                /*
                 *  Trabajo del proceso hijo 
                 */
                comando[strcspn(comando, "&")] = '\000'; //Elimino el caracter '&'
                /*
                 * Imprimo los indicadores de back y ejecuto el programa
                 */
                printf("\r[%d] %d \n",jobID,getpid()); 
                finder(comando);
                printf("\r[%d] + %d done\n",jobID,getpid());
                /*
                 * Descuento el contador al salir del programa
                 */
                *punt_cont-=1;
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
                signal(SIGCHLD,look_the_flowers_Lizzie);
                atexit(finalizar); 
                sleep(1);//para que no se superpongan salidas, coloco un pequeño delay
                /*
                 * Aumento el contador de tareas en back
                 */
                *punt_cont+=1;
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
    /*
     * Libero el espacio de memoria compartido
     */
    munmap(punt_cont, sizeof(int));
}
void look_the_flowers_Lizzie(int status)
{
    int pid_hijo;
    while ((pid_hijo = waitpid(-1, &status, WNOHANG)) > 0){}
}
