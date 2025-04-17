#include "../includes/v2bg.h"
#include <stdio.h>
#include <stdlib.h>

t_ctx	init_display(void)
{
	t_ctx	ctx;

	ctx.dp = XOpenDisplay(NULL);
	if (!ctx.dp)
	{
		fprintf(stderr, "Cannot open dislpay\n");
		exit(1);
	}
	ctx.screen = DefaultScreen(ctx.dp);
	ctx.root   = RootWindow(ctx.dp, ctx.screen);
	return (ctx);
}

t_ctx	create_window(t_ctx ctx)
{
	ctx.win = XCreateSimpleWindow(ctx.dp, ctx.root, 0, 0, DisplayWidth(ctx.dp,
				ctx.screen), DisplayHeight(ctx.dp, ctx.screen), 1,
			BlackPixel(ctx.dp, ctx.screen), WhitePixel(ctx.dp, ctx.screen));
	// read more about XSelectInput Enums
	XSelectInput(ctx.dp, ctx.win, FocusChangeMask | ExposureMask | KeyPressMask | ButtonPressMask);
	return (ctx);
}

t_ctx	change_property(t_ctx ctx)
{
	Atom	win_type;
	Atom	dp_type;

	win_type = XInternAtom(ctx.dp, "_NET_WM_WINDOW_TYPE", False);
	dp_type = XInternAtom(ctx.dp, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
	XChangeProperty(ctx.dp, ctx.win, win_type, XA_ATOM, 32, PropModeReplace,
		(unsigned char *)&dp_type, 1);
	return (ctx);
}

t_ctx	set_attributes(t_ctx ctx)
{
	XSetWindowAttributes	attrs;

	attrs.override_redirect = True;
	XChangeWindowAttributes(ctx.dp, ctx.win, CWOverrideRedirect, &attrs);
	return (ctx);
}

t_ctx	lower_to_bg(t_ctx ctx)
{
	XMapWindow(ctx.dp, ctx.win);
	XLowerWindow(ctx.dp, ctx.win);
	XFlush(ctx.dp);
	return (ctx);
}
