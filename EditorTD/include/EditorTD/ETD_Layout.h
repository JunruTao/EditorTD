#ifndef _ETD_LAYOUT_
#define _ETD_LAYOUT_

#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/util_system.h"
#include "EditorTD/ETD_Widgets.h"
#include "EditorTD/ETD_EditorWidget.h"
#include "EditorTD/util_font_lib.h"
#include "EditorTD/ETD_Gui.h"

namespace ETD 
{
	typedef std::vector<std::unique_ptr<ETD::Widget>> Widget_Ptr_List;
	typedef std::unique_ptr<ETD::Widget> Widget_Ptr;

	namespace UI 
	{
		class Layout
		{
		public:
			Layout();
			virtual ~Layout();
			//public functions
			void DrawLayout();
			virtual void Update(hEvent h_event, sf::IntRect rect = { 0,0,0,0 });

		protected:
			virtual void SelfDraw();

			hRenderWindow _hwnd;
			sf::IntRect _layout_rect;
			std::vector<std::unique_ptr<Layout>> _internal_layouts;
			
		};


		class WindowLayout : public Layout 
		{
		public:
			WindowLayout(hRenderWindow window);
			~WindowLayout();
			void Update(hEvent h_event, sf::IntRect rect = {0,0,0,0});
			void AddLayout(std::unique_ptr<Layout> layout);
		private:
			sf::IntRect getWindowSize();
			void SelfDraw();
		};


		class Column_Layout : public Layout
		{
		public:
			Column_Layout(size_t columns) {};
			~Column_Layout() {};
			void Update(hEvent h_event, sf::IntRect rect) {};
		private:
			void SelfDraw() {};
		protected:
			ETD::Widget_Ptr_List _widgets;
		};
	}
}


#endif
