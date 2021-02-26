#include "ETD_UserScript.h"

int main() 
{
    ETD::hRenderWindow window = ETD::InitWindow();
    ETD::WindowLoop(window);
    ETD::FreeWindow(window);
	return 0;
}