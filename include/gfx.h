#ifndef GFX_H
#define GFX_H

struct gfx;

#include "model.h"

void gfx_reload_shaders(void);
void gfx_init(void);
void gfx_draw(struct gfx *);
void gfx_clear(void);

struct gfx *gfx_load_square(void);
void gfx_load_shader(struct gfx *, const char *, const char *);

#endif