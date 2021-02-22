#include "EditorTD/util_font_lib.h"
using namespace ETD::Util;


typedef sf::String FKey;
typedef sf::Font Font;

bool FontLib::has_init = false;
std::map<FKey, Font> FontLib::fonts;


FontLib::FontLib() 
{
	if (!has_init)
	{
		std::cout << "[ETD::Util::FontLib]Font Library Init" << std::endl;
		AddFont(DEFAULT_FONT, DEFAULT_FONT_PATH);
		has_init = true;
	}
}

FontLib::~FontLib() {}

void FontLib::AddFont(FKey name, sf::String font_PATH) 
{
	if (fonts.find(name) != fonts.end())
	{
		std::cout
			<<"\n [ETD::Util::FontLib]: Font's name has exists in the library."
			<<"\n ------Double check the duplicates of [ " 
			<< std::string(name) 
			<< " ]\n -Status: [Font Not Loaded]"<<std::endl;
	}
	else 
	{
		std::cout 
			<< "\n [ETD::Util::FontLib]: -Loading Font: " 
			<< std::string(font_PATH) << " as " 
			<< std::string(name) << std::endl;

		sf::Font font;
		if (!font.loadFromFile(font_PATH))
		{
			throw std::runtime_error("[ETD::Util::FontLib] Failed to Load Font :" + std::string(font_PATH));
		}
		else
		{
			std::cout << "-Status: [Success] - continue=>>"<<std::endl;
			fonts.insert(std::pair<FKey, Font>(name, font));
		}
	}
}

Font* FontLib::GetFont(const FKey name) 
{
	return &fonts[name];
}
