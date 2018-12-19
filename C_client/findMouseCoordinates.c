#include "mouseActivities.h"
#include <X11/Xlib.h>

int findMouseCoordinates(MouseActivities *unMA)
{
#ifdef WINDOWS
	LPPOINT pCursor = (LPPOINT)malloc(sizeof(LPPOINT));
	unMA->chClickType = '\0';
	if (!GetCursorPos(pCursor))
		return -1;

	if (GetAsyncKeyState(VK_LBUTTON)) {
		unMA->chClickType = "LMK";
	}
	if (GetAsyncKeyState(VK_RBUTTON)) {
		unMA->chClickType = "RMK";
	}
	unMA->iCoords[X_COORD] = pCursor->x;
	unMA->iCoords[Y_COORD] = pCursor->y;
	//printf("%s X: %d Y: %d \n", unMA->chClickType, unMA->iCoords[X_COORD], unMA->iCoords[Y_COORD]);
	//free(pCursor);
#endif // WINDOWS
//#ifdef LINUX

    Display *display;
	Window root;
	Window ret_root;
	Window ret_child;
	int win_x;
	int win_y;
	unsigned int mask, button = -1;

	display = XOpenDisplay(NULL);
	root = XDefaultRootWindow(display);

	XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);

    event.xbutton.window = event.xbutton.subwindow;
    XQueryPointer (display, event.xbutton.window,
		     &event.xbutton.root, &event.xbutton.subwindow,
		     &event.xbutton.x_root, &event.xbutton.y_root,
		     &unMA->iCoords[X_COORD], &unMA->iCoords[Y_COORD],
		     &event.xbutton.state);

        if(event.xbutton.state == 256)
            strcpy(unMA->chClickType, "LMK");
        else if(event.xbutton.state == 1024)
            strcpy(unMA->chClickType, "RMK");
    printf("state %d button %d event type %d", event.xbutton.state,event.xbutton.button, event.type );

//#endif // LINUX
	return 0;
}
