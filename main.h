#ifndef MAIN_H
# define MAIN_H

# include <GL/gl.h>
# include <GL/glx.h>
# include <X11/Xatom.h>
# include <X11/Xlib.h>

typedef struct s_ctx
{
	Display	*dp;
	Window	win;
	Window	root;
	int		screen;
}			t_ctx;

// x11

// GLX | GL
#endif
