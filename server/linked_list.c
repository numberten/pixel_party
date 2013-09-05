#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

//Delete, insert, search, predecessor functions for linked list data structure.

void delete_list(list **l, player_struct *x) {
  list *p, *pred; 
  list *search_list(), *predecessor_list();

  printf("calling search list\n");
  p = search_list(*l, x);
  printf("search_list was just called... supposedly\n");

  if (p != NULL) {
    pred = predecessor_list(*l, x);
    printf("found p in search list\n");
    if (pred == NULL) {
      printf("remove head by destroying link\n");
      *l = p->next;
      printf("*l: %p\n", *l);
    }
    else {
      printf("removing inner link via pred\n");
      pred->next = p->next;
    }
    printf("about to call free_player from delete_list\n");
    free_player(p->player);
    printf("about to free(p)\n");
    free(p);
    printf("home clear\n");
    printf("*l: %p\n", *l);
  }
}

void insert_list(list **l, player_struct *x) {
  list *p;

  p = malloc(sizeof(list));
  p->player = x;
  p->next = *l;
  *l = p;
  printf("New head: %p\n", *l);
}

list *predecessor_list(list *l, player_struct *x) {
  if ((l == NULL) || (l->next == NULL))
    return NULL;
  if ((l->next)->player == x)
    return l;
  else
    return predecessor_list(l->next, x);
}

list *search_list(list *l, player_struct *x) {
  printf("in searchlist\n");
  printf("IN SEARCH_LIST:\n\tl->player: %p\n\t&x: %p\n", l->player, x);
  if (l == NULL)
    return NULL;
  if (l->player == x)
    return l;
  return search_list(l->next, x);
}
