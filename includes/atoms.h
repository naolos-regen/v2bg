#ifndef ATOMS_H
# define ATOMS_H

enum	e_atom_idx
{
	ATOM_NET_WM_WINDOW_TYPE,
	ATOM_NET_WM_WINDOW_TYPE_DESKTOP,
	ATOM_WM_DELETE_WINDOW,
	ATOM_NET_WM_STATE,
	ATOM_NET_WM_STATE_BELOW,
	ATOM_NET_WM_STATE_FOCUSED,
	ATOM_LAST
};

typedef enum e_atom_idx t_atom_idx;

extern const char *g_atom_names[ATOM_LAST];

#endif
