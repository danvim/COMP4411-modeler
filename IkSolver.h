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

	void solve();
	double loss(Vector3d computed, Vector3d target) { return Vector3d(computed - target).norm(); }
	Vector3d computeLocation(vector<pair<double, double>> angles, double armLen = 2);
	Vector3d rotateVector(Vector3d& vec, double degree, char axis);

	double baseHeight;
};

