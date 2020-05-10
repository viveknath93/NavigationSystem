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
	//string poi_name = poi.getName();
	// to the database, name of poi => poi reference is added as Key=> value pair
	if(this->m_CPOI.find(poi.getName()) == this->m_CPOI.end())
	{
		std::map<string,CPOI>::iterator it = this->m_CPOI.end();
		this->m_CPOI.insert(it,std::make_pair(poi.getName(),poi));
	}
	else
	{
		cout<<__FUNCTION__<<": Error : POI already existing, skipping to add\n";
	}
}

/**
 * function to add the Point of interest into route
 * @param string namePoi - The name of POi from database to be added to Route	(IN)
 * @returnvalue void
 **/

CPOI* CPoiDatabase::getPointerToPoi(string name){

	std::map<string,CPOI>::iterator it;
	it = m_CPOI.find(name);

	if(it != m_CPOI.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}
/*
 * function to print the all the pois in database
 * @param none
 * @returnvalue void
 * */
void CPoiDatabase::print()
{
	myPoiMap_t ::iterator it;
	for(it = m_CPOI.begin();it != m_CPOI.end(); ++it)
	{
		cout<<it->second;
	}
}


/*
 * Function to clear the Poi database
 * @param None
 * @returnvalue	void
 * */
void CPoiDatabase::clear_PoiDatabase()
{
	this->m_CPOI.clear();
}
/*
 * Function to get POI database
 * @param None
 * @returnvalue	the map variable containing the database
 * */
CPoiDatabase::myPoiMap_t CPoiDatabase::getPoiDatabase() const
{
	return m_CPOI;
}
