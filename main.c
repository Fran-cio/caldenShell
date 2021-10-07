#include "./include/linea_de_comandos.h"
#include "./include/segundo_plano.h"
#include "./include/leer_desde_script.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char** argv) 
{   
    int background_flag;

    setear_entorno();

    if (fopen(argv[1],"r")!=NULL)
    {
        ejecutar_script(argv[1]);
    }
    else
    {
        while(1)
        {
            background_flag=0; 
            char *comando;

            comando=linea();

            background_flag=segundo_plano(comando); 
            if(!background_flag)
            {
                 comandos(comando);
            }
        }
    }
    return 0;
}

