#include "v2bg.h"
#include <unistd.h>

void	CTXFree(t_ctx ctx)
{
	XCloseDisplay(ctx.dp);
}

void	render_loop(t_ctx ctx, void (*Draw_Foreground)(t_ctx))
{
	while (1)
	{
		Draw_Foreground(ctx);
		usleep(16666); // ~60fps
	}
	CTXFree(ctx);
}
