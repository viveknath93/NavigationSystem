/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          : Viveknath Thulasi
* Description     : Include file for CRoute class
*
*
****************************************************************************/
#ifndef CROUTE_H
#define CROUTE_H

//System Include Files
#include <iostream>
#include <list>
#include <string>

//Own Include Files
#include "CWaypoint.h" //For creating My route
#include "CPoiDatabase.h"//Declaring pointer object of addpoi and add waypoint
#include "CWpDatabase.h"

class CRoute {
private:
	std::list<CWaypoint*> MyRoute;
	CPoiDatabase* m_pPoiDatabase;
	CWpDatabase* m_pWpDatabase;


public:

/**
 * The constructor of CRoute,
 * which sets the initial values of database pointer to null
 * @param - none
 * */
    CRoute();
/*
 * Copy constructor
 * @param Croute Refernce object for copying its content
 * */
    CRoute(CRoute const &obj);


/*
 * Overloaded + operator
 *
 * @param route reference object as right operand
 * @returnvalue CRoute reference object
 *  */
    CRoute operator + (CRoute &CRoute_ref);

/*
 * Overloaded assignment operator
 * @param route reference object as right operand
 * @returnvalue CRoute reference object
 * */
    CRoute& operator = (CRoute &CRoute_ref);

/**
 * the function connects the database manually generated in Navigation system
 * to CRoute instance of CPoiDatabase
 * @param CPoiDatabase* pPoiDB pointer to the database (IN)
 * @returnvalue void
 */
    void connectToPoiDatabase(CPoiDatabase* pPoiDB);

/**
 * the function connects the database manually generated in Navigation system
 * to CRoute instance of CWpDatabase
 * @param CWpDatabase* pWpDB pointer to the database (IN)
 * @returnvalue void
 */
    void connectToWpDatabase(CWpDatabase* pWpDB);

/*function adds a waypoint to route fetching the data from waypoint database
 * @param string name - name of waypoint
 * @returnvalue void
 * */
    void addWaypoint(std::string name);

/*funtion adds a POI to route fetching the data from POI database,
 * this funtion finds the afterWp in route and inserts the POI right next to the found element.
 * @param string name - name of POI
 * @param string afterWp - name of waypoint after which the POI needs to be added
 * @returnvalue void
 * */
    void addPoi(std::string name, std::string afterWp);
/*
 * Funtion prints all the points in the route by dynamic casting the Poi and waypoints
 * @param none
 * @return value None
 * */
    void print();

/*
 * Compound assignment operator
 * @param take the name of POI or waypoint and adds it to the caller object route
 * @returnvalue CRoute reference object
 * */
    void operator += (std::string name);

};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
