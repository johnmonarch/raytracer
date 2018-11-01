#include "ray.h"

/** plane_init() */
obj_t *plane_init(FILE *fp, char *objClass) {
    obj_t *new;
    plane_t *newPlane;
    assert((new = sceneobj_init(fp, objClass)) != NULL);
    assert((newPlane = (plane_t *)malloc(sizeof(plane_t))) != NULL);

    assert(getdouble(fp, &newPlane->point.x) == 1);
    assert(getdouble(fp, &newPlane->point.y) == 1);
    assert(getdouble(fp, &newPlane->point.z) == 1);
    assert(getdouble(fp, &newPlane->normal.x) == 1);
    assert(getdouble(fp, &newPlane->normal.y) == 1);
    assert(getdouble(fp, &newPlane->normal.z) == 1);

    new->typeData = newPlane;
    new->sceneData->hits = plane_hits;
    return(new);
}
   
/** plane_dump() */
void plane_dump(obj_t *objPtr) {
   plane_t *privPtr;

   sceneobj_dump(objPtr);
   
   privPtr = objPtr-> typeData;

   fprintf(stderr, "   Plane data:\n");
   tl_print3(      "      Normal vector:     ", &privPtr->normal);
   tl_print3(      "      Point Coordinates: ", &privPtr->point);
}

double plane_hits(triple_t *base, triple_t *dir, obj_t *obj) { 
   plane_t *planeObj  = (plane_t *)obj->typeData; 
   sceneobj_t *scnPt = (sceneobj_t *)obj->sceneData; 
   double t = -1; 
   triple_t hitLocation; 
   triple_t scaled; 
    
 
   if(tl_dot3(&planeObj->normal, dir)==0) 
      return t;    
   t = (tl_dot3(&planeObj->normal, &planeObj->point)-tl_dot3(&planeObj->normal, base)) / tl_dot3(&planeObj->normal, dir); 
   if(t<0) { 
      t = -1; 
      return t; 
   } 
   scaled = tl_scale3(dir, t); 
   hitLocation = tl_sum3(base, &scaled); 
   if(hitLocation.z > 0) { 
      t = -1; 
      return t; 
   } 
   scnPt->hitloc = hitLocation; 
   scnPt->normal = planeObj->normal; 
   scnPt->distance = t; 
 
   return t; 
} 
