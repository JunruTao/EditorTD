#ifndef _UTIL_SYSTEM_H_
#define _UTIL_SYSTEM_H_
#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include <Windows.h>

//[Reference URL=https://en.sfml-dev.org/forums/index.php?topic=16776.0]
//by Hapax November 16, 2014, 02:35:09 am
extern void ETD_MakeTransparentWindow(sf::RenderWindow* window, bool toggle, UINT8 alpha);

#define __USER_VAR__ extern

namespace ETD 
{
	//ETD custrom typedef
	typedef sf::RenderWindow* hRenderWindow;
	typedef sf::Event* hEvent;

	extern sf::RenderWindow* InitWindow();
	extern void FreeWindow(hRenderWindow &hwnd);

	namespace Glob
	{
		extern int ActiveWidget;
	}

	namespace Window 
	{
		extern void Resizing(hRenderWindow window, hEvent h_event);
	}

	extern void WindowLoop(hRenderWindow window);

	//users to define those functions.
	extern void User_InitField(hRenderWindow window);
	extern void User_ProcessEvents(hEvent h_event);
	extern void User_Drawing(hRenderWindow window);
}
#endif