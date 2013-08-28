#include <netinet/in.h>

struct pixel {
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  unsigned short x;
  unsigned short y;
  struct sockaddr_in clientaddr;
};

