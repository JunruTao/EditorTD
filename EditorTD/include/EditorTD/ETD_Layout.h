#ifndef _ETD_LAYOUT_
#define _ETD_LAYOUT_

#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/util_system.h"
#include "EditorTD/ETD_Widgets.h"
#include "EditorTD/ETD_EditorWidget.h"
#include "EditorTD/util_font_lib.h"

namespace ETD 
{
	typedef std::vector<std::unique_ptr<ETD::Widget>> Widget_Ptr_List;
	typedef std::unique_ptr<ETD::Widget> Widget_Ptr;

	//to throw in as an interface, widget created under;
	enum class WidgetType
	{
		Generic_Widget,
		Multiline_Text_Editor_Widget
	};

	namespace UI 
	{
		class Layout
		{
		public:
			Layout();
			virtual ~Layout();
			//public functions
			void DrawLayout();
			void SetWindowHandle(hRenderWindow hwnd);
			virtual void Update(hEvent h_event);
			virtual void SetSelfRectFromParent(const sf::FloatRect& parent_rect);
			virtual void AddWidget(ETD::WidgetType widget_type);
			sf::FloatRect GetRegion();
		protected:
			virtual void SelfDraw();
			hRenderWindow _hwnd;
			sf::FloatRect _layout_rect;
			std::vector<std::unique_ptr<Layout>> _internal_layouts;
			
		};


		class WindowLayout : public Layout 
		{
		public:
			WindowLayout(hRenderWindow window);
			~WindowLayout();
			void Update(hEvent h_event);
			void AddLayout(std::unique_ptr<Layout>& layout);
			void AddWidget(ETD::WidgetType widget_type);
			void SetSelfRectFromParent(const sf::FloatRect& parent_rect);
		private:
			sf::FloatRect getWindowSize();
			void SelfDraw();
		};


		class Column_Layout : public Layout
		{
		public:
			Column_Layout(size_t columns=2);
			~Column_Layout();
			void Update(hEvent h_event);
			void AddWidget(ETD::WidgetType widget_type);
			void SetSelfRectFromParent(const sf::FloatRect& parent_rect);
			//void AddLayout(std::unique_ptr<Layout> layout, size_t index);
		private:
			void AppendWidget_inter(ETD::WidgetType widget_type);
			void InitAddedWidget();
			void SelfDraw();
			sf::FloatRect GetSubrect(int index);
			size_t _size;
			int _index;
			float _sub_height;
			ETD::Widget_Ptr_List _widgets;
			std::vector<WidgetType> _widgets_type_list;
			bool _widget_inited;
		};


		//User Interface: (must create a basic windowlayout first)
		typedef std::unique_ptr<ETD::UI::WindowLayout> WindowLayout_Ptr;
		typedef std::unique_ptr<ETD::UI::Layout> Layout_Ptr;
	}
}

extern void CreateLayoutFromWindow(ETD::UI::WindowLayout_Ptr& layout_ptr, ETD::hRenderWindow& window);

#endif
