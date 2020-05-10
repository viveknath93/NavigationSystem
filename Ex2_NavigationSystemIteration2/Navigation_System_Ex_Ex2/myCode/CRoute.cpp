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
	if(m_pWpDatabase->getPointerToWaypoint(name)!= NULL){
		MyRoute.push_back(m_pWpDatabase->getPointerToWaypoint(name));
	}
	else{
		cout<<"CRoute::addWaypoint "<<name<<" not in Way point database";
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
	if(m_pPoiDatabase->getPointerToPoi(name) != NULL)
	{
		if(afterWp == "")
		{
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

/*
 * Funtion prints all the points in the route by dynamic casting the Poi and waypoints
 * @param none
 * @return value None
 * */
void CRoute::print()
{
	std::list<CWaypoint*>::iterator it;
	for(it= MyRoute.begin();it!=MyRoute.end();++it)
	{
		if(NULL == dynamic_cast<CPOI*>(*it))
		{
			(*it)->print(2);
		}
		else
		{
			dynamic_cast<CPOI*>(*it)->print(1);
			cout<<endl;
		}
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
   	this->addPoi(name,"");
}
