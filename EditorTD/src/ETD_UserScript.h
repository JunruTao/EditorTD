#ifndef _ETD_USERSCRIPT_H_
#define _ETD_USERSCRIPT_H_

#include "EditorTD/utilities.h"
#include "EditorTD/config.h"
#include "EditorTD/util_system.h"
#include "EditorTD/ETD_Gui.h"

typedef std::vector<std::unique_ptr<ETD::Widget>> Widget_Ptr_List;
typedef std::unique_ptr<ETD::Widget> Widget_Ptr;

extern Widget_Ptr_List widgets;

#endif
