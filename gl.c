#include "v2bg.h"
#include <unistd.h>

void	CTXFree(t_ctx ctx, t_mpv mpv)
{
	mpv_terminate_destroy(mpv.mpv);
	XDestroyWindow(ctx.dp, ctx.win);
	XCloseDisplay(ctx.dp);
}

void	render_loop(t_ctx ctx, t_mpv mpv, void (*Draw_Foreground)(t_ctx, t_mpv))
{
	while (1)
	{
		Draw_Foreground(ctx, mpv);
		usleep(16666); // ~60fps
	}
	CTXFree(ctx, mpv);
}
