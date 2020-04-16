#include "script.h"
#include "utils.h"
#include "jumps.h"

void update()
{
	for (StuntJump jump : jumps)
	{
		// TODO: Replace GRAPHICS::DRAW_BOX with something that does a bunch of DRAW_LINE calls so we can wireframe the box

		// Green to start, blue to end
		// Draw the starting box first so that it draws on top (Rockstar don't seem to do any depth buffering with these DRAW_BOX calls
		GRAPHICS::DRAW_BOX(jump.endCoord1.x, jump.endCoord1.y, jump.endCoord1.z, jump.endCoord2.x, jump.endCoord2.y, jump.endCoord2.z, 48, 255, 255, 127);
		GRAPHICS::DRAW_BOX(jump.startCoord1.x, jump.startCoord1.y, jump.startCoord1.z, jump.startCoord2.x, jump.startCoord2.y, jump.startCoord2.z, 48, 255, 48, 127);
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
