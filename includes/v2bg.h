#ifndef V2BG_H
# define V2BG_H

# include <X11/Xatom.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/Xinerama.h>
# include <X11/X.h>
# include <mpv/client.h>

typedef struct s_atoms
{
	Atom		atom;
	const char	*atom_name;

}		t_atoms;

typedef struct s_ctx
{
	Display			*dp;
	Window			win;
	Window			root;
	int			screen;
	XEvent			ev;
	t_atoms			*atoms;
	XineramaScreenInfo	*monitors;
	int			monitor_cx;
}				t_ctx;

typedef struct s_mpv
{
	mpv_handle	*mpv;
	mpv_event	*event;
	char		wid_str[64];
	const char	*cmd;
}				t_mpv;

typedef struct s_sig_dat
{
	t_ctx		*ctx;
	t_mpv		*mpv;
} t_sig_dat;
/*
typedef struct s_web
{
	TODO IMPLEMENT THIS

}				t_web;
*/
// errormsg.c an idea for later is signal_handling
void			error_msg		(void *ptr, const char *msg);
void			error_msg_quit		(void *ptr, const char *msg, int sig);
void			setup_signal_handler	(t_ctx *ctx, t_mpv *mpv);
int			setup_signal_fd		();
// print.c
int			ft_snprintf	(char *buf, size_t size, const char *fmt, ...);

// x11.c
t_ctx			*init_display		(void);
t_ctx			*create_window		(t_ctx *ctx);
t_ctx			*create_multi_window	(t_ctx *ctx, int x, int y, int w, int h);
t_ctx			*change_property	(t_ctx *ctx);
t_ctx			*set_attributes		(t_ctx *ctx);
t_ctx			*lower_to_bg		(t_ctx *ctx);

// atoms.c
t_ctx			*init_atoms		(t_ctx *ctx);

// since there is only 1 video stream and 1 audio stream there is no need to alloc it for this?
// mpv_goat.c
t_mpv			create_mpv_handle	(void);
t_mpv			set_mpv_options		(t_mpv mpv, t_ctx *ctx);
t_mpv			initialize_mpv_and_play	(t_mpv mpv, const char *filename);

// gl.c
void			CTXFree		(t_ctx *ctx, t_mpv *mpv);
void			render_loop	(t_ctx *ctx, t_mpv mpv, 
		   			void (*Draw_Foreground)(t_ctx* ,t_mpv), 
		   			void (*Handle_Events)  (t_ctx*, t_mpv, int *));

// Main.c
void			Handle_Events	(t_ctx *ctx, t_mpv mpv, int *q);
void			Draw_Foreground	(t_ctx *ctx, t_mpv mpv);
void			initialize	();


#endif
