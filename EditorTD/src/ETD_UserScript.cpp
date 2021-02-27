#include "ETD_UserScript.h"

ETD::Widget_Ptr_List widgets;
std::unique_ptr<ETD::UI::WindowLayout> layout;

void ETD::User_InitField(hRenderWindow window)
{
	widgets.emplace_back(new ETD::Widget(window, sf::FloatRect(0.f, 0.f, 400.f, 200.f)));
	widgets.emplace_back(new ETD::Widgets::TextEditor(window, sf::FloatRect(0.f, 200.f, 800.f, 400.f)));
	layout = std::make_unique<ETD::UI::WindowLayout>(window);
}


void ETD::User_ProcessEvents(hEvent h_event)
{
	for (size_t i = 0; i < widgets.size(); ++i)
	{
		widgets[i]->Update(h_event);
	}
	layout->Update(h_event);
}

void ETD::User_Drawing(hRenderWindow window)
{
	window->clear(sf::Color::Black);

	for (size_t i = 0; i < widgets.size(); ++i)
	{
		widgets[i]->Draw();
	}
	layout->DrawLayout();

	// Update the window
	window->display();
}