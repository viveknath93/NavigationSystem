/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWPDATABASE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CWPDATABASE_H
#define CWPDATABASE_H


#include "CWaypoint.h"
#include "CNaviDatabase.h"

#include <string>
#include <map>

class CWpDatabase:public CNaviDatabase<string,CWaypoint>
{
public:

	typedef std::map<string,CWaypoint> myWpMap_t;
    CWpDatabase();


    /*
     * function to add the Waypoints to the waypoint database
     * @param	wp  reference of CWaypoint	(IN)
     * @returnvalue void */
    void addWaypoint( CWaypoint const& wp);

    /*
	 * function to clear the waypoint database
	 * @param	void
	 * @returnvalue void */
    void clear_WayptDatabase();

    /*
	 * function to get pointer to particular waypoint from waypoint database
	 * @param	name  input search string value 	(IN)
	 * @returnvalue Pointer to CWaypoint  */
    CWaypoint* getPointerToWaypoint(string name);

    /*
	 * function to print the contents of  waypoint database
	 * @returnvalue void  */
    void print();

    /*
	 * getter funtion for the waypoint database
	 * @returnvalue map of wp name and waypoint  */

    std::map<string,CWaypoint> getWpdatabase() const;
    /*
     * Setter function to set the value of map
     * @param waypoint map from other sourves
     * @returnvalue none
     * */
    void setwpdatabase(myWpMap_t mywpmap);

private:

    //myWpMap_t m_CWayPt;
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
