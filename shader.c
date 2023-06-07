#include <stdio.h>
#include <stdlib.h>
#include "gl.h"
#include "gfx/shader.h"

static const char *load_txt(const char *name)
{
	FILE *f;
	size_t len;
	char *s;

	f = fopen(name, "rb");
	if(!f)
		return NULL;

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	rewind(f);

	s = malloc(len+1);
	fread(s, 1, len, f);

	s[len] = 0;

	fclose(f);

	return s;
}

static GLuint compile_shader(GLenum shader_type, const char *src)
{
	GLuint shader;
	GLint len;
	char *buf;

	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	buf = malloc(len);
	glGetShaderInfoLog(shader, len, NULL, buf);
	if(len)
		perror(buf);
	free(buf);

	return shader;
}

struct shader shader_load(const char *vtxt, const char *ftxt)
{
	struct shader s;
	const char *vsrc, *fsrc;

	vsrc = load_txt(vtxt);
	s.vshader = compile_shader(GL_VERTEX_SHADER, vsrc);
	s.vpath = strdup(vtxt);
	free((void *)vsrc);

	fsrc = load_txt(ftxt);
	s.fshader = compile_shader(GL_FRAGMENT_SHADER, fsrc);
	s.fpath = strdup(ftxt);
	free((void *)fsrc);

	s.program = glCreateProgram();
	glAttachShader(s.program, s.vshader);
	glAttachShader(s.program, s.fshader);
	glLinkProgram(s.program);

	return s;
}