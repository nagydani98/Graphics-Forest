#include "modelobjects.h"
#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

float pos = 0;

void drawtest(Deer* deer){
    if(pos > 30){
        pos = 0;
    }

    glPushMatrix();
       // glBindTexture(GL_TEXTURE_2D, scene->texture_id2);       
        //glTranslatef(accum, 0.0, 0.0);
        glTranslatef(pos, 0.0, 0.0);
	    glRotatef(90,1,0,0);
        glRotatef(10,0,1,0);
        glScalef(0.075, 0.075, 0.075);
        draw_model(&(deer->deermodel));
    glPopMatrix();
    
    pos+=0.0002;
    pos*=1.001;

}