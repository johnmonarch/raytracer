/*
 *  triangle.c
 *  
 *
 *  Created by John Monarch on 11/16/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "ray.h"

obj_t *triangle_init(FILE *fp, char *objClass){
    obj_t *new;
    polygon_t *triPtr;
	plane_t *plane;
	double edgezerolen;
	double edgetwolen;
	triple_t unitnormal;
	triple_t unitorientation;
	triple_t proj;
    if((new = polygon_init(fp, objClass)) == NULL) {
       fprintf(stderr, "Error: cannot create rectangle\n");
       return(NULL);
    }
	plane = (plane_t *) new->typeData;
	triPtr = (polygon_t *) plane->priv;
    triPtr = ((plane_t *)new->typeData)->priv;
    triPtr->numEdges = 3;
	assert((triPtr->edges = malloc(triPtr->numEdges*sizeof(edge_t))) != NULL);

	//set edge 0 to plane point
	new->sceneData->hits = polygon_hits;
	triPtr->edges[0].point.x = plane->point.x;
	triPtr->edges[0].point.y = plane->point.y;
	triPtr->edges[0].point.z = plane->point.z;
	//input orientation for edge 0 
	assert(getdouble(fp, &triPtr->edges[0].edgeDir.x)==1);
	assert(getdouble(fp, &triPtr->edges[0].edgeDir.y)==1);
	assert(getdouble(fp, &triPtr->edges[0].edgeDir.z)==1);
	//input length of edge 0
	assert(getdouble(fp, &edgezerolen)==1);

	unitnormal = tl_unitvec3(&plane->normal);

	unitorientation = tl_unitvec3(&triPtr->edges[0].edgeDir);
	
	proj = tl_project3(&unitnormal, &unitorientation);
	proj = tl_unitvec3(&proj);
	proj = tl_scale3(&proj, edgezerolen);
	fprintf(stderr, "\n");
	triPtr->edges[1].point.x = triPtr->edges[0].point.x + proj.x;
	triPtr->edges[1].point.y = triPtr->edges[0].point.y + proj.y;
	triPtr->edges[1].point.z = triPtr->edges[0].point.z + proj.z;
		fprintf(stderr, "\n");
	/**edge 2 **/
	//input orientation for edge 2
	assert(getdouble(fp, &triPtr->edges[2].edgeDir.x)==1);
	assert(getdouble(fp, &triPtr->edges[2].edgeDir.y)==1);
	assert(getdouble(fp, &triPtr->edges[2].edgeDir.z)==1);
	//input length of edge 2
	assert(getdouble(fp, &edgetwolen)==1);
	unitorientation = tl_unitvec3(&triPtr->edges[2].edgeDir);
	proj = tl_project3(&unitnormal, &unitorientation);
	proj = tl_unitvec3(&proj);
	proj = tl_scale3(&proj, edgetwolen);
	triPtr->edges[2].point.x = triPtr->edges[0].point.x +  proj.x;
	triPtr->edges[2].point.y = triPtr->edges[0].point.y +  proj.y;
	triPtr->edges[2].point.z = triPtr->edges[0].point.z +  proj.z;	
	
	//edges info
	/***************************************************************************/
	triPtr->edges[0].edgeDir = tl_diff3(&triPtr->edges[1].point, &triPtr->edges[0].point);
	triPtr->edges[0].edgeDir = tl_unitvec3(&triPtr->edges[0].edgeDir);
	/***************************************************************************/
	triPtr->edges[1].edgeDir = tl_diff3(&triPtr->edges[2].point, &triPtr->edges[1].point);
	triPtr->edges[1].edgeDir = tl_unitvec3(&triPtr->edges[1].edgeDir);
	/***************************************************************************/
	triPtr->edges[2].edgeDir = tl_diff3(&triPtr->edges[0].point, &triPtr->edges[2].point);
	triPtr->edges[2].edgeDir = tl_unitvec3(&triPtr->edges[2].edgeDir);
	/***************************************************************************/
	return (new);
}
