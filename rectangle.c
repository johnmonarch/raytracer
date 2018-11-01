/*
 *  rectangle.c
 *  
 *
 *  Created by John Monarch on 11/16/07.
 *  Initializes rectangles
 *
 */

#include "ray.h"


obj_t *rectangle_init(FILE *fp, char *objClass){
    obj_t *new;
    polygon_t *rectPtr;
	double width;
	double height;
	plane_t *plane;
	triple_t unitnormal;
	triple_t unitorientation;
	triple_t proj;
	triple_t crossresult;
    if ((new = polygon_init(fp, objClass)) == NULL) {
       fprintf(stderr, "Error: cannot create rectangle\n");
       return(NULL);
    }
	plane = (plane_t *) new->typeData;
	rectPtr = (polygon_t *) plane->priv;
    rectPtr = ((plane_t *)new->typeData)->priv;
    rectPtr->numEdges = 4;
	assert((rectPtr->edges = malloc(rectPtr->numEdges*sizeof(edge_t))) != NULL);
	//set edge 0 to plane point
	rectPtr->edges[0].point.x = plane->point.x;
	rectPtr->edges[0].point.y = plane->point.y;
	rectPtr->edges[0].point.z = plane->point.z;
	new->sceneData->hits = polygon_hits;
	//input orientation for edge 0 
	assert(getdouble(fp, &rectPtr->edges[0].edgeDir.x)==1);
	assert(getdouble(fp, &rectPtr->edges[0].edgeDir.y)==1);
	assert(getdouble(fp, &rectPtr->edges[0].edgeDir.z)==1);
	//input width and height
	assert(getdouble(fp, &width)==1);
	assert(getdouble(fp, &height)==1);
	unitnormal = tl_unitvec3(&plane->normal);
	unitorientation = tl_unitvec3(&rectPtr->edges->edgeDir);
	proj = tl_project3(&unitnormal, &unitorientation);
	proj = tl_unitvec3(&proj);
	proj = tl_scale3(&proj, width);
	rectPtr->edges[1].point.x = proj.x + rectPtr->edges[0].point.x;
	rectPtr->edges[1].point.y = proj.y + rectPtr->edges[0].point.y;
	rectPtr->edges[1].point.z = proj.z + rectPtr->edges[0].point.z;
	crossresult = tl_cross3(&unitnormal, &rectPtr->edges[0].edgeDir);
	crossresult = tl_unitvec3(&crossresult);
	crossresult = tl_scale3(&crossresult, height);
	rectPtr->edges[2].point = tl_sum3(&rectPtr->edges[1].point, &crossresult);
	rectPtr->edges[3].point =  tl_sum3(&rectPtr->edges[0].point, &crossresult);
	//unitvector computations
	/***************************************************************************/
	rectPtr->edges[0].edgeDir = tl_diff3(&rectPtr->edges[0].point, &rectPtr->edges[1].point);
	rectPtr->edges[0].edgeDir = tl_unitvec3(&rectPtr->edges[0].edgeDir);
	/***************************************************************************/
	rectPtr->edges[1].edgeDir = tl_diff3(&rectPtr->edges[1].point, &rectPtr->edges[2].point);
	rectPtr->edges[1].edgeDir = tl_unitvec3(&rectPtr->edges[1].edgeDir);
	/***************************************************************************/
	rectPtr->edges[2].edgeDir = tl_diff3(&rectPtr->edges[2].point, &rectPtr->edges[3].point);
	rectPtr->edges[2].edgeDir = tl_unitvec3(&rectPtr->edges[2].edgeDir);
	/***************************************************************************/
	rectPtr->edges[3].edgeDir = tl_diff3(&rectPtr->edges[3].point, &rectPtr->edges[0].point);
	rectPtr->edges[3].edgeDir = tl_unitvec3(&rectPtr->edges[3].edgeDir);
	/***************************************************************************/
	return (new);
}
