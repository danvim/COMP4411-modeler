#include "Tester.h"
#include <string>
#include "Test.h"
#include "IkSolver.h"

Test::Test(std::stringstream& ss):Tester(ss)
{
}


Test::~Test()
{
}

void Test::testForward()
{
	IkSolver ik;
	std::vector<double> v1{ 38,-56,29,85,180,-90 };
	VectorXd loc = ik.computePosition(v1);
	it("forward", Vector3d( 1.19,5.71,0.45 ), loc,0.5);
	std::vector<double> v2{ 0,90,0,0 };
	loc = ik.computePosition(v2);
	it("forward", Vector3d(-2, 3, 0), loc);
}

void Test::testBackward()
{
	IkSolver ik;
	std::vector<double> v1_sln{ 38,-56,29,85,180,-90 };
	std::vector<double> v1_inp{ 0,0,0,0,0,0 };
	Vector3d target1(1.19, 5.71, 0.45);

	ik.solve(v1_inp, target1);
	VectorXd end1 = ik.computePosition(v1_inp);
	it("backward", target1, end1);

	std::vector<double> v2_sln{ 0,90,0,0 };
	std::vector<double> v2_inp{ 0,0,0,0 };
	Vector3d target2(-2, 3, 0);
	ik.solve(v2_inp, target2);
	VectorXd end2 = ik.computePosition(v2_inp);
	it("backwatd", target2, end2);
}