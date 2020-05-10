/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef CCONNECTTODATABASES_H_
#define CCONNECTTODATABASES_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CconnectToDatabases: public CppUnit::TestFixture {
	CRoute* testroute;
public:

	void setUp() {
		testroute = new CRoute;
		}

		void tearDown() {
			delete testroute;
		}
	//Negative Test case
	void test_withoutConnectingPOIDB() {

		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
		//CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		//void connectToPoiDatabase(CPoiDatabase* pPoiDB);
		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);


		testroute->addPoi("EinKaufzentrum","DummyWP");
		CPPUNIT_ASSERT_EQUAL(0,(int)testroute->getRoute().size());

	}

	//Negative Test case
	void test_withoutConnectingWPDB() {

		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		//void connectToPoiDatabase(CPoiDatabase* pPoiDB);
		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		CWpDatabase test_wp_db;
		test_wp_db.addWaypoint(Location_1);

		testroute->addWaypoint("Konzerthaus");
		CPPUNIT_ASSERT_EQUAL(0,(int)testroute->getRoute().size());

	}

	// Positive test case
	void test_ConnectingPOIDB() {
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
		//CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);
		testroute->connectToPoiDatabase(&test_poi_db);

		testroute->addPoi("EinKaufzentrum","DummyWP");
		CPPUNIT_ASSERT_EQUAL(1,(int)testroute->getRoute().size());
		}

	// positive Test case
	void test_ConnectingWPDB() {

			CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
			CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

			//void connectToPoiDatabase(CPoiDatabase* pPoiDB);
			CPoiDatabase test_poi_db;
			test_poi_db.addPoi(poi_1);

			CWpDatabase test_wp_db;
			test_wp_db.addWaypoint(Location_1);

			testroute->connectToWpDatabase(&test_wp_db);

			testroute->addWaypoint("Konzerthaus");
			CPPUNIT_ASSERT_EQUAL(1,(int)testroute->getRoute().size());

		}


	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<CconnectToDatabases>
				 ("Without POI DB", &CconnectToDatabases::test_withoutConnectingPOIDB));

		suite->addTest(new CppUnit::TestCaller<CconnectToDatabases>
				("With POI DB", &CconnectToDatabases::test_ConnectingPOIDB));

		suite->addTest(new CppUnit::TestCaller<CconnectToDatabases>
						 ("Without WP DB", &CconnectToDatabases::test_withoutConnectingWPDB));

		suite->addTest(new CppUnit::TestCaller<CconnectToDatabases>
				("With WP DB", &CconnectToDatabases::test_ConnectingWPDB));
		return suite;
	}
};


#endif /* CLOADTESTS_H_ */
