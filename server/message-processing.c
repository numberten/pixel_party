#include <arpa/inet.h>
#include "message-processing.h"
#include <stdio.h>

int pong_response(char*);
int move_request(char*);
int client_connecting(char*);

int process_recvfrom( struct player_struct cliaddr_list[],
                      char message[], 
                      struct sockaddr_in *client_addr_ptr, 
                      socklen_t *len_ptr) {

  if (pong_response(message)) {
    printf("Caught a pong!\n");
    return 1;
  }
  if (move_request(message)) {
    printf("Caught a move request!\n");
    return 1;
  }
  if (client_connecting(message)) {
    printf("Caught a connection request!\n");
    return 1;
  }
  printf("[Error]: Unresolved udp message from %s:%d.\n", inet_ntoa(client_addr_ptr -> sin_addr), ntohs(client_addr_ptr -> sin_port));
  return 0;
}

int pong_response(char message[]) {
  return 0 == strncmp("PONG", message, 4);
}

int move_request(char message[]) {
  return (0 == strncmp("MOVEN", message, 5) ||
          0 == strncmp("MOVES", message, 5) ||
          0 == strncmp("MOVEW", message, 5) ||
          0 == strncmp("MOVEE", message, 5));
}
    
int client_connecting(char message[]) {
  return 0 == strncmp("HELLO", message, 5);
}
