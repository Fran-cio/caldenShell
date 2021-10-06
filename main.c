#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char actual_path[1024];

void linea_de_comandos(char *comandos);
int ejecutor(char **temp, int args);

int main(int argc,char** argv) 
{   
    char    hostname[20];

    if(gethostname(hostname, 20)) 
        exit(1);

    strcpy(actual_path,"/home/");
    strcpy(actual_path, strcat(actual_path,getlogin()));

    setenv("PWD",  actual_path, 1);

    chdir(getenv("PWD"));
    setenv("OLDPWD", getenv("PWD"), 1);

    getcwd(actual_path, 1024);
    if (fopen(argv[1],"r")!=NULL)
    {
        FILE *file= fopen(argv[1],"r");
        char *temp= (char*) malloc(sizeof(char)*512);
        while (fgets(temp,512,file)!=NULL) {
            linea_de_comandos(temp);
        }
        free(temp);
    }
    else
    {
        while(1)
        {
            char *comando;
            comando= (char*) malloc(sizeof(char)*1024);

            printf( ANSI_COLOR_YELLOW "%s@%s" ANSI_COLOR_RESET ":" 
                    ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
                    getlogin(),hostname,getenv("PWD"));

            fgets(comando,1024,stdin);
            linea_de_comandos(comando);
        }
    }
    return 0;
}
void linea_de_comandos(char* comando)
{
    comando[strcspn(comando, "\n")] = ' ';
    comando=strtok(comando," ");

    if(comando!=NULL)
    {
        if(!strcmp(comando,"quit")||!strcmp(comando,"q"))
        {
            exit(0);
        }

        else if(!strcmp(comando,"cd"))
        {
            comando = strtok(NULL," ");
            if(comando==NULL)
            {
                printf("%s\n",getenv("PWD"));
            }
            else
            {
                char temp[1024];

                if(!strcmp(comando,"-"))
                {
                    chdir(getenv("OLDPWD"));
                    setenv("PWD", getenv("OLDPWD"),1);
                }
                else
                {
                    if(chdir(comando)==-1)
                    {
                        printf("Ruta invalida\n"); 
                    }
                    else
                    {
                        getcwd(actual_path,1024);
                        setenv("OLDPWD", getenv("PWD"),1);
                        setenv("PWD", actual_path,1);
                    }
                }
            }
        }

        else if(!strcmp(comando,"clr"))
        {
            printf("\033c");
        }
        //Aviso: Si pones echo hola$PWD no va a parsear el $, la salida sera hola$PWD 
        else if (!strcmp(comando,"echo"))
        {
            comando = strtok(NULL," ");
            if(comando!=NULL)
            {
                char    *temp;
                int i=0,
                    j=0,
                    flag_$=0;
                while (comando!=NULL)
                {
                    temp= (char*) calloc(1024,sizeof(char));

                    if (comando[j]!='$')
                    {
                        j=0;
                    }
                    i=0;
                    while (comando[j]!='\000' && (comando[j]!='$'||(!flag_$))) 
                    {   
                        if (comando[0]!='$' || flag_$) 
                        {
                            temp[i]=comando[j];
                            i++;
                        }else {
                            flag_$=1;
                        }
                        j++;
                    }
                    if (flag_$)
                    {
                        printf("%s ",getenv(temp));
                        flag_$=0;
                    }
                    else 
                    {
                        printf("%s ",temp);
                    }
                    if (comando[j]=='\000') 
                    {
                        comando=strtok(NULL," ");
                    }
                    free(temp);
                }
                printf("\n");
            }
        }
        else 
        {
            //Insert lo que falta
            int i=0;
            char **temp1;
            temp1=(char**)malloc(sizeof(char));
            int flag_fork=0;
            flag_fork=fork();
            switch (flag_fork) {
                case -1:
                    perror("ha ocurrido un error");
                    exit(1);
                    break;
                case 0:
                    //Cantidad maxima de argumentos que la funcion va a aceptar es 3
                    while (i!=4)
                    {
                        if (i!=0)
                        {
                            temp1=(char**) realloc(temp1,sizeof(char*)*(i+1));
                        }
                        if(comando!=NULL){
                        temp1[i]=comando;
                        }else {
                        temp1[i]="\r";
                        }
                        comando= strtok(NULL, " ");
                        i++;
                    }
                    //Por alguna razon esta funcion no acepta mas de 2 parametros 
                    if(ejecutor(temp1,i)!=-1){}
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
            free(temp1);
        }
    }
}
int ejecutor(char **temp, int args){
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
