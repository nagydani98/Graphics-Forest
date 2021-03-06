#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "modelobjects.h"

#include <obj/model.h>

typedef struct Scene
{
    Camera camera;
    Model cube;
    Deer deer[100];
    Model skybox;
    Material material;
    GLuint texture_id;
    GLuint texture_id2;
    GLuint texture_id3;
    GLuint texture_id4;
    GLuint sky_tex;
    int num_of_deer;
    int are_deers_stopped;
    double light_strength;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
