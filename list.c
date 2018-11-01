/** list.c **/

#include "list.h"

list_t *l_new() {
   list_t *newlist;
   
   assert((newlist = malloc(sizeof(list_t))) != NULL);
   newlist->head = NULL;
   newlist->tail = NULL;
   newlist->position = NULL;
   return(newlist);
}

void l_add(list_t *list, void *object) {
   node_t *new;
   
   /* Create and initialize new node */
   assert((new = malloc(sizeof(node_t))) != NULL);
   new->object = object;
   new->next = NULL;

   /* Update list pointers */
   if (list->head == NULL) {
      list->head = new;        /* Special case of empty list  */
   }
   else {
      list->tail->next = new;  /* Point last node to new node */
   }
   list->tail = new;           /* Point tail to new node      */
}

void l_reset(list_t *list) {
   list->position = list->head;
}

void *l_get(list_t *list) {
   node_t *node;
   if (list->position == NULL) {
      return(NULL);
   }
   node = list->position;
   list->position = list->position->next;
   return(node->object);
}
