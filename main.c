#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Display	*initialize_display(void)
{
	Display	*display;

	display = XOpenDisplay(NULL);
	if (!display)
	{
		fprintf(stderr, "Cannot open display\n");
		return (NULL);
	}
	return (display);
}

int	get_default_screen(Display *dp)
{
	return (DefaultScreen(dp));
}

Window	get_root_window(Display *dp, int screen)
{
	return (RootWindow(dp, screen));
}

Window	create_fullscreen_window(Display *dp, Window root, int screen)
{
	return (XCreateSimpleWindow(dp, root, 0, 0, DisplayWidth(dp, screen),
			DisplayHeight(dp, screen), 0, WhitePixel(dp, screen), BlackPixel(dp,
				screen)));
}

int	change_property(Display *dp, Window win)
{
	Atom	window_type;
	Atom	window_type_desktop;

	window_type = XInternAtom(dp, "_NET_WM_WINDOW_TYPE", False);
	window_type_desktop = XInternAtom(dp, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
	return (XChangeProperty(dp, win, window_type, XA_ATOM, 32, PropModeReplace,
			(unsigned char *)&window_type_desktop, 1));
}

int	attributes(Display *dp, const Window win)
{
	XSetWindowAttributes	attrs;

	attrs.override_redirect = True;
	return (XChangeWindowAttributes(dp, win, CWOverrideRedirect, &attrs));
}

void	lower_to_background(const Display *dp, const Window win)
{
	XMapWindow((Display *)dp, win);
	XLowerWindow((Display *)dp, win);
	XFlush((Display *)dp);
}

GLXContext	create_glx_context(Display *dp, Window win)
{
	int			attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER,
					None};
	XVisualInfo	*vi;
	GLXContext	glc;

	vi = glXChooseVisual(dp, 0, attribs);
	if (!vi)
	{
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}
	glc = glXCreateContext(dp, vi, NULL, GL_TRUE);
	glXMakeCurrent(dp, win, glc);
	return (glc);
}

void	render_loop(Display *dp, Window win)
{
	GLXContext	glc;

	glc = create_glx_context(dp, win);
	if (!glc)
		return ;
	while (1)
	{
		glClearColor(0.0, 0.2, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glXSwapBuffers(dp, win);
		usleep(16000); // ~60fps
	}
	XCloseDisplay(dp);
}

int	create_destroy_loop(void)
{
	Display	*dp;
	int		screen;

	Window root, win;
	dp = initialize_display();
	screen = get_default_screen(dp);
	root = get_root_window(dp, screen);
	win = create_fullscreen_window(dp, root, screen);
	change_property(dp, win);
	attributes(dp, win);
	lower_to_background(dp, win);
	render_loop(dp, win);
	return (0);
}

int	main(void)
{
	return (create_destroy_loop());
}
