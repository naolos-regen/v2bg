#include "v2bg.h"
#include <stdio.h>
#include <unistd.h>

GLXContext	create_glx_context(t_ctx ctx)
{
	int			attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER,
					None};
	GLXContext	glx;

	ctx.vi = glXChooseVisual(ctx.dp, 0, attributes);
	if (!ctx.vi)
	{
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}
	glx = glXCreateContext(ctx.dp, ctx.vi, NULL, GL_TRUE);
	glXMakeCurrent(ctx.dp, ctx.win, glx);
	return (glx);
}

void	CTXFree(t_ctx ctx)
{
	if (ctx.dp && ctx.glx)
	{
		glXMakeCurrent(ctx.dp, None, NULL);
		glXDestroyContext(ctx.dp, ctx.glx);
	}
	if (ctx.vi)
		XFree(ctx.vi);
	XCloseDisplay(ctx.dp);
}

void	render_loop(t_ctx ctx, void (*Draw_Foreground)(t_ctx))
{
	ctx.glx = create_glx_context(ctx);
	if (!ctx.glx)
		return ;
	while (1)
	{
		Draw_Foreground(ctx);
		usleep(16666); // ~60fps
	}
	CTXFree(ctx);
}
