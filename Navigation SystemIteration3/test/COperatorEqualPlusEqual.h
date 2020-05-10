/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef COPERATOREQUALPLUSEQUAL_H_
#define COPERATOREQUALPLUSEQUAL_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class COperatorEqualPlusEqual: public CppUnit::TestFixture {
	CRoute testroute;
public:
	void setUp() {


			}

			void tearDown() {
				//delete testroute;
			}

	// Test case
	void testequalssong() {

		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		CRoute testroute;
		CRoute testroute_2;

		testroute.connectToWpDatabase(&test_wp_db);
		testroute.connectToPoiDatabase(&test_poi_db);

		testroute.addWaypoint("Konzerthaus");
		testroute.addPoi("EinKaufzentrum","Konzerthaus");

		testroute_2 = testroute ;

		CPPUNIT_ASSERT_EQUAL(2,(int)testroute_2.getRoute().size());

	}

	void test_copyconstructor() {

		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		CRoute testroute;


		testroute.connectToWpDatabase(&test_wp_db);
		testroute.connectToPoiDatabase(&test_poi_db);

		testroute.addWaypoint("Konzerthaus");
		testroute.addPoi("EinKaufzentrum","Konzerthaus");

		CRoute testroute_2( testroute );

		CPPUNIT_ASSERT_EQUAL(2,(int)testroute_2.getRoute().size());

	}

	void test_plusequalToOperator()
	{
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		CRoute testroute;

		testroute.connectToWpDatabase(&test_wp_db);
		testroute.connectToPoiDatabase(&test_poi_db);

		testroute.addWaypoint("Konzerthaus");
		testroute.addPoi("EinKaufzentrum","Konzerthaus");

		testroute+=("EinKaufzentrum");

		CPPUNIT_ASSERT_EQUAL(3,(int)testroute.getRoute().size());
	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<COperatorEqualPlusEqual>
				 ("Add Valid Waypoint", &COperatorEqualPlusEqual::testequalssong));
		suite->addTest(new CppUnit::TestCaller<COperatorEqualPlusEqual>
				("Add Valid Waypoint", &COperatorEqualPlusEqual::test_copyconstructor));
		suite->addTest(new CppUnit::TestCaller<COperatorEqualPlusEqual>
				("Add Valid Waypoint", &COperatorEqualPlusEqual::test_plusequalToOperator));

		return suite;
	}
};


#endif /* COPERATOREQUAL_H */
