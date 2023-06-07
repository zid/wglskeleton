#include "game.h"
#include "gfx.h"
#include "model.h"
#include "scene.h"

static struct scene *s;

void game_reload(void)
{

}

void game_init(void)
{
	struct model *m;

	gfx_init();

	s = scene_new();

	model_init_from_square(&m);
	model_set_shader(m, "meow.vshade", "meow.fshade");
	scene_attach(s, m);
}

void game(void)
{
	gfx_clear();
	scene_render(s);
}