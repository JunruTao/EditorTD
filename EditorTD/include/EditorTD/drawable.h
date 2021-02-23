#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

namespace ETD 
{
	class Drawable 
	{
	public:
		Drawable() {};
		virtual ~Drawable() {};
		virtual void Draw() = 0;
	};
}

#endif