#include "shapes.h"

Color::Color(int red, int green, int blue)
{
	r = red;
	g = green;
	b = blue;
	a = 255;
}

Color::Color(int red, int green, int blue, int alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Color::Color()
{
	
}