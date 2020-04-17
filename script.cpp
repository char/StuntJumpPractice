#include "script.h"
#include "utils.h"
#include "keyboard.h"
#include "jumps.h"

void drawWireframeBox(Vector3 pos1, Vector3 pos2, int r, int g, int b, int a)
{
	float minX = min(pos1.x, pos2.x);
	float minY = min(pos1.y, pos2.y);
	float minZ = min(pos1.z, pos2.z);

	float maxX = max(pos1.x, pos2.x);
	float maxY = max(pos1.y, pos2.y);
	float maxZ = max(pos1.z, pos2.z);

#define LINE(x1, y1, z1, x2, y2, z2) GRAPHICS::DRAW_LINE(x1, y1, z1, x2, y2, z2, r, g, b, a)
	LINE(minX, minY, minZ, maxX, minY, minZ);
	LINE(maxX, minY, minZ, maxX, minY, maxZ);
	LINE(maxX, minY, maxZ, minX, minY, maxZ);
	LINE(minX, minY, maxZ, minX, minY, minZ);

	LINE(minX, maxY, minZ, maxX, maxY, minZ);
	LINE(maxX, maxY, minZ, maxX, maxY, maxZ);
	LINE(maxX, maxY, maxZ, minX, maxY, maxZ);
	LINE(minX, maxY, maxZ, minX, maxY, minZ);

	LINE(minX, minY, minZ, minX, maxY, minZ);
	LINE(maxX, minY, minZ, maxX, maxY, minZ);
	LINE(maxX, minY, maxZ, maxX, maxY, maxZ);
	LINE(minX, minY, maxZ, minX, maxY, maxZ);
#undef LINE
}

void drawWireframeBoxWithRadius(Vector3 coord1, Vector3 coord2, float radius1, float radius2, int r, int g, int b, int a)
{
	float centreX = (coord1.x + coord2.x) / 2.f;
	float centreY = (coord1.y + coord2.y) / 2.f;
	float centreZ = (coord1.z + coord2.z) / 2.f;

	float sizeX = (max(abs(coord1.x), abs(coord2.x)) - min(abs(coord1.x), abs(coord2.x))) / 2.f;
	float sizeY = (max(abs(coord1.y), abs(coord2.y)) - min(abs(coord1.y), abs(coord2.y))) / 2.f;
	float sizeZ = (max(abs(coord1.z), abs(coord2.z)) - min(abs(coord1.z), abs(coord2.z))) / 2.f;

	const float ROOT_2 = 1.41421356237f;

	sizeX += abs(radius2) / (2 * ROOT_2);
	sizeY += abs(radius1) / (2 * ROOT_2);

	// Poor man's feathering: Just expand the coords lul
	// TODO: https://stackoverflow.com/a/5394546

	drawWireframeBox(
		v3(centreX - sizeX, centreY - sizeY, centreZ - sizeZ),
		v3(centreX + sizeX, centreY + sizeY, centreZ + sizeZ),
		r, g, b, a
	);
}

void drawBoxWithRadius(Vector3 coord1, Vector3 coord2, float radius1, float radius2, int r, int g, int b, int a)
{
	float centreX = (coord1.x + coord2.x) / 2.f;
	float centreY = (coord1.y + coord2.y) / 2.f;
	float centreZ = (coord1.z + coord2.z) / 2.f;

	float sizeX = (max(abs(coord1.x), abs(coord2.x)) - min(abs(coord1.x), abs(coord2.x))) / 2.f;
	float sizeY = (max(abs(coord1.y), abs(coord2.y)) - min(abs(coord1.y), abs(coord2.y))) / 2.f;
	float sizeZ = (max(abs(coord1.z), abs(coord2.z)) - min(abs(coord1.z), abs(coord2.z))) / 2.f;

	const float ROOT_2 = 1.41421356237f;

	sizeX += abs(radius2) / (2 * ROOT_2);
	sizeY += abs(radius1) / (2 * ROOT_2);


	GRAPHICS::DRAW_BOX(
		centreX - sizeX, centreY - sizeY, centreZ - sizeZ,
		centreX + sizeX, centreY + sizeY, centreZ + sizeZ,
		r, g, b, a
	);

	// And the backfaces:
	GRAPHICS::DRAW_BOX(
		centreX + sizeX, centreY + sizeY, centreZ + sizeZ,
		centreX - sizeX, centreY - sizeY, centreZ - sizeZ,
		r, g, b, a
	);
}

void drawJumps()
{
	// For some reason on patch v1.27, drawing a regular box messes up all line drawing, so we draw all the wireframe boxes first, then the solid ones.

	GRAPHICS::CLEAR_DRAW_ORIGIN();

	for (StuntJump jump : jumps)
	{
		drawWireframeBox(jump.endCoord1, jump.endCoord2, 48, 255, 255, 255);
		drawWireframeBoxWithRadius(jump.endCoord1, jump.endCoord2, jump.radius1, jump.radius2, 0, 0, 0, 255);
		drawWireframeBox(jump.startCoord1, jump.startCoord2, 48, 255, 48, 255);
	}

	static int opacity = 31;
	if (IsKeyJustUp(VK_F3))
		opacity -= 8 * (IsKeyDown(VK_SHIFT) ? -1 : 1);

	opacity = min(max(opacity, 0), 255);

	for (StuntJump jump : jumps)
	{
		drawBoxWithRadius(jump.endCoord1, jump.endCoord2, jump.radius1, jump.radius2, 255, 255, 255, opacity);
	}
}

void main()
{
	initializeJumps();

	while (true)
	{
		static bool enabled = true;
		if (IsKeyJustUp(VK_F4))
			enabled = !enabled;

		if (enabled)
			drawJumps();

		WAIT(0);
	}
}

void ScriptMain()
{
	main();
}
