#include "v2bg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float	angle = 0.0f;
void	Draw_Foreground(t_ctx ctx, t_vid *video)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, video->texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glXSwapBuffers(ctx.dp, ctx.win);
}

int	create_destroy_loop(void)
{
	t_ctx	ctx;
	t_vid	*vtx;

	ctx = init_display();
	ctx = create_window(ctx);
	ctx = change_property(ctx);
	ctx = set_attributes(ctx);
	ctx = lower_to_bg(ctx);
	vtx = init_video(ctx);
	if (!vtx)
	{
		fprintf(stderr, "Failed to init vid\n");
		exit(1);
	}
	render_loop(ctx, vtx, Draw_Foreground);
	return (0);
}

int	main(void)
{
	return (create_destroy_loop());
}
