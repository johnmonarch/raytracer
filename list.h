/** list.h -- lab 3 **/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* List node */
typedef struct node {
   struct node *next;  /* Pointer to next node         */
   void *object;       /* Pointer to associated object */
} node_t;

typedef struct list {
   node_t *head;       /* Head of list pointer         */
   node_t *tail;       /* Tail pointer                 */
   node_t *position;   /* Current list position        */
} list_t;

/* Prototype Statements */
list_t *l_new();                         /* Create and initialize list object */
void   l_add(list_t *list, void *oject); /* Add object to list                */
void   l_reset(list_t *list);            /* Reset position pointer            */
void   *l_get(list_t *list);             /* Get next object from list         */

#endif
