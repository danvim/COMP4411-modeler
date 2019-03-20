#include "GLUtils.h"

void GLUtils::ravelTrigPush(std::vector<double>& a, Eigen::Vector3d v)
{
	a.push_back(v[0]);
	a.push_back(v[1]);
	a.push_back(v[2]);
}

void GLUtils::trigPush(std::vector<double>& vertices, std::vector<double>& normals, const Triangle& triangle)
{
	static const auto EPSILON = 1.0e-4;

	const auto a = triangle[0];
	const auto b = triangle[1];
	const auto c = triangle[2];

	auto normal = (a - b).cross(c - b);
	if (normal.norm() > EPSILON) {
		normal.normalize();
		ravelTrigPush(vertices, c);
		ravelTrigPush(vertices, a);
		ravelTrigPush(vertices, b);
		ravelTrigPush(normals, normal);
		ravelTrigPush(normals, normal);
		ravelTrigPush(normals, normal);
	}
}
