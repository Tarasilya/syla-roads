#pragma once

struct Color {
	int r;
	int g;
	int b;
};

struct Rectangle {
	int x1;
	int y1;
	int x2;
	int y2;
	Color color;
};

struct Circle {
	int x;
	int y;
	int r;
	Color color;
};

struct Line {
	int x1;
	int y1;
	int x2;
	int y2;
	Color color;
};