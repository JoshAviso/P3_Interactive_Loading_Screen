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
	Vec2(float _x, float _y) : x(_x), y(_y){}
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
	Vec2 operator*(const float other) const {
		return { x * other, y * other };
	};
	Vec2& operator*=(const float other) {
		x *= other;
		y *= other;
		return *this;
	};
	Vec2 operator/(const float other) const {
		return { x / other, y / other };
	};
	Vec2& operator/=(const float other) {
		x /= other;
		y /= other;
		return *this;
	};
	float magnitude() {
		return std::sqrt(sqrMagnitude());
    }
    float sqrMagnitude() {
		return x * x + y * y;
    }
    Vec2& normalize() {
		float mag = magnitude();
		if (mag > fEpsilon) {
			x /= mag;
			y /= mag;
		}
		return *this;
    }
};