#pragma once

#include <Math/Vec2i.h>

struct Rect {
	Vec2i position;
	Vec2i size;

	int left() const { return position.x; };
	int top() const { return position.y; };
	int right() const { return position.x + size.x; };
	int bottom() const { return position.y + size.y; };
	bool isHit(Vec2i pos) const {
		return pos.x >= left() && pos.x <= right() && pos.y >= top() && pos.y <= bottom();
	}
};