/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.CPP
 * Author          : Viveknath Thulasi
 * Description     : Class containing the information about Point of Interest (POI)
 *
 *
 ****************************************************************************/

//System Include Files
#include <map>

//Own Include Files
#include "CPoiDatabase.h"
#include "CPOI.h"
//Method Implementations
using namespace std;
CPoiDatabase::CPoiDatabase()
{

}

/*
 * function to add the POIs to the generic database
 * @param	const CPOI& poi	(IN)
 * @returnvalue void */

void CPoiDatabase::addPoi(CPOI const& poi)
{
	addLocation(poi.getName(),poi);
}

/**
 * function to add the Point of interest into route
 * @param string namePoi - The name of POi from database to be added to Route	(IN)
 * @returnvalue void
 **/

CPOI* CPoiDatabase::getPointerToPoi(string name){

	CPOI *ret;
	ret = getPointerToLocation(name);
	return ret;
}

/*
 * function to print the all the pois in database
 * @param none
 * @returnvalue void
 * */
void CPoiDatabase::print()
{
	print_database();
}


/*
 * Function to clear the Poi database
 * @param None
 * @returnvalue	void
 * */
void CPoiDatabase::clear_PoiDatabase()
{
	clear_LocationDB();
//	this->m_CPOI.clear();
}
/*
 * Function to get POI database
 * @param None
 * @returnvalue	the map variable containing the database
 * */
std::map<string,CPOI> CPoiDatabase::getPoiDatabase() const
{
	std::map<string,CPOI> poidb;
	poidb = getdatabase();
	return poidb;

}
/*
 * Setter function to set the value of poi map
 * @param poi map from other sources
 * @returnvalue none
 * */
void CPoiDatabase::setpoidatabase(myPoiMap_t mypoimap)
{
	setdatabase(mypoimap);
//	this->m_Location.insert(mypoimap.begin(),mypoimap.end());
}
