#include "road_view.h"
#include "painter.h"
#include "game/road.h"
#include "game/city.h"

RoadView::RoadView(Road* road) : road_(road) {}

void RoadView::Draw(Painter* painter) const {
    Color road_color = {0, 255, 255};
    double x1 = road_->GetCities()[0]->x();
    double y1 = road_->GetCities()[0]->y();
    double x2 = road_->GetCities()[1]->x();
    double y2 = road_->GetCities()[1]->y();
    Line road_image = {x1, y1, x2, y2, road_color};
    painter->Draw(road_image);	
}