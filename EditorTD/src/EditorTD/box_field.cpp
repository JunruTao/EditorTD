#include "EditorTD/box_field.h"
#include "EditorTD/config.h"

using namespace ETD;

sf::RenderTexture BoxField::_buffer_renderer;

short BoxField::_id = 0;

BoxField::BoxField(sf::RenderWindow* hwnd, const sf::FloatRect& bound) 
{
	_id++;
	_hwnd = hwnd;
	_bound = bound;
	_bound.left += WIDGETS_GAP;
	_bound.top += WIDGETS_GAP;
	_bound.width -= WIDGETS_GAP*2;
	_bound.height -= WIDGETS_GAP*2;
	_winSize = _hwnd->getSize();

	_shape = sf::ConvexShape(12);
	_shape.setFillColor(sf::Color(Col_WIDGET_BACKGROUND));
	_shape.setOutlineColor(sf::Color(Col_WIDGET_BORDER));
	_shape.setOutlineThickness(OUTLINE_WIDTH);
	_mask = sf::IntRect(0, 0, (int)_bound.width - FRAME_BLEED_DIST*2, (int)_bound.height - FRAME_BLEED_DIST * 2);
	_vSlider = sf::RectangleShape();
	_hSlider = sf::RectangleShape();

	UpdateMask();
	ConstructOutline();
}

BoxField::~BoxField() 
{
	_id--;
}

void BoxField::Update(sf::Event* event) 
{
	switch (event->type)
	{
	case sf::Event::Resized:
	{
		Resize(event);
		break;
	}
	default:
		break;
	}
}

void BoxField::Resize(sf::Event* event) 
{
	sf::Vector2u new_win_size = _hwnd->getSize();
	float propX = (float)new_win_size.x / (float)_winSize.x;
	float propY = (float)new_win_size.y / (float)_winSize.y;
	_bound.left *= propX;
	_bound.width *= propX;
	_bound.top *= propY;
	_bound.height *= propY;
	UpdateMask();
	ConstructOutline();

	_winSize = new_win_size;
}

void BoxField::UpdateMask() 
{
	_mask.width = (int)_bound.width - FRAME_BLEED_DIST * 2;
	_mask.height = (int)_bound.height - FRAME_BLEED_DIST * 2;
}

void BoxField::ConstructOutline() 
{
	_shape.setPoint(0, sf::Vector2f(_bound.left + OUTLINE_WIDTH + BEVEL_DIST, _bound.top + OUTLINE_WIDTH));
	_shape.setPoint(1, sf::Vector2f(_bound.left + OUTLINE_WIDTH + (BEVEL_DIST*0.3), _bound.top + OUTLINE_WIDTH + (BEVEL_DIST *0.3)));
	_shape.setPoint(2, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + OUTLINE_WIDTH + BEVEL_DIST));
	
	_shape.setPoint(3, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + _bound.height - OUTLINE_WIDTH - BEVEL_DIST));
	_shape.setPoint(4, sf::Vector2f(_bound.left + OUTLINE_WIDTH + (BEVEL_DIST * 0.3), _bound.top + _bound.height - OUTLINE_WIDTH - (BEVEL_DIST * 0.3)));
	_shape.setPoint(5, sf::Vector2f(_bound.left + OUTLINE_WIDTH + BEVEL_DIST, _bound.top + _bound.height - OUTLINE_WIDTH));

	_shape.setPoint(6, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - BEVEL_DIST, _bound.top + _bound.height - OUTLINE_WIDTH));
	_shape.setPoint(7, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - (BEVEL_DIST * 0.3), _bound.top + _bound.height - OUTLINE_WIDTH - (BEVEL_DIST * 0.3)));
	_shape.setPoint(8, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH, _bound.top + _bound.height - OUTLINE_WIDTH - BEVEL_DIST));

	_shape.setPoint(9, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH, _bound.top + OUTLINE_WIDTH + BEVEL_DIST));
	_shape.setPoint(10, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - (BEVEL_DIST * 0.3), _bound.top + OUTLINE_WIDTH + (BEVEL_DIST * 0.3)));
	_shape.setPoint(11, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - BEVEL_DIST, _bound.top + OUTLINE_WIDTH));
}

void BoxField::Draw() const
{
	//Drawing the outline
	_hwnd->draw(_shape);

	_buffer_renderer.create(_mask.width, _mask.height);
	_buffer_renderer.clear(sf::Color(Col_SREEN_BACKGROUND));
	//Buffer's Draw call here..
	_buffer_renderer.display();
	sf::Sprite spr(_buffer_renderer.getTexture());
	spr.setTextureRect(_mask);
	spr.setPosition(_bound.left + FRAME_BLEED_DIST, _bound.top + FRAME_BLEED_DIST);
	_hwnd->draw(spr);
}