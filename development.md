#Tp4
##Notas de Desarrollo
###1. Command line prompt

* Para mostrar la linea de comandos caracterista de bash utilize printf dandole los colores caracteristicos de la bash original ligeramente distintos, para los parametros del equipo (hostname,username,path) tambien use las herramientas brindadas por las libreria estandar de c.
* Seguido de mostrar la linea con un simple fgets que guarda la entrada por stdin.

###2. Internal commands

1. Para hacer el comando cd, verificamos el argumento en despues de "cd", si este es vacio, devolvemos la variable almacenada en la var env en PWD, si hay un '-', seteamos el directorio actual como lo que este asignado en el env var PWDOLD, que usualmente sera el espacio de trabajo previo a cambiarnos, dicho de otra forma, swapeamos PWD y PWDOLD. Si nos llega un path o una var env (Esto ultimo, marca personal de la casa), verificamos si esto es valido. Si no es valido, imprimimos el error correspondiente a cada uno. Si es valido, cambiamos el directorio actual y actualizamos las variales de entorno.

2. Para hacer el comando clr, se utilizo solamente el comando [ printf("\033c)"](https://stackoverflow.com/questions/47503734/what-does-printf-033c-mean "Whats does printf(\033c) mean"), que segun la fuente adjuntada, resetea la terminal, nos sirve para limpiarla. Otras formas de implemetar esto era usando librerias externas o implemetando un system("clear"), pero opte por esta solucion por simple deconocimiento de las otras herramientas.

3. echo unicamente, imprime lo que le pasemos como comentario, pero como en este proyecto se opto por utilizar la herramienta strtok, hay que manejar un poco la informacion e imprimir la informacion parseada. Tambien detectamos si hay un '$', de ser asi, se intenta imprimir la var env, asociada. Se implemento que se pueda imprimir variables de entorno y comentarios por igual, incluso se pueden agregar var env sin estar separadas por un espacio (ejem: $PWD$HOME), sin embargo esto ultimo no fue implementado con comentarios (es decir, test$PWD, imprimiria exactamente eso)

4. quit (o q, ya que agregue esa opcion), unicamente ejecuta un exit(0), no considere necesario hacer nada mas.

###3. Program Invocation

* Cuando no se encuentra el comando interno, se entra a una subrutina encargada de manejar programas externo. A priori lo unico que hago es dividir la ejecucion y derivar la ejecucion del programa al hijo. En este punto parseo lo informacion ingresada en un arreglo dinamico en la cual almaceno en la primera posicion el programa con su path y el resto de posiciones los argumentos pasados. Ademas se hace un manejo del programa para obtener su nombre. Esto esta implementado para recibir todos los parametros necesarios pero por la limitacion a usar execl, mando unicamente 3 argumentos. Segun tenia entendido, execl aceptaba unicamente path relativos, asi que probaba relativo y si devolvia -1, le concatenaba el PWD. Pero haciendo un par de pruebas resulta que no, que la funcion acepta ambos path.

###4. Batch File

* Siempre que el programa reciba un argumento de ejecucion, verifica si este es un archivo que pueda leer, si es asi, lo abre y empieza a pasarle linea a linea, los comandos en el archivos. Si no es asi, sigue su ejecucion normalemente. El metodo no verifica si el archivo a leer esta en el formato correcto y tampoco genera una salvedad al respecto, eso queda a responsabilidad del que escriba el script.

###5. Background execution

* El programa antes de enviar el comando a ejecutarse verifica si posee un & en su ultima posicion (Recalcar lo de ultima posicion). Este entra a una subrutina donde genera un proceso hijo que se encarga de la ejecucion del comando. Cuando el comando acaba se genera un exit. A todo esto el comando padre se queda en un wait con el fin de evitar procesos zombies.

##Notas al margen

* Fue realmente nutritivo este tp y me quede mas que satisfecho de como quedo. Creo que las funcionalidades quedaron correctamente segmentadas y documentadas. 

* Crei haber terminado el trabajo pero me acorde del cppcheck, lo cual fue un balde de agua ya que me encontro un par de errores que sin ser tan graves no los tuve en cuenta y me fueron utiles para entender determinadas cuestiones
