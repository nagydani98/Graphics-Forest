#if !defined(MODELOBJECTS_H)
#define MODELOBJECTS_H

#include <obj/model.h>

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
        //the time each deer has till its death, decremented in live() function
        double time_to_live;
        //bounding radius is the distance at which two deers count as touching
        double bounding_radius;
} Deer;

void drawdeer(Deer* deer);
//performs setup operations
void initdeer(Deer* deer, double x, double y);
void initdefaultdeer(Deer* deer);

/*handles rotating the model into an angle at a constant speed 
over multiple iterations, incrementing the angle
compared to vector i with angle_increments*/
void rotateinto(Deer* deer);

//calculates how much we should increment the current angle each iteration
float calculate_angle_increment(Deer* deer);

void set_angle_increment(Deer* deer);

void move_towards_target(Deer* deer);

void generate_rnd_target(Deer* deer);

void calculate_target(Deer* deer, float newdirection, float newdistance);

//checks wether the deer has moved outside the allowed perimeter
void check_field_boundaries(Deer* deer);

//this function directs all actions of a deer
void live(Deer* deer);
//all actions a deer performs, once its time_to_live reaches 0
void destroydeer(Deer* deer);

void setspeed(Deer* deer, double speed);

//detects collision by calculating distance between each deer
void detect_collisions(Deer deer[], int number_of_deer);
//resolves the collision between two deers
void resolve_collision(Deer deer[], int index_i, int index_j);
#endif // MODELOBJECTS_H
