#ifndef server_h
#define server_h
void subserver_logic(int client_socket, char *id);
static void sighandler(int signo);
char determine_opps(char * states, char * id);
#endif
