#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "game-structs.h"

//New type 'list' for newly defined linked list struct.
typedef struct list {
  player_struct *player;
  struct list *next;
} list;

//Prototypes for linked list functions.
void delete_list(list**, player_struct);
void insert_list(list**, player_struct*);
list *predecessor_list(list*, player_struct);
list *search_list(list*, player_struct);

#endif /* LINKEDLIST_H */
