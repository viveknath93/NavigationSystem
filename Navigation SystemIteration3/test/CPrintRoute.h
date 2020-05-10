/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef CPRINTROUTE_H_
#define CPRINTROUTE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CPrintRoute: public CppUnit::TestFixture {
	CRoute *testroute;
public:
	void setUp() {
			testroute = new CRoute;

			}

			void tearDown() {
				delete testroute;
			}
	void testemptyprintRoute() {
		testroute->print();

	}

	void testprintRoute() {
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		testroute->connectToWpDatabase(&test_wp_db);
		testroute->connectToPoiDatabase(&test_poi_db);



		testroute->addWaypoint("Konzerthaus");
		testroute->addPoi("EinKaufzentrum","Konzerthaus");

		testroute->print();

		CPPUNIT_ASSERT_EQUAL(2,(int)testroute->getRoute().size());

		}




	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<CPrintRoute>
				 ("Trying to Print Empty route", &CPrintRoute::testemptyprintRoute));

		suite->addTest(new CppUnit::TestCaller<CPrintRoute>
				("Print Route", &CPrintRoute::testprintRoute));


		return suite;
	}
};


#endif /* CPRINTROUTE_H_ */
