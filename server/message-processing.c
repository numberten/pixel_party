#include <arpa/inet.h>
#include "message-processing.h"
#include "player.h"
#include <stdio.h>

//Prototypes for catching valid udp messages.
int client_connecting(char*);
int move_request(char*);
int pong_response(char*);

//Check if the current request came from a listed client.
int check_address(list*, struct sockaddr_in*, socklen_t*, player_struct**);

int process_recvfrom( list **players,
                      char message[], 
                      struct sockaddr_in *client_addr_ptr, 
                      socklen_t *len_ptr) {

  player_struct *client;

  if (pong_response(message)) {
    printf("Caught a pong!\n");
    if (check_address(*players, client_addr_ptr, len_ptr, &client))
      update_timeout(client);
    return 1;
  }
  if (move_request(message)) {
    printf("Caught a move request!\n");
    if (check_address(*players, client_addr_ptr, len_ptr, &client))
      move_player(client, message[4]);
    return 1;
  }
  if (client_connecting(message)) {
    printf("Caught a connection request!\n");
    if (!check_address(*players, client_addr_ptr, len_ptr, &client))
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

//Checks if the request came from a current player.
//Sets *player to that player, if true.
int check_address(list *players, struct sockaddr_in *client_addr, socklen_t *client_addr_len, player_struct **player) {
  if (players == NULL)
    return 0;
  if (!strcmp(inet_ntoa((players->player)->clientaddr.sin_addr), inet_ntoa(client_addr->sin_addr)) &&
      ntohs((players->player)->clientaddr.sin_port) == ntohs(client_addr->sin_port) &&
      (players->player)->clientaddr_len == *client_addr_len) {
    *player = players->player;
    return 1;
  }
  return check_address(players->next, client_addr, client_addr_len, player);
}
