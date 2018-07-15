#pragma once

struct Color {
	int r;
	int g;
	int b;
};

struct Rectangle {
	double x1;
	double y1;
	double x2;
	double y2;
	Color color;

	Rectangle(double x1, double y1, double x2, double y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
};

struct Circle {
	double x;
	double y;
	double r;
	Color color;
};

struct Line {
	double x1;
	double y1;
	double x2;
	double y2;
	Color color;
};