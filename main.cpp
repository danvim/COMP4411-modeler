
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

#include "MyModel.h"
#include "sample.h"
#include "Test.h"

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{
	// return new SampleModel(x, y, w, h, label);
	return new MyModel(x, y, w, h, label);
}

std::stringstream ss;

int main()
{
	Test test(ss);
	test.testForward();
	
	OutputDebugString(ss.str().c_str());
	
	return 0;

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
	controls[ENABLEANIM] = ModelerControl("Enable Anim", 0, 1, 1, 0);
	controls[CYCLINGMOOD] = ModelerControl("Cycling Mood", 0, 1, 1, 0);
	controls[LDISP] = ModelerControl("Lsystem: display", 0, 1, 1, 0);
	controls[LDEPTH] = ModelerControl("Lsystem: depth", 1, 6, 1, 4);
	controls[LANGLE] = ModelerControl("Lsystem: angle", 0, 360, 1, 30);
	controls[LLEN] = ModelerControl("Lsystem: length", 0.01, 1, 0.01, 0.2);
	controls[LTHICKNESS] = ModelerControl("Lsystem: thickness", 0.01, 1, 0.01, 0.1);
	controls[LDECAY] = ModelerControl("Lsystem: decay", 0.01, 1, 0.01, 1);
	controls[BALLJOINTS] = ModelerControl("Ball joints", 0, 1,1, 0);
	controls[IKENABLE] = ModelerControl("IK: enable", 0, 1,1, 1);
	controls[IKX] = ModelerControl("IK: X", -10, 10,0.01, 3);
	controls[IKY] = ModelerControl("IK: Y", -10, 10,0.01, 3);
	controls[IKZ] = ModelerControl("IK: Z", -10, 10,0.01, 3);

	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}

double rad(double deg)
{
	return deg * M_PI / 180.f;
}
