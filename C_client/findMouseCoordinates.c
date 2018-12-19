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
	//int button;
	unsigned int mask, button;

	display = XOpenDisplay(NULL);
	root = XDefaultRootWindow(display);

	if(!XQueryPointer(display, root, &ret_root, &ret_child, &unMA->iCoords[X_COORD], &unMA->iCoords[Y_COORD],
					 &win_x, &win_y, &button))
	{
        return -1;
		// original version
		//    printf("root loc: %4d,%4d win loc: %3d,%3d mask: 0x%08X\n",
		//           root_x, root_y, win_x, win_y, mask);

		// This returns in -geometry format
		// I added \n so it actually shows something so people who test it know it works.
		//printf("+%d+%d\n", root_x, root_y);
	}

	//if(XGrabPointer(display, root, False, ButtonPressMask | ButtonReleaseMask |
    //                 PointerMotionMask, GrabModeAsync,
    //    GrabModeAsync, None, None, CurrentTime))
    //    return 0;

    //if(!XSelectInput(display, root, ButtonPressMask))
    //    return 0;
    //XUngrabPointer(display, CurrentTime);
    sleep(1);
    //XAllowEvents(display, AsyncPointer, CurrentTime);
    XSelectInput(display, root, ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    XEvent event;
    XNextEvent(display,&event);
    XFlush(display);
    if(event.type == ButtonPress){
        if(event.xbutton.button == Button1)
            strcpy(unMA->chClickType, "LMK");
        else if(event.xbutton.button == Button2)
            strcpy(unMA->chClickType, "RMK");
    }


//#endif // LINUX
	return 0;
}
