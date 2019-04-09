#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Camera camera;
    Model cube;
	Model p;
    Model king;
    Model queen;
    Model knight;
    Model rook;
    Model bishop;
    Model deer;
    Material material;
    GLuint texture_id;
    GLuint texture_id2;
    GLuint texture_id3;
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
void draw_scene(const Scene* scene, double elapsed_time);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
