#include "networking.h"

int server_setup() {
  struct addrinfo *hints, *results;
  hints = malloc(sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "43267", hints, &results);

  int server_socket =
      socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  int yes = 1;
  int sockOpt = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt, "sockopt  error");

  bind(server_socket, results->ai_addr, results->ai_addrlen);
  listen(server_socket, 1);
  free(hints);
  freeaddrinfo(results);

  return server_socket;
}

int server_tcp_handshake(int listen_socket) {
  int client_socket = accept(listen_socket, NULL, NULL);

  return client_socket;
}

int client_tcp_handshake(char *server_addr) {
  struct addrinfo *hints, *results;
  hints = malloc(sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  getaddrinfo(server_addr, "43267", hints, &results);

  int server_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  connect(server_socket, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);

  return server_socket;
}
