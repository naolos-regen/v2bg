#include "v2bg.h"
#include <stdio.h>

void	free_video_resources(t_cod cod)
{
	av_frame_free(&cod.frame);
	av_packet_free(&cod.packet);
	avcodec_free_context(&cod.codec_ctx);
	avformat_close_input(&cod.fmt_ctx);
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

GLuint	create_opengl_texture(t_vid *vid, AVCodecContext *codec_ctx)
{
	GLuint	tex;

	printf("Texture dimensions: %d x %d\n", vid->width, vid->height);
	printf("Frame data start address: %p\n", vid->frame_data);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Check the first 10 bytes of the frame data:
	for (int i = 0; i < 10; ++i)
	{
		printf("Frame Data[%d]: %d\n", i, vid->frame_data[i]);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, vid->width, vid->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, vid->frame_data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (tex);
}

t_cod	*init_decoder(const char *filename)
{
	t_cod	*cod;

	cod = calloc(1, sizeof(t_cod));
	if (!cod)
		return (NULL);
	cod->filename = filename;
	cod->vid = calloc(1, sizeof(t_vid));
	if (!cod->vid)
	{
		free(cod);
		return (NULL);
	}
	if (init_ffmpeg(cod) != 0 || init_video_codec(cod) != 0
		|| init_frame_and_packet(cod) != 0 || decode_first_frame(cod) != 0
		|| setup_texture_data(cod) != 0)
	{
		free_video_resources(*cod);
		free_video(cod->vid);
		free(cod);
		return (NULL);
	}
	cod->vid->texture = create_opengl_texture(cod->vid, cod->codec_ctx);
	return (cod);
}
