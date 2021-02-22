#include "EditorTD/ETD_Widgets.h"
#include "EditorTD/config.h"


using namespace ETD;

sf::RenderTexture Widget::_buffer_renderer;
short Widget::_id = 0;

void Widget::Init(sf::RenderWindow* hwnd, const sf::FloatRect& bound, bool has_buffer=false)
{
	_id++;
	_hwnd = hwnd;
	_bound = bound;
	_bound.left += WIDGETS_GAP;
	_bound.top += WIDGETS_GAP;
	_bound.width -= WIDGETS_GAP * 2;
	_bound.height -= WIDGETS_GAP * 2;
	_winSize = _hwnd->getSize();
	_toggle_draw_buffer = has_buffer;

	_outline = sf::ConvexShape(BEVEL_DIST < 0.1 ? 4 : 12);
	_outline.setFillColor(sf::Color(Col_WIDGET_BACKGROUND));
	_outline.setOutlineColor(sf::Color(Col_WIDGET_BORDER));
	_outline.setOutlineThickness(OUTLINE_WIDTH);
	_mask = sf::IntRect(0, 0, (int)_bound.width - FRAME_BLEED_DIST * 2, (int)_bound.height - FRAME_BLEED_DIST * 2);

	_buffer = CacheTexture();

	UpdateMask();
	ConstructOutline();
}

Widget::Widget(sf::RenderWindow* hwnd, const sf::FloatRect& bound) 
{
	this->Init(hwnd, bound);
}

//Constructor for child object
Widget::Widget() {}

Widget::~Widget() 
{
	_id--;
}

void Widget::Update(sf::Event* event) 
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

void Widget::Resize(sf::Event* event) 
{
	sf::Vector2u new_win_size = _hwnd->getSize();
	float propX = (float)new_win_size.x / (float)_winSize.x;
	float propY = (float)new_win_size.y / (float)_winSize.y;
	_bound.left *= propX;
	_bound.width *= propX;
	_bound.top *= propY;
	_bound.height *= propY;
	if (_toggle_draw_buffer) 
	{
		_buffer = CacheTexture();
	}
	UserUpdate(event);
	UpdateMask();
	ConstructOutline();

	_winSize = new_win_size;
}

void Widget::UpdateMask() 
{
	_mask.width = (int)_bound.width - FRAME_BLEED_DIST * 2;
	_mask.height = (int)_bound.height - FRAME_BLEED_DIST * 2;
}

void Widget::ConstructOutline() 
{
	if (BEVEL_DIST < 0.1)
	{
		_outline.setPoint(0, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + OUTLINE_WIDTH));
		_outline.setPoint(1, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + _bound.height - OUTLINE_WIDTH));
		_outline.setPoint(2, sf::Vector2f(_bound.left - OUTLINE_WIDTH + _bound.width, _bound.top + _bound.height - OUTLINE_WIDTH));
		_outline.setPoint(3, sf::Vector2f(_bound.left - OUTLINE_WIDTH + _bound.width, _bound.top + OUTLINE_WIDTH));
	}
	else
	{
		_outline.setPoint(0, sf::Vector2f(_bound.left + OUTLINE_WIDTH + BEVEL_DIST, _bound.top + OUTLINE_WIDTH));
		_outline.setPoint(1, sf::Vector2f(_bound.left + OUTLINE_WIDTH + (float)(0.3f * BEVEL_DIST), _bound.top + OUTLINE_WIDTH + (float)(0.3f * BEVEL_DIST)));
		_outline.setPoint(2, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + OUTLINE_WIDTH + BEVEL_DIST));

		_outline.setPoint(3, sf::Vector2f(_bound.left + OUTLINE_WIDTH, _bound.top + _bound.height - OUTLINE_WIDTH - BEVEL_DIST));
		_outline.setPoint(4, sf::Vector2f(_bound.left + OUTLINE_WIDTH + (float)(0.3 * BEVEL_DIST), _bound.top + _bound.height - OUTLINE_WIDTH - (float)(0.3 * BEVEL_DIST)));
		_outline.setPoint(5, sf::Vector2f(_bound.left + OUTLINE_WIDTH + BEVEL_DIST, _bound.top + _bound.height - OUTLINE_WIDTH));

		_outline.setPoint(6, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - BEVEL_DIST, _bound.top + _bound.height - OUTLINE_WIDTH));
		_outline.setPoint(7, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - (float)(0.3 * BEVEL_DIST), _bound.top + _bound.height - OUTLINE_WIDTH - (float)(0.3 * BEVEL_DIST)));
		_outline.setPoint(8, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH, _bound.top + _bound.height - OUTLINE_WIDTH - BEVEL_DIST));

		_outline.setPoint(9, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH, _bound.top + OUTLINE_WIDTH + BEVEL_DIST));
		_outline.setPoint(10, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - (float)(0.3 * BEVEL_DIST), _bound.top + OUTLINE_WIDTH + (float)(0.3 * BEVEL_DIST)));
		_outline.setPoint(11, sf::Vector2f(_bound.left + _bound.width - OUTLINE_WIDTH - BEVEL_DIST, _bound.top + OUTLINE_WIDTH));
	}
}

void Widget::Draw() const
{
	//Drawing the outline
	_hwnd->draw(_outline);

	if (_toggle_draw_buffer)
	{
		sf::Sprite spr(_buffer);
		spr.setTextureRect(_mask);
		spr.setPosition(_bound.left + FRAME_BLEED_DIST, _bound.top + FRAME_BLEED_DIST);
		_hwnd->draw(spr);
	}
}

sf::Texture Widget::CacheTexture()
{
	if (_toggle_draw_buffer) 
	{
		_buffer_renderer.create(_mask.width, _mask.height);
		_buffer_renderer.clear(sf::Color(Col_STATIC_TEXT));
		//Buffer's Draw call here..
		this->DrawField(&_buffer_renderer);
		_buffer_renderer.display();
		return _buffer_renderer.getTexture();
	}
	else 
	{
		return sf::Texture();
	}
}


/// <summary>
/// Functions for children to overload:
/// </summary>

void Widget::UserUpdate(sf::Event* event) {}
void Widget::DrawField(sf::RenderTexture* _buffer_renderer) {}