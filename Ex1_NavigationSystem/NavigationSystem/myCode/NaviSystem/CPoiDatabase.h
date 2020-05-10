/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.H
* Author          : Viveknath Thulasi
* Description     : Include file for CPOIDatabase
*
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

#include<CPOI.h>
class CPoiDatabase {
private:
    CPOI m_POI[10];
    int m_noPoi;
public:

    CPoiDatabase();

    void addPoi(t_poi type, std::string name, std::string description, double latitude, double longitude);

    CPOI* getPointerToPoi(std::string name);

};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
