/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef CADDPOI_H_
#define CADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"




/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CAddpoi: public CppUnit::TestFixture {
	CRoute *testroute;
public:
	void setUp() {
			testroute = new CRoute;

			}

			void tearDown() {
				delete testroute;
			}
	void testaddPoi_validpoi() {
		CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
		CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

		CPoiDatabase test_poi_db;
		test_poi_db.addPoi(poi_1);

		testroute->connectToPoiDatabase(&test_poi_db);
		testroute->addPoi("EinKaufzentrum","Konzerthaus");
		CPPUNIT_ASSERT_EQUAL(1,(int)testroute->getRoute().size());

	}

	void testaddPoi_invalidpoi() {
			CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
			CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

			CPoiDatabase test_poi_db;
			test_poi_db.addPoi(poi_1);

			testroute->connectToPoiDatabase(&test_poi_db);
			testroute->addPoi("DummyPOI","Konzerthaus");
			CPPUNIT_ASSERT_EQUAL(0,(int)testroute->getRoute().size());

		}

	void testaddPoi_validpoiEmptyWP() {
			CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
			CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

			CPoiDatabase test_poi_db;
			test_poi_db.addPoi(poi_1);

			testroute->connectToPoiDatabase(&test_poi_db);
			testroute->addPoi("EinKaufzentrum","");
			CPPUNIT_ASSERT_EQUAL(1,(int)testroute->getRoute().size());

			}

	void testaddPoi_validpoiValidWP() {
			CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
			CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);

			CPoiDatabase test_poi_db;
			test_poi_db.addPoi(poi_1);

			CWpDatabase test_wp_db;
			test_wp_db.addWaypoint(Location_1);

			testroute->connectToPoiDatabase(&test_poi_db);
			testroute->connectToWpDatabase(&test_wp_db);

			testroute->addWaypoint("Konzerthaus");
			testroute->addPoi("EinKaufzentrum","Konzerthaus");

			CPPUNIT_ASSERT_EQUAL(2,(int)testroute->getRoute().size());

			}


	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		suite->addTest(new CppUnit::TestCaller<CAddpoi>
				 ("Load Existing", &CAddpoi::testaddPoi_validpoi));

		suite->addTest(new CppUnit::TestCaller<CAddpoi>
				("Load Existing", &CAddpoi::testaddPoi_invalidpoi));

		suite->addTest(new CppUnit::TestCaller<CAddpoi>
				("Load Existing", &CAddpoi::testaddPoi_validpoiEmptyWP));

		suite->addTest(new CppUnit::TestCaller<CAddpoi>
				("Load Existing", &CAddpoi::testaddPoi_validpoiValidWP));
		return suite;
	}
};


#endif /* CLOADTESTS_H_ */
