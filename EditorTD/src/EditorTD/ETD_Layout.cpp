#include "EditorTD/ETD_Layout.h"
#define _CALL std::cout

namespace ETD
{
	namespace UI
	{
		////////////Layout Base Class///////////////////////////////
		Layout::Layout():_hwnd(nullptr) {}
		Layout::~Layout() {}
		void Layout::Update(hEvent h_event, sf::IntRect rect) {}
		//override in child
		void Layout::SelfDraw() {}

		void Layout::DrawLayout() 
		{
			this->SelfDraw();
			if(! _internal_layouts.empty())
				for (size_t i = 0; i < _internal_layouts.size(); ++i) 
					_internal_layouts[i]->DrawLayout();
		}

		////////////Widnow Layout Class///////////////////////////////
		WindowLayout::WindowLayout(hRenderWindow window)
		{
			_hwnd = window;
			_layout_rect = getWindowSize();
			_CALL << "widow_layout_init" << std::endl;
		}

		WindowLayout::~WindowLayout() {}

		void WindowLayout::Update(hEvent h_event, sf::IntRect rect)
		{
			if (h_event->type == sf::Event::Resized) 
			{
				_CALL << "widow_layout_resized"<<std::endl;
				_layout_rect = getWindowSize();
			}

			if (!_internal_layouts.empty())
				for (size_t i = 0; i < _internal_layouts.size(); ++i)
					_internal_layouts[i]->Update(h_event, _layout_rect);
		}

		sf::IntRect WindowLayout::getWindowSize()
		{
			_CALL << "size change-> W:"
				<< _layout_rect.width << " H:"
				<< _layout_rect.height << std::endl;
			return sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_hwnd->getSize()));
		}

		void WindowLayout::AddLayout(std::unique_ptr<Layout> layout)
		{
			if (_internal_layouts.empty()) 
			{
				_internal_layouts.emplace_back(std::move(layout));
			}
			else 
			{
				throw std::runtime_error("[WindowLayout] attemped adding the secondlayout");
			}
		}

		void WindowLayout::SelfDraw() 
		{
			//temp
			sf::RectangleShape recshape(sf::Vector2f((float)_layout_rect.width, (float)_layout_rect.height));
			recshape.setFillColor(sf::Color::Red);
			_hwnd->draw(recshape);
		}
	}
}