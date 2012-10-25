CC=gcc
CFLAGS=-I.
APP=Wator

build: main.o
	$(CC) -o $(APP) main.o $(CFLAGS)

clean:
	rm *.o
	rm $(APP)