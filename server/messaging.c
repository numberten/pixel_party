#include "messaging.h"
#include <stdio.h>
#include <string.h>

/* Functions for sending messages to all connected clients.
 *  - Ping all clients.
 *  - Send grid information to all clients.
 */

void ping_clients(list *players) {
  list *p = players;
  char *message = "PING\n";

  while (p != NULL) {
    sendto(*p->player->socket, message, strlen(message), 0, (struct sockaddr *) p->player->clientaddr, sizeof(*p->player->clientaddr));
    p = p->next;
  }
}

void grid_message(list *players) {
  unsigned short x, y, r, g, b;
  list *p = players;
  char temp[1000];
  char str_ptr[1000];

  strcpy(temp, "");
  while (p != NULL) {
    x = *p->player->pixel->x;
    y = *p->player->pixel->y;
    r = *p->player->pixel->red;
    g = *p->player->pixel->green;
    b = *p->player->pixel->blue;
    snprintf(str_ptr, 40, "#%hu,%hu,%hu,%hu,%hu$\n", x, y, r, g, b);
    strcat(temp, str_ptr);
    p = p->next;
  }
  snprintf(str_ptr, 1000, "%s", temp);
  p = players;

  //sendto the grid message to all clients.
  while (p != NULL) {
    sendto(*p->player->socket, str_ptr, strlen(str_ptr), 0, (struct sockaddr *) p->player->clientaddr, sizeof(*p->player->clientaddr));
    p = p->next;
  }
}

void *loop_ping_clients(void *arg) {
  while (1) {
    sleep(15);
    printf("Sending out pings...\n");
    ping_clients(*client_list);
  }
}

void send_updates(void) {
  grid_message(*client_list);
}
