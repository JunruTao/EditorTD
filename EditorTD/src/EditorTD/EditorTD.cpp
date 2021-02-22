#include "EditorTD/text_cursor.h"
#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/ETD_Gui.h"

static int min_window_width = 300;
static int min_window_height = 300;

int main() 
{
    ETD_configure();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Default, settings);
    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);

 
    ETD::Util::FontLib lib1;
    lib1.AddFont(DEFAULT_FONT, DEFAULT_FONT_PATH);
    sf::Text text;
    text.setFont(*lib1.GetFont(DEFAULT_FONT));
    text.setCharacterSize(18);


    sf::String inStr;
    inStr = "Hi Input";
    text.setString(inStr);
    text.setLineSpacing(1);

    sf::RenderTexture text_img;
    text_img.create(400, 300);

    auto cursor = ETD::TextCursor(&window);

    auto box1 = ETD::Widget(&window, sf::FloatRect(0.f, 200.f, 800.f, 400.f));
    auto box2 = ETD::Widgets::TextEditor(&window, sf::FloatRect(0.f, 0.f, 400.f, 200.f));
    

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                break;
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
                {
                    if (!inStr.isEmpty()) inStr.erase(inStr.getSize() - 1);
                    text.setString(inStr);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    inStr += "\n";
                    text.setString(inStr);
                }
                else
                {
                    inStr += event.text.unicode;
                    text.setString(inStr);
                }
            }
            box1.Update(&event);
            box2.Update(&event);
            if (event.type == sf::Event::MouseMoved) 
            {
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
                cursor.Update(pos);
                // text.setOrigin(-pos);
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                auto now_size = window.getSize();
                if ((int)now_size.x <= min_window_width || (int)now_size.y <= min_window_height) {

                    now_size.x = (unsigned int)std::max((int)now_size.x, min_window_width);
                    now_size.y = (unsigned int)std::max((int)now_size.y, min_window_height);
                    window.setSize(now_size);
                }

                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        // Clear screen
        text_img.clear();
        text_img.draw(text);
        text_img.display();
        
        window.clear(sf::Color(Col_SREEN_BACKGROUND));
        sf::Sprite spr(text_img.getTexture());
        window.draw(spr);

        box1.Draw();
        box2.Draw();
        cursor.Draw();

        // Update the window
        window.display();
    }
	return 0;
}