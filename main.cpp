
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

#include "MyModel.h"
#include "sample.h"

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{
	// return new SampleModel(x, y, w, h, label);
	return new MyModel(x, y, w, h, label);
}

int main()
{
	initTextures();

	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[ARM1V] = ModelerControl("Arm1 Vertical Axis Rotation", -180, 180, 1, 0);
	controls[ARM1H] = ModelerControl("Arm1 Horizontal Axis Rotation", -90, 90, 1, 0);
	controls[ARM2V] = ModelerControl("Arm2 Vertical Axis Rotation", -180, 180, 1, 0);
	controls[ARM2H] = ModelerControl("Arm2 Horizontal Axis Rotation", -90, 90, 1, 0);
	controls[ARM3V] = ModelerControl("Arm3 Vertical Axis Rotation", -180, 180, 1, 0);
	controls[ARM3H] = ModelerControl("Arm3 Horizontal Axis Rotation", -90, 90, 1, 0);
	controls[CLAMPWIDTH] = ModelerControl("Clamp Width", 0, 1, 0.01, 0);
	controls[LIGHTX] = ModelerControl("Light X", -30, 30, 0.1, -20);
	controls[LIGHTY] = ModelerControl("Light Y", -30, 30, 0.1, 12);
	controls[LIGHTZ] = ModelerControl("Light Z", -30, 30, 0.1, 20);
	controls[LEVELDETAILS] = ModelerControl("Level of Details", 0, 10, 1, 10);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
