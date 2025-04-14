#include "v2bg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	Draw_Foreground(t_ctx ctx)
{
	glClearColor(0.0, 0.2, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glXSwapBuffers(ctx.dp, ctx.win);
	usleep(16000); // ~60fps
}

int	create_destroy_loop(void)
{
	t_ctx	ctx;

	ctx = init_display();
	ctx = create_window(ctx);
	ctx = change_property(ctx);
	ctx = set_attributes(ctx);
	ctx = lower_to_bg(ctx);
	render_loop(ctx, Draw_Foreground);
	return (0);
}

int	main(void)
{
	return (create_destroy_loop());
}
