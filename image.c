/*
 * image.c
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

 void make_pixel(model_t *model, int x, int y, pixel *pixval)
{
  triple_t world, intensity, dir, ray;
  int ctr;
  intensity.x = 0.0;
  intensity.y = 0.0;
  intensity.z = 0.0;
  triple_t temp_intensity;
  for(ctr = 0;ctr<model->env->samples;ctr++){
	  world = map_pix_to_world(model->env, x, y);
	  temp_intensity.x = 0.0;
	  temp_intensity.y = 0.0;
	  temp_intensity.z = 0.0;
      ray = tl_diff3(&world, &(model->env->view_point));
      dir = tl_unitvec3(&ray);
      ray_trace(model, &model->env->view_point, &dir, &temp_intensity, 0.0, NULL);
	  intensity.x += temp_intensity.x;
	  intensity.y += temp_intensity.y;
	  intensity.z += temp_intensity.z;
  }
	  intensity.x = intensity.x * 1/(model->env->samples);
	  intensity.y = intensity.y * 1/(model->env->samples);
	  intensity.z = intensity.z * 1/(model->env->samples);
   if(intensity.x > 1.0){
   intensity.x = 1.0;}
  if(intensity.y > 1.0){
   intensity.y = 1.0;}     
  if(intensity.z > 1.0){
   intensity.z = 1.0;}
  pixval->r   = (int) (255*(intensity.x));
  pixval->g = (int)  (255*(intensity.y));
  pixval->b  = (int)  (255*(intensity.z));
  
}

void make_image(FILE *outFP, model_t *model)
{
   double imageOutSize;
   int numCols = model->env->winPWidth;
   int numRows = model->env->winPHeight;
   int x, y;
   fprintf(stderr, "COLS ROWS:  %d %d\n", numCols, numRows);
   imageOutSize = numCols * numRows * 3;
   pixel *pixmap = (pixel *)malloc(imageOutSize);

   fprintf(outFP, "P6 %d %d 255\n", numCols, numRows);
   for(y=numRows-1; y>=0; y--) {
      for(x=0; x<numCols; x++) {
			make_pixel(model, x, y, pixmap);
			fprintf(outFP, "%c%c%c", pixmap->r, pixmap->g, pixmap->b);
      }
   }
   if(fwrite(pixmap, 1, imageOutSize, outFP)==0)
      fprintf(stdout, "Write unsuccessful\n");
}
