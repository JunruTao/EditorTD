#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>

extern std::string DEFAULT_FONT;
extern std::string DEFAULT_FONT_PATH;

#define Col_SREEN_BACKGROUND    40,  40,  40,  255
#define Col_WIDGET_BACKGROUND   70,  70,  70,  255
#define Col_WIDGET_BORDER       150, 150, 150, 255
#define Col_EDIT_TEXT           255, 255, 255, 255
#define Col_STATIC_TEXT         187, 187, 187, 255

extern int FRAME_BLEED_DIST;
extern float  WIDGETS_GAP;
extern float  OUTLINE_WIDTH;
extern float  BEVEL_DIST;


extern bool ETD_configure();

#endif 