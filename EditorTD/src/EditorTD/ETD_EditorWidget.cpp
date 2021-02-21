#include "EditorTD/ETD_EditorWidget.h"
#include "EditorTD/config.h"

ETD::Widgets::TextEditor::TextEditor(sf::RenderWindow* hwnd, const sf::FloatRect& bound)
{
	this->Init(hwnd, bound, true);
}