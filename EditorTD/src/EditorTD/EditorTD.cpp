#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/util_system.h"
#include "EditorTD/ETD_Gui.h"

static int min_window_width = 300;
static int min_window_height = 300;

int main() 
{
    sf::RenderWindow* window = ETD::InitWindow();
    auto box2 = ETD::Widget(window, sf::FloatRect(0.f, 0.f, 400.f, 200.f));
    auto box1 = ETD::Widgets::TextEditor(window, sf::FloatRect(0.f, 200.f, 800.f, 400.f));
    

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
            box1.Update(&event);
            box2.Update(&event);
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                auto now_size = window->getSize();
                if ((int)now_size.x <= min_window_width || (int)now_size.y <= min_window_height) {

                    now_size.x = (unsigned int)std::max((int)now_size.x, min_window_width);
                    now_size.y = (unsigned int)std::max((int)now_size.y, min_window_height);
                    window->setSize(now_size);
                }

                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
                window->setView(sf::View(visibleArea));
            }
        }
        
        window->clear(sf::Color::Black);

        box1.Draw();
        box2.Draw();

        // Update the window
        window->display();
    }
    ETD::FreeWindow(window);
	return 0;
}