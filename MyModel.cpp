#include "MyModel.h"
#include "modelerapp.h"
#include <vector>
#include "IkSolver.h"

extern double rad(double deg);

bool MyModel::isAnimating() {
	//return true;
	return ModelerApplication::Instance()->GetAnimating(); 
}

void MyModel::drawLsystem(int systype, int branchtype, int depth, float length, int angle,double thickness,double decayThickness, double decayLength)
{
	if(depth == 0)
	{
		return;
	}
	switch(systype)
	{
	case 2:
		glPushMatrix();


		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		drawCylinder(length, thickness, thickness*decayThickness);
		glPopMatrix();

		glRotated(angle, 0, 1, 0);

		if(branchtype == 1)
		{
			glPushMatrix();
			glTranslated(0, length, 0);
			glRotated(-angle, 0, 0, 1);
			drawLsystem(systype, 0, depth - 1, length*decayLength, angle, thickness*decayThickness, decayThickness, decayLength);
			glPopMatrix();
		}

		glRotated(angle, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, length, 0);
		glRotated(angle, 0, 0, 1);
		drawLsystem(systype, 1, depth - 1, length*decayThickness, angle, thickness*decayThickness, decayThickness, decayLength);
		glPopMatrix();

		glPopMatrix();
		break;

	default:
		glPushMatrix();


		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		drawCylinder(length, thickness, thickness*decayThickness);
		glPopMatrix();

		glRotated(angle, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, length, 0);
		glRotated(-angle, 0, 0, 1);
		drawLsystem(systype, 0, depth - 1, length*decayLength, angle,thickness*decayThickness,decayThickness,decayLength);
		glPopMatrix();

		glRotated(angle, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, length, 0);
		glRotated(angle, 0, 0, 1);
		drawLsystem(systype, 0, depth - 1, length*decayThickness, angle,thickness*decayThickness,decayThickness,decayLength);
		glPopMatrix();

		glPopMatrix();
	}
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out MyModel
void MyModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	bool flag = isAnimating();

	if(isAnimating())
	{
		if(VAL(CYCLINGMOOD))
		{
			if(moodUp)
			{
				moodTick++;
			}else
			{
				moodTick--;
			}
			if(moodTick==maxMoodTick-1 || moodTick==-maxMoodTick)
			{
				moodUp = !moodUp;
			}
		}
		animTick = (animTick + 1) % maxAnimTick;
	}

	glEnable(GL_LIGHTING);
	GLfloat lightPosition0[4];
	lightPosition0[0] = VAL(LIGHTX);
	lightPosition0[1] = VAL(LIGHTY);
	lightPosition0[2] = VAL(LIGHTZ);
	lightPosition0[3] = 1;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	glPushMatrix();
	setDiffuseColor(0.5f, 0.9f, 0.9f);
	glTranslated(-4, 0.001, -4);
	drawLathe({ {0.0, 1.0}, {1.0, 2.0}, {1.2, 2}, {0.1, 0.9}, {0.1, 0.1}, {1.0, 0.0}, {0.0, 0.0} });
	glPopMatrix();

	// draw ik target point
	if(VAL(IKENABLE))
	{
		setDiffuseColor(COLOR_RED);
		glPushMatrix();
		glTranslated(VAL(IKX), VAL(IKY), VAL(IKZ));
		drawSphere(0.5);
		glPopMatrix();

		std::vector<double> angles{ 0,0,0,0,0,0 };
		IkSolver ik;
		ik.baseHeight = VAL(HEIGHT);
		ik.minangle = VAL(IKMIN);
		ik.maxangle= VAL(IKMAX);
		Vector3d target(VAL(IKX), VAL(IKY), -VAL(IKZ));
		ik.solve(angles, target);
		for(int i=0;i<angles.size();i++)
		{
			SET(ARM1V + i, angles[i]);
		}
	}

	// draw the model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);

	// drawTest();

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS) + 0.001f, VAL(ZPOS));

	//base
	if(VAL(LDISP))
	{
		drawLsystem(VAL(LDISP), 0, VAL(LDEPTH), VAL(LLEN), VAL(LANGLE),VAL(LTHICKNESS),VAL(LDECAYTHICKNESS),VAL(LDECAYLENGTH));
		return;
	}
	if(VAL(LEVELDETAILS)>0)
	{
		glPushMatrix();
		// glTranslated(-1, 0, -1);
		glScaled(1, VAL(HEIGHT), 1);
		glRotated(-90, 1, 0, 0);
		drawTextureCylinder(1, 2, 2);
		glPopMatrix();

		//arm
		if(VAL(LEVELDETAILS)>1)
		{
			glPushMatrix();
			glTranslated(0, VAL(HEIGHT), 0);
			drawArm(3);
			glPopMatrix();
		}
	}
	

	glPopMatrix();
}

void MyModel::drawArm(int levels, int curDept)
{
	double mood = VAL(CYCLINGMOOD);
	if(levels == 0)
	{
		if(VAL(LEVELDETAILS) > 1 + curDept)
		{
			drawClamp();
		}
		return;
	}

	glPushMatrix();
		// set vertical axis rotation
		glRotated(VAL(ARM1V + curDept*2)+(mood==1)*moodTick, 0, 1, 0);

		if (mood == 2)
			glTranslated(levels*sin(32 * rad(levels*moodTick)) / 1000.f, 0, levels*cos(32 * rad(levels*moodTick)) / 1000.f);
		//vertical arm cylinder
		glPushMatrix();
	if(VAL(BOXARMS)==0)
	{
		glRotated(-90, 1, 0, 0);
		drawCylinder(2, 1, 1);
	}else
	{
		glTranslated(-1, 0, -0.5);
		drawBox(2, 2, 1);
	}
		glPopMatrix();

		//joint cylinder
		glTranslated(0, 2, 0);
		glRotated(VAL(ARM1H + curDept * 2)+(mood==1)*moodTick, 0, 0, 1);

		glPushMatrix();
		if(VAL(BALLJOINTS))
		{
			drawSphere(1);
		}else
		{
			glTranslated(0, 0, -0.5);
			drawCylinder(1, 1, 1);
		}
		glPopMatrix();

		//recursively draw the rest of arm
		if(VAL(LEVELDETAILS)>1+ curDept)
		{
			drawArm(levels - 1, curDept + 1);
		}

	glPopMatrix();
}

void MyModel::drawClamp()
{
	// const double palmThickness = 0.2;
	const double fingerThickness = 0.2;
	const double fingerLength = 0.5;

	if(isAnimating())
	{
		ModelerApplication::Instance()->SetControlValue(CLAMPWIDTH, sin(16*rad(animTick)) / 2.f + 0.5);
	}

	glPushMatrix();
		glTranslated(0, 0, 0);
		glPushMatrix();
			glTranslated(-1, 0, -0.5);
			drawBox(2, 1, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, 1, 0);
			glPushMatrix();
				glTranslated(-VAL(CLAMPWIDTH)-fingerThickness/2, 0, -0.5);
				drawBox(fingerThickness, fingerLength, 1);
			glPopMatrix();
			glPushMatrix();
				glTranslated(VAL(CLAMPWIDTH) , 0, -0.5);
				drawBox(fingerThickness, fingerLength, 1);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void MyModel::drawTest()
{
	glPushMatrix();
	glTranslated(3, 3, 3);
	drawTriangularColumn(1, 1, 1, 1);
	glPopMatrix();
}
