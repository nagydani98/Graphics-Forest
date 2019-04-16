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
        glTranslatef(deer->x, 0.0, deer->y);
        draw_model(&(deer->deermodel));
    glPopMatrix();
}

void initdeer(Deer* deer){
    int help = 0;
    deer->speed = 1;
    deer->is_rotating = 0;
    deer->is_moving = 0;
    deer->current_direction = 0;
    deer->x = 0;
    deer->y = 0;

    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&help);
}

void rotateinto(Deer* deer){ 
    glTranslatef(deer->x, deer->y, 0.0);
    
    if(((deer->angle_increments != 0) && (deer->current_direction != deer->target_direction))){
        deer->current_direction+=deer->angle_increments;
    } 
    if ((fabs(deer->target_direction - deer->current_direction + 0.000001) < fabs(deer->angle_increments))) {
        deer->current_direction = deer->target_direction;
        deer->is_rotating = 0;
        deer->is_moving = 1;
    }
    glRotatef(radian_to_degree(deer->current_direction),0,0,1);
    glTranslatef(0.0, 0.0, 0.0);
    return ;
}

float calculate_angle_increment(Deer* deer){
    float increment = 1;
        increment = (deer->target_direction - deer->current_direction) / 500;
    return increment;
}

void set_angle_increment(Deer* deer){
    if (deer->target_direction != 0) {
        float increment = calculate_angle_increment(deer);
        deer->angle_increments = increment;
    }
}


void move_towards_target(Deer* deer){

    if(fabs(deer->target_x - deer->x) > fabs(deer->incr_x)){
        deer->x += deer->incr_x * deer->speed;
    }
    if(fabs(deer->target_x - deer->x) <= fabs(deer->incr_x)){
        deer->x = deer->target_x;
    }
    if(fabs(deer->target_y - deer->y) > fabs(deer->incr_y)){
        deer->y += deer->incr_y * deer->speed;
    }
    if(fabs(deer->target_y - deer->y) <= fabs(deer->incr_y)){
        deer->y = deer->target_y;
    }
    if((deer->x == deer->target_x) && (deer->y == deer->target_y)){
        deer->is_moving = 0;
    }
    
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void generate_rnd_target(Deer* deer){
    deer->target_direction = degree_to_radian((int)pcg32_boundedrand_r(&rng, 340) + 20);
    //rand() % (341) + 20;
    //printf("test angle: %d\n", (int)pcg32_boundedrand_r(&rng, 360));
    float rnddistance = randfrom(5, 20);
    deer->target_x = cos(deer->target_direction) * rnddistance;
    deer->target_y = sin(deer->target_direction) * rnddistance;

    printf("angle: %.6f x:%.6f y:%.6f distance: %.6f\n", deer->target_direction,
    deer->target_x,
    deer->target_y,
     rnddistance);
}

void set_xy_increment(Deer* deer){
        if(deer->target_x != deer->x){
        deer->incr_x =   (deer->target_x - deer->x) * 0.001;
        } 
        else deer->incr_x = 0;

        if(deer->target_y != deer->y){
        deer->incr_y = (deer->target_y - deer->y) * 0.001;
        } 
        else deer->incr_y = 0;
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
    drawdeer(deer);
}




