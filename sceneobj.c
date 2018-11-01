#include "ray.h"

/** object_init() */
obj_t *sceneobj_init(FILE *fp, char *objclass) {
   obj_t *obj;
   sceneobj_t *new;

   /* Allocate space for object */
   assert ((obj = object_init(fp, objclass, SCENEOBJ)) != NULL);

   /* Allocate space for sceneobj_t data */
   assert((new = (sceneobj_t *)malloc(sizeof(sceneobj_t))) != NULL);
   obj->sceneData = new;

   /* Read surface reflectivity values */
   assert(getdouble(fp, &new->color.x) == 1);
   assert(getdouble(fp, &new->color.y) == 1);
   assert(getdouble(fp, &new->color.z) == 1);

   assert(getdouble(fp, &new->diffuse) == 1);
   assert(getdouble(fp, &new->specular) == 1);

   return(obj);
} /* End sceneobj_init */

void sceneobj_dump(obj_t *obj) {
   object_dump(obj);

   fprintf(stderr, "   Reflectivity data:\n");
   tl_print3(      "      Color:   ", &obj->sceneData->color);
   fprintf(stderr, "      Diffuse:  %8.4lf\n", obj->sceneData->diffuse);
   fprintf(stderr, "      Specular: %8.4lf\n", obj->sceneData->specular);

} /* End scendobj_dump */
