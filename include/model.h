#ifndef MODEL_H
#define MODEL_H

struct model;

void model_init_from_square(struct model **);
void model_init_from_bin(struct model **, const char *);
void model_set_shader(struct model *, const char *, const char *);
void model_draw(struct model *);

#endif
