#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_ctx	initialize_display(void)
{
	t_ctx	ctx;

	ctx.dp = XOpenDisplay(NULL);
	if (!ctx.dp)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
	ctx.screen = DefaultScreen(ctx.dp);
	ctx.root = RootWindow(ctx.dp, ctx.screen);
	return (ctx);
}

t_ctx	create_window_ctx(t_ctx ctx)
{
	ctx.win = XCreateSimpleWindow(ctx.dp, ctx.root, 0, 0, DisplayWidth(ctx.dp,
				ctx.screen), DisplayHeight(ctx.dp, ctx.screen), 0,
			WhitePixel(ctx.dp, ctx.screen), BlackPixel(ctx.dp, ctx.screen));
	return (ctx);
}
t_ctx	change_property(t_ctx ctx)
{
	Atom	window_type;
	Atom	window_type_desktop;

	window_type = XInternAtom(ctx.dp, "_NET_WM_WINDOW_TYPE", False);
	window_type_desktop = XInternAtom(ctx.dp, "_NET_WM_WINDOW_TYPE_DESKTOP",
			False);
	XChangeProperty(ctx.dp, ctx.win, window_type, XA_ATOM, 32, PropModeReplace,
		(unsigned char *)&window_type_desktop, 1);
	return (ctx);
}

t_ctx	attributes_ctx(t_ctx ctx)
{
	XSetWindowAttributes	attrs;

	attrs.override_redirect = True;
	XChangeWindowAttributes(ctx.dp, ctx.win, CWOverrideRedirect, &attrs);
	return (ctx);
}

t_ctx	lower_to_background(t_ctx ctx)
{
	XMapWindow(ctx.dp, ctx.win);
	XLowerWindow(ctx.dp, ctx.win);
	XFlush(ctx.dp);
	return (ctx);
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
	t_ctx	ctx;

	ctx = initialize_display();
	ctx = create_window_ctx(ctx);
	ctx = change_property(ctx);
	ctx = attributes_ctx(ctx);
	ctx = lower_to_background(ctx);
	render_loop(ctx.dp, ctx.win);
	return (0);
}

int	main(void)
{
	return (create_destroy_loop());
}
