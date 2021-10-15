CC=gcc
CFLAGS=-Wall -Werror -pedantic 
PATHh=./include/
PATHrec=./src/
PATHout=./out/
PATHlib=./lib/
PATHbin=./bin/

Tp4: $(PATHbin)my_shell

$(PATHbin)my_shell: $(PATHout)my_shell.o $(PATHlib)libtp4.a 
	mkdir -p $(PATHbin)
	$(CC) $(CFLAGS) -o $(PATHbin)my_shell $(PATHout)my_shell.o -L$(PATHlib) -ltp4 

$(PATHout)my_shell.o: main.c 
	mkdir -p $(PATHout)
	$(CC) $(CFLAGS) -c main.c
	mv ./main.o $(PATHout)/my_shell.o

$(PATHout)cd.o: $(PATHrec)cd.c 
	$(CC) $(CFLAGS) -c $(PATHrec)cd.c
	mv ./cd.o $(PATHout)

$(PATHout)echo.o: $(PATHrec)echo.c
	$(CC) $(CFLAGS) -c $(PATHrec)echo.c
	mv ./echo.o $(PATHout)

$(PATHout)leer_desde_script.o: $(PATHrec)leer_desde_script.c  
	$(CC) $(CFLAGS) -c $(PATHrec)leer_desde_script.c 
	mv ./leer_desde_script.o $(PATHout)

$(PATHout)linea_de_comandos.o: $(PATHrec)linea_de_comandos.c 
	$(CC) $(CFLAGS) -c $(PATHrec)linea_de_comandos.c 
	mv ./linea_de_comandos.o $(PATHout)
	
$(PATHout)programa_externo.o: $(PATHrec)programa_externo.c  
	$(CC) $(CFLAGS) -c $(PATHrec)programa_externo.c 
	mv ./programa_externo.o $(PATHout)

$(PATHout)segundo_plano.o: $(PATHrec)segundo_plano.c  
	$(CC) $(CFLAGS) -c $(PATHrec)segundo_plano.c 
	mv ./segundo_plano.o $(PATHout)

$(PATHlib)libtp4.a: $(PATHout)cd.o $(PATHout)echo.o $(PATHout)leer_desde_script.o $(PATHout)linea_de_comandos.o $(PATHout)programa_externo.o $(PATHout)segundo_plano.o
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)libtp4.a $(PATHout)cd.o $(PATHout)echo.o $(PATHout)leer_desde_script.o $(PATHout)linea_de_comandos.o $(PATHout)segundo_plano.o $(PATHout)programa_externo.o 

clean:
	rm -f -d $(PATHlib)* $(PATHlib) $(PATHout)* $(PATHout) $(PATHbin)* $(PATHbin) 




