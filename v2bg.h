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
	Display			*dp;
	Window			win;
	Window			root;
	GLXContext		glx;
	XVisualInfo		*vi;
	int				screen;
}					t_ctx;
/*
typedef struct s_vrs
{
	int				width;
	int				height;
	int				video_stream_index;
	AVRational		time_base;
	AVFormatContext	*av_format_ctx;
	AVCodecContext	*av_codec_ctx;
	AVFrame			*av_frame;
	AVPacket		*av_packet;
	SwsContext		*sws_scaler_ctx;

}					t_vrs;*/

// x11.c
t_ctx				init_display(void);
t_ctx				create_window(t_ctx ctx);
t_ctx				change_property(t_ctx ctx);
t_ctx				set_attributes(t_ctx ctx);
t_ctx				lower_to_bg(t_ctx ctx);

// GLX | GL.c
GLXContext			create_glx_context(t_ctx ctx);
void				CTXFree(t_ctx ctx);
void				render_loop(t_ctx ctx, void (*Draw_Foreground)(t_ctx));

// Main.c
void				Draw_Foreground(t_ctx ctx);
int					create_destroy_loop(void);

#endif
