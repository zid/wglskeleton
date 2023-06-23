#include <stdio.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "game.h"

int main(void)
{
	Display *d;
	Window win;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	GLXContext g;
	GLXFBConfig *fb;
	GLXContext (*glXCreateContextAttribsARB)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
	int major, minor, r, count;

	const int visual_attribs[] =
	{
		GLX_X_RENDERABLE,   True,
		GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,    GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_ALPHA_SIZE,     8,
		GLX_DEPTH_SIZE,     24,
		GLX_DOUBLEBUFFER,   True,
		GLX_SAMPLE_BUFFERS, 1,
		GLX_SAMPLES,        4,
		None
	};

	const int context_attribs[] =
	{
		GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
		GLX_CONTEXT_MINOR_VERSION_ARB, 5,
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		0, 0
	};

	d = XOpenDisplay(NULL);

	r = glXQueryVersion(d, &major, &minor);
	if(!r || major < 1 || (major == 1 && minor < 3))
	{
		fprintf(stderr, "GLX Version < 1.3\n");
		return 1;
	}

	fb = glXChooseFBConfig(d, DefaultScreen(d), visual_attribs, &count);
	if(!fb)
	{
		fprintf(stderr, "glXChooseFBConfig failed\n");
		return 1;
	}

	/* Just take the first valid FBConfig */
	vi = glXGetVisualFromFBConfig(d, fb[0]);

	if(!vi)
	{
		fprintf(stderr, "No appropriate visual found.\n");
		return 1;
	}

	cmap = XCreateColormap(d, RootWindow(d, vi->screen), vi->visual, AllocNone);

	swa.colormap          = cmap;
	swa.background_pixmap = None;
	swa.event_mask        = ExposureMask | KeyPressMask;

	win = XCreateWindow(
	    d,
	    RootWindow(d, vi->screen),
	    0, 0,
	    1600, 900,
	    0,
	    vi->depth,
	    InputOutput,
	    vi->visual,
	    CWColormap | CWEventMask,
	    &swa
	);

	if(!win)
	{
		fprintf(stderr, "Failed to create window.\n");
		return 1;
	}

	XFree(vi);
	
	XMapWindow(d, win);
	XStoreName(d, win, "OpenGL Test");


	glXCreateContextAttribsARB = (void *)glXGetProcAddressARB((const unsigned char *)"glXCreateContextAttribsARB");

	g = glXCreateContextAttribsARB(d, fb[0], 0, True, context_attribs);
	if(!g)
	{
		fprintf(stderr, "Failed to create Opengl context.\n");
		return 1;
	}

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

