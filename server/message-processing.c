#include <arpa/inet.h>
#include "message-processing.h"
#include <stdio.h>

//Prototypes for catching valid udp messages.
int client_connecting(char*);
int move_request(char*);
int pong_response(char*);

//Protoypes for handling state after a valid message has been received.
void add_player(struct player_struct[], int*, int*, struct sockaddr_in*, socklen_t*);
int check_address(struct player_struct[], int*, struct sockaddr_in*, socklen_t*);
void move_player(struct player_struct*, char);
void update_timeout(struct player_struct*);

int process_recvfrom( struct player_struct players[],
                      int *nplayers,
                      int *max_players,
                      char message[], 
                      struct sockaddr_in *client_addr_ptr, 
                      socklen_t *len_ptr) {
  int i;

  if (pong_response(message)) {
    printf("Caught a pong!\n");
    if (i=check_address(players, nplayers, client_addr_ptr, len_ptr) >= 0)
      update_timeout(&players[i]);
    return 1;
  }
  if (move_request(message)) {
    printf("Caught a move request!\n");
    if (i=check_address(players, nplayers, client_addr_ptr, len_ptr) >= 0)
      move_player(&players[i], message[4]);
    return 1;
  }
  if (client_connecting(message)) {
    printf("Caught a connection request!\n");
    if (check_address(players, nplayers, client_addr_ptr, len_ptr) == -1)
      add_player(players, nplayers, max_players, client_addr_ptr, len_ptr);
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

void add_player(struct player_struct players[], int *nplayers, int *max_players, struct sockaddr_in *client_addr, socklen_t *client_addr_len) {
  if (*nplayers == *max_players - 1)
    //Make room for new player. (Dynamic array? or linked list)
    printf("Making room for new player.\n"); 
  //Add player to players.
  printf("Adding a player!\n");
  (*nplayers)++;
}

int check_address(struct player_struct players[], int *nplayers, struct sockaddr_in *client_addr, socklen_t *client_addr_len) {
  printf("checking address!\n");
  return -1;
}

void move_player(struct player_struct *player, char direction) {
  printf("Direction: %c\n", direction);
}

void update_timeout(struct player_struct *player) {
  printf("Updating the time yo.\n");
}
