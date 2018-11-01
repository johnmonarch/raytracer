#include "ray.h"

   struct func{
		char *typestring;
		obj_t * (*init)(FILE*, char *);
		void (*dump)(obj_t*);
   } array[]={ {"plane", plane_init, plane_dump}, {"sphere", sphere_init, sphere_dump}, {"pointlight", light_init, light_dump }, {"polytest", polytest_init, polygon_dump }, {"triangle", triangle_init, polygon_dump }, {"rectangle", rectangle_init, polygon_dump } };

/** model_init **/
int model_init(FILE *in, model_t *model) { 
   obj_t *obj = NULL; 
   char  buf[256]; 
   char  objclass[128]; 
   int counter; 
   int flag; 
    
/* Load the objects in the scene */ 
   while (fscanf(in, "%128s", objclass) == 1) 
   { 
      /* The word just inputted must be either a class name or the 
         beginning of a comment  
      */ 
      flag = 0; 
      if (objclass[0] == '#') { 
         /* It's a comment -- skip the rest of the line */ 
         fgets(buf, sizeof(buf), in); /* consume rest of line */ 
      } 
      else { 
         for(counter = 0; counter < (sizeof(array)/sizeof(*array)); counter++) { 
            // Use array struct to call correct init 
            if(strcmp(objclass, (array[counter]).typestring) == 0) { 
               obj = array[counter].init(in, objclass); 
               flag = 1; 
               break; 
            } 
         } 
          
         // Catches objects not in the array struct 
         if (flag == 0) { 
            fprintf(stderr, "Unrecognized object type\n"); 
            exit(1); 
         } 
          
         // Catches failed initiation procedure otherwise adds 
         if (obj == NULL) { 
            fprintf(stderr, "Failed to load type %s \n", objclass); 
            model_dump(model); 
            exit(2); 
         } 
         else 
         { 
            /* Add object to scene object linked list */ 
            if(obj->objcat == 0) 
               l_add(model->scene, obj); 
            else 
               l_add(model->lights, obj); 
         } 
      } /* End else "not a comment" */ 
   } 
   return(0); 
}

/** model_dump **/
void model_dump(model_t *model) {
   obj_t *obj;
   int flag = 0;
   int counter;

   l_reset(model->scene);
   while ((obj = l_get(model->scene)) != NULL)
   {
   		 for(counter = 0;counter < sizeof(array)/sizeof(*array);counter++){
			if (strcasecmp(obj->objclass, array[counter].typestring) == 0) {
				array[counter].dump(obj);
				flag = 1;
			}
    }
	if(flag==0){
            fprintf(stderr, "Bad class \"%s\" \n", obj->objclass);
            exit(1);
         }
   }
   
/** LIGHT DUMP **/
   l_reset(model->lights);
   while ((obj = l_get(model->lights)) != NULL)
   {
   		 for(counter = 0;counter < sizeof(array)/sizeof(*array);counter++){
			if (strcasecmp(obj->objclass, array[counter].typestring) == 0) {
				array[counter].dump(obj);
				flag = 1;
			}
    }
	if(flag==0){
            fprintf(stderr, "Bad class \"%s\" \n", obj->objclass);
            exit(1);
         }
   }

}
