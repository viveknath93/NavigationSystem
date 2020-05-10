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
void CWpDatabase::addWaypoint(CWaypoint const& wp)
{
	std::map<string,CWaypoint>::iterator it;
	if(this->m_CWayPt.find(wp.getName()) == this->m_CWayPt.end())
	{
		it = this->m_CWayPt.end();
		this->m_CWayPt.insert(it, std::make_pair(wp.getName(),wp));
	}
	else
	{
		cout<<__FUNCTION__<<" : Error : Waypoint already existing, skipping to add \n";
	}
}
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	std::map<string,CWaypoint>::iterator it;
	it = m_CWayPt.find(name);

	if(it != m_CWayPt.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}
void CWpDatabase::print()
{
	std::map<string,CWaypoint> ::iterator it;
	for(it = m_CWayPt.begin();it != m_CWayPt.end(); ++it)
	{
		cout<<it->second;
	}
}

void CWpDatabase::clear_WayptDatabase()
{
	this->m_CWayPt.clear();
}

CWpDatabase::myWpMap_t CWpDatabase::getWpdatabase() const
{
	return m_CWayPt;
}
