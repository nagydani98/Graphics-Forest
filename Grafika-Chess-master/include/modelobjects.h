#if !defined(MODELOBJECTS_H)
#define MODELOBJECTS_H

#include <obj/model.h>
#include "scene.h"

typedef struct Deer
{
        Model deermodel;
        double x;
        double y;
        double z;
        double speed;
        //the current degree of rotation compared to vector i
        float current_direction; 
        /*the targeted angle into which we want to rotate into
        elso the direction in which the deer wants to move */
        float target_direction;
        //used for incrementing the current direction until it reaches the target
        float angle_increments;
        //flags for checking wther a deer is moving or rotating;
        int is_moving;
        int is_rotating;
        //target x,y coordanites to move to
        double target_x;
        double target_y;
        double incr_x;
        double incr_y;
} Deer;

void drawdeer(Deer* deer);
//performs setup operations
void initdeer(Deer* deer);

/*handles rotating the model into an angle at a constant speed 
over multiple iterations, incrementing the angle
compared to vector i with angle_increments*/
void rotateinto(Deer* deer);

//calculates how much we should increment the current angle each iteration
float calculate_angle_increment(Deer* deer);

void set_angle_increment(Deer* deer);

void move_towards_target(Deer* deer);

void generate_rnd_target(Deer* deer);

//this function directs all actions of a deer
void live(Deer* deer);
#endif // MODELOBJECTS_H
