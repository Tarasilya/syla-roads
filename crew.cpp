#include "crew.h"

#include <algorithm>

Crew::Crew(double thickness)
{
    thickness_ = thickness;
    start_percentage_ =  0;
    end_percentage_ = 0;
}

double Crew::GetStartPercentage()
{
    return start_percentage_;
}

double Crew::GetEndPercentage()
{
	return end_percentage_;
}

double Crew::GetThickness()
{
    return thickness_;
}

double Crew::GetCumulativeSyla() {
	return (GetEndPercentage() - GetStartPercentage()) * GetThickness();
}

bool Crew::MoveForward(double tick_time, double start_speed, double end_speed, double boundary_coordinate, int crew_index) {
	bool still_present = 1;
	if (start_percentage_ != 0 || crew_index) {
		double new_start_percentage = std::max(start_percentage_ + start_speed * tick_time, 0.);
		if (new_start_percentage < boundary_coordinate) {
			start_percentage_ = new_start_percentage;
		}
		else {
			still_present = 0;
		}
	}
    if (still_present) {
        end_percentage_ = std::min(boundary_coordinate, end_percentage_ + tick_time * end_speed);
    }
	if (end_percentage_ < start_percentage_) {
		still_present = 0;
	}
	return still_present;
}

double Crew::OffensiveSpeed(Crew* enemy_crew, double road_speed) {
    double resulting_speed = road_speed*(thickness_ - enemy_crew->GetThickness()) / (thickness_ + enemy_crew->GetThickness() + 1);
	return resulting_speed;
}
