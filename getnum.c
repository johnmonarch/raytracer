/*
 *  getnum.c
 *  
 *
 *  Created by John Monarch on 9/10/07.
 *  This contains the getint() function for the .ppm test
 *  Homework 2 - Due 9/11/07
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getint(FILE *, int *);
int getdouble(FILE *fp, double *result);

int getint(FILE *fp, int *result) {
    char buf[256];
    int  code;

    while ((code=fscanf(fp, "%d", result)) != 1) {
       if (fgets(buf, sizeof(buf), fp) == NULL) {
          return(-1);
       }
       if (buf[0] != '#') {
          fprintf(stderr, "getint[%d]: Error in input: \"%s\"\n", code, buf);
          return(0);
       }
    }
    return(1);
}

int getdouble(FILE *fp, double *result){
    char buf[256];
    int  code;

	while ((code=fscanf(fp, "%lf", result)) != 1) { 
			if(fgets(buf, sizeof(buf), fp) == NULL) { 
			return(-1); 
		} 
		if(buf[0] != '#') { 
			fprintf(stderr, "getdouble[%d]: Error in input: \"%s\"\n", code, buf); 
			return(0); 
		} 
	} 
   return(1); 
}