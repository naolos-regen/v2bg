#include "v2bg.h"
#include <stdio.h>
#include <unistd.h>

GLXContext	create_glx_context(t_ctx ctx)
{
	int			attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER,
					None};
	GLXContext	glx;

	ctx.vi = glXChooseVisual(ctx.dp, 0, attributes);
	if (!ctx.vi)
	{
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}
	glx = glXCreateContext(ctx.dp, ctx.vi, NULL, GL_TRUE);
	glXMakeCurrent(ctx.dp, ctx.win, glx);
	return (glx);
}

void	CTXFree(t_ctx ctx)
{
	if (ctx.dp && ctx.glx)
	{
		glXMakeCurrent(ctx.dp, None, NULL);
		glXDestroyContext(ctx.dp, ctx.glx);
	}
	if (ctx.vi)
		XFree(ctx.vi);
	XCloseDisplay(ctx.dp);
}

void	render_loop(t_ctx ctx, t_vid *vtx, t_cod *cod,
		void (*Draw_Foreground)(t_ctx, t_vid *))
{
	ctx.glx = create_glx_context(ctx);
	if (!ctx.glx)
		return ;
	printf("Created texture ID: %u\n", cod->vid->texture);
	while (1)
	{
		if (av_read_frame(cod->fmt_ctx, cod->packet) >= 0)
		{
			if (cod->packet->stream_index == cod->video_stream_index)
			{
				if (avcodec_send_packet(cod->codec_ctx, cod->packet) == 0
					&& avcodec_receive_frame(cod->codec_ctx, cod->frame) == 0)
				{
					convert_frame_to_rgb(cod->frame, vtx, cod->codec_ctx);
					glBindTexture(GL_TEXTURE_2D, vtx->texture);
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vtx->width,
						vtx->height, GL_RGB, GL_UNSIGNED_BYTE, vtx->frame_data);
				}
			}
			av_packet_unref(cod->packet);
		}
		Draw_Foreground(ctx, vtx);
		usleep(16666); // ~60fps
	}
	CTXFree(ctx);
}
