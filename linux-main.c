#include <stdio.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "game.h"

int main(void)
{
	Display *d;
	Window root, win;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	GLXContext g;

	d = XOpenDisplay(NULL);
	printf("%p\n", d);

	root = DefaultRootWindow(d);
	vi = glXChooseVisual(d, 0, (GLint[5]){GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None});

	if(!vi)
	{
		fprintf(stderr, "No appropriate visual found.\n");
		return 0;
	}

	cmap = XCreateColormap(d, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(
	    d, root, 0, 0, 1600, 900, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa
	);

	XMapWindow(d, win);
	XStoreName(d, win, "OpenGL Test");

	g = glXCreateContext(d, vi, NULL, GL_TRUE);
	glXMakeCurrent(d, win, g);

	game_init();

	while(1)
	{
		XEvent ev;

		if(!XPending(d))
		{
			game();
			glXSwapBuffers(d, win);
			continue;
		}

		XNextEvent(d, &ev);

		if(ev.type == Expose)
		{
			XWindowAttributes wa;

			XGetWindowAttributes(d, win, &wa);
			glViewport(0, 0, wa.width, wa.height);
		}
		else if(ev.type == KeyPress && ev.xkey.keycode == 9)
		{
			glXMakeCurrent(d, None, NULL);
			glXDestroyContext(d, g);
			XDestroyWindow(d, win);
			XCloseDisplay(d);
			return 0;
		}
	}

	return 0;
}

