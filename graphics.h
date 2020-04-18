#pragma once

#include "../../inc/natives.h"
#include "../../inc/types.h"

#include "vectors.h"

void drawQuad(Vector3 pos1, Vector3 pos2, Vector3 pos3, Vector3 pos4, int r, int g, int b, int a)
{
	GRAPHICS::DRAW_POLY(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, pos3.x, pos3.y, pos3.z, r, g, b, a);
	GRAPHICS::DRAW_POLY(pos3.x, pos3.y, pos3.z, pos4.x, pos4.y, pos4.z, pos1.x, pos1.y, pos1.z, r, g, b, a);
}

void drawBoxWireframe(RotatableCuboid box, int r, int g, int b, int a)
{
	Vector3 start = box.start, end = box.end;
	float width = abs(box.width) / 2.f;

	auto delta = v3(end.x - start.x, end.y - start.y, end.z - start.z);
	auto up = v3(0, 0, 1);

	auto perp = crossProduct(delta, up);
	perp.z = 0;
	perp = normalize(perp);

	float bottom = min(start.z, end.z);
	float top = max(start.z, end.z);

#define LINE(lX1, lY1, lZ1, lX2, lY2, lZ2) GRAPHICS::DRAW_LINE(lX1, lY1, lZ1, lX2, lY2, lZ2, r, g, b, a)
#define LINE2D(lX1, lY1, lX2, lY2) LINE(lX1, lY1, bottom, lX2, lY2, bottom); LINE(lX1, lY1, top, lX2, lY2, top)

	LINE2D(start.x + perp.x * width, start.y + perp.y * width, end.x + perp.x * width, end.y + perp.y * width);
	LINE2D(start.x - perp.x * width, start.y - perp.y * width, end.x - perp.x * width, end.y - perp.y * width);
	LINE2D(start.x - perp.x * width, start.y - perp.y * width, start.x + perp.x * width, start.y + perp.y * width);
	LINE2D(end.x - perp.x * width, end.y - perp.y * width, end.x + perp.x * width, end.y + perp.y * width);

	LINE(start.x + perp.x * width, start.y + perp.y * width, bottom, start.x + perp.x * width, start.y + perp.y * width, top);
	LINE(end.x + perp.x * width, end.y + perp.y * width, bottom, end.x + perp.x * width, end.y + perp.y * width, top);
	LINE(start.x - perp.x * width, start.y - perp.y * width, bottom, start.x - perp.x * width, start.y - perp.y * width, top);
	LINE(end.x - perp.x * width, end.y - perp.y * width, bottom, end.x - perp.x * width, end.y - perp.y * width, top);
#undef LINE2D
#undef LINE
}

void drawBox(RotatableCuboid box, int r, int g, int b, int a)
{
	Vector3 start = box.start, end = box.end;
	float width = abs(box.width) / 2.f;

	auto delta = v3(end.x - start.x, end.y - start.y, end.z - start.z);
	auto up = v3(0, 0, 1);

	auto perp = crossProduct(delta, up);
	perp.z = 0;
	perp = normalize(perp);

	float bottom = min(start.z, end.z);
	float top = max(start.z, end.z);

	Vector3
		vertex4Top = v3(start.x + perp.x * width, start.y + perp.y * width, top),
		vertex3Top = v3(start.x - perp.x * width, start.y - perp.y * width, top),
		vertex2Top = v3(end.x - perp.x * width, end.y - perp.y * width, top),
		vertex1Top = v3(end.x + perp.x * width, end.y + perp.y * width, top);

	Vector3
		vertex4Bottom = v3(start.x + perp.x * width, start.y + perp.y * width, bottom),
		vertex3Bottom = v3(start.x - perp.x * width, start.y - perp.y * width, bottom),
		vertex2Bottom = v3(end.x - perp.x * width, end.y - perp.y * width, bottom),
		vertex1Bottom = v3(end.x + perp.x * width, end.y + perp.y * width, bottom);

	drawQuad(vertex1Top, vertex2Top, vertex3Top, vertex4Top, r, g, b, a);
	drawQuad(vertex4Bottom, vertex3Bottom, vertex2Bottom, vertex1Bottom, r, g, b, a);

	drawQuad(vertex1Bottom, vertex1Top, vertex4Top, vertex4Bottom, r, g, b, a);
	drawQuad(vertex4Bottom, vertex4Top, vertex3Top, vertex3Bottom, r, g, b, a);
	drawQuad(vertex3Bottom, vertex3Top, vertex2Top, vertex2Bottom, r, g, b, a);
	drawQuad(vertex2Bottom, vertex2Top, vertex1Top, vertex1Bottom, r, g, b, a);
}
