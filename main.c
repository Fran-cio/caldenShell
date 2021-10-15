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
    int background_flag;        //Si hay un proceso corriendo en segundo plano, se activa

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
            background_flag=0;  //La flag se inicia en 0 
            char *comando;      //los comandos ingresados se almacenan aqui

            /*
             * La funcion devuelve un mensaje ingresado por teclado
             */
            comando=linea();
            /*
             * Verifica si efectivamente el comando tiene la orden de ser
             * ejecutado en 2do plano
             */
            background_flag=segundo_plano(comando); 
            /*
             *  Contrario al criterio de dejar el main lo mas limpio posible[1]
             *  aca tome la decision usar efectivamente la variable background_flag
             *  porque considere que era mas ilustrativo para que se vea su funcion
             *  en lugar de hacer simplemente if(!segundo_plano(comando))
             *  lo cual hubiera sintetizado el codigo y eliminado esa variable
             *  pero sin duda hubiera sido mas dificil de seguir.
             */
            if(!background_flag)
            {
                /*
                 *  Si la background_flag esta en bajo, el comando se ejecuta con
                 *  normalidad y se manda lo ingresado a la funcion encargada
                 */
                comandos(comando);
            }
        }
    }
    return 0;
}

