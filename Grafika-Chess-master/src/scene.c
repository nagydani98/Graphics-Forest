#include "scene.h"
#include "modelobjects.h"

#include <math.h>
#include <time.h>

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/model.h>

void init_scene(Scene* scene)
{
    scene->are_deers_stopped = 0;
    scene->light_strength = 1;
    int i = 0;
    scene->num_of_deer = 8;
    for(i = 0; i < scene->num_of_deer; i++)
    {
        load_model(&(scene->deer[i].deermodel), "res/deer.obj");
        
        initdeer(&(scene->deer[i]), i*2, i*2);
    }

    load_model(&(scene->cube), "res/cube.obj");
    load_model(&(scene->skybox), "res/compatiblebox.obj");
    
    
	
    scene->texture_id = load_texture("res/grass.jpg"); 
    scene->texture_id2 = load_texture("res/lighttexture.png");
    scene->texture_id3 = load_texture("res/deertexture.jpg");
    scene->texture_id4 = load_texture("res/dead.png");
    scene->sky_tex = load_texture("res/skybox2.png");

    

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.0;
}

void set_lighting(double light_strength)
{
    int i;
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuse_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float specular_light[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    float position[] = { 10.0f, 10.0f, 20.0f, 1.0f };

    for(i = 0; i < 3; i++){
        ambient_light[i]*=light_strength;
        diffuse_light[i]*=light_strength;
        specular_light[i]*=light_strength;
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene){
    int i;
    draw_origin();
    set_material(&(scene->material));
    set_lighting(scene->light_strength);
    
    glPushMatrix(); 
    glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90,1,0,0);
    glScalef(30.0, 0.003, 30.0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    draw_model(&(scene->cube));
    glPopMatrix();

    draw_skybox(scene);

    for (i = 0; i < scene->num_of_deer; i++)
    {
        glPushMatrix(); 
        if((scene->deer[i]).time_to_live > 0){
            glBindTexture(GL_TEXTURE_2D, scene->texture_id3);
            live(&(scene->deer[i]));
        }
        else {
            glBindTexture(GL_TEXTURE_2D, scene->texture_id4);
            live(&(scene->deer[i]));
        }
        glPopMatrix();
        if(scene->are_deers_stopped == 1){
            setspeed(&(scene->deer[i]), 0);
        }
        else setspeed(&(scene->deer[i]), 1);
    }
    detect_collisions(scene->deer, scene->num_of_deer);
    
    

    
}

void draw_skybox(Scene* scene){
    /*double boxcoordsx[] = {10, 10, -10, -10, 10, 10, -10, -10};
    double boxcoordsy[] = {10, -10, -10, 10, 10, -10, -10, 10};
    double boxcoordsz[] = {10, 10, 10, 10, -10, -10, -10, -10};

    double facex[][3] = {{10, 10, 10}, {10, 10, -10,}, {10, -10, 10}, {10, -10, -10}};
    double facey[][3] = {{10, 10, 10}, {10, 10, -10,}, {-10, 10, 10}, {-10, 10, -10}};
    double facez[][3] = {{10, 10, 10}, {10, -10, 10,}, {-10, 10, 10}, {-10, -10, 10}};

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->sky_tex);
        glBegin(GL_POLYGON);
        glVertex3d(facex[0][0], facex[0][1], facex[0][2]);
        glVertex3d(facex[1][0], facex[1][1], facex[1][2]);
        glVertex3d(facex[2][0], facex[2][1], facex[2][2]);
        glVertex3d(facex[3][0], facex[3][1], facex[3][2]);
        glEnd();
    glPopMatrix();*/

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->sky_tex);
        //glTranslatef(1.0, 0.0, 0.0);
        //glTranslatef(0.0, 1.0, 0.0);
        glScalef(100, 100, 100);
	    draw_model(&(scene->skybox));
    glPopMatrix();
}

/*void transform(){
    glPushMatrix();



    glPopMatrix();
}*/

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

static void myShadowMatrix(float ground[4], float light[4])
{
    float  dot;
    float  shadowMat[4][4];

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];
    
    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];
    
    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];
    
    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];
    
    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];

    glMultMatrixf((const GLfloat*)shadowMat);
}

void draw_skybox_bottom(Scene* scene)
{
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 36;
    n_stacks = 18;
    radius = 10000.0;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_tex);
    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, -z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, -z2);
        }
    }

    glEnd();
    glPopMatrix();
}



void draw_skybox_top(Scene* scene)
{
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 36;
    n_stacks = 18;
    radius = 10000.0;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->sky_tex);
    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

	glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)i / n_stacks;
        v2 = (double)(i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();
    glPopMatrix();
}