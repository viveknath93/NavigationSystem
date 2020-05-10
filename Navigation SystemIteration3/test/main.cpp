#include <iostream>

using namespace std;


#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CAddpoi.h"
#include "CAddwaypoint.h"
#include "CconnectToDatabases.h"
#include "CPrintRoute.h"
#include "COperatorPlus.h"
#include "COperatorEqualPlusEqual.h"

using namespace CppUnit;
//using namespace APTTest;
int main(int argc, char **argv)
{
	cout << "starting test cases:\n" << endl;

	TextUi::TestRunner runner;

	runner.addTest( CAddpoi::suite());
	runner.addTest( CAddwaypoint::suite());
	runner.addTest( CconnectToDatabases::suite());
	runner.addTest( CPrintRoute::suite());
	runner.addTest( COperatorPlus::suite());
	runner.addTest( COperatorEqualPlusEqual::suite());

	//runner.addTest( CSelectionTests::suite());
	runner.run();
	return 0;
}
