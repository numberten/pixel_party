#include "colors.h"
#include "player.h"
#include <stdlib.h>
#include <stdio.h>

void generate_pos(U_SHORT*, U_SHORT*);

void add_player(list **players, struct sockaddr_in *client_address, socklen_t *client_address_len) {
  struct pixel_struct *new_pixel;
  player_struct *new_player;

  printf("Adding a player..\n");

  new_pixel = malloc(sizeof(struct pixel_struct));
  initialize_pixel(new_pixel);

  generate_pos(new_pixel->x, new_pixel->y); 
  generate_rgb(new_pixel->red, new_pixel->green, new_pixel->blue);

  printf("\tRed: %.3hu\n\tGreen: %.3hu\n\tBlue: %.3hu\n", *(new_pixel->red), *(new_pixel->green), *(new_pixel->blue));
  printf("\n\tX: %.2hu\n\tY: %.2hu\n", *(new_pixel->x), *(new_pixel->y));

  new_player = malloc(sizeof(player_struct));
  new_player->pixel = new_pixel;
  new_player->clientaddr = *client_address;
  new_player->clientaddr_len = *client_address_len;

  insert_list(players, new_player);
}

void move_player(player_struct *player, char direction) {
  struct pixel_struct *current_pixel;
  current_pixel = player->pixel;

  printf("Found the old client, and moving his pixel now!\n");

  printf("\tOld X: %.2hu\n\tOld Y: %.2hu\n", *(current_pixel->x), *(current_pixel->y));
  if (direction == 'N' && *current_pixel->y > 0) {
    *current_pixel->y -= 1;
    printf("\tNew X: %.2hu\n\tNew Y: %.2hu\n", *(current_pixel->x), *(current_pixel->y));
    return;
  }
  if (direction == 'S' && *current_pixel->y < 49) {
    *current_pixel->y += 1;
    printf("\tNew X: %.2hu\n\tNew Y: %.2hu\n", *(current_pixel->x), *(current_pixel->y));
    return;
  }
  if (direction == 'W' && *current_pixel->x > 0) {
    *current_pixel->x -= 1;
    printf("\tNew X: %.2hu\n\tNew Y: %.2hu\n", *(current_pixel->x), *(current_pixel->y));
    return;
  }
  if (direction == 'E' && *current_pixel->x < 49) {
    *current_pixel->x += 1;
    printf("\tNew X: %.2hu\n\tNew Y: %.2hu\n", *(current_pixel->x), *(current_pixel->y));
    return;
  }
}


void update_timeout(player_struct *player) {
  printf("update_timeout called!\n");

  //printf("printing the red value in this player: %.3hu\n", *(player->pixel).red);
}

void generate_pos(U_SHORT *x_ptr, U_SHORT *y_ptr) {
  printf("generating_position...\n");
  
  *x_ptr = rand() % 50;
  *y_ptr = rand() % 50;
  // Note these random numbers aren't uniformly random.
}


