/* CPSC 210
 *
 * veclib.c
 *
 * Vector and triple functions
 *
 */

#include <math.h>
#include <stdlib.h>
#include "triple.h"

/** tl_length3 **/
/* Computes the length of a 3-D vector */
double tl_length3(triple_t * v1) {
   double sum;
   
   sum = v1->x*v1->x + v1->y*v1->y + v1->z*v1->z;
   sum = sqrt(sum);
   return sum;
}


/** tl_scale3 **/
/* Scales a 3-D vector by a specified factor. Returns a new vector */
triple_t  tl_scale3(triple_t * v, double factor) {
   triple_t result;
   
   result.x = v->x * factor;
   result.y = v->y * factor;
   result.z = v->z * factor;

   return result;
}


/** tl_unitvec3 **/
/* Returns a unit vector in the same direction as the vector v.  */
triple_t tl_unitvec3(triple_t * v) {
   triple_t result = {0, 0, 0};
   double len;

   len = tl_length3(v);
   if (len != 0) {
      result.x = v->x / len;
      result.y = v->y / len;
      result.z = v->z / len;
   }
   
   return result;
}


/** tl_dot3 **/
/* Computes the dot product of two 3-D vectors */
double tl_dot3(triple_t * v1, triple_t * v2) {
   double sum;
   
   sum = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
   
   return sum;
}


/** tl_diff3 **/
/* Returns a new triple that has the value of v1 - v2 */
triple_t tl_diff3(triple_t * v1, triple_t * v2) {
   triple_t result;

   result.x = v1->x - v2->x;
   result.y = v1->y - v2->y;
   result.z = v1->z - v2->z;
   
   return result;
}


/** tl_sum3 **/
/* Returns a new triple that has the value of v1 + v2 */
triple_t tl_sum3(triple_t * v1, triple_t * v2) {
   triple_t  result;
   
   result.x = v1->x + v2->x;
   result.y = v1->y + v2->y;
   result.z = v1->z + v2->z;
   
   return result;
}

/** tl_print3 **/
/* Print a triple to stderr, with a label */
void tl_print3(char *label, triple_t *v) {
   fprintf(stderr, "%s %8.4lf %8.4lf %8.4lf\n", label, v->x, v->y, v->z);
}


/** tl_cross3 **/ 
triple_t tl_cross3(triple_t *v, triple_t *w) { 
   triple_t resultant; 
    
   resultant.x = (v->y * w->z) - (v->z * w->y); 
   resultant.y = (v->z * w->x) - (v->x * w->z); 
   resultant.z = (v->x * w->y) - (v->y * w->x); 
    
   return resultant; 
} 
 
/** tl_project3 **/ 
triple_t tl_project3(triple_t *normal, triple_t *v) { 
   double dot;
   triple_t scale;
   triple_t result;
   dot = tl_dot3(normal, v);
   scale = tl_scale3(normal, dot);
   result = tl_diff3(v, &scale);
   return result;
}
