#pragma once
#include <vector>
#include <array>
#include <Eigen/Dense>

class GLUtils
{
public:
	typedef std::array<Eigen::Vector3d, 3> Triangle;

	static void ravelTrigPush(std::vector<double>& a, Eigen::Vector3d v);
	
	/**
	 * @param vertices vertices used for GLDrawArray
	 * @param normals normals used for GLDrawArray
	 * @param triangle vertices of the triangle in anti-clockwise order, to be inputted into the corresponding vectors
	 */
	static void trigPush(std::vector<double>& vertices, std::vector<double>& normals, const Triangle& triangle);
};
