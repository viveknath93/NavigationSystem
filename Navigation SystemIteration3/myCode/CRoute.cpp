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
#include <iostream>

//Own Include Files
#include "CRoute.h"
#include "CWaypoint.h"
#include <vector>

//Method Implementations
using namespace std;

/**
 * The constructor of CRoute,
 * which sets the initial values of database pointer to null
 * @param - none
 * */
CRoute::CRoute()
{
	// Make database to point to NULL
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;
}

/*
 * Copy constructor
 * @param Croute Refernce object for copying its content
 * */
CRoute::CRoute( CRoute const &obj)
{
	this->MyRoute = obj.MyRoute;
	this->m_pPoiDatabase = obj.m_pPoiDatabase;
	this->m_pWpDatabase = obj.m_pWpDatabase;
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
	cout<<"\nConnected this POI data base to user created database\n";
}

/**
 * the function connects the database manually generated in Navigation system
 * to CRoute instance of CWpDatabase
 * @param CWpDatabase* pWpDB pointer to the database (IN)
 * @returnvalue void
 */
void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	m_pWpDatabase = pWpDB;
	cout<<"\nConnected this Way point data base to user created database\n";
}

/*function adds a waypoint to route fetching the data from waypoint database
 * @param string name - name of waypoint
 * @returnvalue void
 * */
void CRoute::addWaypoint(string name)
{
	if(this->m_pWpDatabase != NULL)
	{
		if(m_pWpDatabase->getPointerToWaypoint(name)!= NULL){
				MyRoute.push_back(m_pWpDatabase->getPointerToWaypoint(name));
			}
		else{
			cout<<"CRoute::addWaypoint "<<name<<" not in Way point database";
		}
	}
	else
	{
		cout<<"CRoute::addWaypoint :  Empty waypoint database";
	}
}

/*funtion adds a POI to route fetching the data from POI database,
 * this funtion finds the afterWp in route and inserts the POI right next to the found element.
 * @param string name - name of POI
 * @param string afterWp - name of waypoint after which the POI needs to be added
 * @returnvalue void
 * */
void CRoute::addPoi(string name, string afterWp)
{
	std::list<CWaypoint*>::iterator it;
	std::list<CWaypoint*>::iterator it_pos;
	it_pos = this->MyRoute.end();
	if(m_pPoiDatabase != NULL)
	{
	if(m_pPoiDatabase->getPointerToPoi(name) != NULL)
	{
		if(afterWp == "")
		{
			//This is executed from+=operator
			cout<<"\nCRoute::addPoi : Invalid afterWp : adding to last element in route";
			MyRoute.push_back(m_pPoiDatabase->getPointerToPoi(name));
		}
		else
		{	//TODO we can check if afterWp is present first in CwpDb
			// itself before checking each and every "MyRoute"

			// Searched the Route, if it finds the waypoint , notes the iterator of that particular position
			for (it = MyRoute.begin(); it!=MyRoute.end(); ++it)
			{
				if(NULL == dynamic_cast<CPOI*>(*it) )
				{
					if((*it)->getName() == afterWp)
					{
						it_pos = it;
					}
				}
				else
				{
					// This implies the casting is successful and POI is present in location
				}
			}


			if(it_pos == this->MyRoute.end())
			{
				// If search for Waypoint is complete and waypoint not found, adding the PoI to end
				cout<<"\nCRoute::addPoi : "<<afterWp<<" waypoint not found : adding to POI to last element in route";
				MyRoute.push_back(m_pPoiDatabase->getPointerToPoi(name));

			}
			else
			{
				// If found, placing POI at position next to latest matching Waypoint
				++it_pos;
				MyRoute.insert(it_pos,m_pPoiDatabase->getPointerToPoi(name));
			}
		}
	}
	else
	{
		cout<<"\nERROR in "<<__FUNCTION__<<" :Invalid POI : " << name << " not in database\n";
	}
	}
	else
	{
		cout<<"\nERROR in "<<__FUNCTION__ << " POI database is empty\n";
	}
}

