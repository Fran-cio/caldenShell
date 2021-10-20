#include "../../include/linea_de_comandos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void gestor_IO(FILE *leido,FILE *escrito);
char *obtener_siguiente_palabra(char * file);
char *obterner_comando(char* comando);

int IO(char* comando)
{
   char *aux_input,
        *aux_output;
   /*
    * Guardo la linea de comando posterior a < y/o >
    */
   aux_input=strchr(comando, '<'); 
   aux_output=strchr(comando, '>'); 
   if (aux_input!=NULL || aux_output!=NULL)
   {
      /*
       * Si una de las 2 no es NULL, entonces hay que chear que conexiones hay
       * que hacer
       */
      int fds_input[2];
      int fds_output[2];
      /*
       * Como los pipes son halfduplex, creo 2, uno para manejar lo que me llega
       * desde la input y otro para sacar la salida
       */
      pid_t pid;
      pipe(fds_input);
      pipe(fds_output);
      pid=fork();
      if(pid==-1)
      {
         perror("fork");
      }
      else if (pid==(pid_t)0)
      {
         /*
          * El proceso hijo se encagarga de gestionar de donde va a recibir
          * el input y a donde dirigir el output. Y ejecuta el comando
          */
         close(fds_input[1]);
         if (aux_input!=NULL) 
         {  
            /*
             * Si entra, espera recibir el input de otra parte
             */
            dup2(fds_input[0], STDIN_FILENO);
         }
         close(fds_input[0]);
         close(fds_output[0]);
         if (aux_output!=NULL) {
            /*
             * Si entra, espera recibir el output de otra parte
             */
            dup2(fds_output[1],STDOUT_FILENO);
         }
         close(fds_output[1]);
         /*
          * Con la IO dirigida, ejecuta el comando en cuestion
          */
         comando=obterner_comando(comando);
         comandos(comando);
         free(comando);
         exit(0);
      }
      else 
      {
         pid=fork();
         if(pid==0)
         {
            close(fds_input[0]);
            if (aux_input!=NULL) 
            {      
               /* 
                * Si entra aca, es porque debo leer y dirigir eso al stdin
                */
               FILE *stream1;
               /*
                * creo un stream conectado al pipe de entrada y lo configuro 
                * para escribir en el lo que lea del archivo
                */
               stream1=fdopen(fds_input[1], "w");
               char *file_input=obtener_siguiente_palabra(aux_input);
               FILE *file1= fopen(file_input,"r"); 
               /*
                * Envio el stream para ser escrito y el archivo para ser leido
                */
               gestor_IO(file1, stream1); 
               close(fds_input[1]);
            }
            close(fds_output[1]);
            if (aux_output!=NULL) {
               /* 
                * Si entra aca, es porque debo leer el stdout y dirigirlo
                * a un archivo
                */
               FILE *stream2;
               /*
                * creo un stream conectado al pipe de salida y lo configuro 
                * para leer en el y escribir sobre el archivo
                */
               stream2=fdopen(fds_output[0], "r");
               char *file_output=obtener_siguiente_palabra(aux_output);
               FILE *file2= fopen(file_output,"w"); 
               /*
                * Envio el stream para ser leido y el archivo para ser escrito
                */
               gestor_IO(stream2, file2);
               close(fds_output[0]);
            }
            exit(0);
         }
         /*
          * cierro todos los pipes y espero que los hijos acaben la ejecucion
          */
         close(fds_input[0]);
         close(fds_input[1]);
         close(fds_output[0]);
         close(fds_output[1]);
         wait(0);
         sleep(1);
         return 1;
      }
   }
   return 0;
}
/*
 * Va a leer uno de los FILE recibidos y dirigir lo leido a el otro FILE
 */
void gestor_IO(FILE *leido,FILE *escrito)
{
   if(escrito==NULL) //Me aseguro que si es nulo, salga de la ejecucion
   {
      perror("File Nulo");
   }
   else 
   {
      char *temp= (char*) malloc(sizeof(char)*512); //genero una variable donde guardar las lineas de comandos
      while (fgets(temp,512,leido)!=NULL) 
      {
         fputs(temp,escrito);
      }
      fflush(leido);
      fclose(escrito);
      free(temp);
   }
}
/*
 * Filtro todo el texto previo a el < o >, el cual es el comando a ejecutar
 */
char *obterner_comando(char* comando)
{
   char *temp=(char *)calloc(1024,sizeof(char));
   for(int i=0;comando[i]!='<'&&comando[i]!='>';i++)
   {
      temp[i]=comando[i];
   }
   return temp;
}
/*
 * Obtengo el texto inmediato a el < o > que va a ser el archivo de direccionamiento
 */
char *obtener_siguiente_palabra(char * file)
{
   file++;
   file=strtok(file, " ");
   return file;
}

