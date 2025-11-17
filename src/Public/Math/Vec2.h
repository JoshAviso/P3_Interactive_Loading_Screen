#pragma once

#include <Math/Constants.h>

struct Vec2 {
	union {
		struct { float x, y; };
		struct { float w, h; };
		struct { float u, v; };
		struct { float r, g; };
		struct { float a, b; };
		float data[2];
	};

	Vec2& operator=(const Vec2& other) {
		x = other.x;
		y = other.y;
		return *this;
	};
	bool operator==(const Vec2& other) const {
		return (x > other.x - fEpsilon && x < other.x + fEpsilon) &&
			(y > other.y - fEpsilon && y < other.y + fEpsilon);
	};
	bool operator!=(const Vec2& other) const {
		return !(*this == other);
	};
	Vec2 operator+(const Vec2& other) const {
		return { x + other.x, y + other.y };
	};
	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	};
	Vec2 operator-(const Vec2& other) const {
		return { x - other.x, y - other.y };
	};
	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	};
};