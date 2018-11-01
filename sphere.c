#include "ray.h"

/** sphere_init() */
obj_t *sphere_init(FILE *fp, char *objClass) {
    obj_t *new;
    sphere_t *newSphere;
    /* Create new instance of a sphere object */
    assert((new = sceneobj_init(fp, objClass)) != NULL);

    /* Create sphere specific part */
    assert((newSphere = (sphere_t *)malloc(sizeof(sphere_t))) != NULL);

    /* Get sphere specific data */
    assert(getdouble(fp, &newSphere->center.x) == 1);
    assert(getdouble(fp, &newSphere->center.y) == 1);
    assert(getdouble(fp, &newSphere->center.z) == 1);
    assert(getdouble(fp, &newSphere->radius) == 1);

    /* Link sphere specific data to object */
    new->typeData = (void *) newSphere;
    new->sceneData->hits = sphere_hits;
    return(new);
}
   
/** sphere_dump() */
void sphere_dump(obj_t *objPtr) {
   sphere_t *privPtr;

   sceneobj_dump(objPtr);
   
   privPtr = objPtr->typeData;

   fprintf(stderr, "   Sphere data:\n");
   fprintf(stderr, "      Sphere radius:      %8.4lf\n", privPtr->radius);
   tl_print3(      "      Center Coordinates:", &privPtr->center);
}

double sphere_hits(triple_t *base, triple_t *dir, obj_t *obj) {
   double t;              /* Distance                          */
   triple_t vPrime;       /* Remapped view point               */
   double a, b, c;        /* Intermediate results              */
   double disc;           /* Discriminant                      */
   triple_t v2;           /* Vector from viewpoint to hitpoint */
   triple_t n2;           /* Normal to hit point               */
   sphere_t *spherePtr;   /* Pointer to sphere data            */

   spherePtr = obj->typeData;

   /* Remap the viewpoint */
   vPrime = tl_diff3(base, &spherePtr->center);

   /* Set components of quadractic equation */
   a = tl_dot3(dir, dir);
   b = 2*tl_dot3(&vPrime, dir);
   c = tl_dot3(&vPrime, &vPrime) -
             spherePtr->radius * spherePtr->radius;

   /* Compute discriminant */
   disc = b*b - 4*a*c;
  
   if (disc <= 0) {
      /* Miss */
      return(-1);
   }

   /* This is a hit  -- compute the distance */
   t = (-b - sqrt(disc))/(2*a);
   obj->sceneData->distance = t;
  
   /* Set hit point for sphere and determine the normal */
   v2 = tl_scale3(dir, t);
   obj->sceneData->hitloc = tl_sum3(base, &v2);
   if (obj->sceneData->hitloc.z > 0) {
      /* Hit is in front of screen  -- we don't display that */
      return(-1);
   }

   /* Compute the normal */
   n2=tl_diff3(&obj->sceneData->hitloc, &spherePtr->center);
   obj->sceneData->normal = tl_unitvec3(&n2);

   /* And return the distance to the hit point */
   return(t);
} /* End sphere_hits */
