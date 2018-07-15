#include "map_choice_presenter.h"
#include "map_presenter.h"
#include "painter.h"
#include "controller.h"
#include "restricted_painter.h"

#include <iostream>
#include <fstream>
#include <string>

MapChoicePresenter::MapChoicePresenter(Controller* controller, Painter* painter) : Presenter(controller, painter) {
	std::ifstream maps ("maps.in");
	std::string filename;
	for (int i = 0; maps >> filename; i++) {
		double x1 = -1 + (i % 3) * 2 / 3.0;
		double y1 = -1 + (i / 3) * 2 / 3.0;
		map_presenters_.push_back(
			new MapPresenter(
				controller,
				new RestrictedPainter(painter, {x1, y1, x1 + 2/3, y1 + 2/3}), 
				Map(filename)
			)
		);
		std::cerr << filename << std::endl;

	}
	std::cerr << "done reading maps" << std::endl;
}

void MapChoicePresenter::Draw() {
	for (auto presenter : map_presenters_) {
		std::cerr << "presenter->Draw()" << std::endl;
		presenter->Draw();
	}
}

void MapChoicePresenter::ProcessKey(sf::Keyboard::Key key) {
	if (sf::Keyboard::Num1 <= key && key <= sf::Keyboard::Num9) {
		map_presenters_[key - sf::Keyboard::Num1]->GetMap();
	}
}