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
#include <string>
#include <map>

class CWpDatabase {

public:

	typedef std::map<std::string,CWaypoint> myWpMap_t;
    CWpDatabase();

    void addWaypoint( CWaypoint const& wp);
    void clear_WayptDatabase();
    CWaypoint* getPointerToWaypoint(std::string name);

    void print();

    myWpMap_t getWpdatabase() const;

private:

    myWpMap_t m_CWayPt;
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
