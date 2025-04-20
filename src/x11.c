#include "../includes/v2bg.h"
#include "../includes/atoms.h"
#include <stdio.h>
#include <stdlib.h>

t_ctx	*init_display(void)
{
	t_ctx	*ctx;
	
	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
	{	
		error_msg(ctx, "couldn't allocate failed\n");
		return (NULL);
	}
	ctx->dp = XOpenDisplay(NULL);
	if (!ctx->dp)
	{
		error_msg(ctx, "Cannot open display\n");
		return (NULL);
	}
	ctx->screen = DefaultScreen(ctx->dp);
	ctx->root   = RootWindow(ctx->dp, ctx->screen);
	return (ctx);
}

t_ctx	*create_window(t_ctx *ctx)
{
	ctx->win = XCreateSimpleWindow(ctx->dp, ctx->root, 0, 0, DisplayWidth(ctx->dp,
				ctx->screen), DisplayHeight(ctx->dp, ctx->screen), 1,
			BlackPixel(ctx->dp, ctx->screen), WhitePixel(ctx->dp, ctx->screen));
	// read more about XSelectInput Enums
	
	XSelectInput(ctx->dp, ctx->win, FocusChangeMask | ExposureMask | KeyPressMask | ButtonPressMask);

	return (ctx);
}

t_ctx	*change_property(t_ctx *ctx)
{
	Atom	*atoms;
	int	p_cx;
	XChangeProperty(ctx->dp, ctx->win, 
		        ctx->atoms[ATOM_NET_WM_WINDOW_TYPE].atom, 
		        XA_ATOM, 32, PropModeReplace,
			(unsigned char *)&ctx->atoms[ATOM_NET_WM_WINDOW_TYPE_DESKTOP].atom, 1);
	XChangeProperty(ctx->dp, ctx->win,
			ctx->atoms[ATOM_NET_WM_STATE].atom,
			XA_ATOM, 32, PropModeReplace,
			(unsigned char *)&ctx->atoms[ATOM_NET_WM_STATE_BELOW].atom, 1);
	p_cx = 3;
	atoms = malloc(sizeof(Atom) * p_cx);
	if (!atoms)
		return (NULL);
	atoms[0] = ctx->atoms[ATOM_WM_DELETE_WINDOW].atom;
	atoms[1] = ctx->atoms[ATOM_NET_WM_STATE].atom;
	atoms[2] = ctx->atoms[ATOM_NET_WM_STATE_FOCUSED].atom;
	XSetWMProtocols(ctx->dp, ctx->win, atoms, p_cx);
	free(atoms);
	return (ctx);
}

t_ctx	*set_attributes(t_ctx *ctx)
{
	XSetWindowAttributes	attrs;

	attrs.override_redirect = True;
	XChangeWindowAttributes(ctx->dp, ctx->win, CWOverrideRedirect, &attrs);
	return (ctx);
}

t_ctx	*lower_to_bg(t_ctx *ctx)
{
	XWindowChanges changes;
	changes.stack_mode = Below;
	XConfigureWindow(ctx->dp, ctx->win, CWStackMode, &changes);
	XMapWindow(ctx->dp, ctx->win);
	XFlush(ctx->dp);
	return (ctx);
}
