#pragma once

#include "MathLib\shapes.h"


void drawCircle(const circle& c);
void drawBox(const AABB& box);
void writeString(const char* s, size_t slen, int x, int y, float size, int lines = 1);
void drawTexture(int texId, const AABB& box);
