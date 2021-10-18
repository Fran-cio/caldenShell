#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void comandos(char *comando);

char** elementos_de_pipe(char* ,int *,const char* );
char* pipe_gen(char **elementos_en_pipe,int num_elementos);

char* get_pipe(char* comando)
{
    comando[strcspn(comando, "\n")] = '\000';
   char **elementos_en_pipe;
   int num_elementos;

   elementos_en_pipe = elementos_de_pipe(comando,&num_elementos,"|");

   comando= pipe_gen(elementos_en_pipe,num_elementos);

   return comando;
}

char* pipe_gen(char **elementos_en_pipe,int num_elementos)
{
   int fds[2];
   pid_t pid;
   pipe(fds);
   pid=fork();
   if (pid==(pid_t)0)
   {
      if(num_elementos>2)
      {
         elementos_en_pipe[num_elementos-1]=pipe_gen(elementos_en_pipe,num_elementos-1);
      }
      close(fds[0]);
      dup2(fds[1], STDOUT_FILENO);
      comandos(elementos_en_pipe[num_elementos-1]);
      close(fds[1]);
      exit(0);
   }
   else 
   {
       char comando_padre[1024];
       close(fds[1]);
       read(fds[0], comando_padre, sizeof(comando_padre));
       while (strcspn(comando_padre,"\n")<strcspn(comando_padre,"\000")) {
        comando_padre[strcspn(comando_padre, "\n")]= ' ';
        /*printf("%ld \n",(strcspn(comando_padre,"\n")));;*/
       }
       strcat(elementos_en_pipe[num_elementos], " ");
       strcat(elementos_en_pipe[num_elementos], comando_padre);
   }
   return elementos_en_pipe[num_elementos];
}

char** elementos_de_pipe(char* comando,int *i,const char* limitador)
{
    //Cantidad maxima de argumentos que la funcion va a aceptar es 3
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
        *i=+1;
    }
    
    /*temp[*i]=NULL; //Se le agrego al final para marcar el fin del  arreglo*/
    
    return temp;
}
