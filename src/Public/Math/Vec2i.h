#pragma once

#include <Math/Constants.h>

struct Vec2i {
	union {
		struct { int x, y; };
		struct { int w, h; };
		struct { int u, v; };
		struct { int r, g; };
		struct { int a, b; };
		int data[2];
	};
	Vec2i(int _x = 0, int _y = 0) : x(_x), y(_y) {};
	Vec2i& operator=(const Vec2i& other) {
		x = other.x;
		y = other.y;
		return *this;
	};
	bool operator==(const Vec2i& other) const {
		return x == other.x && y == other.y;
	};
	Vec2i operator+(const Vec2i& other) const {
		return { x + other.x, y + other.y };
	};
	Vec2i& operator+=(const Vec2i& other) {
		x += other.x;
		y += other.y;
		return *this;
	};
	Vec2i operator-(const Vec2i& other) const {
		return { x - other.x, y - other.y };
	};
	Vec2i& operator-=(const Vec2i& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	};
};