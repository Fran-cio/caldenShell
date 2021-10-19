#include "../../include/linea_de_comandos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *obtener_siguiente_palabra(char * file);
char *obterner_comando(char* comando);

int IO(char* comando)
{
   char *aux_input,
         *aux_output;
   aux_input=strchr(comando, '<'); 
   aux_output=strchr(comando, '>'); 
   if (aux_input!=NULL || aux_output!=NULL)
   {
      int fds_input[2];
      int fds_output[2];
      pid_t pid;
      pipe(fds_input);
      pipe(fds_output);
      pid=fork();
      if (pid==(pid_t)0)
      {
         close(fds_input[1]);
         if (aux_input!=NULL) 
         {      
            printf("%s\n",aux_input);
            dup2(fds_input[0], STDIN_FILENO);
         }
         else 
         {
            close(fds_input[0]);
         }
         close(fds_output[0]);
         if (aux_output!=NULL) {
            printf("%s\n",aux_output);
            dup2(fds_output[1],STDOUT_FILENO);
         }
         else
         {
            close(fds_output[1]);
         }
         comando=obterner_comando(comando);
         printf("%s\n",comando);
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
               FILE *stream;
               stream=fdopen(fds_input[1], "w");
               char *file_input=obtener_siguiente_palabra(aux_input);
               printf("%s\n",file_input);
               FILE *file= fopen(file_input,"r"); //Abro el archivo pasado
               if(file==NULL) //Me aseguro que si es nulo, salga de la ejecucion
               {
                  perror("File Nulo");
               }
               else 
               {
                  char *temp= (char*) malloc(sizeof(char)*512); //genero una variable donde guardar las lineas de comandos
                  while (fgets(temp,512,file)!=NULL) 
                  {
                     fprintf(stream,"%s",temp);
                  }
                  fflush(stream);
                  fclose(file);
                  free(temp);
                  free(file_input);
               }
               close(fds_input[1]);
            }
            close(fds_output[1]);
            if (aux_output!=NULL) {
               FILE *stream;
               stream=fdopen(fds_output[0], "r");
               char *file_output=obtener_siguiente_palabra(aux_output);
               FILE *file= fopen(file_output,"wt"); //Abro el archivo pasado
               printf("%s\n",file_output);
               if(file==NULL) //Me aseguro que si es nulo, salga de la ejecucion
               {
                  perror("File Nulo");
               }
               else 
               {
                  char *temp= (char*) malloc(sizeof(char)*512); //genero una variable donde guardar las lineas de comandos
                  while (fgets(temp,512,stream)!=NULL) 
                  {
                     printf("%s\n",temp);
                     fputs(temp,file);
                  }
                  /*fflush(strwam);*/
                  fclose(file);
                  free(temp);
                  free(file_output);
               }
               close(fds_output[0]);
            }
            exit(0);
         }
         wait(0);
         sleep(1);
         return 1;
      }
   }
   return 0;
}

char *obterner_comando(char* comando)
{
   printf("%s\n",comando);
   char *temp=(char *)calloc(1024,sizeof(char));
   for(int i=0;comando[i]!='<'&&comando[i]!='>';i++)
   {
      temp[i]=comando[i];
   }
   return temp;
}
char *obtener_siguiente_palabra(char * file)
{
   file++;
   file=strtok(file, " ");
   return file;
}

