#include "v2bg.h"

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
	glGenTextures(1, &vid->texture);
	glBindTexture(GL_TEXTURE_2D, vid->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, codec_ctx->width, codec_ctx->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, vid->frame_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (vid->texture);
}
t_vid	*init_video(t_ctx ctx)
{
	t_cod	cod;

	memset(&cod, 0, sizeof(t_cod));
	cod.filename = "video.mp4";
	cod.vid = calloc(1, sizeof(t_vid));
	if (!cod.vid)
		return (NULL);
	if (init_ffmpeg(&cod) != 0)
		return (cleanup_fail(&cod));
	if (init_video_codec(&cod) != 0)
		return (cleanup_fail(&cod));
	if (init_frame_and_packet(&cod) != 0)
		return (cleanup_fail(&cod));
	if (decode_first_frame(&cod) != 0)
		return (cleanup_fail(&cod));
	if (setup_texture_data(&cod) != 0)
		return (cleanup_fail(&cod));
	create_opengl_texture(cod.vid, cod.codec_ctx);
	free_video_resources(cod);
	return (cod.vid);
}
