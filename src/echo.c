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
    if(comando!=NULL)
    {
        while (comando!=NULL)
        {
            comando=imprimir_mensajes(comando);
        }
        printf("\n");
    }

}
char* imprimir_mensajes(char *comando)
{
    temp= (char*) calloc(1024,sizeof(char));

    if ((comando[j]!='$'||comando[j-1]=='\000'))
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
        if (getenv(temp)!=NULL) {
            printf("%s ",getenv(temp));
        }
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
    return comando;
}
