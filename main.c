#include "v2bg.h"
#include <unistd.h>

void	Draw_Foreground(t_ctx ctx, t_mpv mpv)
{
	while(XPending(ctx.dp)){
		XNextEvent(ctx.dp, &ctx.ev);
		// handle events
	}
	while ((mpv.event = mpv_wait_event(mpv.mpv, 0.0)) && mpv.event->event_id != MPV_EVENT_NONE)
	{
		// Handle events
	}
	XFlush(ctx.dp);
}

int	create_destroy_loop(void)
{
	t_ctx	ctx;
	t_mpv   mpv;
	
	ctx = init_display();
	ctx = create_window(ctx);
	ctx = change_property(ctx);
	ctx = set_attributes(ctx);
	ctx = lower_to_bg(ctx);
	
	
	mpv = create_mpv_handle();
	
	mpv = set_mpv_options(mpv, ctx);
	mpv = initialize_mpv_and_play(mpv, "video.mp4");
	render_loop(ctx, mpv, Draw_Foreground);
	return (0);
}

int	main(void)
{
	return (create_destroy_loop());
}
