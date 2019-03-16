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
	VectorXd loc = ik.computeLocation({ {38,-56},{29,85},{180,-90} }, 2);
	it("forward", Vector3d( 1.19,5.71,0.45 ), loc,0.5);
	loc = ik.computeLocation({ {0,90},{0,0} }, 2);
	it("forward", Vector3d(-2, 3, 0), loc);
}
