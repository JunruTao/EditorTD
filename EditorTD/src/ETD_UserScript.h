#ifndef _ETD_USERSCRIPT_H_
#define _ETD_USERSCRIPT_H_

#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/util_system.h"
#include "EditorTD/ETD_Gui.h"

__USER_VAR__
ETD::Widget_Ptr_List widgets;

__USER_VAR__
std::unique_ptr<ETD::UI::WindowLayout> layout;

#endif
