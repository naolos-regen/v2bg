#ifndef V2BG_H
# define V2BG_H

# include <GL/gl.h>
# include <GL/glx.h>
# include <X11/Xatom.h>
# include <X11/Xlib.h>

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

// x11.c
t_ctx			init_display(void);
t_ctx			create_window(t_ctx ctx);
t_ctx			change_property(t_ctx ctx);
t_ctx			set_attributes(t_ctx ctx);
t_ctx			lower_to_bg(t_ctx ctx);

// video.c
# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libavutil/imgutils.h>
# include <libswscale/swscale.h>

t_vid			*init_video(t_ctx ctx);
void			free_video(t_vid *vtx);

// GLX | GL.c
GLXContext		create_glx_context(t_ctx ctx);
void			CTXFree(t_ctx ctx);
void			render_loop(t_ctx ctx, t_vid *vtx,
					void (*Draw_Foreground)(t_ctx, t_vid *));

// Main.c
void			Draw_Foreground(t_ctx ctx, t_vid *video);
int				create_destroy_loop(void);

#endif
