/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CROUTE.CPP
 * Author          : Viveknath Thulasi
 * Description     : Operations with creating Route containing Waypoints and POIs and interface with database
 *
 *
 ****************************************************************************/

//System Include Files
using namespace std;
#include <iostream>

//Own Include Files
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CWaypoint.h"
#include "CPOI.h" // For printing Type values

//Method Implementations
/**
 * The constructor of CRoute,
 * which sets the initial values and allocates memory
 * @param unsigned int maxWp	- The max no of waypoints in route, default 1 (IN)
 * @param unsigned int maxPoi	- The max no if Point of interest in route, default 1 (IN)
 * */
CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi)
{

	m_maxPoi = maxPoi;
	m_maxWp = maxWp;
	m_nextPoi = 0;
	m_nextWp = 0;
	m_pWaypoint = new CWaypoint[m_maxWp];
	m_pPoi = new CPOI*[m_maxPoi];
	m_pPoiDatabase = NULL;

}

/*
 * The copy constructor of CRoute
 * @param	CRoute const & origin input original
 *  */
CRoute::CRoute(CRoute const & origin)
{
	//Copy constructor needs to be implemeneted
	// Deep copy not shallow copy
	this->m_maxPoi = origin.m_maxPoi;
	this->m_maxWp = origin.m_maxWp;
	this->m_nextPoi = origin.m_nextPoi;
	this->m_nextWp = origin.m_nextWp;

	this->m_pWaypoint = new CWaypoint[m_maxWp];
	this->m_pPoi = new CPOI*[m_maxPoi];

	this->m_pPoiDatabase = NULL;

	for (unsigned int i = 0; i < m_maxWp; i++)
	{
		this->m_pWaypoint[i] = origin.m_pWaypoint[i];
	}
	for (unsigned int i = 0; i < m_maxPoi; i++)
	{
		this->m_pPoi[i] = origin.m_pPoi[i];
	}

}

/**
 * the function connects the database manually generated in Navigation system
 * to CRoute instance of CPoiDatabase
 * @param CPoiDatabase* pPoiDB pointer to the database (IN)
 * @returnvalue void
 */
void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	m_pPoiDatabase = pPoiDB;
}

/**
 * function to add a waypoint to the route
 * @param CWaypoint const & wp	- The reference through which waypoints are added to route (IN)
 * @returnvalue void
 * */
void CRoute::addWaypoint(CWaypoint const & wp)
{
if(m_nextWp <m_maxWp)
{
	m_pWaypoint[m_nextWp] = wp;//m_nextWp index starts from 0
	m_nextWp += 1;
}
else
{
	cout<<"\nWARNING in "<<__FUNCTION__<<" : Inputs exceeding max no of waypoints : "<<m_maxWp;
}

}

/**
 * function to add the Point of interest into route
 * @param string namePoi - The name of POi from database to be added to Route	(IN)
 * @returnvalue void
 **/
void CRoute::addPoi(string namePoi)
{
	CPOI* ptr2POI = m_pPoiDatabase->getPointerToPoi(namePoi);

	if (ptr2POI == NULL)
	{
		cout<<"\nERROR in "<<__FUNCTION__<<" :Invalid POI : " << namePoi << " not in database\n";
	}
	else
	{
		if(m_nextPoi <m_maxPoi)
		{
		m_pPoi[m_nextPoi] = ptr2POI;	//m_nextPoi starts from 0th index
		m_nextPoi++;
		}
		else
		{
			cout<<"\nWARNING in "<<__FUNCTION__<<" : Inputs exceeding max no of POI : "<<m_maxPoi;
		}
	}

}
/**
 * calculates the distance of current position to all points of interests
 * and calculates the minimum value
 * @params	CWaypoint const& wp	reference to current position	(IN)
 * @params	reference that points to nearest point of interest	(OUT)
 * @returnvalue	min_distance minimum distance
 * */
double CRoute::getDistanceNextPoi(CWaypoint const& wp, CPOI& poi)
{
	//calc distance of all POI with current location
	double *distace2Poi;
	double min_distance;
	unsigned int min_index;

	distace2Poi = new double[m_nextPoi];
	for (unsigned int i = 0; i < m_nextPoi; i++)
	{
		distace2Poi[i] = m_pPoi[i]->calculateDistance(wp);

	}
	min_distance = distace2Poi[0];// Initialising the minimum distance to first POI for reference
	min_index = 0;
	for (unsigned int i = 0; i < m_nextPoi; i++)
	{
		if (min_distance >= distace2Poi[i])
		{
			min_distance = distace2Poi[i];
			min_index = i;
		}
	}
	poi = *m_pPoi[min_index];	// assigning the nearest Poi to return value

	return min_distance;
}

/**
 * function to print the waypoints and POI in a route
 * @returnvalue void*/
void CRoute::print()
{
	string name;
	double latitude, longitude;
	t_poi type;
	string description;

	cout << "\n\nRoute has " << m_nextWp << " Waypoints and " << m_nextPoi
			<< " POIs \n\nWayPoints : \n";

	for (unsigned int i = 0; i < m_nextWp; i++)
	{
		m_pWaypoint[i].getAllDataByReference(name, latitude, longitude);
		cout << name << " " << latitude << " " << longitude << endl;
	}
	cout << "\n\nPOI : \n";
	for (unsigned int i = 0; i < m_nextPoi; i++)
	{
		m_pPoi[i]->getAllDataByReference(name, latitude, longitude, type,
				description);
		cout << name << " " << latitude << " " << longitude;
		print_type(type);
		cout << description << endl;

	}
}
/*
 * Destructor of CRoute*/
CRoute::~CRoute()
{
	delete[] m_pWaypoint;
	delete[] m_pPoi;
}
