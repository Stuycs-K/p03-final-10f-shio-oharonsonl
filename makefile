.PHONY: server-run client-run server-compile client-compile clean
server-run: server
	@./server
client-run: client
	@./client
server-compile server: server.o networking.o
	@gcc -o server server.o
client-compile: client.o networking.o
	@gcc -o client client.o
networking.o: networking.c networking.h
	@gcc -c networking.c
client.o: client.c networking.h
	@gcc -c client.c
server.o: server.c networking.h
	@gcc -c server.c
clean:
	@rm -r *.o
	@rm -r server
	@rm -r client
