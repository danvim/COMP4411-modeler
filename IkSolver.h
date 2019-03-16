#pragma once
#include <Eigen/Core>
#include <vector>

using std::vector;
using std::pair;
using namespace Eigen;

class IkSolver
{
public:
	explicit IkSolver();
	~IkSolver();

	void solve(vector<double>& angles, Vector3d target, int maxIter = 2000, double lr = 15, double delta = 0.1, double esp = 1e-6);
	double findDist(Vector3d computed, Vector3d target) { return Vector3d(computed - target).norm(); }
	Vector3d computePosition(vector<double>& angles);
	Vector3d rotateVector(Vector3d& vec, double degree, char axis);
	Matrix4d rotateMatrix(double degree, char axis);
	Matrix4d translateMatrix(double x, double y, double z);

	double baseHeight = 1;
	double armLen = 2;
	double minangle = -180;
	double maxangle = 180;
};

