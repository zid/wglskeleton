#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gfx/common.h"
#include "gfx/geom.h"

static const float square_verts[] =
{
	-1.0, -1.0, 0.0, /* Top Left */
	 1.0, -1.0, 0.0, /* Top Right */
	-1.0,  1.0, 0.0, /* Bottom Left */
	 1.0,  1.0, 0.0  /* Bottom Right */
};

static const unsigned short square_indices[] =
{
	0, 1, 3,
	0, 3, 2
};

void gfx_geom_load_square(struct gfx *g)
{
	g->verts = malloc(sizeof square_verts);
	if(!g->verts)
		goto err1;
	memcpy(g->verts, square_verts, sizeof square_verts);
	g->verts_sizeb = sizeof square_verts;

	g->indices = malloc(sizeof square_indices);
	if(!g->indices)
		goto err2;
	memcpy(g->indices, square_indices, sizeof square_indices);
	g->indices_sizeb = sizeof square_indices;

	return;

err2:
	free(g->verts);
	g->verts = NULL;
err1:
	return;
}

void gfx_geom_load_bin(struct gfx *g, const char *path)
{
	FILE *f;
	unsigned char a[4];
	size_t vert_bytes, elem_bytes;

	f = fopen(path, "rb");
	if(!f)
		return;

	if(fread(a, 1, 4, f) != 4)
		goto err1;

	vert_bytes = a[3]<<24 | a[2]<<16 | a[1]<<8 | a[0];

	if(vert_bytes < 4 || vert_bytes > 100000000)
		goto err1;

	g->verts = malloc(vert_bytes);
	if(!g->verts)
		goto err1;

	if(fread(g->verts, 1, vert_bytes, f) != vert_bytes)
		goto err2;

	if(fread(a, 1, 4, f) != 4)
		goto err2;

	elem_bytes = a[3]<<24 | a[2]<<16 | a[1]<<8 | a[0];
	if(elem_bytes < 6 || elem_bytes > 1000000000)
		goto err2;

	g->indices = malloc(elem_bytes);
	if(!g->indices)
		goto err2;

	if(fread(g->indices, 1, elem_bytes, f) != elem_bytes)
	{
		free(g->indices);
		g->indices = NULL;
		goto err2;
	}

	g->verts_sizeb = vert_bytes;
	g->indices_sizeb = elem_bytes;

	return;
err2:
	free(g->verts);
	g->verts = NULL;
err1:
	fclose(f);
	return;
}
