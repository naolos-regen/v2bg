#include "../includes/v2bg.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *msg)
{
	size_t	cx;
	
	cx = 0;
	while(msg[cx])
		++cx;
	return (cx);
}

void	error_msg(void *ptr, const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (ptr)
		free(ptr); // might not be nessesary
}
