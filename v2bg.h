#ifndef V2BG_H
# define V2BG_H

# include <GL/gl.h>
# include <GL/glx.h>
# include <X11/Xatom.h>
# include <X11/Xlib.h>

typedef struct s_ctx
{
	Display	*dp;
	Window	win;
	Window	root;
	GLXContext glx;
	XVisualInfo *vi;
	int		screen;
}			t_ctx;

// x11
t_ctx		init_display		(void);
t_ctx		create_window		(t_ctx ctx);
t_ctx		change_property		(t_ctx ctx);
t_ctx		set_attributes		(t_ctx ctx);
t_ctx		lower_to_bg		(t_ctx ctx);

// GLX | GL
GLXContext	create_glx_context	(t_ctx ctx);
void		CTXFree			(t_ctx ctx);
void		render_loop		(t_ctx ctx, void(*Draw_Foreground)(t_ctx ctx)));


// Main
void		Draw_Foreground		(t_ctx ctx);
int		create_destroy_loop	(void);


#endif
