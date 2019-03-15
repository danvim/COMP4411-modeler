#include "MyModel.h"
#include "modelerapp.h"


bool MyModel::isAnimating() {
	//return true;
	return ModelerApplication::Instance()->GetAnimating(); 
}

void MyModel::drawLsystem(int systype, int branchtype, int depth, float length, int angle,double thickness,double decay)
{
	if(depth == 0)
	{
		return;
	}
	switch(systype)
	{
	default:
		glPushMatrix();


		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		drawCylinder(length, thickness, thickness*decay);
		glPopMatrix();

		glRotated(angle, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, length, 0);
		glRotated(-angle, 0, 0, 1);
		drawLsystem(systype, 0, depth - 1, length*decay, angle,thickness*decay,decay);
		glPopMatrix();

		glRotated(angle, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, length, 0);
		glRotated(angle, 0, 0, 1);
		drawLsystem(systype, 0, depth - 1, length*decay, angle,thickness*decay,decay);
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

	// draw the model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);

	// drawTest();

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	//base
	if(VAL(LDISP))
	{
		drawLsystem(VAL(LDISP), 0, VAL(LDEPTH), VAL(LLEN), VAL(LANGLE),VAL(LTHICKNESS),VAL(LDECAY));
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
		glRotated(VAL(ARM1V + curDept*2)+moodTick, 0, 1, 0);

		//vertical arm cylinder
		glPushMatrix();
			glRotated(-90, 1, 0, 0);
			drawCylinder(2, 1, 1);
		glPopMatrix();

		//joint cylinder
		glTranslated(0, 2, 0);
		glRotated(VAL(ARM1H + curDept * 2)+moodTick, 0, 0, 1);

		glPushMatrix();
		glTranslated(0, 0, -0.5);
		drawCylinder(1, 1, 1);
		glPopMatrix();

		//recursively draw the rest of arm
		if(VAL(LEVELDETAILS)>1+ curDept)
		{
			drawArm(levels - 1, curDept + 1);
		}

	glPopMatrix();
}

double rad(double deg)
{
	return deg * M_PI / 180.f;
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
