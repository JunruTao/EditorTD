#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#define ETD_WINDOW_TITLE "Editor TD"

//Window sizes
extern unsigned int INIT_WIN_WIDTH;
extern unsigned int INIT_WIN_HEIGHT;
extern unsigned int INIT_WIN_WIDTH_MIN;
extern unsigned int INIT_WIN_HEIGHT_MAX;

//Editor default font properties
extern std::string DEFAULT_FONT;
extern std::string DEFAULT_FONT_PATH;

//Editor Colors
extern  sf::Color Col_SREEN_BACKGROUND;
extern  sf::Color Col_WIDGET_BACKGROUND;
extern  sf::Color Col_WIDGET_BORDER;
extern  sf::Color Col_EDIT_TEXT;
extern  sf::Color Col_STATIC_TEXT;

//Widget Drawing
extern int FRAME_BLEED_DIST;
extern float  WIDGETS_GAP;
extern float  OUTLINE_WIDTH;
extern float  BEVEL_DIST;

namespace ETD 
{
	namespace Config 
	{
		extern bool Configure();
		extern bool Reload_Config();
		extern bool Load_ConfigurationFiles();
	}
}


#endif 