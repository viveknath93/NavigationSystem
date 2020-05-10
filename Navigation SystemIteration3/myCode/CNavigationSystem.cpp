/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.CPP
* Author          : Viveknath Thulasi
* Description     : The class is the central class to interact with other classes and database
*
*
****************************************************************************/
//System Include Files
//Own Include Files
#include "CNavigationSystem.h"
#include "CPOI.h"//CPOI new variables declaration
#include "CRoute.h"
#include "CWaypoint.h"
#include "CCSV.h"
#include <vector>

#define TESTREADWRITE 1;
//Method Implementations

CNavigationSystem::CNavigationSystem()
{

}

void CNavigationSystem::fill_templateDB()
{

	CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
	CPOI poi_2(CPOI::RESTAURANT, "Italian", " Pizza ", 23.2356, 32.6778);
	CPOI poi_3(CPOI::GASSTATION, "Aral", "Fill up the tank ", 78.2356,32.6589);

	m_TKeyIntPoiDatabase.addLocation(1,poi_1);
	m_TKeyIntPoiDatabase.addLocation(2,poi_2);
	m_TKeyIntPoiDatabase.addLocation(3,poi_3);

	CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
	CWaypoint Location_2("Rathaus", 56.22435, 41.954);
	CWaypoint Location_3("Hauptbahnhof", 20.987, 13.345);

	m_TKeyIntWpDatabase.addLocation(4,Location_1);
	m_TKeyIntWpDatabase.addLocation(5,Location_2);
	m_TKeyIntWpDatabase.addLocation(6,Location_3);

	m_TKeyIntPoiDatabase.print_database();
	m_TKeyIntWpDatabase.print_database();

}

/*
 * Funciton to run the test case of Navigation system
 * @returnvalue void
 * */
void CNavigationSystem::run()
{

#if OLDCODE
	//1.2.2k
	cout<<"\nCheck for +=\n";
	CRoute m_route2;
	m_route2.connectToPoiDatabase(&m_PoiDatabase);
	m_route2.connectToWpDatabase(&m_WpDatabase);
	m_route2.addWaypoint("Konzerthaus");

	m_route2+=("Rathaus");
	m_route2+=("Aral");// Currently not in CRoute2
	m_route2.print();

	//1.2.2L
	cout<<"\nTC - Check + operator \n\n";
	CRoute m_route3 = m_route + m_route2;
	m_route3.print();

	//1.2.1.g
	cout<<"\nTC - Copy constructor \n";
	//until here , route2 contains only 2 WP and 1POI
	CRoute m_route4(m_route2);
	m_route4.print();

	//1.2.1.g
	cout<<"\nTC - check '=' operator \n";
	CRoute m_route5;
	m_route5 = m_route2;
	m_route5.print();

	m_csv.storage_merge_mode = CCSV::REPLACE;
	m_csv.setMediaName("MyNaviSystem");

	writeToFile();

	//Calling create database to check if MERGE is working
	createDatabases();
	//Modify and check with merge option
	readFromFile();
#endif

	TC_fillWpDB();
	TC_fillPOIDatabase();

	m_route.connectToPoiDatabase(&m_PoiDatabase);
	m_route.connectToWpDatabase(&m_WpDatabase);

//	enterRoute();
//	printRoute();

// 3.3 MEthod test
//	std::vector<CWaypoint*> Temp_route;
//	Temp_route = m_route.getRoute();

//3.1 Alternative persistence implementation
#ifdef TESTREADWRITE
	m_json.setMediaName("Given_sample.json");
	//m_json.readData(m_WpDatabase,m_PoiDatabase,m_csv.storage_merge_mode);
	m_json.readData(m_WpDatabase,m_PoiDatabase,CJsonPersistence::REPLACE);

	m_json.setMediaName("Given_sample_writing.json");
	m_json.writeData(m_WpDatabase,m_PoiDatabase);
#endif
//	fill_templateDB();
	//m_json.setMediaName("Database_Template.json");
	//m_json.writeData(m_TKeyIntWpDatabase.,m_TKeyIntPoiDatabase);

}


