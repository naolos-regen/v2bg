#include "v2bg.h"

t_vid	*init_video(t_ctx ctx)
{
	t_vid	*vtx;

	vtx = malloc(sizeof(t_vid));
	if (!vtx)
		return (NULL);
	vtx->width = DisplayWidth(ctx.dp, ctx.screen);
	vtx->height = DisplayHeight(ctx.dp, ctx.screen);
	vtx->frame_data = calloc(vtx->width * vtx->height * 3, sizeof(uint8_t));
	if (!vtx->frame_data)
	{
		free(vtx);
		return (NULL);
	}
	glGenTextures(1, &vtx->texture);
	glBindTexture(GL_TEXTURE_2D, vtx->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, vtx->width, vtx->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, vtx->frame_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (vtx);
}

void	free_video(t_vid *vid)
{
	if (!vid)
		return ;
	if (vid->frame_data)
		free(vid->frame_data);
	glDeleteTextures(1, &vid->texture);
	free(vid);
}
