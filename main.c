/*
 * main.c
 * John Monarch
 * CPSC 210
 * Project 1
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "rayhdrs.h"
#include "triple.h"

int main( 
int argc, 
char **argv) 
{ 
   model_t *model  = (model_t *)malloc(sizeof(model_t)); 
   int     rc; 
   FILE *inputFP;
   FILE *outputFP;
   double numCols;
   int samples;
 
   if (argc == 4){
   		fprintf(stderr, "Number of samples ignored, auto set to 1\n");
   		model->env->samples = 1;
	}
   if (argc == 5){
	  samples=atoi(argv[4]);
   }
   else {
      fprintf(stderr, "Usage: ./ray3 worldFile outputPPMFile columns samples\n");
      exit(1);
   }
   
   if ((inputFP = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr,"Input Open Error\n");
      exit(1);
   }
   
   if ((outputFP = fopen(argv[2], "w")) == NULL) {
      fprintf(stderr,"Output Open Error\n");
      exit(1);
   }
   
   if ((numCols=atoi(argv[3])) <= 0) {
      fprintf(stderr,"Error: cannot convert number of rows\n");
      exit(1);
   }

   model->env = environment_init(inputFP, numCols); 
   model->env->samples = samples;
   environment_dump(model->env); 
   model->lights  = l_new(); 
   model->scene   = l_new(); 
   rc = model_init(inputFP, model); 
   model_dump(model); 
 
   if (rc == 0) 
      make_image(outputFP, model); 
 
   return(0); 
} 