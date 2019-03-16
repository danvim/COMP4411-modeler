#include "IkSolver.h"

extern double rad(double deg);
extern std::stringstream ss;

IkSolver::IkSolver()
{
}


Vector3d IkSolver::computePosition(vector<double>& angles)
{
	Vector4d pos(0, baseHeight, 0,1);
	Matrix4d M = Matrix4d::Identity();
	for(int i = 0; i<angles.size();i+=2)
	{
		double v = angles[i];
		double h = angles[i+1];
		M = M * rotateMatrix(v,1);
		pos = pos + M*Vector4d(0, armLen, 0, 1);
		M = M * rotateMatrix(h, 2);
	}
	return Vector3d(pos[0],pos[1],pos[2]);
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

Matrix4d IkSolver::rotateMatrix(double degree, char axis)
{
	double c = cos(rad(degree)), s = sin(rad(degree));
	Matrix4d M;
	switch (axis)
	{
	case 0:
	case 'x':
	case 'X':
		M << 1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1;
		break;
	case 1:
	case 'y':
	case 'Y':
		M << c, 0, -s, 0,
			0, 1, 0, 0,
			s, 0, c, 0,
			0, 0, 0, 1;
		break;
	case 2:
	case 'z':
	case 'Z':
		M << c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
		break;
	}
	return M;
}

Matrix4d IkSolver::translateMatrix(double x, double y, double z)
{
	Matrix4d M;
	M << 1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1;
	return M;
}

IkSolver::~IkSolver()
{
}

void IkSolver::solve(vector<double>& angles, Vector3d target, int maxIter,double lr, double delta,double esp)
{
	Vector3d prevPos = computePosition(angles);
	for(int i=0; i<maxIter; i++)
	{
		vector<double> grad(angles.size());
		for(int j=0; j<angles.size(); j++)
		{
			// double cache = angles[i];
			angles[j] += delta;
			double upper = findDist(computePosition(angles), target);
			angles[j] -= 2 * delta;
			double lower = findDist(computePosition(angles), target);
			angles[j] += delta;
			grad[j] = (upper - lower) / (2 * delta);
		}
		for(int j=0; j<angles.size(); j++)
		{
			double newangle = angles[j] - lr * grad[j];
			if(newangle >= minangle && newangle <= maxangle)
			{
				angles[j] = newangle;
			}
		}

		Vector3d currPos = computePosition(angles);
		if(findDist(prevPos,currPos)<esp)
		{
			break;
		}
		if (findDist(target, currPos) < esp)
		{
			break;
		}
		prevPos = currPos;
		if(i==maxIter -1)
		{
			break;
		}
	}
}
