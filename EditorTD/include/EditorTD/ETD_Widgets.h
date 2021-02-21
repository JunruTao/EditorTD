#ifndef _ETD_WIDGETS_H_
#define _ETD_WIDGETS_H_
#include "EditorTD/utilities.h"
#include "EditorTD/drawable.h"
#include "EditorTD/text_cursor.h"

namespace ETD 
{
	class Widget : public Drawable
	{
	public:
		Widget(sf::RenderWindow* hwnd, const sf::FloatRect& bound);
		Widget();
		~Widget();
		void Draw() const override;
		void Update(sf::Event* event);
	protected:
		void Resize(sf::Event* event); //update _bound
		void UpdateMask(); //using _bound to shrink and transform _sprite
		void ConstructOutline(); //using _bound to expand and construct _convexShape
		sf::Texture CacheTexture(); //update the buffer only there is an update

		//Call it in constructor if inherit
		void Init(sf::RenderWindow* hwnd, const sf::FloatRect& bound, bool has_buffer);
		//Overload if inherit
		void UserUpdate(sf::Event* event); //Allow the child the to update to this.
		//Overload if inherit
		void DrawField(sf::RenderTexture* _buffer_renderer);//Allow the child the to draw to this.
		//Set to True if inherit and using it.
		bool _toggle_draw_buffer;

		//bounding region
		sf::FloatRect _bound;
		sf::Vector2u _winSize;
		sf::IntRect _mask;
		sf::Texture _buffer;
		//outline convex
		sf::ConvexShape _outline;
		//window handle
		sf::RenderWindow* _hwnd;
		
		//object id
		static short _id;
		static sf::RenderTexture _buffer_renderer;
	};
}


#endif