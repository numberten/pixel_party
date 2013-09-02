#include "linked_list.h"
#include <stdlib.h>

//Delete, insert, search, predecessor functions for linked list data structure.

void delete_list(list **l, player_struct x) {
  list *p, *pred; 
  list *search_list(), *predecessor_list();

  p = search_list(*l, x);
  if (p != NULL) {
    pred = predecessor_list(*l, x);
    if (pred == NULL)
      *l = p->next;
    else
      pred->next = p->next;
    free_player(&(p->player));
    free(p);
  }
}

void insert_list(list **l, player_struct x) {
  list *p;

  p = malloc(sizeof(list));
  p->player = x;
  p->next = *l;
  *l = p;
}

list *predecessor_list(list *l, player_struct x) {
  if ((l == NULL) || (l->next == NULL))
    return NULL;
  if (&((l->next)->player) == &x)
    return l;
  else
    return predecessor_list(l->next, x);
}

list *search_list(list *l, player_struct x) {
  if (l == NULL)
    return NULL;
  if (&(l->player) == &x)
    return l;
  return search_list(l->next, x);
}
