/* Prototype statements for vector library (structure version)
 *
 * CPSC 210, Fall 2007
 *
 */

#ifndef TRIPPLE_H
#define TRIPPLE_H

#include <stdio.h>


/** Data type definitions **/
typedef struct triple {
   double x;
   double y;
   double z;
} triple_t;


/** Vector Library Prototype Statement **/
/* Vector Length */
double tl_length3(triple_t *v1);

/* Scale Vector
 *
 * Returns a vector containing (v * factor)
 */
triple_t tl_scale3(
       triple_t *v,               /* Input triple   */
       double factor              /* Scaling factor */
);

/* Unitize vector
 *
 * Returns a vector containing (v / ||v||)
 */
triple_t tl_unitvec3(
       triple_t *v                /* Input vector            */
);

/* Dot Product */
double tl_dot3(
       triple_t *v1,              /* Input vector 1 */
       triple_t *v2               /* Input vector 2 */
);

/* Vector Difference
 *
 * Returns a vector containing (v1 - v2)
 */
triple_t tl_diff3(
       triple_t *v1,              /* First triple   */
       triple_t *v2               /* Second triple  */
);
     
/* Vector Addition
 * Returns a  vector containing (v1 + v2)
 */
triple_t tl_sum3(
       triple_t *v1,              /* First triple   */
       triple_t *v2               /* Second triple  */
);

/* Triple print
 * Print a label and the x, y, z values of a triple 
*/
void tl_print3(
      char *label,               /* Message lable */
      triple_t *v                /* triple        */
);

/* Cross Product */
triple_t tl_cross3(triple_t *v, triple_t *w); 

/* Projection */
triple_t tl_project3(triple_t *normal, triple_t *v);

#endif
