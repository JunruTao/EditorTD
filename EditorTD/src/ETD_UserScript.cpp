#include "ETD_UserScript.h"

ETD::UI::WindowLayout_Ptr layout;

void ETD::User_InitField(hRenderWindow window)
{
	CreateLayoutFromWindow(layout,window);
	ETD::UI::Layout_Ptr col_layout(new ETD::UI::Column_Layout(3));
	col_layout->AddWidget(ETD::WidgetType::Generic_Widget);
	col_layout->AddWidget(ETD::WidgetType::Multiline_Text_Editor_Widget);
	layout->AddLayout(col_layout);
}


void ETD::User_ProcessEvents(hEvent h_event)
{
	layout->Update(h_event);
}

void ETD::User_Drawing(hRenderWindow window)
{
	window->clear(sf::Color::Black);
	layout->DrawLayout();
	window->display();
}