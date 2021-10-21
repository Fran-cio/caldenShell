#include "./include/linea_de_comandos.h"
#include "./include/leer_desde_script.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char** argv) 
{   
    /*
     * Da mensaje de bienvenida 
     */
    print_mensaje_de_intro();
    /*
     *  Recibe el arg1, que si es un archivo valido, lo abra y ejecute 
     */
    if(ejecutar_script(argv[1]))
    {
        //esto esta asi para que si entra, no ejecute lo siguiente   
    }
    else
    {
        while(1)
        {
            char *comando;      //los comandos ingresados se almacenan aqui
            /*
             * La funcion devuelve un mensaje ingresado por teclado
             */
            comando=linea();
            //Mando el comando a ser ejecutado
            comandos(comando);
        }
    }
    return 0;
}

