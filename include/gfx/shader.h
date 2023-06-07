#ifndef SHADER_H
#define SHADER_H

struct shader
{
	GLuint vshader, fshader;
	GLuint program;
	const char *vpath, *fpath;
};

struct shader shader_load(const char *, const char *);

#endif