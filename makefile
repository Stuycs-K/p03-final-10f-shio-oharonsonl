.PHONY: server-run client-run server-compile client-compile clean
server-run: server
	@./server
client-run: client
	@./client
server-compile server: server.o networking.o sema.o
	@gcc -o server server.o networking.o sema.o
client-compile client: client.o networking.o sema.o
	@gcc -o client client.o networking.o sema.o
sema.o: sema.c sema.h
	@gcc -c sema.c
networking.o: networking.c networking.h
	@gcc -c networking.c
client.o: client.c networking.h sema.h
	@gcc -c client.c
server.o: server.c networking.h sema.h
	@gcc -c server.c
clean:
	@rm -f *.o
	@rm -f server
	@rm -f client
