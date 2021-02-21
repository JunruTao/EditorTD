#ifndef _ETD_EDITOR_WIDGET_H_
#define _ETD_EDITOR_WIDGET_H_
#include "EditorTD/ETD_Widgets.h"

namespace ETD 
{
	namespace Widgets 
	{
		class TextEditor : public Widget
		{
		public:
			TextEditor(sf::RenderWindow* hwnd, const sf::FloatRect& bound);
			~TextEditor() {};
		protected:
		};
	}
}

#endif
