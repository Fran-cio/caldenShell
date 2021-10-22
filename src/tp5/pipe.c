#include "../../include/linea_de_comandos.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

char** elementos_de_pipe(char* ,int *,const char* );
void pipe_gen(char **elementos_en_pipe,int num_elementos);
void conectador_de_pipes(int fds[]);
void apertura_de_salida_de_pipe(int fds[]);

/*
 * Recibe el comando y verifica si se trata de una pipe, si lo es retorna 1 
 * posterior de la ejecucion del pipe. Sino un 0 indicando que no es un pipe
 */
int get_pipe(char* comando)
{
    if (strchr(comando, '|')!=NULL) 
    {
        char **elementos_en_pipe;
        int num_elementos;

        /*
         * Los elementos pipes se ordenan en un arreglo para su posterior ejecucion
         */
        elementos_en_pipe = elementos_de_pipe(comando,&num_elementos,"|");

        num_elementos--;//Para la funcion cuenta un elemento de mas
        pipe_gen(elementos_en_pipe,num_elementos);
        return 1;
    }
    else
    {
        return 0;
    }

}
/*
 * Recibe el arreglo de elementos a ejecutar y utiliza recursividad para 
 * concatenar salidas, entradas y ejecuta
 */
void pipe_gen(char **elementos_en_pipe,int num_elementos)
{
    int fds[2];
    pid_t pid;
    pipe(fds);
    pid=fork();
    if (pid==(pid_t)0)
    {
        conectador_de_pipes(fds);// conecta salidas con entradas del siguiente proc
        if(num_elementos>1)
        {
            /*
             * Si hay mas de 2 elementos a conectar, recusivamente los conecto
             */
            pipe_gen(elementos_en_pipe,num_elementos-1);
        }
        else 
        {
            /*
             * Si es el ultimo elemento o el 2do, se ejecuta el comando directamente
             */
            comandos(elementos_en_pipe[num_elementos-1]);
        }
        exit(0);
    }
    else 
    {
        wait(0);
        pid=fork();

        if(pid==0)
        {
            /*
             * conecto mi entrada a la salida de los procesos anteriores y eje
             * cuto el comando ingresado.
             */
            apertura_de_salida_de_pipe(fds);    
            comandos(elementos_en_pipe[num_elementos]);
            exit(0);
        }
        /*
         * cierro los pipes de parte del proceso padre
         */
        close(fds[0]);
        close(fds[1]);
        wait(0);
        sleep(1);
    }
}
/*
 * Conecta la entrada del pipe a la salida estandar
 */
void conectador_de_pipes(int fds[])
{
    dup2(fds[1], STDOUT_FILENO);
    close(fds[0]);
    close(fds[1]);
}
/*
 * Conecta la saldia del pipe a la entrada estandar
 */
void apertura_de_salida_de_pipe(int fds[])
{
    dup2(fds[0], STDIN_FILENO);
    close(fds[1]);
    close(fds[0]);
}
/*
 * Es una version mejorada de "ordenar_argumentos" de programa_externo,
 * ya que este permite recibir un contador y el caracter limitador
 * no lo implemento en el .c del tp4 para mantener el proyecto lo mas parecido
 * al original posible
 */
char** elementos_de_pipe(char* comando,int *i,const char* limitador)
{
    char **temp;
    temp=(char**)malloc(sizeof(char)*1024);
    *i=0;

    comando=strtok(comando  , limitador);
    while (comando!=NULL)
    {
        /*
         * Este realloc va generando alocacion de memoria en base a medida que
         * agregamos palabras
         */
        if (*i!=0)
        {   
            void *memleek_saver = (char**) realloc(temp,sizeof(char*)*(*i+1)*1024);
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
            temp[*i]=comando; //Si tengo comando, lo guardo en el arreglo
        }
        comando= strtok(NULL,limitador);
        *i=*i+1;
    }

    return temp;
}
