
typedef struct llist_node_t
{
  int val;
  struct llist_node_t *next;
} llist_node_t;

void llist_insert(llist_node_t **l, int val);
void llist_destroy(llist_node_t *list);

// get all the pairs in the linked list
void llist_getPairs(llist_node_t *list, void (*callback)(int index1, int index2));
