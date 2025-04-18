#include "../includes/v2bg.h"
#include <fcntl.h>
#include <unistd.h>

void	Handle_Events(t_ctx *ctx, t_mpv mpv, int *q)
{
	// Instead of handling events it will handle temporary files (?) listening to changes if made apply
	// I can also make sure if SIGKILL, SIGINT, SIGTERM was called and with that also CTXFree the shit out of this app
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
		ctx = lower_to_bg(set_attributes(change_property(create_window(init_atoms(init_display())))));
		if (!ctx)
		{
			write(STDERR_FILENO, "Something Went Wrong!.\n", 24); 
			return (1);
		}
		mpv = initialize_mpv_and_play(set_mpv_options(create_mpv_handle(), ctx), argv[1]);
		render_loop(ctx, mpv, Draw_Foreground, Handle_Events);
	}
	return (0);
}
