#ifndef SCENE_H
#define SCENE_H

#include "model.h"

struct scene;

struct scene *scene_new(void);
void scene_attach(struct scene *, struct model *);
void scene_render(struct scene *);

#endif