/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          : Viveknath Thulasi
* Description     : Include file for CRoute class
*
*
****************************************************************************/


#ifndef CROUTE_H
#define CROUTE_H

//Own Include Files
#include "CPOI.h"
#include "CPoiDatabase.h"


class CRoute {
private:
    CWaypoint* m_pWaypoint;
    unsigned int m_maxWp;
    unsigned int m_nextWp;
    CPOI** m_pPoi;
    unsigned int m_maxPoi;
    unsigned int m_nextPoi;

    CPoiDatabase* m_pPoiDatabase;
public:

    CRoute(unsigned int maxWp =1 ,unsigned int maxPoi =1);

    CRoute(CRoute const & origin);

    void connectToPoiDatabase(CPoiDatabase* pPoiDB);

    void addWaypoint(CWaypoint const & wp);

    void addPoi(std::string namePoi);

    double getDistanceNextPoi(CWaypoint const& wp, CPOI& poi);

    void print();

    ~CRoute();
};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
