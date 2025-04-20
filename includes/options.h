#ifndef OPTIONS_H
# define OPTIONS_H

typedef enum
{
	MPV_OPTION_TYPE_BOOL,		// "yes", "no"
	MPV_OPTION_TYPE_INT,		// unsigned
	MPV_OPTION_TYPE_FLOAT,		// signed
	MPV_OPTION_TYPE_STRING		// bitch can be everything
}	e_mpv_option_type;

typedef enum
{
	OPTION_HWDEC,			// audo, no 
	OPTION_VOLUME,			// 0 - 100 (int)
	OPTION_MUTE,			// yes, no (bool)
	OPTION_SPEED,			// float (-/+)
	OPTION_SUB_AUDIO,		// yes, no, fuzzy
	OPTION_VIDEO_OUTPUT,		// gpu
	OPTION_AUDIO_OUTPUT,		// pulse
	OPTION_IDLE,			// yes, no (bool)
	OPTION_LOOP,			// inf, no, file
	OPTION_COUNT,
}	e_mpv_option_id;

typedef struct
{
	e_mpv_option_id		id;	// id of the	option
	const char		*name;	// name of the	option
	e_mpv_option_type	type;	// type of the	option 
					// depending on it union is diff
	union {
		int		b;	// for boolean or int
		float		f;	// for float	:OOO
		const char	*s;	// for string	:OOOOo
	} value;
}	t_mpv_option;

// Options like change video are not within the enum
//		change font
//		change scale : bilinear, bicubic_fast, oversample, spline16...
//		change blur  : :o <- later

#endif
