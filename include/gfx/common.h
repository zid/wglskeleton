#ifndef GFX_GFX_H
#define GFX_GFX_H

#include <stddef.h>
#include "gl.h"
#include "gfx/shader.h"

struct vao
{
	GLuint vao;
	GLuint vbo[2];
};

struct gfx
{
	float *verts;
	unsigned short *indices;

	size_t verts_sizeb, indices_sizeb;
	struct shader shader;
	struct vao v;
};

#endif