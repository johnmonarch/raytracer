#include "ray.h"

/** object_init() */
obj_t *object_init(FILE *fp, char *objclass, int objcat) {
   static int objectID = 0;
   obj_t *new;

   /* Allocate space for object */
   assert((new = malloc(sizeof(obj_t))) != NULL);

   /* Initialize standard object data */
   new -> objid = objectID;
   new -> objclass = strdup(objclass);
   new -> objcat = objcat;

   objectID++;
   return(new);
} /* End object_init */

void object_dump(obj_t *obj) {
   fprintf(stderr, "\nDumping object %d, category %d, type %s\n",
           obj->objid,
           obj->objcat,
           obj->objclass);
} 
   
