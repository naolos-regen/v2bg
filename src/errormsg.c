#include "../includes/v2bg.h"
#include <sys/signalfd.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

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


void	error_msg_quit(void *ptr, const char *msg, int sig)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (ptr)
		free(ptr);
	exit(sig);
}

static t_sig_dat *g_sig_dat = NULL;

void	signal_handler(int signum, siginfo_t *info, void *context)
{	
	(void) context;
	(void) info;
	if (signum == SIGINT || signum == SIGTERM)
	{	
		if (g_sig_dat)
			CTXFree(g_sig_dat->ctx, g_sig_dat->mpv);
	}
	exit(signum);
}

void	setup_signal_handler(t_ctx *ctx, t_mpv *mpv)
{	
	g_sig_dat = malloc(sizeof(t_sig_dat));
	if (!g_sig_dat)
		error_msg_quit(NULL, "MALLOC failed\n", 1);
	g_sig_dat->ctx = ctx;
	g_sig_dat->mpv = mpv;

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}


int	setup_signal_fd()
{
	sigset_t	mask;
	int		sfd;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);

	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
	{
		perror("sigprocmask");
		return (-1);
	}
	sfd = signalfd(-1, &mask, SFD_CLOEXEC);
	if (sfd == -1)
	{
		perror("signalfd");
		return (-1);
	}
	return (sfd);
}
