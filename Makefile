CC=gcc
CFLAGS=-Wall -Werror -pedantic 
PATHh=./include/
PATHrec=./src/
PATHout=./out/
PATHlib=./lib/
PATHbin=./bin/

main: main.o libtp3.a libcjson.so 
	mkdir -p $(PATHbin)
	$(CC) $(CFLAGS) -o $(PATHbin)main $(PATHout)main.o -L$(PATHlib) -ltp3 -ldl -Wl,-rpath,$(PATHlib)

main.o: main.c $(PATHh)function.h
	mkdir -p $(PATHout)
	$(CC) $(CFLAGS) -c main.c
	mv ./main.o $(PATHout)

punto1.o: $(PATHrec)punto1.c $(PATHh)function.h 
	$(CC) $(CFLAGS) -c $(PATHrec)punto1.c
	mv ./punto1.o $(PATHout)

punto2.o: $(PATHrec)punto2.c $(PATHh)function.h
	$(CC) $(CFLAGS) -c $(PATHrec)punto2.c
	mv ./punto2.o $(PATHout)

cJSON.o: $(PATHrec)cJSON.c
	$(CC) $(CFLAGS) -c $(PATHrec)cJSON.c
	mv ./cJSON.o $(PATHout)

filesystem.o: $(PATHrec)filesystem.c 
	$(CC) $(CFLAGS) -c $(PATHrec)filesystem.c
	mv ./filesystem.o $(PATHout)

libtp3.a: punto1.o punto2.o cJSON.o
	mkdir -p $(PATHlib) 
	ar cr $(PATHlib)libtp3.a $(PATHout)punto1.o $(PATHout)punto2.o $(PATHout)cJSON.o 

libcjson.so: filesystem.o cJSON.o
	$(CC) $(CFLAGS) -shared -fPIC -o libcjson.so $(PATHout)filesystem.o $(PATHout)cJSON.o 
	mv ./libcjson.so $(PATHlib)

clean:
	rm -f -d $(PATHlib)* $(PATHlib) $(PATHout)* $(PATHout) $(PATHbin)* $(PATHbin) 




