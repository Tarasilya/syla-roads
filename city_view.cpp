#include "city_view.h"
#include "painter.h"
#include "game/city.h"

CityView::CityView(Game* game, City* city) : NodeView(game, city) {}

void CityView::Draw(Painter* painter) const {
    Color city_color = {255, 255 * focused_, 0};
    City* city = (City*) node_;
    Circle city_image = {city->x(), city->y(), 0.1, city_color};
    painter->Draw(city_image);
}
