#include "../includes/v2bg.h"
#include <fcntl.h>
#include <unistd.h>


void	Handle_Events(t_ctx ctx, t_mpv mpv)
{
	while (XPending(ctx.dp))
	{
		XNextEvent(ctx.dp, &ctx.ev);
	}
	while ((mpv.event = mpv_wait_event(mpv.mpv, 0.0))
		&& mpv.event->event_id != MPV_EVENT_NONE)
	{
		// handle events
	}
}

void	Draw_Foreground(t_ctx ctx, t_mpv mpv)
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
	t_ctx	ctx;
	t_mpv	mpv;

	if (cmd_helper(argc, argv) == 0)
	{
		ctx = lower_to_bg(set_attributes(change_property(create_window(init_display()))));
		mpv = initialize_mpv_and_play(set_mpv_options(create_mpv_handle(), ctx), argv[1]);
		render_loop(ctx, mpv, Draw_Foreground, Handle_Events);
	}
	return (0);
}
