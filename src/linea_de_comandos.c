#include "../include/comandos/echo.h"
#include "../include/comandos/cd.h"
#include "../include/comandos/quit.h"
#include "../include/comandos/clr.h"
#include "../include/programa_externo.h"
#include "../include/segundo_plano.h"
#include "../include/colorines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_mensaje_de_intro();
void help(void);
void dormir(char*);

void comandos_linea(char* comando)
{
    /*
     *  Elimino el caracter '\n' y parseo el comando
     */
    comando[strcspn(comando, "\n")] = '\000';
    comando=strtok(comando," ");

    if(comando!=NULL) //Si el comando se ingreso, entramos al if
    {
        /*
         *  El comando quit solamente ejecuta exit y de manera correcta y 
         *  cierra la ejecucion
         */
        if(!strcmp(comando,"quit")||!strcmp(comando,"q"))
        {
            quit();
        }

        /*
         *  El comando cd recibe un path o variable de entorno y la asigna al
         *  espacio actual.
         */
        else if(!strcmp(comando,"cd"))
        {
            cd(comando);
        }
        /*
         *  El comando clr, limpia la terminal
         */
        else if(!strcmp(comando,"clr"))
        {
            clr();
        }
        /*
         *  El comando echo escribe en pantalla un comentario o devuelve una
         *  var env
         */
        //Aviso: Si pones echo hola$PWD no va a parsear el $, la salida sera hola$PWD 
        else if (!strcmp(comando,"echo"))
        {
            echo(comando); 
        }
        else if (!strcmp(comando,"help"))
        {
            help(); 
        }
        else 
        {
            /*
             * Si no se matcheo ningun comando interno, se da por hecho que es un
             * comando externo enviado por dir relativo o absoluto
             */
            programa_externo(comando);
        }
    }   
}
void comandos(char *comando)
{

    int background_flag=0;  //La flag se inicia en 0 
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
        comandos_linea(comando);
    }

}

char* get_hostname()
{
    /* creo una variable hostname donde voy a guardar dicho parametro y con
     * gethostname lo obtengo, esta decision de diseño no es la mejor ya que
     * cada vez que se genere una linea de comandos, recalculo esta variable.
     * Seria mas sencillo crear una varable global o pasarle esto como parametro
     * pero quise dejar el main lo mas limpio posible[1]
     */
    char* hostname=(char*) malloc(sizeof(char)*20);
    gethostname(hostname, 20);

    return hostname;
}

char* linea()
{  
    /*
     * genero una variable donde guardar el comando, imprimo el mensaje de la
     * linea de comando (de ahi el nombre del metodo),
     */
    char *comando;
    comando= (char*) malloc(sizeof(char)*1024);

    char *hostname=get_hostname();
    printf( ANSI_COLOR_YELLOW "\r%s@%s" ANSI_COLOR_RESET ":" 
            ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
            getlogin(),hostname,getenv("PWD"));
    free(hostname);

    fgets(comando,1024,stdin);

    return comando;
}

/*
 * Se ilustran los comandos disponibles y las funcionalidades
 */
void help(void)
{
    printf("Por favor ingrese uno de los siguiente comandos:"
            "\n\tclr: Limpia la consola"
            "\n\techo <comando|env path>: imprime por pantalla el argumento"
            "\n\tcd <path>: Coloca el directorio de trabajo en el path asignado"
            "\n\tquit: cierra la consola"
            "\nPuede ingresar el path de un programa para ejecutarlo"
            "\nPuede ejecutar My_Shell con el path de un script de la manera ./myshell <script>\n");
}

/*
 *  Un pequeño mensaje de bienvenida a la shell
 */
void print_mensaje_de_intro(void)
{
    printf( "\n/*------------------------------------------------------------------------------------------*"
            "\n *\tCalden-shell es la primera shell desarrollada al 100 en la Pampa (O eso creeria)"
            "\n *\tcreada por Francisco Ciordia Cantarella para la materia de Sistemas"
            "\n *\toperativos 1."
            "\n *\t"
            "\n *\tPor favor, ingresa help para ver las funciones disponible."
            "\n */------------------------------------------------------------------------------------------*\n\n");
}
