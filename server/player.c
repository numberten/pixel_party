#include "player.h"
#include <stdlib.h>
#include <stdio.h>

#define U_SHORT unsigned short

void generate_pos(U_SHORT*, U_SHORT*);
void generate_rgb(U_SHORT*, U_SHORT*, U_SHORT*);

void add_player(list **players, struct sockaddr_in *client_address, socklen_t *client_address_len) {
  struct pixel_struct *new_pixel;
  player_struct *new_player;

  printf("Adding a player..\n");

  new_pixel = malloc(sizeof(struct pixel_struct));
  generate_pos(&(new_pixel->x), &(new_pixel->y)); 
  generate_rgb(&(new_pixel->red), &(new_pixel->green), &(new_pixel->blue));

  new_player = malloc(sizeof(player_struct));
  new_player->pixel = *new_pixel;
  new_player->clientaddr = *client_address;
  new_player->clientaddr_len = *client_address_len;

  insert_list(players, *new_player);
}

void move_player(list **players, char direction) {
  printf("moving player called!\n");
}

void update_timeout(player_struct *player) {
  printf("update_timeout called!\n");
}

void generate_pos(U_SHORT *x_ptr, U_SHORT *y_ptr) {
  printf("generate_pos...\n");
}

void generate_rgb(U_SHORT *red_ptr, U_SHORT *green_ptr, U_SHORT *blue_ptr) {
  printf("generate_rgb...\n");
}

