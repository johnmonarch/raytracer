/*
 *  light.c
 *  
 *
 *  Created by John Monarch on 11/13/07.
 *  Raytracer, initializes a light object
 *
 */

#include "ray.h"

obj_t *light_init(FILE *fp, char *objClass) {
	obj_t *new;
	lightobj_t *newLight;
	/* Create new instance of a light object */
	new = object_init(fp, objClass, LIGHTOBJ); 

    /* Create light specific part */
    assert((newLight = (lightobj_t *)malloc(sizeof(lightobj_t))) != NULL);
	
    /* Get light specific data */
    assert(getdouble(fp, &newLight->emissivity.x) == 1);
    assert(getdouble(fp, &newLight->emissivity.y) == 1);
    assert(getdouble(fp, &newLight->emissivity.z) == 1);
    assert(getdouble(fp, &newLight->center.x) == 1);
    assert(getdouble(fp, &newLight->center.y) == 1);
    assert(getdouble(fp, &newLight->center.z) == 1);
	

    /* Link light specific data to object */
    new->lightData = newLight;
    return(new);
}

void light_dump(obj_t *obj){
	lightobj_t *privPtr;
	object_dump(obj);
	privPtr = obj->lightData;
	fprintf(stderr, "   Light data:\n");
	tl_print3(      "      Emissivity:     ", &privPtr->emissivity);
	tl_print3(      "      Center    :     ", &privPtr->center);
}
