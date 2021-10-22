Para instalar el programa ejecute:
``` bash
❯ make
```
Si el programa no lanza ningun error, el programa se instalo con exito.

El ejecutable se encuentra en la carpeta */bin* y se llama my_shell, y es cuention de ejecutarlo como cualquier programa:

``` bash
❯ bin/my_shell
```
Ejecutando el comando help puede ver un resumen de los comandos e implementaciones:

*clr: Limpia la consola*

*echo <comando|env path>: imprime por pantalla el argumento*

*cd <path>: Coloca el directorio de trabajo en el path asignado*

*quit: cierra la consola*

*Puede ingresar el path de un programa para ejecutarlo*

*Puede ejecutar My_Shell con el path de un script de la manera ./myshell 'script'*

Ademas en la version de tp5 se agrega:

*Funcionalidad de multiples pipe's "comando1 | comando2 ", con el cual conectamos la salida std de comando1 con la entrada std de comando2*

*Redireccion de entrada (<) salida (>).*

### Bugs:
* echo no parsea texto$varenv sin separar
* Algunas entradas de texto muy especificas generan un *malloc(): Invalid size (unsorted)*
* Hacer la combinacion Ctrl-D, genera que el programa deje de pedir input y genere un bucle que solo se puede salir cerrando la pestaña. 
