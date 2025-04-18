#include "../includes/v2bg.h"
#include <unistd.h>
#include <stdlib.h>

void	CTXFree(t_ctx *ctx, t_mpv mpv)
{	
	mpv_terminate_destroy(mpv.mpv);
	XDestroyWindow(ctx->dp, ctx->win);
	XCloseDisplay(ctx->dp);
	if (ctx->atoms)
	{
		free(ctx->atoms);
		ctx->atoms = NULL;
	}
	free(ctx);
}

void	render_loop(t_ctx *ctx, 
		    t_mpv mpv, 
		    void (*Draw_Foreground)(t_ctx*, t_mpv),
		    void (*Handle_Events)(t_ctx*, t_mpv, int *))
{
	int		q;
	int		x11_fd;
	int		mpv_fd;
	int		maxfd;
	fd_set		fds;

	x11_fd = ConnectionNumber(ctx->dp);
	mpv_fd = mpv_get_wakeup_pipe(mpv.mpv);
	maxfd = (x11_fd > mpv_fd ? x11_fd : mpv_fd) + 1;
	q = 1;
	while (q)
	{
		FD_ZERO(&fds);
		FD_SET(x11_fd, &fds);
		FD_SET(mpv_fd, &fds);
		if (select(maxfd, &fds, NULL, NULL, NULL) > 0)
		{
			if (FD_ISSET(mpv_fd, &fds) || FD_ISSET(x11_fd, &fds))
			{
				Handle_Events(ctx, mpv, &q);
			}
			Draw_Foreground(ctx, mpv);
		}
	}
	CTXFree(ctx, mpv);
}
