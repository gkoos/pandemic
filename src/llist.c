#include <stdlib.h>
#include <stdio.h>

#include "llist.h"

void llist_insert(llist_node_t **l, int val)
{
  llist_node_t *tmp = *l;

  while (tmp && tmp->next)
  {
    tmp = tmp->next;
  }

  llist_node_t *node = malloc(sizeof(llist_node_t));
  node->next = NULL;
  node->val = val;

  if (tmp) tmp->next = node;
  else *l = node;
}

void llist_destroy(llist_node_t *list)
{
  llist_node_t *l = list;
  while(l && l->next != NULL)
  {
    l = l->next;
    free(l);
  }
}

void llist_getPairs(llist_node_t *list, void (*callback)(int index1, int index2))
{
  if (!list) return;

  llist_node_t *p1 = list;
  while (p1->next)
  {
    llist_node_t *p2 = p1->next;
    while(p2)
    {
      callback(p1->val, p2->val);
      p2 = p2->next;
    }

    p1 = p1->next;
  }
}
