#ifndef _ETD_WIDGETS_H_
#define _ETD_WIDGETS_H_
#include "EditorTD/utilities.h"
#include "EditorTD/drawable.h"

namespace ETD 
{
	class Widget : public Drawable
	{
	public:
		Widget(sf::RenderWindow* hwnd, const sf::FloatRect& bound, bool hasParent=false);
		Widget();
		~Widget();
		void Draw() override;
		void Update(sf::Event* event);

		int GetID();
		void Activate();
		void Deactivate();
		bool isInbound(sf::Vector2f location);
		void Resize(sf::FloatRect new_frect);
	protected:
		void Resize(sf::Event* event); //update _bound
		void UpdateMask(); //using _bound to shrink and transform _sprite
		void ConstructOutline(); //using _bound to expand and construct _convexShape
		void CacheTexture(); //update the buffer only there is an update
		sf::Vector2i GetClientPivot_i() const;
		sf::Vector2f GetClientPivot_f() const;

		//Call it in constructor if inherit
		void Init(sf::RenderWindow* hwnd, const sf::FloatRect& bound, bool has_buffer);
		//Override if inherit
		virtual void UserUpdate(sf::Event* event); //Allow the child the to update to this.
		//Override if inherit
		virtual void BufferDrawField();//Allow the child the to draw buffers to this.(__buffer_renderer.draw(..))
		//Override if inherit
		virtual void ExtraDraw();//Allow the child the to draw to this.
		//Set to True if inherit and using it.
		bool _toggle_draw_buffer;

		//bounding region
		sf::FloatRect _bound;
		sf::Vector2u _winSize;
		//child. translate value into _mask_offset_x/y
		sf::IntRect _mask;
		float _mask_offset_x;
		float _mask_offset_y;

		sf::Texture _buffer;
		//outline convex
		sf::ConvexShape _outline;
		//window handle
		sf::RenderWindow* _hwnd;
		
		int _id;
		bool _active;
		bool _parented;
		//object id
		static int _widget_count;
		static sf::RenderTexture _buffer_renderer;
	};
}


#endif