void CNavigationSystem::TC_fillPOIDatabase()
{
	//Adding a generic Set of values to database

	CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
	CPOI poi_2(CPOI::RESTAURANT, "Italian", " Pizza ", 23.2356, 32.6778);
	CPOI poi_3(CPOI::GASSTATION, "Aral", "Fill up the tank ", 78.2356,32.6589);
	CPOI poi_4(CPOI::UNIVERSITY, "H-da", "University in Darmstadt",	34.6589, 58.432);
	CPOI poi_5(CPOI::TOURISTIC, "Alps", "Skiing in winter", 09.2356,32.6589);
	CPOI poi_6(CPOI::UNIVERSITY, "Mensa", "Canteen inside University",12.32654, 9.658);
	CPOI poi_7(CPOI::TOURISTIC, "Eberstadt", "Place of living", 32.658,63.784);
	CPOI poi_8(CPOI::RESTAURANT, "LuisenPlatz", "center for Darmstadt",83.471, 23.6589);

	m_PoiDatabase.addPoi(poi_1);
	m_PoiDatabase.addPoi(poi_2);
	m_PoiDatabase.addPoi(poi_3);
//	m_PoiDatabase.addPoi(poi_4);
//	m_PoiDatabase.addPoi(poi_5);
//	m_PoiDatabase.addPoi(poi_6);
//	m_PoiDatabase.addPoi(poi_7);
//	m_PoiDatabase.addPoi(poi_8);

	m_PoiDatabase.print();
}

/*
 * Function to add the Waypoint and POI to route
 * @param none
 * @returnvalue void
 * */
void CNavigationSystem::enterRoute()
{
	//TCs 1.2.1a,b,c
	m_route.addWaypoint("Hauptbahnhof");
	m_route.addWaypoint("Rathaus");
	m_route.addWaypoint("Hauptbahnhof");

	m_route.addPoi("EinKaufzentrum","Rathaus");

	// To add POI in middle 1.2.1f
	m_route.addPoi("Eberstadt","Hauptbahnhof");

	// To check if a not existing Waypoint is present,POI is added to last
	//m_route.addPoi("EinKaufzentrum","DummyWaypoint");

	// To check if dummy string is passed as nextwp
	//m_route.addPoi("Eberstadt","");

	// Add 2 wapoint of same name , and then try adding the poi
	m_route.addWaypoint("Rathaus");
	m_route.addPoi("Eberstadt","Rathaus"); // Trying to add POI after second last matching Waypoint


}
void CNavigationSystem::printRoute()
{
	cout<<"\n\nRoute data Begins from here: \n";
	m_route.print();

	cout<<"\n\nRoute data ends here: \n";
}

void CNavigationSystem::TC_fillWpDB()
{
	CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
	CWaypoint Location_2("Rathaus", 56.22435, 41.954);
	CWaypoint Location_3("Hauptbahnhof", 20.987, 13.345);

	m_WpDatabase.addWaypoint(Location_1);
	m_WpDatabase.addWaypoint(Location_2);
	m_WpDatabase.addWaypoint(Location_3);

	m_WpDatabase.print();
}
/**
 * creation of database is done here
 * also Refer TC_fillPOIDatabase()
 * and TC_fillWpDB()
 * */
void CNavigationSystem::createDatabases()
{
	CPOI poi_1(CPOI::TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",45.2356, 32.6589);
	m_PoiDatabase.addPoi(poi_1);

	CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
	m_WpDatabase.addWaypoint(Location_1);
}
/*
 * funtion to test write operation
 * */
void CNavigationSystem::writeToFile()
{
	m_csv.writeData(m_WpDatabase,m_PoiDatabase);
}

/*
 * function to test the reading operation
 *  */
void CNavigationSystem::readFromFile()
{
	m_csv.readData(m_WpDatabase,m_PoiDatabase,m_csv.storage_merge_mode);
	cout<<"\nThe read Waypoints :\n\n";
	m_WpDatabase.print();
	cout<<"\nThe read POI database :\n\n";
	m_PoiDatabase.print();
}


