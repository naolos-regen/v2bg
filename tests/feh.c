#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <Imlib2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	Display *dp = XOpenDisplay(NULL);
	if (!dp)
		return (1);
	Window root = DefaultRootWindow(dp);
	char cmd[1024];
	const char *video_path = "/home/naolos/Documents/Programming/C-Lang/v2bg/video.mp4";
	snprintf(cmd, sizeof(cmd), "mpv --loop --no-audio -wid=0x%lx \"%s\" &", root, video_path);
	int ret = system(cmd);
	XCloseDisplay(dp);
	return (ret);
}
