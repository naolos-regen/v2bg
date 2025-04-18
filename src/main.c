#include "../includes/v2bg.h"
#include <fcntl.h>
#include <unistd.h>


void	Handle_Events(t_ctx ctx, t_mpv mpv)
{
	while (XPending(ctx.dp))
	{
		XNextEvent(ctx.dp, &ctx.ev);

		switch(ctx.ev.type) { 
			// ??? changing Workspace affects FocusOut FocusIn too damn
			// Them being opposite is the correct way doe. In a sense of reading at least
			// ok so what the fuck is going on on DWM where there are no workspaces it works like the naming conventon
			// on I3 it doesn't
			// This is why we can't have nice things in life :(
			case FocusIn:
				mpv_set_option_string(mpv.mpv, "mute", "no");
			break;
			case FocusOut:
				mpv_set_option_string(mpv.mpv, "mute", "yes");
			break;
			default:
				break;
		}
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
		ctx = init_display();
		ctx = init_atoms(ctx);
		ctx = create_window(ctx);
		ctx = change_property(ctx);
		ctx = set_attributes(ctx);
		ctx = lower_to_bg(ctx);
		mpv = initialize_mpv_and_play(set_mpv_options(create_mpv_handle(), ctx), argv[1]);
		render_loop(ctx, mpv, Draw_Foreground, Handle_Events);
	}
	return (0);
}
