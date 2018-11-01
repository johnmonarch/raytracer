/*
 *  illuminate.c
 *  
 *
 *  Created by John Monarch on 11/13/07.
 *  Raytracer.  Does diffuse illumination and light processing.
 *
 */

#include "ray.h"

triple_t diffuse_illumination(model_t *model, obj_t *hitobj){
	triple_t total;
	total.x = 0;
	total.y = 0;
	total.z = 0;
//	obj_t *type = l_get(model->lights); 
	obj_t *currentl;
	triple_t temp;
	l_reset(model->lights);
	while((currentl= l_get(model->lights)) != NULL){
		temp = process_light(model->scene, hitobj, currentl->lightData);
		total = tl_sum3(&total, &temp);
	}
//   fprintf(stderr,"X: %.4f  Y: %.4f  Z: %.4f", total.x, total.y, total.z);
	return total;
}
triple_t process_light( 
   list_t *lst,          /* List of all scene objects      */ 
   obj_t  *hitobj,       /* The object hit by the ray      */ 
   lightobj_t *lobj)         /* the current light source       */                 
{ 
/************************/
   triple_t snormal; 
   triple_t lightvec; 
   triple_t lightunit; 
   triple_t light; 
   obj_t *closest; 
   double dotP; 
   light = tl_scale3(&light, 0); 
   closest = NULL; 
   snormal = tl_unitvec3(&hitobj->sceneData->normal); 
   lightvec = tl_diff3(&lobj->center, &hitobj->sceneData->hitloc); 
   lightunit = tl_unitvec3(&lightvec); 
/*************************/
/*************************/
   dotP = tl_dot3(&lightunit, &snormal); 
   if(dotP < 0) { 
      return light; 
   } 
   lightvec = tl_diff3(&hitobj->sceneData->hitloc, &lobj->center); 
   lightunit = tl_unitvec3(&lightvec); 
   closest = find_closest_obj(lst, &lobj->center, &lightunit, NULL); 
   if(closest->objid != hitobj->objid) { 
      return light; 
   } 
   light = tl_scale3(&lobj->emissivity, (hitobj->sceneData->diffuse * dotP)/(tl_length3(&lightvec))); 
 
   return light; 
}

