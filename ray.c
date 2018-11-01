/*
 * ray.c
 * John Monarch
 * CPSC 210
 * Project 1
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "triple.h"
#include "ray.h"
#include "rayhdrs.h"

obj_t *find_closest_obj(list_t *scene, triple_t *base, triple_t *unitDir, obj_t *lasthit){ 
   obj_t *obj; 
   obj_t *closest; 
   double dist; 
   l_reset(scene); 
   closest = NULL; 
   obj = NULL; 
   dist = 0; 
    
   while ((obj = ((obj_t *)l_get(scene))) != NULL) 
   { 
      if(obj != lasthit) { 
         // Call the object's hits function 
         dist = obj->sceneData->hits(base, unitDir, obj); 
          
         if(dist > 0) { 
            // First hit scenario -- auto assigns 
            if(closest == NULL) { 
               closest = obj; 
            } 
            else { 
               if(dist < closest->sceneData->distance){ 
                  closest = obj; 
               } 
            } 
         } 
      } 
   } 
   lasthit = closest; 
   return closest; 
}


void ray_trace(model_t *model, triple_t *base, triple_t *unitDir, triple_t *intensity, double total_dist, obj_t *last_hit){
   obj_t *closest = NULL;
   triple_t reflected_intensity;
   triple_t v, n, u, *r, temporary;
   r = unitDir;
   closest = find_closest_obj(model->scene, base, unitDir, last_hit);
	if(closest == NULL){
      return;
   }
   u = tl_scale3(r, -1);
   n = tl_unitvec3(&closest->sceneData->normal);
   double mindist;
   triple_t diffuse = diffuse_illumination(model, closest);
   triple_t difference;
   difference = tl_diff3(&closest->sceneData->hitloc, base);
   mindist = tl_length3(&difference);
   total_dist += mindist;
   *intensity = tl_sum3(intensity, &closest->sceneData->color);
   *intensity = tl_sum3(intensity, &diffuse);
   *intensity = tl_scale3(intensity,1/total_dist); 
   if(closest->sceneData->specular != 0){
		reflected_intensity.x = 0;
		reflected_intensity.y = 0;
		reflected_intensity.z = 0;
        u = tl_scale3(unitDir, -1); 
        u = tl_unitvec3(&u); 
        n = tl_unitvec3(&closest->sceneData->normal); 
        temporary = tl_scale3(&n, 2 * tl_dot3(&u, &n)); 
        v = tl_diff3(&temporary, &u); 
        v = tl_unitvec3(&v); 
        ray_trace(model, &closest->sceneData->hitloc, &v, &reflected_intensity, total_dist, closest); 
        reflected_intensity = tl_scale3(&reflected_intensity, closest->sceneData->specular); 
        *intensity = tl_sum3(intensity, &reflected_intensity);
	}  
}

