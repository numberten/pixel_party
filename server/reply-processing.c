#include <stdio.h>
#include <string.h>
#include "reply-processing.h"

//All functions set str_ptr to the proper response.
//str_ptr will be used in main()'s sendto call.
void error_message(char *str_ptr) {
  snprintf(str_ptr, 40, "ERROR\n");
}

void move_message(char direction, char *str_ptr) {
  switch (direction) {
    case 'N':
      snprintf(str_ptr, 40, "ACK MOVE NORTH\n");
      break;
    case 'S':
      snprintf(str_ptr, 40, "ACK MOVE SOUTH\n");
      break;
    case 'E':
      snprintf(str_ptr, 40, "ACK MOVE EAST\n");
      break;
    case 'W':
      snprintf(str_ptr, 40, "ACK MOVE WEST\n");
      break;
  }
}

void pong_message(char *str_ptr) {
  snprintf(str_ptr, 40, "PONG ACK\n");
}

void welcome_message(player_struct *player, char *str_ptr) {
  unsigned short x, y, r, g, b;

  x = *player->pixel->x;
  y = *player->pixel->y;
  r = *player->pixel->red;
  g = *player->pixel->green;
  b = *player->pixel->blue;

  snprintf(str_ptr, 40, "WELCOME: x:%hu,y:%hu,r:%hu,g:%hu,b:%hu\n", x, y, r, g, b);
  return ;
}

//Generate the grid message with pixel data of all connected clients.
void grid_message(list *players) {
  unsigned short x, y, r, g, b;
  list *p = players;
  char temp[1000];
  char str_ptr[1000];

  strcpy(temp, "");
  while (p != NULL) {
    x = *p->player->pixel->x;
    y = *p->player->pixel->y;
    r = *p->player->pixel->red;
    g = *p->player->pixel->green;
    b = *p->player->pixel->blue;
    snprintf(str_ptr, 40, "%hu,%hu,%hu,%hu,%hu$\n", x, y, r, g, b);
    strcat(temp, str_ptr);
    p = p->next;
  }
  snprintf(str_ptr, 1000, "%s", temp);
  p = players;

  //sendto the grid message to all clients.
  while (p != NULL) {
    sendto(*p->player->socket, str_ptr, strlen(str_ptr), 0, (struct sockaddr *) p->player->clientaddr, sizeof(*p->player->clientaddr));
    p = p->next;
  }
}

