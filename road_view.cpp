#include "road_view.h"
#include "painter.h"
#include "road.h"
#include "city.h"
#include "sizes.h"

#include <cmath>

RoadView::RoadView(Road* road) : road_(road), selected_cities_(2) {}

const double THICKNESS = 0.03;

void RoadView::Draw(Painter* painter) const {
    if (road_->GetState() != WAR)
    {
        Color road_color = ROAD_COLOR;
        std::vector<double> x(6);
        std::vector<double> y(6);
        x[0] = road_->GetCities()[0]->x();
        y[0] = road_->GetCities()[0]->y();
        x[5] = road_->GetCities()[1]->x();
        y[5] = road_->GetCities()[1]->y();
        double dx = (x[5] - x[0]);
        double dy = (y[5] - y[0]);
        double len = sqrt(dx*dx + dy*dy);
        x[1] = x[0] + dx * CITY_RADIUS / len;
        y[1] = y[0] + dy * CITY_RADIUS / len;
        x[4] = x[5] - dx * CITY_RADIUS / len;
        y[4] = y[5] - dy * CITY_RADIUS / len;
        dx = x[4] - x[1];
        dy = y[4] - y[1];
        len = sqrt(dx*dx + dy*dy);
        x[2] = x[1] + dx * road_->GetCompleteness(0);
        y[2] = y[1] + dy * road_->GetCompleteness(0);
        x[3] = x[4] - dx * road_->GetCompleteness(1);
        y[3] = y[4] - dy * road_->GetCompleteness(1);
        std::vector<Color> colors(6);
        colors[0] = selected_cities_[0] ? SELECTED_ROAD_COLOR : ROAD_COLOR;
        colors[1] = BUILT_ROAD;
        colors[2] = ROAD_COLOR;
        colors[3] = BUILT_ROAD;
        colors[4] = selected_cities_[1] ? SELECTED_ROAD_COLOR : ROAD_COLOR;

        for (int i = 0; i < (int) x.size() - 1; i++) {
            painter->Draw({x[i], y[i], x[i+1], y[i+1], colors[i], ROAD_THICKNESS});
        }
    }
    else
    {
        std::vector<double> x(2);
        std::vector<double> y(2);
        x[0] = road_->GetCities()[0]->x();
        y[0] = road_->GetCities()[0]->y();
        x[1] = road_->GetCities()[1]->x();
        y[1] = road_->GetCities()[1]->y();
        painter->Draw({x[0], y[0], x[1], y[1], BUILT_ROAD, ROAD_THICKNESS});
        for (int i = 0; i < 2; i++)
        {
            City* city = road_->GetCities()[i];
            for (int j = 0; j < road_->GetContingents()[i].size(); j++)
            {   
                Crew* crew = road_->GetContingents()[i][j];
                std::vector<double> crew_x(2);
                std::vector<double> crew_y(2);
                double start_p = crew->GetStartPercentage();
                double end_p = crew->GetEndPercentage();
                crew_x[0] = x[i] * (1 - start_p) + x[!i] * start_p;
                crew_y[0] = y[i] * (1 - start_p) + y[!i] * start_p;
                crew_x[1] = x[i] * (1 - end_p) + x[!i] * end_p;
                crew_y[1] = y[i] * (1 - end_p) + y[!i] * end_p;
                painter->Draw({crew_x[0], crew_y[0], crew_x[1], crew_y[1], PLAYER_COLORS[i], crew->GetThickness() / 600});
            }
        }
    }
}

void RoadView::SelectFromCity(int city_id) {
	for (int i = 0; i < 2; i++) {
		if (road_->GetCities()[i]->GetIndex() == city_id) {
			selected_cities_[i] = true;
		}
	}
}

void RoadView::DeselectFromCity(int city_id) {
	for (int i = 0; i < 2; i++) {
		if (road_->GetCities()[i]->GetIndex() == city_id) {
			selected_cities_[i] = false;
		}
	}
}

Road* RoadView::GetRoad() {
    return road_;
}