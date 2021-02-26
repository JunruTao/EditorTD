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
	namespace UI 
	{
		class Layout
		{
		public:
			Layout();
			virtual ~Layout();
			//public functions
			void Update();
			void DrawLayout();

			//need to think about it... the logic.
			void AddLayout(std::unique_ptr<Layout> layout);

		protected:

			std::unique_ptr<Layout> _internal_layouts;
		};


		class Column_Layout : public Layout
		{
		public:
			Column_Layout(size_t columns);
			~Column_Layout();

		protected:
			std::vector<std::unique_ptr<ETD::Widget>> _widgets;
		};
	}
}


#endif
