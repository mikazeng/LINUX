all:server 
server:wrap.o server.o
	gcc server.o  wrap.o -o server
wrap.o:
	gcc wrap.c -o wrap.o
server.o:
	gcc server.c -o server.o
