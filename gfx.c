#include <stdlib.h>
#include "gl.h"
#include "gfx.h"
#include "gfx/common.h"
#include "gfx/geom.h"
#include "gfx/shader.h"
#include "model.h"

static void gfx_init_vao(struct gfx *g)
{
	glGenVertexArrays(1, &g->v.vao);
	glGenBuffers(2, g->v.vbo);

	glBindVertexArray(g->v.vao);
	glBindBuffer(GL_ARRAY_BUFFER, g->v.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, g->verts_sizeb, g->verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->v.vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, g->indices_sizeb, g->indices, GL_STATIC_DRAW);
}

struct gfx *gfx_load_square(void)
{
	struct gfx *g;

	g = malloc(sizeof *g);
	if(!g)
		return NULL;

	gfx_geom_load_square(g);

	gfx_init_vao(g);

	return g;
}

void gfx_load_shader(struct gfx *g, const char *vsrc, const char *fsrc)
{
	g->shader = shader_load(vsrc, fsrc);
}

void gfx_reload_shaders(void)
{
	
}

void gfx_init(void)
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH);
}

void gfx_clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx_draw(struct gfx *g)
{
	glUseProgram(g->shader.program);
	glBindVertexArray(g->v.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}