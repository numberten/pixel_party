#include "server.h"

//Callback for main's ping loop thread.
void *loop_ping_clients(void *);
void send_updates(void);
