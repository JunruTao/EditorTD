#ifndef _UTIL_FONT_LIB_H_
#define _UTIL_FONT_LIB_H_
#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include <map>


namespace ETD
{
	namespace Util 
	{
		class FontLib
		{
			typedef sf::String FKey;
			typedef sf::Font Font;
		public:
			FontLib();
			~FontLib();
			void AddFont(FKey name, sf::String font_PATH);
			Font* GetFont(const FKey name);
		private:
			static bool has_init;
			static std::map<FKey, Font> fonts;
		};
	}
}
#endif
