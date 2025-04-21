#include "../includes/v2bg.h"
#include <fcntl.h>
#include <unistd.h>

void	Handle_Events(t_ctx *ctx, t_mpv mpv, int *q)
{
	while (XPending(ctx->dp))
	{
		XNextEvent(ctx->dp, &ctx->ev);
		switch(ctx->ev.type)
		{
			case Expose:
				XClearWindow(ctx->dp, ctx->win);
			break;
			case KeyPress:
				{
					KeySym key = XLookupKeysym(&ctx->ev.xkey, 0);
					if ((ctx->ev.xkey.state & Mod1Mask) && key == XK_q)
						*q = 0;
				}
			break;

		}
	}
	while ((mpv.event = mpv_wait_event(mpv.mpv, 0.0))
		&& mpv.event->event_id != MPV_EVENT_NONE)
	{
		// handle events
	}
}

void	Draw_Foreground(t_ctx *ctx, t_mpv mpv)
{
	(void)ctx; (void)mpv;
	// draw
}

void	initialize()
{	
	int i;
	t_ctx	*ctx;
	t_mpv	mpv;

	ctx = init_display();
	if (!ctx)
		error_msg(ctx, "Couldn't initialize display\n");
	i = 0;
	while (i < ctx->monitor_cx)
	{	
		XineramaScreenInfo m = ctx->monitors[i];
		ctx = init_atoms(ctx);
		if (!ctx)
			error_msg(ctx, "Couldn't initialize atoms\n");
		ctx = create_multi_window(ctx, m.x_org, m.y_org, m.width, m.height);
		ctx = change_property(ctx);
		if (!ctx)
			error_msg(ctx, "Change_property failed\n");
		ctx = set_attributes(ctx);
		if (!ctx)
			error_msg(ctx, "Setting attributes returned NULL\n");
		ctx = lower_to_bg(ctx);
	}
	mpv = create_mpv_handle();
	mpv = set_mpv_options(mpv, ctx);
	mpv = initialize_mpv_and_play(mpv, "");
	render_loop(ctx, mpv, Draw_Foreground, Handle_Events);
}

int	cmd_helper(int argc, char **argv)
{
	int	n;

	if (argc < 2)
	{
		write(STDERR_FILENO, "File name missing.\n", 19);
		return (1);
	}
	if (argc > 2)
	{
		write(STDERR_FILENO, "Too many arguments.\n", 20);
		return (1);
	}
	if ((n = open(argv[1], O_RDONLY)) == -1)
	{
		write(STDERR_FILENO, "Cannot read file.\n", 18);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_ctx	*ctx;
	t_mpv	mpv;

	if (cmd_helper(argc, argv) == 0)
	{
		ctx = init_display();
		ctx = init_atoms(ctx);
		ctx = create_window(ctx);
		ctx = change_property(ctx);
		ctx = set_attributes(ctx);
		ctx = lower_to_bg(ctx);
		if (!ctx)
		{
			error_msg((void *)0, "Something Went Wrong\n");
			return (1);
		}
		mpv = initialize_mpv_and_play(set_mpv_options(create_mpv_handle(), ctx), argv[1]);
		render_loop(ctx, mpv, Draw_Foreground, Handle_Events);
	}
	return (0);
}
