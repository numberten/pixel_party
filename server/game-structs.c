#include "game-structs.h"
#include <stdlib.h>
#include <stdio.h>

//Functions to deallocate memory for game-structs.

void free_pixel(struct pixel_struct *pixel) {
  printf("in free pixel man\n");
  free(pixel->red);
  free(pixel->green);
  free(pixel->blue);
  printf("middle of free pixel man\n");
  free(pixel->x);
  free(pixel->y);
  free(pixel);
  printf("leaving free pixel man\n");
}

void free_player(player_struct *player) {
  printf("in free_player man\n");
  free_pixel(player->pixel);
  printf("before old free not mallocs?\n");
  free(player->clientaddr);
  free(player->clientaddr_len);
  free(player->last_pong);
  printf("after old free not mallocs?\n");
  free(player);
  printf("after free_player\n");
}

void initialize_pixel(struct pixel_struct *pixel) {
  pixel->red = malloc(sizeof(unsigned short));
  pixel->green = malloc(sizeof(unsigned short));
  pixel->blue = malloc(sizeof(unsigned short));
  pixel->x = malloc(sizeof(unsigned short));
  pixel->y = malloc(sizeof(unsigned short));
}
