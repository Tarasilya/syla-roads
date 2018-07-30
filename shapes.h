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
	double thickness;
};