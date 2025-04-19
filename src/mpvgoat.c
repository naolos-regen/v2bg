#include "../includes/v2bg.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

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

t_mpv	set_mpv_options(t_mpv mpv, t_ctx *ctx)
{	
//	if(!ctx) so being able to do that t_mpv must also be allocated ig
//		return (NULL);
	void *handle = dlopen("libcuda.so", RTLD_LAZY);
	
	snprintf(mpv.wid_str, sizeof(mpv.wid_str), "%lu", ctx->win);
	mpv_set_option_string(mpv.mpv, "vo", "gpu-next");
	mpv_set_option_string(mpv.mpv, "gpu-api", "vulkan");
	mpv_set_option_string(mpv.mpv, "wid", mpv.wid_str);
	mpv_set_option_string(mpv.mpv, "video-sync", "display-resample");
	mpv_set_option_string(mpv.mpv, "loop", "inf");
	mpv_set_option_string(mpv.mpv, "idle", "yes");	
	if (handle)
	{
		mpv_set_option_string(mpv.mpv, "hwdec", "auto");
		dlclose(handle);
	}
	else
		printf("mpv starting without hardware acceleration, download libcuda.so. Error %s\n", dlerror());
	return (mpv);
}

t_mpv	initialize_mpv_and_play(t_mpv mpv, const char *file_name)
{	
	if (mpv_initialize(mpv.mpv) < 0)
	{
		fprintf(stderr, "mpv_init error\n");
		exit(1);
	}
	const char *cmd[] = { "loadfile", file_name, NULL };
	mpv_command(mpv.mpv, cmd);
	return (mpv);
}
