#include "IkSolver.h"

extern double rad(double deg);

IkSolver::IkSolver()
{
	baseHeight = 1;
}


Vector3d IkSolver::computeLocation(vector<pair<double, double>> angles, double armLen)
{
	Vector3d pos(0, 0, 0);
	for(int i = angles.size() - 1; i>=0;i--)
	{
		double v = -angles[i].first;
		double h = -angles[i].second;
		pos = rotateVector(pos, h, 'Y');
		pos += Vector3d(0, armLen, 0);
		pos = rotateVector(pos, v, 'Z');
	}
	return pos + Vector3d(0, baseHeight, 0);
}

Vector3d IkSolver::rotateVector(Vector3d& vec, double degree, char axis)
{
	double c = cos(rad(degree)), s = sin(rad(degree));
	Matrix3d M;
	switch(axis)
	{
	case 0:
	case 'x':
	case 'X':
		M << 1,0,0,
			0,c,-s,
			0,s,c;
		break;
	case 1:
	case 'y':
	case 'Y':
		M << c, 0, -s,
			0, 1, 0,
			s, 0, c;
		break;
	case 2:
	case 'z':
	case 'Z':
		M << c, -s, 0,
			s, c, 0,
			0, 0, 1;
		break;
	}
	return M*vec;
}

IkSolver::~IkSolver()
{
}
