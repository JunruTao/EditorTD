#include "EditorTD/ETD_Layout.h"
#define _CALL std::cout

//User Interface functions:
void CreateLayoutFromWindow(ETD::UI::WindowLayout_Ptr& layout_ptr, ETD::hRenderWindow& window)
{
	layout_ptr = std::make_unique<ETD::UI::WindowLayout>(window);
}

namespace ETD
{
	namespace UI
	{
		
		////////////Layout Base Class///////////////////////////////
		Layout::Layout():_hwnd(nullptr) {}
		Layout::~Layout() {}
		void Layout::Update(hEvent h_event) {}
		sf::FloatRect  Layout::GetRegion() { return _layout_rect; }
		void Layout::SetWindowHandle(hRenderWindow hwnd) { _hwnd = hwnd; }
		void Layout::AddWidget(ETD::WidgetType widget_type) {}
		//override in child
		void Layout::SelfDraw() {}

		void Layout::SetSelfRectFromParent(const sf::FloatRect& parent_rect)
		{}

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
			_layout_rect = this->getWindowSize();
#if defined(_DEBUG)
			_CALL << "[ETD::UI::WindowLayout's Constructor] Window_layout_init" << std::endl;
#endif
		}

		WindowLayout::~WindowLayout() 
		{
#if defined(_DEBUG)
			_CALL << "[ETD::UI::WindowLayout's Destructor] Window_layout_destoryed" << std::endl;
#endif
		}

		void WindowLayout::Update(hEvent h_event)
		{
			if (h_event->type == sf::Event::Resized) 
			{
#if defined(_DEBUG)
				_CALL << "[ETD::UI::WindowLayout::Update]widow_layout_resized"<<std::endl;
#endif
				_layout_rect = this->getWindowSize();

				//window size event trigers the sub-layouts to update the size;
				if (!_internal_layouts.empty())
					for (size_t i = 0; i < _internal_layouts.size(); ++i)
						_internal_layouts[i]->SetSelfRectFromParent(_layout_rect);
			}

			if (!_internal_layouts.empty())
				for (size_t i = 0; i < _internal_layouts.size(); ++i)
					_internal_layouts[i]->Update(h_event);
		}

