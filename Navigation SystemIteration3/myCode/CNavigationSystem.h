/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CCSV.h"
#include "CJsonPersistence.h"
#include "CNaviDatabase.h"
#include "CWaypoint.h"
#include "CPOI.h"

class CNavigationSystem {
private:

/*
* Function to print the route database
* @param none
* @returnvalue void
* */
    void printRoute();
/*
 * function to enter all waypoints and POI in class
 * @param	None
 * @returnvalue void
 * */
    void enterRoute();
    CGPSSensor m_GPSSensor;
    CRoute m_route;
    CPoiDatabase m_PoiDatabase;
    CWpDatabase m_WpDatabase;
    CCSV m_csv;
    CJsonPersistence m_json;

    // Typedef datatypes containing the int and waypoint or database
    // This cannot be written into JSON
    CintegerPoiDatabase m_TKeyIntPoiDatabase;
    CintegerWpDatabase m_TKeyIntWpDatabase;

/*
 * Function to print the distance from current position to nearest POI in the route
 * @param	none
 * @returnvalue	void
 *
 * */
    void TC_fillPOIDatabase();
    void TC_fillWpDB();
    void createDatabases();
    void writeToFile();
    void readFromFile();
    void fill_templateDB();

public:

    CNavigationSystem();
    void run();

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
