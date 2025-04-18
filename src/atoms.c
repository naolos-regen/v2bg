#include "../includes/v2bg.h"
#include "../includes/atoms.h"
#include <stdlib.h>

t_ctx	init_atoms(t_ctx ctx)
{
	int		i;
	const char	*atom_names[ATOM_LAST] =
	{
		[ATOM_NET_WM_WINDOW_TYPE]		= "_NET_WM_WINDOW_TYPE",
		[ATOM_NET_WM_WINDOW_TYPE_DESKTOP]	= "_NET_WM_WINDOW_TYPE_DESKTOP",
		[ATOM_WM_DELETE_WINDOW]			= "WM_DELETE_WINDOW",
		[ATOM_NET_WM_STATE]			= "_NET_WM_STATE",
		[ATOM_NET_WM_STATE_FOCUSED]		= "_NET_WM_STATE_FOCUSED",
	};

	ctx.atoms = malloc(sizeof(t_atoms) * ATOM_LAST);
	if (!ctx.atoms)
		return (ctx);
	i = 0;
	while (i < ATOM_LAST)
	{
		ctx.atoms[i].atom_name	= atom_names[i];
		ctx.atoms[i].atom	= XInternAtom(ctx.dp, atom_names[i], False);
		i++;
	}
	return (ctx);
}
