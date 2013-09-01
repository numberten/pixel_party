#include "game-structs.h"
#include <netinet/in.h>

extern int process_recvfrom(struct player_struct[],
                            char[],
                            struct sockaddr_in*,
                            socklen_t*);
