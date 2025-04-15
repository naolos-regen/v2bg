#include "v2bg.h"
#include <stdio.h>
#include <stdlib.h>

t_mpv	create_mpv_handle(void)
{
	t_mpv	mpv;

	mpv.mpv = mpv_create();
	if (!mpv.mpv)
	{
		fprintf(stderr, "create_mpv_failed\n");
		exit(1);
	}
	return (mpv);
}

t_mpv	set_mpv_options(t_mpv mpv, t_ctx ctx)
{
	mpv_set_option_string(mpv.mpv, "vo", "gpu-next");
	mpv_set_option_string(mpv.mpv, "gpu-api", "vulkan");
	
	mpv_set_option_string(mpv.mpv, "video-sync", "display-resample");
	mpv_set_option_string(mpv.mpv, "loop", "inf");
	mpv_set_option_string(mpv.mpv, "idle", "yes");
	
	snprintf(mpv.wid_str, sizeof(mpv.wid_str), "%lu", ctx.win);
	mpv_set_option_string(mpv.mpv, "wid", mpv.wid_str);
	mpv_set_option_string(mpv.mpv, "log-file", "mpv_log.txt");
	mpv_set_option_string(mpv.mpv, "msg-level", "all-v");
	
	return (mpv);
}

t_mpv	initialize_mpv_and_play(t_mpv mpv, const char *filename)
{
	const char *cmd[] = { "loadfile", filename, NULL };
	mpv_command(mpv.mpv, cmd);
	return (mpv);
}
