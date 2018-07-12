#include "city.h"
#include "road.h"
#include "shapes.h"
#include "../painter.h"
#include "../shapes.h"

City::City(int x_coord, int y_coord, int index)
{
    x_ = x_coord;
    y_ = y_coord;
    city_index_ = index;
    syla_ = 0;
    capacity_ = 100;
    wall_ = 100;
}



void City::Draw()
{
    Color city_color(255, 0, 0);
    Circle city_image(x_, y_, 10, city_color);
    Painter.draw(city_image);
}

