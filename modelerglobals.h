#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.

// v is rotation angle using the axis along the arm
// h is rotation angle of joint
enum SampleModelControls
{ 
	XPOS, YPOS, ZPOS, HEIGHT, ROTATE,
	ARM1V, ARM1H, ARM2V, ARM2H, ARM3V, ARM3H, CLAMPWIDTH,
	LIGHTX, LIGHTY, LIGHTZ, LEVELDETAILS, 
	ENABLEANIM, CYCLINGMOOD,
	LDISP, LDEPTH, LANGLE, LLEN, NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif