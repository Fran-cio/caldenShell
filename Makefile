CC=gcc
CFLAGS=-Wall -Werror -pedantic 
PATHh=./include/
PATHrec=./src/
PATHout=./out/
PATHlib=./lib/
PATHbin=./bin/

my_shell: my_shell.o libtp4.a 
	mkdir -p $(PATHbin)
	$(CC) $(CFLAGS) -o $(PATHbin)my_shell $(PATHout)my_shell.o -L$(PATHlib) -ltp4 

my_shell.o: main.c 
	mkdir -p $(PATHout)
	$(CC) $(CFLAGS) -c main.c
	mv ./main.o $(PATHout)/my_shell.o

cd.o: $(PATHrec)cd.c 
	$(CC) $(CFLAGS) -c $(PATHrec)cd.c
	mv ./cd.o $(PATHout)

echo.o: $(PATHrec)echo.c
	$(CC) $(CFLAGS) -c $(PATHrec)echo.c
	mv ./echo.o $(PATHout)

leer_desde_script.o: $(PATHrec)leer_desde_script.c  $(PATHrec)linea_de_comandos.c
	$(CC) $(CFLAGS) -c $(PATHrec)leer_desde_script.c 
	mv ./leer_desde_script.o $(PATHout)

linea_de_comandos.o: $(PATHrec)linea_de_comandos.c  $(PATHrec)programa_externo.c $(PATHrec)segundo_plano.c
	$(CC) $(CFLAGS) -c $(PATHrec)linea_de_comandos.c 
	mv ./linea_de_comandos.o $(PATHout)
	
programa_externo.o: $(PATHrec)programa_externo.c  
	$(CC) $(CFLAGS) -c $(PATHrec)programa_externo.c 
	mv ./programa_externo.o $(PATHout)

segundo_plano.o: $(PATHrec)segundo_plano.c  $(PATHrec)linea_de_comandos.c
	$(CC) $(CFLAGS) -c $(PATHrec)segundo_plano.c 
	mv ./segundo_plano.o $(PATHout)

libtp4.a: cd.o echo.o leer_desde_script.o linea_de_comandos.o programa_externo.o segundo_plano.o
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)libtp4.a $(PATHout)cd.o $(PATHout)echo.o $(PATHout)leer_desde_script.o $(PATHout)linea_de_comandos.o $(PATHout)programa_externo.o $(PATHout)segundo_plano.o

clean:
	rm -f -d $(PATHlib)* $(PATHlib) $(PATHout)* $(PATHout) $(PATHbin)* $(PATHbin) 