/*
 * Funtion prints all the points in the route by dynamic casting the Poi and waypoints
 * @param none
 * @return value None
 * */
void CRoute::print()
{
	std::list<CWaypoint*>::iterator it;
	if(MyRoute.size() !=0 )
	{
		for(it= MyRoute.begin();it!=MyRoute.end();++it)
			{
				if(NULL == dynamic_cast<CPOI*>(*it))
				{
					(*it)->print(2);
					cout<<endl;
				}
				else
				{
					dynamic_cast<CPOI*>(*it)->print(1);
					cout<<endl;
				}
			}
	}
	else
	{
		cout<<"You are trying to print a empty Route List!!"<<endl;
	}

}

/*
 * Overloaded + operator
 *
 * @param route reference object as right operand
 * @returnvalue CRoute reference object
 *  */
CRoute CRoute::operator + (CRoute &CRoute_obj)
{
	std::list<CWaypoint*>::iterator it;
	CRoute temp;

	if((this->m_pPoiDatabase == CRoute_obj.m_pPoiDatabase) && (this->m_pWpDatabase == CRoute_obj.m_pWpDatabase))
	{
		for(it = this->MyRoute.begin(); it!= this->MyRoute.end();++it)
		{
			temp.MyRoute.push_back(*it);
		}

		for(it = CRoute_obj.MyRoute.begin(); it!= CRoute_obj.MyRoute.end();++it)
		{
			temp.MyRoute.push_back(*it);
		}
	}
	else
	{
		cout<<"\nError : CRoute Operator+ : Concatenating 2 Routes failed\n";
	}
	return temp;
}

/*
 * Overloaded assignment operator
 * @param route reference object as right operand
 * @returnvalue CRoute reference object
 * */
CRoute& CRoute::operator = (CRoute &CRoute_obj)
{
	this->MyRoute = CRoute_obj.MyRoute;
	this->m_pPoiDatabase = CRoute_obj.m_pPoiDatabase;
	this->m_pWpDatabase = CRoute_obj.m_pWpDatabase;
	return *this;
}


/*
 * Compound assignment operator
 * @param take the name of POI or waypoint and adds it to the caller object route
 * @returnvalue CRoute reference object
 * */
void CRoute::operator +=(std::string name)
{
   	this->addWaypoint(name);
   	// empty nextWp - from+=operator
   	this->addPoi(name,"");
}

/*
 * getter funtion to get the route database
 * @param none
 * @returnvalue const vector of route */
const vector<const CWaypoint*> CRoute::getRoute()
{
	const vector<const CWaypoint*> myConst_vectPtr(MyRoute.begin(),MyRoute.end());
	return myConst_vectPtr;
}


/**
 * calculates the distance of current position to all points of interests
 * and calculates the minimum value
 * @params	CWaypoint const& wp	reference to current position	(IN)
 * @params	reference that points to nearest point of interest	(OUT)
 * @returnvalue	min_distance minimum distance
 * */
//double CRoute::getDistanceNextPoi(CWaypoint const& wp, CPOI& poi)
//{
//	//calc distance of all POI with current location
//	double *distace2Poi;
//	double min_distance;
//	unsigned int min_index;
//
//	distace2Poi = new double[m_nextPoi];
//	for (unsigned int i = 0; i < m_nextPoi; i++)
//	{
//		distace2Poi[i] = m_pPoi[i]->calculateDistance(wp);
//
//	}
//	min_distance = distace2Poi[0];// Initialising the minimum distance to first POI for reference
//	min_index = 0;
//	for (unsigned int i = 0; i < m_nextPoi; i++)// can start the loop with 1
//	{
//		if (min_distance >= distace2Poi[i])
//		{
//			min_distance = distace2Poi[i];
//			min_index = i;
//		}
//	}
//	poi = *m_pPoi[min_index];	// assigning the nearest Poi to return value
//
//	return min_distance;
//}
