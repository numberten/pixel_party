#include "game-structs.h"
#include <stdlib.h>

//Functions to deallocate memory for game-structs.

void free_pixel(struct pixel_struct *pixel) {
  free(&(pixel->red));
  free(&(pixel->green));
  free(&(pixel->blue));
  free(&(pixel->x));
  free(&(pixel->y));
  free(pixel);
}

void free_player(player_struct *player) {
  free_pixel(&(player->pixel));
  free(&(player->clientaddr));
  free(&(player->clientaddr_len));
  free(player);
}

