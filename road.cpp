#include "road.h"
#include "enum.h"
#include "city.h"
#include "crew.h"
#include "painter.h"
#include "shapes.h"
#include "road_view.h"

#include <cmath>
#include <sstream>
#include <iostream>


RoadState Road::GetState()
{
    return state_;
}

Road::Road(std::vector<City*> cities){
    cities[0]->AddRoad(this);
    cities[1]->AddRoad(this);
    contingents_.assign(2, {});
    cities_indices_ = {cities[0]->GetIndex(), cities[1]->GetIndex()};
	view_ = 0;
    cities_connected_ = cities;
    state_ = CONSTRUCTION;
    syla_influx_.assign(2, 0);
    completeness_.assign(2, 0);
    speed_ = 6;
    cost_ = 5;
    trade_profit_ = 1.1;
}



std::vector<std::deque<Crew*>> Road::GetContingents(){
    return contingents_;
}

void Road::Tick(double tick_time) {
    if (state_ == CONSTRUCTION){
        TickBuild(tick_time);
    }
    else if (state_  == TRADE){
        TickTrade(tick_time);
    }
    else if (state_ == WAR){
        TickWar(tick_time);
    }

}

double Road::CityExpense(int city_index){
    double expense;
    int position_ind = GetCityPositionInVectors(city_index);
    int num_crew = contingents_[position_ind].size();
    if (num_crew > 0){
        expense = contingents_[position_ind][0]->GetThickness();
    }
    else{
        expense = 0;
    }
    return expense;
}

int Road::GetCityPositionInVectors(int city_index){
	int position = -1;
	for (int i = 0; i < 2; i++){
		if (cities_indices_[i] == city_index){
			position = i;
		}
	}
	return position;
}


void Road::SetSylaInflux(int city_index, double syla_rate){
	int city_position = GetCityPositionInVectors(city_index);
    std::cout << "SetSylaInflux: city_pos " << city_position << " syla " << syla_rate << "\n";
	syla_influx_[city_position] = syla_rate;
	if (state_ != CONSTRUCTION){
        AddCrew(city_position, syla_rate);
    }
}

void Road::AddCrew(int position, double thickness){
    Crew* new_crew = new Crew(thickness);
    contingents_[position].push_front(new_crew);
}

void Road::TickBuild(double tick_time){
    for (int i = 0; i < 2; i++){
        double syla_spending = tick_time * syla_influx_[i];
        if (cities_connected_[i]->LoseSyla(syla_spending)){
            completeness_[i] += syla_spending * speed_ / cost_;
        }
    }
    if (completeness_[0] + completeness_[1] > 1){
        ResetToTrade();
    }
}

void Road::ResetToTrade(){
    // By default, road state resets to trade after completion
    // with zero contingents on both sides
    if (completeness_[0] + completeness_[1] < 1 - 1e-9) {
        return;
    }
    completeness_[0] = std::min(1.0, completeness_[0]);
    completeness_[1] = 1 - completeness_[0];
    state_ = TRADE;
    syla_influx_[0] = 0;
    syla_influx_[1] = 0;
}

void Road::InitiateWar(){
	// Arbitrary constants
    state_ = WAR;
    syla_influx_[0] = 0;
    syla_influx_[1] = 0;
    contingents_.assign(2, {});
}

void Road::TickTrade(double tick_time){
	for (int i = 0; i < 2; i++){
        if  (contingents_[i].size()){

        	UpdateCityProfit(i, tick_time);
            
            SendNewTraders(i, tick_time);

            MoveTraders(i, tick_time);
        }
	}
}

double Road::CumulativeArmy(int position)
{
    double result = 0;
    int num_crew = contingents_[position].size();
    for (int i = 0; i < num_crew; i++){
        result += contingents_[position][i]->GetCumulativeSyla();
    }
    return result;
}

void Road::TickWar(double tick_time) {

	std::vector<Crew*> front_crew = GetFrontCrew(tick_time);

	for (int i = 0; i < 2; i++) {
        if (!contingents_[i].empty()) {
            double boundary_coordinate = GetBoundary(i, front_crew);
            
            bool meeting = FrontCrewsMeet(front_crew);

            double advancement_speed = GetAdvancementSpeed(i, front_crew, meeting);
            
            PadEmptyCrews(i, tick_time);

            MoveAndEliminateContingents(i, tick_time, boundary_coordinate, advancement_speed);

            Siege(i, front_crew, tick_time, 1e-2, advancement_speed);

        }
	}
}

