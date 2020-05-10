/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef CADDWAYPOINT_H_
#define CADDWAYPOINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CAddwaypoint: public CppUnit::TestFixture {
	CRoute *testroute;
public:
	void setUp() {
			testroute = new CRoute;

			}

			void tearDown() {
				delete testroute;
			}
	void testaddPoi_validWP() {
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		testroute->connectToWpDatabase(&test_wp_db);

		testroute->addWaypoint("Konzerthaus");

		CPPUNIT_ASSERT_EQUAL(1,(int)testroute->getRoute().size());

	}

	void testaddPoi_invalidWP() {
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		testroute->connectToWpDatabase(&test_wp_db);

		testroute->addWaypoint("DummyWP");

		CPPUNIT_ASSERT_EQUAL(0,(int)testroute->getRoute().size());

		}




	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<CAddwaypoint>
				 ("Add Valid Waypoint", &CAddwaypoint::testaddPoi_validWP));

		suite->addTest(new CppUnit::TestCaller<CAddwaypoint>
				("Adding invalid WP", &CAddwaypoint::testaddPoi_invalidWP));


		return suite;
	}
};


#endif /* CLOADTESTS_H_ */
