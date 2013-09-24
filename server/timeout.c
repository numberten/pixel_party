#include "timeout.h"
#include "reply-processing.h"
#include <stdio.h>
#include <string.h>

/* Functions for dealing with timeouts. 
 * Used in main()'s timeout pthread.
 */

//Checks "server.h"'s list **client_list for players that have timedout.
void check_timeouts(list **original_players, list *players) {
  time_t current_time;
  double delta;
  list *next_ptr, *p;
  int timeout = 20; //Maximum time allowed in seconds for a client to go unresponsive.
  char reply_buffer[50];

  if (players == NULL)
    return;
  next_ptr = players->next;
  current_time = time(NULL);
  delta = difftime(current_time, *((players->player)->last_pong));
  printf("Time since last PONG by client: %.2f\n", delta);
  if (delta > timeout) {
    printf("deleting player from list, timed out\n");
    removal_message(players->player, reply_buffer);
    delete_list(original_players, players->player);

    p = *original_players;
    //sendto the removal message to all still connected clients.
    while (p != NULL) {
      sendto(*p->player->socket, reply_buffer, strlen(reply_buffer), 0, (struct sockaddr *) p->player->clientaddr, sizeof(*p->player->clientaddr));
      p = p->next;
    }
  }
  check_timeouts(original_players, next_ptr);
}

//The callback for main()'s pthread
void *loop_check_timeouts(void *arg) {
  while (1) {
    sleep(30);
    printf("Checking for timeouts...\n");
    check_timeouts(client_list, *client_list);
  }
}
