#include "EditorTD/util_font_lib.h"
#include "EditorTD/utilities.h"

//bool ETD::FontLibrary::has_init = false;

//std::map<sf::String, sf::Font> ETD::FontLibrary::fonts;

FontLibrary::FontLibrary()
{
	id = 0;
	printf("font_int");
}

FontLibrary::~FontLibrary()
{
	printf("distory");
}


TestClass::TestClass() 
{
	printf("some test class");
}

void TestClass::Call() 
{
	static int i = false;
	if (!i) 
	{
		printf("first call");
		i = true;
	}
}

//sf::Font* ETD::Util::FontLibrary::GetFont(sf::String name){}