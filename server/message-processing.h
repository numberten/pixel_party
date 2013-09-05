#include "linked_list.h"
#include <netinet/in.h>

//Processes recvfrom, in main.
int process_recvfrom(list**,
                     char[],
                     struct sockaddr_in*,
                     socklen_t*,
                     int*,
                     char*);
