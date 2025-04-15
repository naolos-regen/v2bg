#include "v2bg.h"

AVCodecContext	*init_codec_context(AVFormatContext *fmt_ctx,
		int video_stream_index)
{
	const AVCodec	*decoder = avcodec_find_decoder(fmt_ctx->streams[video_stream_index]->codecpar->codec_id);
	AVCodecContext	*codec_ctx;

	codec_ctx = avcodec_alloc_context3(decoder);
	avcodec_parameters_to_context(codec_ctx,
		fmt_ctx->streams[video_stream_index]->codecpar);
	avcodec_open2(codec_ctx, decoder, NULL);
	return (codec_ctx);
}

int	find_video_stream_index(AVFormatContext *fmt_ctx)
{
	unsigned int	i;
	int				video_stream_idx;

	i = 0;
	video_stream_idx = -1;
	while (i < fmt_ctx->nb_streams)
	{
		if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream_idx = i;
			break ;
		}
		i++;
	}
	return (video_stream_idx);
}

int	prepare_frame_and_packet(AVFrame **frame, AVPacket **packet)
{
	*frame = av_frame_alloc();
	if (*frame == NULL)
	{
		fprintf(stderr, "failed to alloc\n");
		return (-1);
	}
	*packet = av_packet_alloc();
	if (*packet == NULL)
	{
		fprintf(stderr, "failed to alloc\n");
		return (-1);
	}
	return (0);
}

int	read_first_frame(AVFormatContext *fmt_ctx, AVPacket *packet,
		AVCodecContext *codec_ctx, AVFrame *frame)
{
	while (av_read_frame(fmt_ctx, packet) >= 0)
	{
		// todo: this breaks
		// check if packet and codec have the same index on stream
		if (avcodec_send_packet(codec_ctx, packet) == 0
			&& avcodec_receive_frame(codec_ctx, frame) == 0)
			return (0);
		av_packet_unref(packet);
	}
	return (-1);
}

int	convert_frame_to_rgb(AVFrame *frame, t_vid *vid, AVCodecContext *codec_ctx)
{
	struct SwsContext	*sws_ctx;
	uint8_t				*dest[4] = {vid->frame_data, NULL, NULL, NULL};
	int					dest_linesize[4] = {codec_ctx->width * 3, 0, 0, 0};

	sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height,
			codec_ctx->pix_fmt, codec_ctx->width, codec_ctx->height,
			AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);
	sws_scale(sws_ctx, (const uint8_t *const *)frame->data, frame->linesize, 0,
		codec_ctx->height, dest, dest_linesize);
	sws_freeContext(sws_ctx);
	// Debugging: Print out first few pixels of the converted frame
	for (int i = 0; i < 10; ++i)
	{
		printf("Converted Frame Data[%d]: %d\n", i, vid->frame_data[i]);
	}
	return (0);
}

int	init_ffmpeg(t_cod *cod)
{
	if (avformat_open_input(&cod->fmt_ctx, cod->filename, NULL, NULL) != 0)
	{
		fprintf(stderr, "Could not open video file\n");
		return (-1);
	}
	if (avformat_find_stream_info(cod->fmt_ctx, NULL) < 0)
		return (-1);
	return (0);
}

int	init_video_codec(t_cod *cod)
{
	cod->video_stream_index = find_video_stream_index(cod->fmt_ctx);
	if (cod->video_stream_index == -1)
	{
		fprintf(stderr, "No video stream found\n");
		return (-1);
	}
	cod->codec_ctx = init_codec_context(cod->fmt_ctx, cod->video_stream_index);
	if (!cod->codec_ctx)
	{
		fprintf(stderr, "Failed to init codec context\n");
		return (-1);
	}
	return (0);
}

int	init_frame_and_packet(t_cod *cod)
{
	return (prepare_frame_and_packet(&cod->frame, &cod->packet));
}

int	decode_first_frame(t_cod *cod)
{
	if (read_first_frame(cod->fmt_ctx, cod->packet, cod->codec_ctx,
			cod->frame) < 0)
	{
		fprintf(stderr, "Failed to read video frame\n");
		return (-1);
	}
	return (0);
}

int	setup_texture_data(t_cod *cod)
{
	cod->vid = malloc(sizeof(t_vid));
	if (!cod->vid)
	{
		fprintf(stderr, "Failed to alloc vid\n");
		return (-1);
	}
	memset(cod->vid, 0, sizeof(t_vid));
	cod->vid->width = cod->codec_ctx->width;
	cod->vid->height = cod->codec_ctx->height;
	cod->vid->frame_data = malloc(cod->vid->width * cod->vid->height * 3);
	if (!cod->vid->frame_data)
	{
		fprintf(stderr, "Failed to allocate RGB buffer\n");
		return (-1);
	}
	if (convert_frame_to_rgb(cod->frame, cod->vid, cod->codec_ctx) != 0)
		return (-1);
	return (0);
}

t_vid	*cleanup_fail(t_cod *cod)
{
	free_video_resources(*cod);
	free_video(cod->vid);
	return (NULL);
}
