CC=gcc
CFLAGS=-Wall -Werror -pedantic 
PATHh=./include/
PATHrec=./src/
PATHrec_tp5=./src/tp5/
PATHrec_com=./src/comandos/
PATHout=./out/
PATHlib=./lib/
PATHbin=./bin/

Tp5: $(PATHbin)my_shell
	
my_shell_db: $(PATHout)my_shell.o $(PATHlib)libtp4.a $(PATHlib)lib_comandos.a $(PATHlib)lib_tp5.a 
	$(CC) $(CFLAGS) -g -O2 $(PATHout)my_shell.o -L$(PATHlib) -ltp4 -l_comandos -l_tp5 

$(PATHbin)my_shell: $(PATHout)my_shell.o $(PATHlib)libtp4.a $(PATHlib)lib_comandos.a $(PATHlib)lib_tp5.a 
	mkdir -p $(PATHbin)
	$(CC) $(CFLAGS) -o $(PATHbin)my_shell $(PATHout)my_shell.o -L$(PATHlib) -ltp4 -l_comandos -l_tp5 

$(PATHout)signals.o: $(PATHrec_tp5)signals.c 
	$(CC) $(CFLAGS) -c $(PATHrec_tp5)signals.c
	mv ./signals.o $(PATHout)

$(PATHout)pipe.o: $(PATHrec_tp5)pipe.c 
	$(CC) $(CFLAGS) -c $(PATHrec_tp5)pipe.c
	mv ./pipe.o $(PATHout)

$(PATHlib)lib_tp5.a: $(PATHout)signals.o $(PATHout)pipe.o
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)lib_tp5.a  $(PATHout)signals.o $(PATHout)pipe.o

$(PATHout)my_shell.o: main.c 
	mkdir -p $(PATHout)
	$(CC) $(CFLAGS) -c main.c
	mv ./main.o $(PATHout)/my_shell.o

$(PATHout)cd.o: $(PATHrec_com)cd.c 
	$(CC) $(CFLAGS) -c $(PATHrec_com)cd.c
	mv ./cd.o $(PATHout)

$(PATHout)echo.o: $(PATHrec_com)echo.c
	$(CC) $(CFLAGS) -c $(PATHrec_com)echo.c
	mv ./echo.o $(PATHout)

$(PATHout)clr.o: $(PATHrec_com)clr.c 
	$(CC) $(CFLAGS) -c $(PATHrec_com)clr.c
	mv ./clr.o $(PATHout)

$(PATHout)quit.o: $(PATHrec_com)quit.c
	$(CC) $(CFLAGS) -c $(PATHrec_com)quit.c
	mv ./quit.o $(PATHout)

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

$(PATHlib)lib_comandos.a: $(PATHout)cd.o $(PATHout)echo.o $(PATHout)quit.o $(PATHout)clr.o
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)lib_comandos.a  $(PATHout)cd.o $(PATHout)echo.o $(PATHout)quit.o $(PATHout)clr.o

$(PATHlib)libtp4.a:  $(PATHout)leer_desde_script.o $(PATHout)linea_de_comandos.o $(PATHout)programa_externo.o $(PATHout)segundo_plano.o 
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)libtp4.a $(PATHout)leer_desde_script.o $(PATHout)linea_de_comandos.o $(PATHout)segundo_plano.o $(PATHout)programa_externo.o 

clean:
	rm -f -d $(PATHlib)* $(PATHlib) $(PATHout)* $(PATHout) $(PATHbin)* $(PATHbin) 




