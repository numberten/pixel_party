#include <arpa/inet.h>
#include "message-processing.h"
#include <stdio.h>

//Prototypes for catching valid udp messages.
int client_connecting(char*);
int move_request(char*);
int pong_response(char*);

//Protoypes for handling state after a valid message has been received.
void add_player(list**, struct sockaddr_in*, socklen_t*);
int check_address(list**, struct sockaddr_in*, socklen_t*, player_struct*);
void move_player(list**, char);
void update_timeout(player_struct*);

int process_recvfrom( list **players,
                      char message[], 
                      struct sockaddr_in *client_addr_ptr, 
                      socklen_t *len_ptr) {

  player_struct *client;

  if (pong_response(message)) {
    printf("Caught a pong!\n");
    if (check_address(players, client_addr_ptr, len_ptr, client))
      update_timeout(client);
    return 1;
  }
  if (move_request(message)) {
    printf("Caught a move request!\n");
    if (check_address(players, client_addr_ptr, len_ptr, client))
      move_player(players, message[4]);
    return 1;
  }
  if (client_connecting(message)) {
    printf("Caught a connection request!\n");
    if (check_address(players, client_addr_ptr, len_ptr, client))
      add_player(players, client_addr_ptr, len_ptr);
    return 1;
  }
  printf("[Error]: Unresolved udp message from %s:%d.\n", inet_ntoa(client_addr_ptr->sin_addr), ntohs(client_addr_ptr->sin_port));
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

void add_player(list **players, struct sockaddr_in *client_addr, socklen_t *client_addr_len) {
  printf("add_player call.\n");
}

int check_address(list **players, struct sockaddr_in *client_addr, socklen_t *client_addr_len, player_struct *player) {
  printf("checking address!\n");
  return 1;
}

void move_player(list **player, char direction) {
  printf("Direction: %c\n", direction);
}

void update_timeout(player_struct *player) {
  printf("Updating the time yo.\n");
}
