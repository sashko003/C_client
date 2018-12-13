#include "mouseActivities.h"

int findMouseCoordinates(MouseActivities *unMA)
{
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
	return 0;
}