#include <stdlib.h>
#include <string.h>
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
