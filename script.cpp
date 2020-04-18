#include "script.h"
#include "utils.h"
#include "keyboard.h"
#include "jumps.h"
#include "graphics.h"

void drawJumps()
{
	// For some reason on patch v1.27, drawing a regular box messes up all line drawing, so we draw all the wireframe boxes first, then the solid ones.

	GRAPHICS::CLEAR_DRAW_ORIGIN();

	for (StuntJump stunt : stunts)
	{
		drawBoxWireframe(stunt.jump, 48, 255, 127, 255);
		drawBoxWireframe(stunt.landing, 255, 255, 255, 255);
	}

	static int opacity = 127;
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
