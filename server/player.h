#include "linked_list.h"
#include <netinet/in.h>

//Protoypes for handling state after a valid udp message has been received.
void add_player(list**, struct sockaddr_in*, socklen_t*, int*);
void move_player(player_struct*, char);
void update_timeout(player_struct*);
