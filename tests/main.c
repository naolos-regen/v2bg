#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/Xatom.h>

int main() {
    Display *dp;
    Window root, win;
    XEvent ev;
    
    dp = XOpenDisplay(NULL);
    if (!dp) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    root = DefaultRootWindow(dp);
    win = XCreateSimpleWindow(dp, root, 0, 0, 800, 600, 0, 0, 0);
    Atom wm_type;
    Atom dp_type;
    XSetWindowAttributes attrs;
    attrs.override_redirect = True;

    wm_type = XInternAtom(dp, "_NET_WM_WINDOW_TYPE", False);
    dp_type = XInternAtom(dp, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
    

    XSelectInput(dp, win, KeyPressMask);
    
    XChangeProperty(dp, win, wm_type, XA_ATOM, 32, PropModeAppend, (unsigned char *)&dp_type, 1);
    XChangeWindowAttributes(dp, win, CWOverrideRedirect, &attrs);
    // Map the window to show it
    XMapWindow(dp, win);
    // Set the window focus to the new window (optional)
    XLowerWindow(dp, win);
    // Set window to stay in the background
    XFlush(dp);
    // Event loop to keep the window active
    while (1) {
        XNextEvent(dp, &ev);
        switch(ev.type)
        {
	    case KeyPress:
                printf("key, pressed\n");
            break;
        }
    }

    return 0;
}
