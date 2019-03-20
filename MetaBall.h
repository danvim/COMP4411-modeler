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

	double domainXMin = -5.0;
	double domainXMax = 5.0;
	double domainYMin = 0.0;
	double domainYMax = 10.0;
	double domainZMin = -5.0;
	double domainZMax = 5.0;

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
