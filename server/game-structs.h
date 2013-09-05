#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H

#include <netinet/in.h>
#include <time.h>

struct pixel_struct {
  unsigned short *red;
  unsigned short *green;
  unsigned short *blue;
  unsigned short *x;
  unsigned short *y;
};

typedef struct player_struct {
  struct pixel_struct *pixel;
  struct sockaddr_in *clientaddr;
  socklen_t *clientaddr_len;
  time_t *last_pong;
  int *socket;
} player_struct;

void free_pixel(struct pixel_struct*);
void free_player(player_struct*);
void initialize_pixel(struct pixel_struct*);

#endif /* GAMESTRUCTS_H */
