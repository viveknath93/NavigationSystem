/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef COPERATORPLUS_H_
#define COPERATORPLUS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class COperatorPlus: public CppUnit::TestFixture {
	CRoute testroute;
public:
	void setUp() {


			}

			void tearDown() {
				//delete testroute;
			}

	//Negative Test case
	void testoverloadPlusDiffrentDatabases() {

		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		CRoute testroute;
		CRoute testroute_2;


		testroute.connectToWpDatabase(&test_wp_db);
		testroute.addWaypoint("Konzerthaus");

		CRoute testroute_3 = testroute + testroute_2;

		CPPUNIT_ASSERT_EQUAL(0,(int)testroute_2.getRoute().size());

	}

	void testPverloadPlusSimilarDB() {
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

		testroute_2.connectToWpDatabase(&test_wp_db);
		testroute_2.connectToPoiDatabase(&test_poi_db);

		testroute_2.addWaypoint("Konzerthaus");
		testroute.addPoi("EinKaufzentrum","Konzerthaus");

		CRoute testroute_3 = testroute + testroute_2;

		CPPUNIT_ASSERT_EQUAL(2,(int)testroute_3.getRoute().size());

		}




	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<COperatorPlus>
				 ("Add Valid Waypoint", &COperatorPlus::testoverloadPlusDiffrentDatabases));

		suite->addTest(new CppUnit::TestCaller<COperatorPlus>
				("Adding invalid WP", &COperatorPlus::testPverloadPlusSimilarDB));


		return suite;
	}
};


#endif /* COPERATORPLUS_H */
