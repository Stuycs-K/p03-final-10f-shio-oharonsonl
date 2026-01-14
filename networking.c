#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>

void err(int i, char *msg) {
  if (i < 0) {
    printf("Error: %s - %s\n", msg, strerror(errno));
    exit(1);
  }
}

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

ssize_t recv_cstring(int sock, char *buf, size_t max) {
  size_t i = 0;
  while (i + 1 < max) {
    char c;
    ssize_t n = recv(sock, &c, 1, 0);
    if (n == 0) return 0;
    if (n < 0) {
      if (errno == EINTR) continue;
      return -1;
    }
    buf[i++] = c;
    if (c == '\0') return (ssize_t)i;
  }
  buf[max - 1] = '\0';
  return (ssize_t)max;
}
