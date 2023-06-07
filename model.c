#include <stdlib.h>
#include "model.h"
#include "gfx.h"

struct model
{
	struct gfx *g;
};

void model_set_shader(struct model *m, const char *vtxt, const char *ftxt)
{
	gfx_load_shader(m->g, vtxt, ftxt);
}

static struct model *model_new(void)
{
	struct model *m;

	m = malloc(sizeof *m);
	if(!m)
		return NULL;

	m->g = NULL;

	return m;
}

void model_draw(struct model *m)
{
	gfx_draw(m->g);
}

void model_init_from_square(struct model **m)
{
	*m = model_new();
	if(!*m)
		return;

	(*m)->g = gfx_load_square();
}

