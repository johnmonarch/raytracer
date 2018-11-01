/*
 *  environment.c
 *  
 *
 *  Created by John Monarch, 10/2/07.
 *  Homework 5
 *  
 *
 */

#include <math.h>
#include "ray.h"

env_t *environment_init(FILE *inFP, int columns);
void environment_dump(env_t *environment);
triple_t map_pix_to_world (env_t *environment, int x, int y);
void raytest(env_t *environment);

env_t *environment_init(FILE *inFP, int columns){
	env_t *project;  //Declares the initial pointer for the project
	project = (env_t *) malloc(sizeof(env_t));  //Allocates memory for the environment
	if(getdouble(inFP, &project->view_point.x)!=1) { 
		fprintf(stderr, "Error with x component\n"); 
		return NULL; 
	} 
	if(getdouble(inFP, &project->view_point.y)!=1) { 
		fprintf(stderr, "Error with y component\n"); 
		return NULL; 
	} 
	if(getdouble(inFP, &project->view_point.z)!=1) { 
		fprintf(stderr, "Error with z component\n"); 
		return NULL; 
	} 
	if(getdouble(inFP, &project->winWWidth)!=1) { 
		fprintf(stderr, "Error with window width component\n"); 
		return NULL; 
	} 
	if(getdouble(inFP, &project->winWHeight)!=1) { 
		fprintf(stderr, "Error with window height component\n"); 
		return NULL; 
	} 
	project->winPWidth = columns;  //Sets the width dimension
	project->winPHeight = ((project->winWHeight)/(project->winWWidth))*columns;  //Sets the height dimension
	return(project);  //Returns the pointer to the project, therefore initializing the environment
}

double randpix(int p){
	double rv1;
	rv1 = drand48();
	double rv2 = rv1 - 0.5;
	return (p + rv2);
}
void environment_dump(env_t *environment){
/*
 * This function outputs the data of the environment
 * This allows for debugging
 *
 */

	fprintf(stderr, "Dumping environment data:\n");
	tl_print3(      "---Viewpoint Coordinate: ", &environment->view_point);
	fprintf(stderr, "---Size of Pixels      : %8d %8d\n", environment->winPWidth, environment->winPHeight);
	fprintf(stderr, "---Size of World       : %8.2lf %8.2lf\n", environment->winWWidth, environment->winWHeight);
}

triple_t map_pix_to_world (env_t *environment, int x, int y){
/* 
 * This function maps the pixels of the width and height
 * to the world environment, therefore "creating" the world
 *
 */

	triple_t world;
	double rx = randpix(x);
	double ry = randpix(y);
	
	world.x = (((rx)/(double)(environment->winPWidth-1))*environment->winWWidth);  //Gets the X values
	world.y = (((ry)/(double)(environment->winPHeight-1))*environment->winWHeight);  //Gets the Y values
	world.z = 0;  //Sets Z to zero
	world.x = world.x - environment->winWWidth/2;  //Subtracts half of the window width from the world
	world.y = world.y - environment->winWHeight/2 ; //Subtracts half of the window height from the world
	return(world);
}

void raytest(env_t *environment){
	int row; //Row number
	int col; //Column number
	double magnitude; //Magnitude of the vector
	triple_t world_pixel; //Coordinates of pixels
	triple_t dir_v; //Viewpoint vector direction
	triple_t unit_dir_v; //Unit Vector direction
	fprintf(stderr, " row#  col#       x-pos       y-pos   unit_dir_v.x unit_dir_v.y unit_dir_v.z  magnitude\n");
	for (row=0; row<environment->winPHeight; row++) {
		for (col=0; col<environment->winPWidth; col++) {
			world_pixel = map_pix_to_world(environment, col, row);
			dir_v = tl_diff3(&world_pixel,&environment->view_point);
			magnitude = tl_length3(&dir_v);
			unit_dir_v = tl_unitvec3(&dir_v);
			fprintf(stderr, "%4d %4d %7.3lf %7.2lf %7.2lf %7.2lf %7.2lf %7.2lf\n", row, col,world_pixel.x, world_pixel.y, unit_dir_v.x, unit_dir_v.y, unit_dir_v.z, magnitude); 
		}
	}
}
