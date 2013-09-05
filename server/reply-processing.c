#include <stdio.h>
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
