#include "callbacks.h"
#include "ctype.h"
#include "utils.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_help_visible) {
        show_help();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    
	
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
   if ((button == 3) || (button == 4)) // It's a wheel event
   {
       // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
       if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
       (button == 3) ? set_camera_speed(&camera, 1) : set_camera_speed(&camera, -1);
   }else{  // normal button event
       (state == GLUT_DOWN) ? set_camera_speed(&camera, -1) : set_camera_speed(&camera, 1);
		mouse_position.x = x;
		mouse_position.y = y;
   }
	set_camera_speed(&camera, 0.0);
}

void motion(int x, int y)
{
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    key = tolower(key);
    switch (key) {
    case 'w':
        set_camera_speed(&camera, 1);
        break;
    case 's':
        set_camera_speed(&camera, -1);
        break;
    case 'a':
        set_camera_side_speed(&camera, 1);
        break;
    case 'd':
        set_camera_side_speed(&camera, -1);
        break;
	case 'e':
        set_camera_vertical_speed(&camera, 1);
        break;
	case 'q':
        set_camera_vertical_speed(&camera, -1);
        break;
    case 't':
        if (is_help_visible) {
            is_help_visible = FALSE;
        }
        else {
            is_help_visible = TRUE;
        }
        break;
    case 'r':
        if(!scene.are_deers_stopped){
            scene.are_deers_stopped = 1;
        }
        else scene.are_deers_stopped = 0;
        break;
    case '+':
        scene.light_strength+=0.5;
        break;
    case '-':
        scene.light_strength-=0.5;
        break;
    case 27:
        exit(0);
        break;
    }
    
    glutPostRedisplay();
}


void keyboard_up(unsigned char key, int x, int y)
{
    key = tolower(key);
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
	case 'e':
	case 'q':
        set_camera_vertical_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    //printf(" %.6f ", elapsed_time);

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}
