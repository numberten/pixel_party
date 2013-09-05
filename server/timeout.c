#include "timeout.h"
#include <stdio.h>

void check_timeouts(list **original_players, list *players) {
  time_t current_time;
  double delta;
  list *next_ptr;
  int timeout = 20; //Maximum time allowed in seconds for a client to go unresponsive.

  printf("In check_timeouts.\n");
  if (players == NULL) {
    printf("players == NULL\n");
    printf("original_players head: %p\n", *original_players);
    return;
  }
  printf("original_players head: %p\n", *original_players);
  printf("@@@@@@@@@\n");
  next_ptr = players->next;
  printf("#########\n");
  current_time = time(NULL);
  delta = difftime(current_time, *((players->player)->last_pong));
  printf("Time since last PONG by client: %.2f\n", delta);
  if (delta > timeout) {
    printf("deleting player from list, timed out\n");
    printf("location of players->player: %p\n", players->player);
    delete_list(original_players, players->player);
    printf("past delete_list\n");
  }
  (next_ptr == NULL) ? printf("Tots NULL coming up\n") : printf("Tots player_struct coming up\n");
  check_timeouts(original_players, next_ptr);
}

void *loop_check_timeouts(void *arg) {
  printf("in loop!!!!\n");

  while (1) {
    sleep(30);
    check_timeouts(client_list, *client_list);
  }
}
