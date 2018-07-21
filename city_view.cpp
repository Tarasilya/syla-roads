#include "city_view.h"
#include "painter.h"
#include "game/city.h"

CityView::CityView(City* city) : city_(city) {}

void CityView::Draw(Painter* painter) const {
    Color city_color = {255, 255 * focused_, 0};
    Circle city_image = {city_->x(), city_->y(), 0.1, city_color};
    painter->Draw(city_image);
}

Node* CityView::GetNode() const {
	return city_;
}