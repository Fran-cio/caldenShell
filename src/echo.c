#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* imprimir_mensajes(char *comando);

char    *temp;
int i=0,
    j=0,
    flag_$=0;

void echo(char *comando)
{
    comando = strtok(NULL," ");
    if(comando!=NULL) //Si el mensaje esta vacio, no hace nada
    {
        while (comando!=NULL) //Se ejecuta la funcion imprimir_mensajes mientras haya texto
        {
            comando=imprimir_mensajes(comando);
        }
        printf("\n");
    }

}
char* imprimir_mensajes(char *comando)
{
    temp= (char*) calloc(1024,sizeof(char));
    /*
     *  Existe la posiblidad de que se impriman 2 var env sin espacio, entonces
     *  para hace esto me fijo si el caracter "j" no es un '$' o si se trata de
     *  un primer caracter. Si esto es asi, reinicio la el parseo de carcteres
     */
    if ((comando[j]!='$'||comando[j-1]=='\000'))
    {
        j=0;
    }
    i=0;
    while (comando[j]!='\000' && (comando[j]!='$'||(!flag_$))) 
    {   
        /*
         *  Si el primer caracter es un '$' levanto la flag de env var e ignoro
         *  ese primer caracter
         */
        if (comando[0]!='$' || flag_$) 
        {
            /* 
             * Los caracteres se agregan 1 a 1, cada uno con su puntero
             */
            temp[i]=comando[j];
            i++;
        }
        else
        {
            flag_$=1;
        }
        j++;
    }
    if (flag_$)
    {  
        /*
         * Si el flag de env var esta en alto intento imprimir el entorno pedido
         */
        if (getenv(temp)!=NULL) {
            printf("%s ",getenv(temp));
        }
        /*
         *  Sino, no se imprime nada y se baja el flag
         */
        flag_$=0;
    }
    else 
    {
        /*
         *  Si la flag esta baja, directamente se imprime el mensaje
         */
        printf("%s ",temp);
    }
    if (comando[j]=='\000') 
    {
        /*
         * No hay mas caracteres en esta palabra, paso al siguiente toke
         */
        comando=strtok(NULL," ");
    }
    free(temp);
    return comando;
}
