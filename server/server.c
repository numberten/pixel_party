#include <sys/socket.h>
#include "linked_list.h"
#include "message-processing.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int sockfd, n;
  struct sockaddr_in servaddr, client_address;
  socklen_t len;
  char mesg[10];
  list *end = NULL;
  list **players = &end;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(32000);
  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  while (1) {
    len = sizeof(client_address);
    n = recvfrom(sockfd, mesg, 10, 0, (struct sockaddr *) &client_address, &len);
    process_recvfrom(players, mesg, &client_address, &len);
    sendto(sockfd, mesg, n, 0, (struct sockaddr *) &client_address, sizeof(client_address));
    printf("-------------------------------------------------------\n");
    mesg[n] = 0;
    printf("Received the following:\n%s", mesg);
    printf("-------------------------------------------------------\n");
  }
} 

//TODO: 
//    - Add message-appropriate replies.
//    - Add board grid.
//    - Add timeout handling.
