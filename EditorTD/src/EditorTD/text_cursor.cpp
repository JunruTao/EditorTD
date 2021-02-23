#include "EditorTD/text_cursor.h"

using namespace ETD;

TextCursor::TextCursor(sf::RenderWindow* hwnd)
{
	_shape = sf::RectangleShape(sf::Vector2f(1.0f, 10.0f));
	_shape.setFillColor(sf::Color::White);
	_shape.setPosition(sf::Vector2f(50, 50));
	_hwnd = hwnd;
}

TextCursor::~TextCursor() {}

void TextCursor::Draw()
{
	_hwnd->draw(_shape);
}


void TextCursor::Update(const sf::Vector2f& location) 
{
	_shape.setPosition(location);
}