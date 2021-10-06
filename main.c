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

int ejecutor(char **temp, int args);

int main(int argc,char** argv) 
{   
    char    hostname[20],
    actual_path[1024];

    if(gethostname(hostname, 20)) 
        exit(1);

    strcpy(actual_path,"/home/");
    strcpy(actual_path, strcat(actual_path,getlogin()));

    setenv("PWD",  actual_path, 1);

    chdir(getenv("PWD"));
    setenv("OLDPWD", getenv("PWD"), 1);

    getcwd(actual_path, 1024);

    while(1)
    {
        char *opt_1;
        opt_1= (char*) malloc(sizeof(char)*1024);

        printf( ANSI_COLOR_YELLOW "%s@%s" ANSI_COLOR_RESET ":" 
                ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
                getlogin(),hostname,getenv("PWD"));

        fgets(opt_1,1024,stdin);
        opt_1[strcspn(opt_1, "\n")] = ' ';
        opt_1=strtok(opt_1," ");

        if(opt_1!=NULL)
        {
            if(!strcmp(opt_1,"quit"))
            {
                exit(0);
            }
            
            else if(!strcmp(opt_1,"cd"))
            {
                opt_1 = strtok(NULL," ");
                if(opt_1==NULL)
                {
                    printf("%s\n",getenv("PWD"));
                }
                else
                {
                    char temp[1024];

                    if(!strcmp(opt_1,"-"))
                    {
                        chdir(getenv("OLDPWD"));
                        setenv("PWD", getenv("OLDPWD"),1);
                    }
                    else
                    {
                        if(chdir(opt_1)==-1)
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
            
            else if(!strcmp(opt_1,"clr"))
            {
                printf("\033c");
            }
           //Aviso: Si pones echo hola$PWD no va a parsear el $, la salida sera hola$PWD 
            else if (!strcmp(opt_1,"echo"))
            {
                opt_1 = strtok(NULL," ");
            if(opt_1!=NULL)
                {
                    char    *temp;
                    int i=0,
                        j=0,
                        flag_$=0;
                    while (opt_1!=NULL)
                    {
                        temp= (char*) calloc(1024,sizeof(char));
                        
                        if (opt_1[j]!='$')
                        {
                            j=0;
                        }
                        i=0;
                        while (opt_1[j]!='\000' && (opt_1[j]!='$'||(!flag_$))) 
                        {   
                            if (opt_1[0]!='$' || flag_$) 
                            {
                                temp[i]=opt_1[j];
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
                        if (opt_1[j]=='\000') 
                        {
                            opt_1=strtok(NULL," ");
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
                    while (opt_1!=NULL)
                    {
                        if (i!=0)
                        {
                            temp1=(char**) realloc(temp1,sizeof(char*)*(i+1));
                        }
                       temp1[i]=opt_1;
                       opt_1= strtok(NULL, " ");
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

    return 0;
}

int ejecutor(char **temp, int args){
    char *aux;
    aux=(char*) malloc(sizeof(char)*512);
    aux=strrchr(temp[0],'/');
    aux++;
    switch (args-1) {
        case 0:
            if(execl(temp[0],aux,(char *)0)!=-1)
                return 0;
            else 
            {
                temp[0]=strcat(temp[0],getenv("PWD"));
                if (execl(temp[0],aux,(char *)0)!=-1) 
                    return 0;
                else 
                    return -1;
            }
            break;
        case 1:
            if(execl(temp[0],aux,temp[1],(char *)0)!=-1)
                return 0;
            else 
            {
                temp[0]=strcat(temp[0],getenv("PWD"));
                if (execl(temp[0],aux,temp[1],(char *)0)!=-1) 
                    return 0;
                else 
                    return -1;
            }
            break;
        case 2:
            if(execl(temp[0],aux,temp[1],temp[2],(char *)0)!=-1)
                return 0;
            else 
            {
                temp[0]=strcat(temp[0],getenv("PWD"));
                if (execl(temp[0],aux,temp[1],temp[2],(char *)0)!=-1) 
                    return 0;
                else 
                    return -1;
            }
            break;
        case 3:
            if(execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1)
                return 0;
            else 
            {
                temp[0]=strcat(temp[0],getenv("PWD"));
                if (execl(temp[0],aux,temp[1],temp[2],temp[3],(char *)0)!=-1) 
                    return 0;
                else 
                    return -1;
            }
            break;
    }
    return -1;
}