		sf::FloatRect WindowLayout::getWindowSize()
		{
#if defined(_DEBUG)
			_CALL << "--[ETD::UI::WindowLayout::getWindowSize] Size change-> X:"
				<< _layout_rect.left << " Y:"
				<< _layout_rect.top << " W:"
				<< _layout_rect.width << " H:"
				<< _layout_rect.height
				<<std::endl;
#endif
			return sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(_hwnd->getSize()));
		}

		void WindowLayout::AddWidget(ETD::WidgetType widget_type) 
		{
			___ERROR_MESSAGE_FEILD___
			_CALL << "[ETD::UI::WindowLayout] Warning: can't add widget to a window layout" << std::endl;
		}

		void WindowLayout::AddLayout(std::unique_ptr<Layout>& layout)
		{
#if defined(_DEBUG)
			_CALL << "[ETD::UI::WindowLayout] Adding layout to layoutlist" << std::endl;
#endif
			if (_internal_layouts.empty()) 
			{
				layout->SetWindowHandle(_hwnd);
				layout->SetSelfRectFromParent(_layout_rect);
				_internal_layouts.emplace_back(std::move(layout));
			}
			else 
			{
				___ERROR_MESSAGE_FEILD___
				throw std::runtime_error("[ETD::UI::WindowLayout] attemped adding the second layout");
			}
		}

		void WindowLayout::SelfDraw()
		{
		}

		void WindowLayout::SetSelfRectFromParent(const sf::FloatRect& parent_rect)
		{
			this->_layout_rect = parent_rect;
		}

		////////////Column Layout Class///////////////////////////////
		Column_Layout::Column_Layout(size_t columns)
			: _size(columns), _index(-1), _sub_height(0), _widget_inited(false)
		{
#if defined(_DEBUG)
			_CALL << "[ETD::UI::Column_Layout's Constructor] Column_Layout_init" << std::endl;
#endif
		}



		Column_Layout::~Column_Layout() 
		{
#if defined(_DEBUG)
			_CALL << "[ETD::UI::Column_Layout's Constructor] Column_Layout_destroyed" << std::endl;
#endif
		}

		void Column_Layout::SetSelfRectFromParent(const sf::FloatRect& parent_rect)
		{
			this->_layout_rect = parent_rect;
			if (!_widget_inited) 
			{
				this->InitAddedWidget();
				_widget_inited = true;
			}
		}


		void Column_Layout::Update(hEvent h_event)
		{
			if (h_event->type == sf::Event::Resized)
			{
#if defined(_DEBUG) 
				_CALL << "[ETD::UI::Column_Layout_layout]_resized" << std::endl;
#endif
				for (size_t i = 0; i < _widgets.size();++i) 
				{
					_widgets[i]->Resize(this->GetSubrect(i));
				}
			}
			for (size_t i = 0; i < _widgets.size();++i)
			{
				_widgets[i]->Update(h_event);
			}
		}



		void Column_Layout::AddWidget(ETD::WidgetType widget_type)
		{
#if defined(_DEBUG) 
			_CALL << "[ETD::UI::Column_Layout_layout]AddWidget to type list" << std::endl;
#endif
			_widgets_type_list.push_back(widget_type);
		}



		void Column_Layout::AppendWidget_inter(ETD::WidgetType widget_type)
		{

#if defined(_DEBUG) 
			_CALL << "[ETD::UI::Column_Layout_layout]AppendWidget internal creating widgets" << std::endl;
#endif
			if (_layout_rect.width != 0 && _layout_rect.height != 0 && _size != 0)
			{
				this->_sub_height = _layout_rect.height / (float)_size;
			}
			else 
			{
				___ERROR_MESSAGE_FEILD___
				_CALL << "[ETD::UI::Column_Layout-AddWidget] Failed, layout_rec or column size not valid\n";
				return;
			}
			if (_size != 0 && _index < (int)_size) 
			{
				this->_index++;
				sf::FloatRect sub_rect(this->GetSubrect(_index));

				switch (widget_type)
				{
				case ETD::WidgetType::Generic_Widget:
					_widgets.emplace_back(std::make_unique<ETD::Widget>(_hwnd, sub_rect, true));
					break;
				case ETD::WidgetType::Multiline_Text_Editor_Widget:
					_widgets.emplace_back(std::make_unique<ETD::Widgets::TextEditor>(_hwnd, sub_rect, true));
					break;
				default:
					___ERROR_MESSAGE_FEILD___
					throw std::runtime_error("[ETD::UI::Column_Layout-AddWidget] Invalid Widget Type");
				}
			}
			else 
			{
				___ERROR_MESSAGE_FEILD___
				throw std::runtime_error("[ETD::UI::Column_Layout-AddWidget] Column Stack is full");
			}
		}

		void Column_Layout::InitAddedWidget() 
		{
			if (!_widgets_type_list.empty()) 
			{
				for (size_t i = 0; i < _widgets_type_list.size(); ++i)
				{
					AppendWidget_inter(_widgets_type_list[i]);
				}
			}
		}

		void Column_Layout::SelfDraw()
		{
			for (size_t i = 0; i < _widgets.size();++i)
			{
				_widgets[i]->Draw();
			}
		}

		// internal function: in order to calculate a subdiv rectangle according to the index
		sf::FloatRect Column_Layout::GetSubrect(int index) 
		{
			return sf::FloatRect(
				sf::Vector2f(_layout_rect.left, _layout_rect.top + (index * _sub_height)),
				sf::Vector2f(_layout_rect.width, _sub_height));
		}
	}
}