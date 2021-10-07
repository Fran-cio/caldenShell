#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void retornar();
void setear_directorio();

void cd(char *comando){
    comando = strtok(NULL," ");
    if(comando==NULL)
    {
        printf("%s\n",getenv("PWD"));
    }
    else
    {
        if(!strcmp(comando,"-"))
        {
            retornar();
        }
        else
        {
            if(chdir(comando)==-1)
            {
                printf("Ruta invalida\n"); 
            }
            else
            {
                setear_directorio();
            }
        }
    }
}

void setear_directorio(void)
{
    char actual_path[1024];

    getcwd(actual_path,1024);
    setenv("OLDPWD", getenv("PWD"),1);
    setenv("PWD", actual_path,1);

    return;
}

void retornar(void){
    chdir(getenv("OLDPWD"));
    setenv("PWD", getenv("OLDPWD"),1);

    return;
}
