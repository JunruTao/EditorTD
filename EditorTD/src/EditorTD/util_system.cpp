#include "EditorTD/util_system.h"


void ETD_MakeTransparentWindow(sf::RenderWindow* window, bool toggle, UINT8 alpha) 
{
	HWND hwnd = window->getSystemHandle();
	if (toggle)
	{
		SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA);
	}
	else 
	{
		SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
		SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}
}

sf::RenderWindow* ETD::InitWindow() 
{
	//Configuration, loading configuration variables.
	ETD_configure();

	//window context setting.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//create window.
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(INIT_WIN_WIDTH, INIT_WIN_HEIGHT), ETD_WINDOW_TITLE, sf::Style::Default, settings);
	if (!window) 
	{
		throw std::runtime_error("[ETD::InitWindow] Failed to create window.");
	}

	std::cout << "[ETD::InitWindow] - Status: [Success], registed window on heap at:" << static_cast<void*>(window) << std::endl;
	//working with view. so that the geometries won't be stretched.
	sf::View view(sf::FloatRect(0, 0, (float)INIT_WIN_WIDTH, (float)INIT_WIN_HEIGHT));
	window->setView(view);
	window->setFramerateLimit(30);
	window->setVerticalSyncEnabled(true);
	return window;
}

void ETD::FreeWindow(sf::RenderWindow* &hwnd) 
{
	std::cout << "[ETD::FreeWindow] delete window on heap at:" << static_cast<void*>(hwnd) << std::endl;
	delete hwnd;
}