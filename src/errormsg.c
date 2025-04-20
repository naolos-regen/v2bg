#include "../includes/v2bg.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *msg)
{
	size_t	cx;
	
	cx = 0;
	while(msg[cx])
		++cx;
	return (cx);
}


void	t_ctx_error(t_ctx *ctx, const char *msg)
{
	// freeing is less robust
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (ctx)
	{
		XDestroyWindow(ctx->dp, ctx->win);
		XCloseDisplay(ctx->dp);
		if (ctx->atoms)
		{
			free(ctx->atoms);
			ctx->atoms = NULL;
		}
		free(ctx);
	}
}

void	t_mpv_error(t_mpv *mpv, const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (mpv)
		free(mpv);
	if (mpv->mpv)
		mpv_terminate_destroy(mpv->mpv);
}

void	error_msg(void *ptr, const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if(ptr)
		free(ptr);
}
