#include "timeout.h"
#include <stdio.h>

//Checks "server.h"'s list **client_list for players that have timedout.
void check_timeouts(list **original_players, list *players) {
  time_t current_time;
  double delta;
  list *next_ptr;
  int timeout = 20; //Maximum time allowed in seconds for a client to go unresponsive.

  if (players == NULL)
    return;
  next_ptr = players->next;
  current_time = time(NULL);
  delta = difftime(current_time, *((players->player)->last_pong));
  printf("Time since last PONG by client: %.2f\n", delta);
  if (delta > timeout) {
    printf("deleting player from list, timed out\n");
    delete_list(original_players, players->player);
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
