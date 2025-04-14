#include "v2bg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float	angle = 0.0f;
void	Draw_Foreground(t_ctx ctx, t_vid *video)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glXSwapBuffers(ctx.dp, ctx.win);
	angle += 0.5f;
	if (angle >= 360.0f)
		angle -= 360.0f;
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
