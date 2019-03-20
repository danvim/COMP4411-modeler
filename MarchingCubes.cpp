#include "MarchingCubes.h"
#include <FL/gl.h>

void MarchingCubes::polygonizeDraw(const Grid& grid, const double threshold)
{
	static const auto EPSILON = 1.0e-4;

	std::array<Eigen::Vector3d, 12> verticesOnEdges;

	unsigned int cubeIndex = 0;
	if (grid.isoLevels[0] < threshold) cubeIndex |= 1u;
	if (grid.isoLevels[1] < threshold) cubeIndex |= 2u;
	if (grid.isoLevels[2] < threshold) cubeIndex |= 4u;
	if (grid.isoLevels[3] < threshold) cubeIndex |= 8u;
	if (grid.isoLevels[4] < threshold) cubeIndex |= 16u;
	if (grid.isoLevels[5] < threshold) cubeIndex |= 32u;
	if (grid.isoLevels[6] < threshold) cubeIndex |= 64u;
	if (grid.isoLevels[7] < threshold) cubeIndex |= 128u;

	if (EDGE_TABLE[cubeIndex] == 0) return;
	if (EDGE_TABLE[cubeIndex] & 1u) verticesOnEdges[0] = interpolate(threshold, grid, 0, 1);
	if (EDGE_TABLE[cubeIndex] & 2u) verticesOnEdges[1] = interpolate(threshold, grid, 1, 2);
	if (EDGE_TABLE[cubeIndex] & 4u) verticesOnEdges[2] = interpolate(threshold, grid, 2, 3);
	if (EDGE_TABLE[cubeIndex] & 8u) verticesOnEdges[3] = interpolate(threshold, grid, 3, 0);
	if (EDGE_TABLE[cubeIndex] & 16u) verticesOnEdges[4] = interpolate(threshold, grid, 4, 5);
	if (EDGE_TABLE[cubeIndex] & 32u) verticesOnEdges[5] = interpolate(threshold, grid, 5, 6);
	if (EDGE_TABLE[cubeIndex] & 64u) verticesOnEdges[6] = interpolate(threshold, grid, 6, 7);
	if (EDGE_TABLE[cubeIndex] & 128u) verticesOnEdges[7] = interpolate(threshold, grid, 7, 4);
	if (EDGE_TABLE[cubeIndex] & 256u) verticesOnEdges[8] = interpolate(threshold, grid, 0, 4);
	if (EDGE_TABLE[cubeIndex] & 512u) verticesOnEdges[9] = interpolate(threshold, grid, 1, 5);
	if (EDGE_TABLE[cubeIndex] & 1024u) verticesOnEdges[10] = interpolate(threshold, grid, 2, 6);
	if (EDGE_TABLE[cubeIndex] & 2048u) verticesOnEdges[11] = interpolate(threshold, grid, 3, 7);

	for (auto i = 0; TRI_TABLE[cubeIndex][i] != -1; i+= 3)
	{
		
		const auto a = verticesOnEdges[TRI_TABLE[cubeIndex][i]];
		const auto b = verticesOnEdges[TRI_TABLE[cubeIndex][i + 1]];
		const auto c = verticesOnEdges[TRI_TABLE[cubeIndex][i + 2]];

		auto normal = (a - b).cross(c - b);
		if (normal.norm() > EPSILON) {
			normal.normalize();
			glBegin(GL_TRIANGLES);
			glNormal3d(normal.x(), normal.y(), normal.z());
			glVertex3d(a.x(), a.y(), a.z());
			glVertex3d(b.x(), b.y(), b.z());
			glVertex3d(c.x(), c.y(), c.z());
			glEnd();
		}
	}
}

Eigen::Vector3d MarchingCubes::interpolate(const double threshold, const Grid& grid, const int i, const int j)
{
	static const auto EPSILON = 1.0e-5;
	auto& i1 = grid.isoLevels[i];
	auto& i2 = grid.isoLevels[j];
	auto& p1 = grid.cornerPositions[i];
	auto& p2 = grid.cornerPositions[j];


	if (abs(threshold - i1) < EPSILON) return p1;
	if (abs(threshold - i2) < EPSILON) return p2;
	if (abs(i1 - i2) < EPSILON) return p1;

	return p1 + (threshold - i1) / (i2 - i1) * (p2 - p1);
}