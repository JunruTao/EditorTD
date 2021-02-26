#include "EditorTD/util_system.h"
#include <math.h>

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
	if (!ETD::Config::Configure()) 
	{
		throw std::runtime_error("[ETD::InitWindow] Failed to configure.");
	}

	//window context setting.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//create window.
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(INIT_WIN_WIDTH, INIT_WIN_HEIGHT), ETD_WINDOW_TITLE, sf::Style::Default, settings);
	if (!window) 
	{
		throw std::runtime_error("[ETD::InitWindow] Failed to create window.");
	}

	std::cout << "[ETD::InitWindow] - Status: [Success], registed window on heap at:0x" << (void*)(window) << std::endl;
	//working with view. so that the geometries won't be stretched.
	sf::View view(sf::FloatRect(0, 0, (float)INIT_WIN_WIDTH, (float)INIT_WIN_HEIGHT));
	window->setView(view);
	window->setFramerateLimit(30);
	window->setVerticalSyncEnabled(true);
	return window;
}

void ETD::FreeWindow(hRenderWindow &hwnd)
{
	std::cout << "[ETD::FreeWindow] delete window on heap at:0x" << (void*)(hwnd) << std::endl;
	delete hwnd;
}


void ETD::Window::Resizing(hRenderWindow window, hEvent h_event)
{
	if (h_event->type == sf::Event::Resized)
	{
		// update the view to the new size of the window
		auto now_size = window->getSize();
		if ((int)now_size.x <= INIT_WIN_WIDTH_MIN || (int)now_size.y <= INIT_WIN_HEIGHT_MIN) {

			now_size.x = (unsigned int)std::max((int)now_size.x, (int)INIT_WIN_WIDTH_MIN);
			now_size.y = (unsigned int)std::max((int)now_size.y, (int)INIT_WIN_HEIGHT_MIN);
			window->setSize(now_size);
		}

		sf::FloatRect visibleArea(0, 0, (float)h_event->size.width, (float)h_event->size.height);
		window->setView(sf::View(visibleArea));
	}
}



//This is a global variable that should be include in widgets.
int ETD::Glob::ActiveWidget = -1;

void ETD::WindowLoop(hRenderWindow window)
{
	ETD::User_InitField(window);
	while (window->isOpen())
	{
		// Process events
		sf::Event event;
		while (window->pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				window->close();
				break;
			}

			//Process Users's event
			ETD::User_ProcessEvents(&event);
			ETD::Window::Resizing(window, &event);
		}
		ETD::User_Drawing(window);
	}
}