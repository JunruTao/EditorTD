#ifndef _UTILITIES_H_
#define _UNITILIES_H_

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>


namespace ETD
{
	typedef std::vector<std::unique_ptr<ETD::Widget>> Widget_Ptr_List;
	typedef std::unique_ptr<ETD::Widget> Widget_Ptr;
}

#endif
