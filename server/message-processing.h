#include "linked_list.h"
#include <netinet/in.h>

extern int process_recvfrom(list**,
                            char[],
                            struct sockaddr_in*,
                            socklen_t*);
