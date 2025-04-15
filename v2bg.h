#ifndef V2BG_H
# define V2BG_H

# include <GL/gl.h>
# include <GL/glx.h>
# include <X11/Xatom.h>
# include <X11/Xlib.h>
# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libavutil/imgutils.h>
# include <libswscale/swscale.h>


typedef struct s_ctx
{
	Display		*dp;
	Window		win;
	Window		root;
	GLXContext	glx;
	XVisualInfo	*vi;
	int			screen;
}				t_ctx;

typedef struct s_vid
{
	uint8_t		*frame_data;
	int			width;
	int			height;
	GLuint		texture;
}				t_vid;

typedef struct s_cod
{
	AVFormatContext *fmt_ctx;
	AVCodecContext  *codec_ctx;
	AVFrame		*frame;
	AVPacket	*packet;
	t_vid		*vid;
	int		video_stream_index;
	const char 	*filename;
}				t_cod;

// x11.c
t_ctx			init_display	(void);
t_ctx			create_window	(t_ctx ctx);
t_ctx			change_property	(t_ctx ctx);
t_ctx			set_attributes	(t_ctx ctx);
t_ctx			lower_to_bg	(t_ctx ctx);

// ffmpeg.c
int			convert_frame_to_rgb    (AVFrame *frame, t_vid *vid, AVCodecContext *codec_ctx);
int			init_ffmpeg		(t_cod *cod);
int			init_video_codec	(t_cod *cod);
int			init_frame_and_packet	(t_cod *cod);
int			decode_first_frame	(t_cod *cod);
int			setup_texture_data	(t_cod *cod);
t_vid			*cleanup_fail		(t_cod *cod);

// video.c
t_cod			*init_decoder		(const char *filename);
t_vid			*init_video		(void);
void			free_video_resources 	(t_cod cod);
void			free_video		(t_vid *vtx);

// GLX | GL.c
GLXContext		create_glx_context	(t_ctx ctx);
void			CTXFree			(t_ctx ctx);
void			render_loop		(t_ctx ctx, t_vid *vtx, t_cod *cod,
					void (*Draw_Foreground)(t_ctx, t_vid *));

// Main.c
void			Draw_Foreground		(t_ctx ctx, t_vid *video);
int			create_destroy_loop	(void);

#endif
