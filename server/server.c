#include <sys/socket.h>
#include "game-structs.h"
#include "message-processing.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int sockfd, n, i = -1, max_clients = 10;
  struct sockaddr_in servaddr, client_address;
  socklen_t len;
  char mesg[1000];
  struct player_struct players[max_clients];

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(32000);
  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  while (1) {
    len = sizeof(client_address);
    n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *) &client_address, &len);
    printf("i: %d\n", i);
    process_recvfrom(players, &i, &max_clients, mesg, &client_address, &len);
    sendto(sockfd, mesg, n, 0, (struct sockaddr *) &client_address, sizeof(client_address));
    printf("-------------------------------------------------------\n");
    mesg[n] = 0;
    printf("Received the following:\n%s", mesg);
    printf("-------------------------------------------------------\n");
  }
} 

//TODO: Add client tracking for multiple clients.
//    - Store in linked list or dynamic array.
//    - Add message-appropriate replies.
//    - Add board grid.
//    - Add timeout handling.
