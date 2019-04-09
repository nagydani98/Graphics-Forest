#include "scene.h"
#include "modelobjects.h"

#include <math.h>
#include <time.h>

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>


float posx = 0;


void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "res/cube.obj");
	load_model(&(scene->bishop), "res/bishop.obj");
	load_model(&(scene->p), "res/pawn.obj");
	load_model(&(scene->king), "res/king.obj");
	load_model(&(scene->rook), "res/rook.obj");
	load_model(&(scene->knight), "res/knight.obj");
    load_model(&(scene->deer), "res/deer.obj");
	
    scene->texture_id = load_texture("res/forest.jpg"); 
    scene->texture_id2 = load_texture("res/lighttexture.png");
    scene->texture_id2 = load_texture("res/else.png");

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

void set_lighting()
{
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuse_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float specular_light[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    float position[] = { 10.0f, 10.0f, 20.0f, 1.0f };

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

void draw_scene(const Scene* scene, double elapsed_time){
    char test;
    int random = 1;
    int rndpos = 0;
    Deer deer;

    (deer.deermodel)=scene->deer;

    srand(time(0));
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    /*glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id3);
        //glTranslatef(0.0, 3.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
	draw_model(&(scene->p));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
        glTranslatef(0.0, 5.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->king));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
        //glTranslatef(0.0, 0.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->bishop));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id3);
        glTranslatef(13.0, 20.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->king));
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
        glTranslatef(0.0, 30.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->rook));
    glPopMatrix();*/
	
    if(posx > 30){
        posx = 0;
    }

    random = rand();
    /*glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id2);       
        //glTranslatef(accum, 0.0, 0.0);
        glTranslatef(posx, 0.0, 0.0);
	    glRotatef(90,1,0,0);
        glRotatef(random,0,1,0);
        glScalef(0.075, 0.075, 0.075);
        draw_model(&(scene->deer));
    glPopMatrix();*/

    drawtest(&deer);
    
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    //glTranslatef(10.0, 30.0, 0.0);
	glRotatef(90,1,0,0);
    glScalef(30.0, 0.003, 30.0);
    draw_model(&(scene->cube));
    posx+=0.0002;
    posx*=1.01;
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