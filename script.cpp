#include "script.h"
#include "utils.h"
#include "keyboard.h"
#include "jumps.h"
#include "graphics.h"

bool isInRotatableCuboid(Vector3 p, RotatableCuboid region)
{
	// We can check the Z axis trivially.
	if (p.z < min(region.start.z, region.end.z) || p.z > max(region.start.z, region.end.z))
		return false;

	// https://math.stackexchange.com/a/2193733
	
	// line = A + t * B with A = region.start and B = delta
	// f(t) = (1 - t)A + tB - P

	auto vX = region.end.x - region.start.x;
	auto vY = region.end.y - region.start.y;

	auto uX = region.start.x - p.x;
	auto uY = region.start.y - p.y;

	auto vdotu = vX * uX + vY * uY;
	auto vdotv = vX * vX + vY * vY;

	auto t = -vdotu / vdotv;
	if (t < 0 || t > 1)
		return false;

	auto interpX = region.start.x + vX * t;
	auto interpY = region.start.y + vY * t;

	return (interpX - p.x) * (interpX - p.x) + (interpY - p.y) * (interpY - p.y) < (region.width * region.width) / 4.f;
}

void drawJumps()
{
	// For some reason on patch v1.27, drawing a regular box messes up all line drawing, so we draw all the wireframe boxes first, then the solid ones.

	GRAPHICS::CLEAR_DRAW_ORIGIN();

	auto playerPed = PLAYER::PLAYER_PED_ID();
	auto vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	auto vehicleCoords = vehicle ? ENTITY::GET_ENTITY_COORDS(vehicle, true) : v3(0, 0, 0);
	
	for (StuntJump stunt : stunts)
	{
		drawBoxWireframe(stunt.jump, 48, 127, 127, 255);
		
		if (vehicle && isInRotatableCuboid(vehicleCoords, stunt.landing))
		{
			drawBoxWireframe(stunt.landing, 96, 255, 96, 255);
		}
		else
		{
			drawBoxWireframe(stunt.landing, 255, 96, 255, 255);
		}
	}

	static int opacity = 48;
	if (IsKeyJustUp(VK_F3))
		opacity -= 8 * (IsKeyDown(VK_SHIFT) ? -1 : 1);
	opacity = min(max(opacity, 0), 255);

	for (StuntJump stunt : stunts)
	{
		drawBox(stunt.landing, 255, 255, 255, opacity);
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
