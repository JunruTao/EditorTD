#ifndef _BOX_FIELD_H_
#define _BOX_FIELD_H_
#include <SFML/Graphics.hpp>
#include "EditorTD/drawable.h"
#include "EditorTD/text_cursor.h"

namespace ETD 
{
	class BoxField : public Drawable
	{
	public:
		BoxField(sf::RenderWindow* hwnd, const sf::FloatRect& bound);
		~BoxField();
		void Draw() const override;
		void Update(sf::Event* event);
	protected:
		void Resize(sf::Event* event); //update _bound
		void UpdateMask(); //using _bound to shrink and transform _sprite
		void ConstructOutline(); //using _bound to expand and construct _convexShape

		//bounding region
		sf::FloatRect _bound;
		sf::IntRect _mask;
		sf::Vector2u _winSize;
		//outline convex
		sf::ConvexShape _shape;
		// navigators
		sf::RectangleShape _vSlider;
		sf::RectangleShape _hSlider;

		//window handle
		sf::RenderWindow* _hwnd;
		
		//object id
		static short _id;
		static sf::RenderTexture _buffer_renderer;
	};
}


#endif
