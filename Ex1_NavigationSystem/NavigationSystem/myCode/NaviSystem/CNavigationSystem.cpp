/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CNAVIGATIONSYSTEM.CPP
 * Author          : Viveknath Thulasi
 * Description     : Main driving file for co-ordinating from classes
 *
 *
 ****************************************************************************/
//System Include Files
#include <iostream>

//Own Include Files
#include "CPOI.h"//CPOI new variables declaration
#include "CWaypoint.h"
#include "CNavigationSystem.h"


#define MAX_WAYPOINT	3
#define MAX_POI			3

using namespace std;
//Method Implementations

CNavigationSystem::CNavigationSystem() : m_route(MAX_WAYPOINT, MAX_POI)
{

}

/*
 * Funciton to run the test case of Navigation system
 * @returnvalue void
 * */
void CNavigationSystem::run()
{
	TC_addPOIDatabase();

	m_route.connectToPoiDatabase(&m_pPoiDatabase);

	TC_createRoute();

	printRoute();

	printDistanceCurPos();
}
/*
 * Function to add the Waypoint and POI to route
 * @param none
 * @returnvalue void
 * */
void CNavigationSystem::enterRoute()
{
	// Directly add Waypoints to the Route
	CWaypoint Location_1("Konzerthaus", 19.09090, 26.658);
	CWaypoint Location_2("Rathaus", 56.22435, 41.954);
	CWaypoint Location_3("Hauptbahnhof", 20.987, 13.345);

	m_route.addWaypoint(Location_1); //wp1 added
	m_route.addWaypoint(Location_2); //wp2 added
	m_route.addWaypoint(Location_3); //wp3 added

	m_route.addPoi("Mensa");
	m_route.addPoi("Eberstadt");
	m_route.addPoi("LuisenPlatz");

}

/*
 * function to print all waypoints and POI in class
 * @param	None
 * @returnvalue void
 * */
void CNavigationSystem::printRoute()
{

	//Just call the print() function in CRoute Class
	// Print all POIs that are added to current route

	m_route.print();
	// All the members are declared private, hence these can be accessed from the corresponding class's member functions

}
/*
 * Function to print the distance from current position to nearest POI in the route
 * @param	none
 * @returnvalue	void
 *
 * */
void CNavigationSystem::printDistanceCurPos()
{
	double distance_to_nearest_POI;
	CPOI nearest_POI;
	CWaypoint current_pos = m_GPSSensor.getCurrentPosition();

	if (variable_limit_flag == LATTITUDE_LONGITUDE_NOT_IN_LIMIT)
	{
		cout<<"\n\n ERROR in "<<__FUNCTION__<<": Distance to next POI : Not calculated as Latitude Longitude are not in limits"	<< endl;
	}
	else
	{
		distance_to_nearest_POI = m_route.getDistanceNextPoi(current_pos,nearest_POI);
		cout << "\n\nDistance to next POI : " << distance_to_nearest_POI<< endl;
		nearest_POI.print();
	}

}

void CNavigationSystem::TC_addPOIDatabase()
{
	//Adding a generic Set of values to database
		m_pPoiDatabase.addPoi(TOURISTIC, "EinKaufzentrum", "es gibt Viel angebot",
				45.2356, 32.6589);
		m_pPoiDatabase.addPoi(RESTAURANT, "Italian", " Pizza ", 23.2356, 32.6778);
		m_pPoiDatabase.addPoi(GASSTATION, "Aral", "Fill up the tank ", 78.2356,
				32.6589);
		m_pPoiDatabase.addPoi(UNIVERSITY, "H-da", "University in Darmstadt",
				34.6589, 58.432);
		m_pPoiDatabase.addPoi(TOURISTIC, "Alps", "Skiing in winter", 09.2356,
				32.6589);

		m_pPoiDatabase.addPoi(UNIVERSITY, "Mensa", "Canteen inside University",
				12.32654, 9.658);
		m_pPoiDatabase.addPoi(TOURISTIC, "Eberstadt", "Place of living", 32.658,
				63.784);
		m_pPoiDatabase.addPoi(RESTAURANT, "LuisenPlatz", "center for Darmstadt",
				83.471, 23.6589);

		m_pPoiDatabase.addPoi(UNIVERSITY, "Mensa", "Canteen inside University",
						12.32654, 9.658);
		m_pPoiDatabase.addPoi(TOURISTIC, "Eberstadt", "Place of living", 32.658,
						63.784);
		// Adding 11th element to check the error condition
		m_pPoiDatabase.addPoi(TOURISTIC, "Eberstadt", "Place of living", 32.658,
								63.784);

}

void CNavigationSystem::TC_createRoute()
{
	// Add POI and waypoint
		enterRoute();

	// Add an invalid POI not present in database
		m_route.addPoi("POI_DUMMY");

	// Test for copy constructor
		CRoute m_test_copy_constructuor  = m_route;
		m_test_copy_constructuor.print();
}
