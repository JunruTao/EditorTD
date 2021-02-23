#ifndef _TEXT_CURSOR_H_
#define _TEXT_CURSOR_H_

//Extern
#include "SFML/Graphics.hpp"
//Intern
#include "EditorTD/drawable.h"


namespace ETD 
{
	class TextCursor : public Drawable
	{
	public:
		TextCursor(sf::RenderWindow* hwnd);
		~TextCursor();
		void Draw() override;
		void Update(const sf::Vector2f& location);
	private:
		sf::RectangleShape _shape;
		sf::RenderWindow* _hwnd;
	};
}

#endif
