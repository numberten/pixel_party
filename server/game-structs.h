#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H

#include <netinet/in.h>

struct pixel_struct {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  unsigned short x;
  unsigned short y;
};

struct player_struct {
  struct pixel_struct pixel;
  struct sockaddr_in clientaddr;
  socklen_t clientaddr_len;
};

#endif /* GAMESTRUCTS_H */
