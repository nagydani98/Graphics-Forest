#include "modelobjects.h"
#include "scene.h"
#include "callbacks.h"
#include "pcg_basic.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

#include <math.h>
#include <time.h>
#include <stdint.h>


pcg32_random_t rng;

void drawdeer(Deer* deer){
    glPushMatrix();     
	    glRotatef(90,1,0,0);
        glScalef(0.075, 0.075, 0.075);
        glTranslatef(deer->x, deer->z, deer->y);
        draw_model(&(deer->deermodel));
    glPopMatrix();
}

void initdefaultdeer(Deer* deer){
    int help = 0;
    deer->speed = 1;
    deer->is_rotating = 0;
    deer->is_moving = 0;
    deer->current_direction = 0;
    deer->x = 0;
    deer->y = 0;
    deer->z = 0;
    deer->time_to_live = 50000;
    deer->bounding_radius = 0.5;

    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&help);
}

void initdeer(Deer* deer, double x, double y){
    int help = 0;
    deer->speed = 1;
    deer->is_rotating = 0;
    deer->is_moving = 0;
    deer->current_direction = 0;
    deer->x = x;
    deer->y = y;
    deer->z = 0;
    deer->time_to_live = 20000;
    deer->bounding_radius = 0.5;

    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&help);
}

void rotateinto(Deer* deer){ 
    glTranslatef(deer->x, deer->y, 0.0);
    
    if(deer->time_to_live >=0){
        if(((deer->angle_increments != 0) && (deer->current_direction != deer->target_direction))){
         deer->current_direction+=deer->angle_increments*elapsed_time;
        } 
        if ((fabs(deer->target_direction - deer->current_direction + 0.0001) < fabs(deer->angle_increments)*elapsed_time)) {
            deer->current_direction = deer->target_direction;
            deer->is_rotating = 0;
            deer->is_moving = 1;
        }
    }
    glRotatef(radian_to_degree(deer->current_direction),0,0,1);
    glTranslatef(0.0, 0.0, 0.0);
    return ;
}

void move_towards_target(Deer* deer){
    double desired_proximity = 0.01;
    if(deer->time_to_live >=0){
    if(fabs(deer->target_x - deer->x) > fabs(deer->incr_x)*desired_proximity){
        deer->x += (deer->incr_x * deer->speed * elapsed_time);
    }
    if(fabs(deer->target_x - deer->x) <= fabs(deer->incr_x)*desired_proximity){
        deer->x = deer->target_x;
    }
    if(fabs(deer->target_y - deer->y) > fabs(deer->incr_y) * desired_proximity){
        deer->y += (deer->incr_y * deer->speed * elapsed_time);
    }
    if(fabs(deer->target_y - deer->y) <= fabs(deer->incr_y) * desired_proximity){
        deer->y = deer->target_y;
    }
    if((deer->x == deer->target_x) && (deer->y == deer->target_y)){
        deer->is_moving = 0;
    }
    }
    
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void generate_rnd_target(Deer* deer){
    float newdirection = degree_to_radian((int)pcg32_boundedrand_r(&rng, 340) + 20);
    float rnddistance = randfrom(5, 20);
    
    calculate_target(deer, newdirection, rnddistance);

    printf("angle: %.6f x:%.6f y:%.6f distance: %.6f\n", deer->target_direction,
    deer->target_x,
    deer->target_y,
     rnddistance);
}

void calculate_target(Deer* deer, float newdirection, float newdistance){
    deer->target_direction = newdirection;
    deer->target_x = cos(deer->target_direction) * newdistance + deer->x;
    deer->target_y = sin(deer->target_direction) * newdistance + deer->y;
}

void set_xy_increment(Deer* deer){
        if(deer->target_x != deer->x){
        deer->incr_x =   (deer->target_x - deer->x) * 0.5;
        } 
        else deer->incr_x = 0;

        if(deer->target_y != deer->y){
        deer->incr_y = (deer->target_y - deer->y) * 0.5;
        } 
        else deer->incr_y = 0;
}

float calculate_angle_increment(Deer* deer){
    float increment = 1;
        increment = (deer->target_direction - deer->current_direction) / 2;
    return increment;
}

void set_angle_increment(Deer* deer){
    if (deer->target_direction != 0) {
        float increment = calculate_angle_increment(deer);
        deer->angle_increments = increment;
    }
}

void live(Deer* deer){
        if(!deer->is_rotating && !deer->is_moving){
            deer->is_rotating = 1;
            deer->is_moving = 0;
            generate_rnd_target(deer);
            set_xy_increment(deer);
            set_angle_increment(deer);
            printf("set angle incr: %.6f", deer->angle_increments);

            }
        if(deer->is_rotating && !deer->is_moving){
            rotateinto(deer);
            //printf("is rotating: %.6f ", deer->angle_increments);
        }

        if(!(deer->is_rotating) && deer->is_moving){
            rotateinto(deer);
            move_towards_target(deer);
            //printf("is moving ");
        }

        if(deer->time_to_live <= 0){
            destroydeer(deer);
        }
        drawdeer(deer);
        check_field_boundaries(deer);
        deer->time_to_live = deer->time_to_live -  elapsed_time;
    }




void destroydeer(Deer* deer){
        if(deer->z >= -20){ 
            deer->z+= -elapsed_time*10;
        }
}

void check_field_boundaries(Deer* deer){
    int distance_limit = 10;

    /*deer's current position that's over the limit is reduced
    by this setback, so that the next time we check if it is
    outside the boundaries, it won't get its movement reset
    and thus will not get stuck*/
    float boundary_setback = 0.01;
    if(deer->x >= distance_limit){
        deer->is_moving = 0;
        deer->is_rotating = 0;
        deer->x =  deer->x - boundary_setback;
    }
    if(deer->x <= -distance_limit){
        deer->is_moving = 0;
        deer->is_rotating = 0;
        deer->x = deer->x + boundary_setback;
    }
    if(deer->y >= distance_limit){
        deer->is_moving = 0;
        deer->is_rotating = 0;
        deer->y = deer->y - boundary_setback;
    }
    if(deer->y <= -distance_limit){
        deer->is_moving = 0;
        deer->is_rotating = 0;
        deer->y = deer->y + boundary_setback;
    }
}

void setspeed(Deer* deer, double speed){
    deer->speed = speed;
}

void detect_collisions(Deer deer[], int number_of_deer){
    int i, j;
    double distancex, distancey, distance;
    for(i = 0; i < number_of_deer; i++){
        if(deer[i].time_to_live > 0){
            for(j = i + 1; j < number_of_deer; j++){
                if(deer[j].time_to_live > 0){
                   distancex = deer[i].x - deer[j].x;
                   distancey = deer[i].y - deer[j].y;
                   distance = sqrt(distancex*distancex + distancey*distancey);
                   if(distance <= (deer[i].bounding_radius + deer[j].bounding_radius)){
                       resolve_collision(deer, i, j);
                   }
                }
            }
        }
    }
}

void resolve_collision(Deer deer[], int index_i, int index_j){
    deer[index_i].is_moving = 0;
    deer[index_i].is_rotating = 0;
    calculate_target(&deer[index_i], deer[index_i].target_direction + M_PI, 0.1);
    deer[index_i].x = deer[index_i].target_x;
    deer[index_i].y = deer[index_i].target_y;

    deer[index_j].is_moving = 0;
    deer[index_j].is_rotating = 0;
    calculate_target(&deer[index_j], deer[index_j].target_direction + M_PI, 0.1);
    deer[index_j].x = deer[index_j].target_x;
    deer[index_j].y = deer[index_j].target_y;
}



