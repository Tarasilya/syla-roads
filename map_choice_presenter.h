#pragma once
#include "presenter.h"
#include "map_presenter.h"

class MapChoicePresenter : public Presenter {
private:
	std::vector<MapPresenter*> map_presenters_;
public:
	MapChoicePresenter(Controller* controller, Painter* painter);
	void Draw();
	void ProcessKey(sf::Keyboard::Key key);
};