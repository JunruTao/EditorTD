#ifndef _ETD_EDITOR_WIDGET_H_
#define _ETD_EDITOR_WIDGET_H_
#include "EditorTD/ETD_Widgets.h"
#include "EditorTD/util_font_lib.h"

namespace ETD 
{
	namespace Widgets 
	{
		/*[Instruction for Children of Widgets]
		* 
		*	- 1. process any events here.
			void UserUpdate(sf::Event* event) {}

			- 2. use buffer draw field: in init(), set has_buffer to `true` 
			void BufferDrawField()
			{
				_buffer_renderer.draw( <geometry> );
			}

			- 3. any extra draw calls will use this function, overlay on top of widgets
			void ExtraDraw() 
			{
				_hwnd->draw( <geometry> );
			}
		*/
		class TextEditor : public Widget
		{
		public:
			TextEditor(sf::RenderWindow* hwnd, const sf::FloatRect& bound);
			~TextEditor() {};
		protected:
			void ExtraDraw();
			void BufferDrawField();
			void UserUpdate(sf::Event* event);

		private:
			void Update_TypingOffset();
			
			sf::String _text_string;
			sf::Text _text_object;
			ETD::Util::FontLib* _fontlib;
		};
	}
}

#endif
