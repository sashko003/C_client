#ifndef C_SERVER_MOUSE_ACTIVITIES_H_
#define C_SERVER_MOUSE_ACTIVITIES_H_

#include "header.h"
#define COORDINATES 2
#define CLICK_TYPE 4

typedef union unMouseActivities
{
	int iCoords[COORDINATES];
	struct {
		char chX[sizeof(int)];
		char chY[sizeof(int)];
		char chClickType[CLICK_TYPE];
	};
	char chMessage[sizeof(int) * COORDINATES + CLICK_TYPE];// for '\0'
} MouseActivities;

#ifdef WINDOWS
int findMouseCoordinates(MouseActivities *unMA);
#endif // WINDOWS


#endif // !C_SERVER_MOUSE_ACTIVITIES_H_
