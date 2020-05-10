/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWPDATABASE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/
//System Include Files


//Own Include Files
#include "CWpDatabase.h"
#include "CWaypoint.h"

using namespace std;
//Method Implementations

CWpDatabase::CWpDatabase()
{

}

/*
* function to add the Waypoints to the waypoint database
* @param	wp  reference of CWaypoint	(IN)
* @returnvalue void */
void CWpDatabase::addWaypoint(CWaypoint const& wp)
{
	addLocation(wp.getName(),wp);
}


/*
 * function to get pointer to particular waypoint from waypoint database
 * @param	name  input search string value 	(IN)
 * @returnvalue Pointer to CWaypoint  */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint *ret;
	ret = getPointerToLocation(name);
	return ret;
}

/*
 * function to print the contents of  waypoint database
 * @returnvalue void  */
void CWpDatabase::print()
{
	print_database();
}


/*
 * function to clear the waypoint database
 * @param	void
 * @returnvalue void */
void CWpDatabase::clear_WayptDatabase()
{
	clear_LocationDB();
}


/*
 * getter funtion for the waypoint database
 * @returnvalue map of wp name and waypoint  */
std::map<string,CWaypoint> CWpDatabase::getWpdatabase() const
{
	std::map<string,CWaypoint> wpdb;
	wpdb = getdatabase();
	return wpdb;
}


/*
 * Setter function to set the value of map
 * @param waypoint map from other sourves
 * @returnvalue none
 * */
void CWpDatabase::setwpdatabase(myWpMap_t mywpmap)
{
	setdatabase(mywpmap);
	//this->m_Location.insert(mywpmap.begin(),mywpmap.end());
}
