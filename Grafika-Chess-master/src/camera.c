#include "camera.h"

#include <GL/glut.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 1.564245; //x: 1.564245,y: 1.807708,z: 1.117000
    camera->position.y = 1.807708;
    camera->position.z = 1.117000;
    camera->rotation.x = 336.0; //x: 336.000000,y: 0.000000,z: 229.000000
    camera->rotation.y = 0.0;
    camera->rotation.z = 229.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    is_help_visible = FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	double vertical_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
	vertical_angle = degree_to_radian(camera->rotation.y + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
	camera->position.z += cos(vertical_angle) * camera->speed.z * time;
	camera->position.z += sin(vertical_angle) * camera->speed.z * time;
	//printf("x: %lf,y: %lf,z: %lf", camera->rotation.x, camera->rotation.y, camera->rotation.z);
	//printf("x: %lf,y: %lf,z: %lf", camera->position.x, camera->position.y, camera->position.z);
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 0.1, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 0.1);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed*3;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed*3;
}

void set_camera_vertical_speed(Camera* camera, double speed){
	camera->speed.z = speed*3;
}

void show_help()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("res/guide.png"));
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -5);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -5);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -5);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -5);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

