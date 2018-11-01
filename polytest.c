#include "ray.h"

/** polytest_init() */
obj_t *polytest_init(FILE *fp, char *objClass) {
    obj_t *new;
    polygon_t *polyPtr;
    int ndx;
    double dedges;

    /* Create new instance of a polygon object */
    if ((new = polygon_init(fp, objClass)) == NULL) {
       fprintf(stderr, "Error: cannot create fplane object\n");
       return(NULL);
    }
    polyPtr = ((plane_t *)new->typeData)->priv;

    /* Get the number of edges in the polygon */
    assert(getdouble(fp, &dedges) == 1);
    polyPtr->numEdges = dedges;

    /* And allocate space for the edge array */
    assert((polyPtr->edges = malloc(polyPtr->numEdges*sizeof(edge_t))) != NULL);

    /* Now get the point data -- point 0 is the point provided with the 
       plane data */
    polyPtr->edges[0].point = ((plane_t *)new->typeData)->point;
    for (ndx=1; ndx<polyPtr->numEdges; ndx++) {
        assert(getdouble(fp, &polyPtr->edges[ndx].point.x) == 1);
        assert(getdouble(fp, &polyPtr->edges[ndx].point.y) == 1);
        assert(getdouble(fp, &polyPtr->edges[ndx].point.z) == 1);
    }

    /* Now construct the edge unit vectors */
    for (ndx=0; ndx<polyPtr->numEdges; ndx++) {
        polyPtr->edges[ndx].edgeDir = 
           tl_diff3(&polyPtr->edges[(ndx+1)%polyPtr->numEdges].point,
                    &polyPtr->edges[ndx].point);
        polyPtr->edges[ndx].edgeDir = tl_unitvec3(&polyPtr->edges[ndx].edgeDir);
    }

    /* Special case for polytest objects ONLY:
          We have to over-ride the normal from the input data based on the 
          points.  It will just be the cross-product of any two edges 
    */
    ((plane_t *)new->typeData)->normal = tl_cross3(&polyPtr->edges[0].edgeDir,
                                                   &polyPtr->edges[1].edgeDir);
    ((plane_t *)new->typeData)->normal = 
         tl_unitvec3(&((plane_t *)new->typeData)->normal);

    return(new);
}
