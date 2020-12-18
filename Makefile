# Makefile for TCP project

all: sender Measure client server

Measure: Measure.c
	gcc -o Measure Measure.c

sender: sender.c
	gcc -o sender sender.c

clean:
	rm -f *.o Measure senderclient server

runs:
	./Measure

runc:
	./sender

runs-strace:
	strace -f ./Measure

runc-strace:
	strace -f ./sender
	
client: client.c
	gcc -o client client.c

server: server.c
	gcc -o server server.c