ObjectView* Road::GetView(Game* game) {
	if (view_ == 0) {
		view_ = new RoadView(this);
	}
	return view_;
}

const std::vector<City*>& Road::GetCities() const{
	return cities_connected_;
}

double Road::GetCompleteness(int index) {
    return completeness_[index];
}

// HELPER FUNCTIONS FOR TICKTRADE

void Road::UpdateCityProfit(int i, double tick_time){
	if (contingents_[i].back()->GetEndPercentage() >= 1){
        double profit = tick_time*trade_profit_ * contingents_[i].back()->GetThickness();
        cities_connected_[i]->AcquireSyla(profit);
	}	
}

void Road::SendNewTraders(int i, double tick_time){
    if (contingents_[i].front()->GetStartPercentage() <= 0){
        double maintenance_cost = contingents_[i].front()->GetThickness()*tick_time;
        if (!cities_connected_[i]->LoseSyla(maintenance_cost)){
            AddCrew(i, 0);
        }
    }
}

void Road::MoveTraders(int i, double tick_time){
    for (int j = 0; j < (int) contingents_[i].size(); j++){
        if ( !contingents_[i][j]->MoveForward(tick_time, speed_, speed_, 1, j) ){
            contingents_[i].erase(contingents_[i].begin() + j);
        }
    }
}

// HELPER FUNCTIONS FOR TICKWAR

std::vector<Crew*> Road::GetFrontCrew(double tick_time) const{
	/*
	Determines what crews are at the front of respective sides of the road
	*/
	std::vector<Crew*> front_crew;

	for (int i = 0; i < 2; i++) {
        if (contingents_[i].size()) {
            front_crew.push_back(contingents_[i][contingents_[i].size() - 1]);
        }
        else {
        	if (cities_connected_[i]->LoseSyla(syla_influx_[i]*tick_time)) {
				front_crew.push_back(new Crew(syla_influx_[i]));	
        	}
        	else {
        		front_crew.push_back(new Crew(0));
        	}
        }
    }
    return front_crew;
}


bool Road::FrontCrewsMeet(const std::vector<Crew*>& front_crew){
	return ((front_crew[0]->GetEndPercentage() + front_crew[1]->GetEndPercentage()) > (1 - 1e-2));
}


double Road::GetAdvancementSpeed(int i, std::vector<Crew*> front_crew, bool meeting){
	if (!meeting){
        return speed_;
    }
	return front_crew[i]->OffensiveSpeed(front_crew[1-i], speed_);
}

double Road::GetBoundary( int i, std::vector<Crew*> front_crew){
	return (front_crew[i]->GetEndPercentage() + 1 - front_crew[1-i]->GetEndPercentage())/2;
}

void Road::PadEmptyCrews(int i, double tick_time){
	if (!cities_connected_[i]->LoseSyla(contingents_[i].front()->GetThickness()*tick_time)){
        AddCrew(i, 0);  
    }
}

void Road::MoveAndEliminateContingents(int i, double tick_time, double boundary, double adv_speed){
	for (int j = 0; j < (int) contingents_[i].size() - 1; j++) {
        if(!contingents_[i][j]->MoveForward(tick_time, speed_, speed_, boundary, j)) {
            contingents_[i].erase(contingents_[i].begin() + j);
        }
    }
    if (!contingents_[i].back()->MoveForward(tick_time, speed_, adv_speed, boundary, (int) contingents_[i].size() - 1 )) {
         contingents_[i].pop_back();
    }
}

void Road::Siege(int i, std::vector<Crew*> front_crew, double tick_time, double close_enough, double adv_speed){
	if (front_crew[i]->GetEndPercentage() >= 1-close_enough) {
        cities_connected_[!i]->DamageWall(adv_speed * tick_time*(front_crew[i]->GetThickness() - front_crew[1-i]->GetThickness() ));
        if (cities_connected_[!i]->GetWall() <= 0) {
            cities_connected_[!i]->ChangeOwner(cities_connected_[i]->GetOwner());
            cities_connected_[!i]->ResetCapture();
            ResetToTrade();
        }
    }
}
