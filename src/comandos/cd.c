#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void retornar();
void setear_directorio();

void cd(char *comando){
    /*
     *  Pedimos el siguiente token del comando que se supone que es el path que se
     *  exige
     */
    comando = strtok(NULL," "); 

    if(comando==NULL)// Si el comando es "cd" devolvemos el espacio de trabajo actual
    {
        printf("%s\n",getenv("PWD"));
    }
    else
    {
        if(!strcmp(comando,"-"))
        {
            /*
             *  Si el comando es "cd -" retornamos el PWD a OLDPWD
             */
            retornar();
        }
        else
        {
            if(comando[0]=='$') //Si el primer char es '$' se trata de una var env
            {
                comando++;//movemos el puntero descartando '$'
                if(chdir(getenv(comando))==-1)
                {
                    /*
                     *  Se intenta cambiar el PWD y si no se puede se especifica
                     */
                    perror("Entorno invalido"); 
                }
                else
                {
                    setear_directorio();
                }   
            }
            /*
             * Sino es una var env, se deberia tratar del path o el dir
             * al que se quiere cambiar, y se hace lo mismo que antes
             */
            else if(chdir(comando)==-1)
            {
                perror("Ruta invalida"); 
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
    char temp[1024]; //La memoria reservada para la variable busca solamente no quedarse corta 

    getcwd(temp,1024); //guardo el entorno de trabajo actual y lo guardo en temp
    setenv("OLDPWD", getenv("PWD"),1); //Swapeo el entorno OLDPWD con el anterior
    setenv("PWD", temp,1); //actualizo la variable de entorno PWD

    return;
}

void retornar(void){
    /*
     *  Seteamos el espacio de trabajo con lo almacenado en la var env OLDPWD
     */ 
    chdir(getenv("OLDPWD"));
    setear_directorio();

    return;
}
