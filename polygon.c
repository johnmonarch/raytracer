/*
 *  polygon.c
 *  
 *
 *  Created by John Monarch on 11/14/07.
 *  Initializes polygons, dumps polygon data, and the polygon_hits function for Raytracer 
 *
 */

#include "ray.h"

obj_t *polygon_init( FILE *in, char *objclass) {  
   obj_t *obj; 
   plane_t *planePtr; 
   obj = plane_init(in, objclass); 
   planePtr = (plane_t *) obj->typeData; 
   planePtr->priv = (polygon_t *) malloc(sizeof(polygon_t)); 
   obj->sceneData->hits = polygon_hits; 
   return(obj); 
}
 

void polygon_dump(obj_t *objPtr){
	int i;
	plane_dump(objPtr);
	polygon_t *type;
	type = (polygon_t *) (((plane_t *)objPtr->typeData)->priv); 
	fprintf(stdout, "   Number of Edges:  %d\n", type->numEdges);
	for(i=0;i < type->numEdges;i++){
		fprintf(stdout, "Edge %d: \n", i);
		tl_print3("Point:     ", &type->edges[i].point);
		fprintf(stdout, "\n");
		tl_print3("Direction: ", &type->edges[i].edgeDir);
		fprintf(stdout, "\n");
		
	}
}


double polygon_hits(triple_t *base, triple_t *dir, obj_t *obj) {  
   double dist; 
   int edgectr; 
   polygon_t *polygonPtr; 
   triple_t vec; 
   triple_t crossproduct; 
   double dotproduct; 
   double lastdot; 
   dist = plane_hits(base, dir, obj); 

   if(dist == -1) {
		return -1; 
	}
   polygonPtr = (polygon_t *) (((plane_t *)obj->typeData)->priv); 
   lastdot = 0; 
      int sides = polygonPtr->numEdges;
   for(edgectr = 0; edgectr < sides; edgectr++) {  
      vec = tl_diff3(&obj->sceneData->hitloc, &polygonPtr->edges[edgectr].point); 
      vec = tl_unitvec3(&vec); 
      crossproduct = tl_cross3(&polygonPtr->edges[edgectr].edgeDir, &vec); 
      crossproduct = tl_unitvec3(&crossproduct); 
      dotproduct = tl_dot3(&obj->sceneData->normal, &crossproduct); 
      if(edgectr != 0) 
         if((lastdot * dotproduct) <= 0){
            return -1;
		 }
      lastdot = dotproduct; 
    }
	return dist; 
} 
