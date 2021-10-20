#include "./include/tp5/signals.h"

#include "./include/linea_de_comandos.h"
#include "./include/leer_desde_script.h"

#include <string.h>

int main(int argc,char** argv) 
{   
    set_func_sig(SIG_IGN); //Con este comando, el programa ignora las señales externas

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
            comando[strcspn(comando, "\n")] = '\000';
        
            comandos(comando);
        }
    }
    return 0;
}

