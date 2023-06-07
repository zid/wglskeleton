#include <stdlib.h>
#include "scene.h"
#include "gfx.h"

struct node
{
	struct model *m;
	struct node *next;
};

struct scene
{
	struct node *n;
};

struct scene *scene_new(void)
{
	struct scene *s;

	s = malloc(sizeof *s);
	if(!s)
		return NULL;

	s->n = NULL;

	return s;
}

void scene_attach(struct scene *s, struct model *m)
{
	struct node *n;

	n = malloc(sizeof *n);
	if(!n)
		return;

	n->m = m;
	n->next = s->n;

	s->n = n;
}

void scene_render(struct scene *s)
{
	struct node *n;

	for(n = s->n; n; n = n->next)
		model_draw(n->m);
}
