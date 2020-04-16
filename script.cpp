#include "script.h"
#include "utils.h"
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

void update()
{
	for (StuntJump jump : jumps)
	{
		// TODO: Replace GRAPHICS::DRAW_BOX with something that does a bunch of DRAW_LINE calls so we can wireframe the box

		// Green to start, blue to end
		// Draw the starting box first so that it draws on top (Rockstar don't seem to do any depth buffering with these DRAW_BOX calls
		drawWireframeBox(jump.endCoord1, jump.endCoord2, 48, 255, 255, 255);
		drawWireframeBox(jump.startCoord1, jump.startCoord2, 48, 255, 48, 255);
	}
}

void main()
{
	initializeJumps();

	while (true)
	{
		update();
		WAIT(0);
	}
}

void ScriptMain()
{
	main();
}
