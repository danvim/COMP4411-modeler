#include "MetaBall.h"
#include <numeric>
#include <execution>
#include "MyModel.h"
#include <Eigen/src/Core/util/ForwardDeclarations.h>
#include "GLUtils.h"

double MetaBall::getIsoLevel(Vector3d pos)
{
	return std::transform_reduce(
		std::execution::par_unseq, 
		spheres.begin(), 
		spheres.end(), 
		0.0, 
		[](const double a, const double b) {return a + b;},
		[&](const Sphere& sphere)
	    {
			return pow(sphere.r, 3) / (pow(pos.x() - sphere.p.x(), 2) + pow(pos.y() - sphere.p.y(), 2) + pow(pos.z() - sphere.p.z(), 2));
		}
	);
}

void MetaBall::initializeGrids()
{
	const auto gs = getGridSize();
	const auto xSteps = unsigned int((DOMAIN_X_MAX - DOMAIN_X_MIN) / gs);
	const auto ySteps = unsigned int((DOMAIN_Y_MAX - DOMAIN_Y_MIN) / gs);
	const auto zSteps = unsigned int((DOMAIN_Z_MAX - DOMAIN_Z_MIN) / gs);

	if (grids.size() == xSteps * ySteps * zSteps) return;
	grids.clear();

	for (auto zi = 0u; zi < zSteps; zi++)
	{
		auto z = DOMAIN_Z_MIN + zi * gs;
		for (auto yi = 0u; yi < ySteps; yi++)
		{
			auto y = DOMAIN_Y_MIN + yi * gs;
			for (auto xi = 0u; xi < xSteps; xi++)
			{
				auto x = DOMAIN_X_MIN + xi * gs;
				grids.push_back(MarchingCubes::Grid{
					{
						Vector3d(x, y, z + gs),
						Vector3d(x + gs, y, z + gs),
						Vector3d(x + gs, y, z),
						Vector3d(x, y, z),
						Vector3d(x, y + gs, z + gs),
						Vector3d(x + gs, y + gs, z + gs),
						Vector3d(x + gs, y + gs, z),
						Vector3d(x, y + gs, z)
					},
					{}
				});
			}
		}
	}
}

void MetaBall::drawMetaBalls()
{
	initializeGrids();
	std::for_each(
		std::execution::seq,
		grids.begin(),
		grids.end(),
		[&](MarchingCubes::Grid& grid)
	{
		for (auto i = 0u; i < 8; i++)
		{
			grid.isoLevels[i] = getIsoLevel(grid.cornerPositions[i]);
		}
		
		MarchingCubes::polygonizeDraw(grid, threshold);
	}
	);
}

double MetaBall::getGridSize()
{
	double gridSize;
	switch (ModelerDrawState::Instance()->m_quality)
	{
	case HIGH:
		gridSize = 0.5;
		break;
	case MEDIUM:
	default:
		gridSize = 1;
		break;
	case LOW:
		gridSize = 2;
		break;
	case POOR: 
		gridSize = 3;
		break;
	}

	return gridSize;
}

MetaBall* MetaBall::getInstancePtr()
{
	if (instancePtr == nullptr)
	{
		instancePtr = new MetaBall();
		instancePtr->initializeGrids();
	}

	return instancePtr;
}
