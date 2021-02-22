#ifndef _UTIL_SYSTEM_H_
#define _UTIL_SYSTEM_H_
#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include <Windows.h>

//[Reference URL=https://en.sfml-dev.org/forums/index.php?topic=16776.0]
//by Hapax November 16, 2014, 02:35:09 am
extern void ETD_MakeTransparentWindow(sf::RenderWindow* window, bool toggle, UINT8 alpha);


namespace ETD 
{
	extern sf::RenderWindow* InitWindow();
	extern void FreeWindow(sf::RenderWindow* &hwnd);
}
#endif