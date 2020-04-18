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

	float sizeX = abs(coord1.x - coord2.x) / 2.f;
	float sizeY = abs(coord1.y - coord2.y) / 2.f;
	float sizeZ = abs(coord1.z - coord2.z) / 2.f;

	const float ROOT_2 = 1.41421356237f;

	// length by radius1 and width by radius2
	// We assume the length is longer than the width
	if (sizeX > sizeY)
	{
		sizeX += abs(radius1) / (2 * ROOT_2);
		sizeY += abs(radius2) / (2 * ROOT_2);
	} else {
		sizeX += abs(radius2) / (2 * ROOT_2);
		sizeY += abs(radius1) / (2 * ROOT_2);
	}

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

	float sizeX = abs(coord1.x - coord2.x) / 2.f;
	float sizeY = abs(coord1.y - coord2.y) / 2.f;
	float sizeZ = abs(coord1.z - coord2.z) / 2.f;

	const float ROOT_2 = 1.41421356237f;

	if (sizeX > sizeY)
	{
		sizeX += abs(radius1) / (2 * ROOT_2);
		sizeY += abs(radius2) / (2 * ROOT_2);
	}
	else {
		sizeX += abs(radius2) / (2 * ROOT_2);
		sizeY += abs(radius1) / (2 * ROOT_2);
	}


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
void ShowSubtitle(char* text)
{
	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::END_TEXT_COMMAND_PRINT(2000, 1);
}
char* stringToCharPtr(std::string string) {
	// if using C++ 2017 or later in Visual Studio and the below #if is inactive see https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=vs-2017
#if __cplusplus >= 201703L
	return string.data();
#else
	std::vector<char> tmp{ begin(string), end(string) };
	tmp.push_back('\0'); // ensure null terminated
	char* ret = tmp.data();
	return ret;
#endif
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
	{
		opacity -= 8 * (IsKeyDown(VK_SHIFT) ? -1 : 1);
		std::string message = "Opacity changed to: " + std::to_string(opacity);
		ShowSubtitle(stringToCharPtr(message));
	}


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
