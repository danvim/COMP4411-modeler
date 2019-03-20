#pragma once
#include <FL/gl.h>
#include <vector>
#include "MarchingCubes.h"

class MetaBall
{
public:
	struct Sphere
	{
		Eigen::Vector3d p;
		GLdouble r;
	};

	inline static const double DOMAIN_X_MIN = -5.0;
	inline static const double DOMAIN_X_MAX = 5.0;
	inline static const double DOMAIN_Y_MIN = 0.0;
	inline static const double DOMAIN_Y_MAX = 10.0;
	inline static const double DOMAIN_Z_MIN = -5.0;
	inline static const double DOMAIN_Z_MAX = 5.0;

	inline static double threshold = 1.0;
	inline static MetaBall* instancePtr = nullptr;

	static double getGridSize();
	static MetaBall* getInstancePtr();

	std::vector<MarchingCubes::Grid> grids;
	std::vector<Sphere> spheres;

	double getIsoLevel(Eigen::Vector3d pos);
	void initializeGrids();
	void drawMetaBalls();
};
